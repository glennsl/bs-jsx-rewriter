[%%raw {|
  // Load compiler
  require('../vendor/jsoo_reactjs_jsx_ppx_v2.js');
  // Attach to local variable, so we can still access it if the global is overwritten
  var jsx = global && global.jsxv2 || window.jsxv2;
|}];

type location = {
  line: int,
  column: int
};

type success = {
  code: string
};

type error = {
  message: string,
  from: location,
  until: location
};

type result = Js.Result.t(success, error);

module InternalResult : {
  type t;
  external unsafeFromJson   : Js.Json.t => t = "%identity";
  let toResult : t => result;
} = {
  type t = {.
    "_type":           Js.nullable(string)
  };

  type internalSuccess = {.
    "ocaml_code":     string
  };

  type internalError = {.
    "ppx_error_msg":  string,
    "row":            int,
    "column":         int,
    "endRow":         int,
    "endColumn":      int,
    "text":           string
  };

  external unsafeFromJson   : Js.Json.t => t = "%identity";
  external unsafeAsSuccess  : t => internalSuccess = "%identity";
  external unsafeAsError    : t => internalError = "%identity";

  let toResult = jsObj =>
    switch (Js.Nullable.to_opt(jsObj##_type)) {
    | Some("error") => {
        let error = jsObj |> unsafeAsError;
        Js.Result.Error({
          message: error##text,
          from: { line: error##row, column: error##column },
          until: { line: error##endRow, column: error##endColumn }
        })
      }
    | _ => Js.Result.Ok({ code: (jsObj |> unsafeAsSuccess)##ocaml_code })
    };
};

[%%raw {|
  function _captureConsoleOutput(f) {
    const capture = (...args) => args.forEach(argument => errors += argument + `\n`);
    let errors = "";
    let res;
    if ((typeof process !== "undefined") && process.stdout && process.stdout.write) {
      const _stdoutWrite = process.stdout.write; // errors are written to stdout
      const _stderrWrite = process.stderr.write; // warnings are written to stderr ...
      process.stdout.write = capture;
      process.stderr.write = capture;
      res = f();
      process.stdout.write = _stdoutWrite;
      process.stderr.write = _stderrWrite;
    } else {
      const _consoleLog = console.log;     // errors are written to console.log
      const _consoleError = console.error; // warnings are written to console.error (at least it's consistently incnsistent)
      console.log = capture;
      console.error = capture;
      res = f();
      console.log = _consoleLog;
      console.error = _consoleError;
    }
    return [res, errors ? [errors] : 0];
  }
|}];
[@bs.val] external _captureConsoleOutput : (unit => 'a) => ('a, option(string)) = "";

[@bs.val] [@bs.scope "jsx"] external rewrite : string => string = "";
let rewrite = code => {
  let (json, consoleOutput) = 
    _captureConsoleOutput(() =>
      code |> rewrite
    );

  json |> Js.Json.parseExn
       |> InternalResult.unsafeFromJson
       |> InternalResult.toResult;
};