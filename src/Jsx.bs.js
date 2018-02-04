// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");


  // Load compiler
  require('../vendor/jsoo_reactjs_jsx_ppx_v2.js');
  // Attach to local variable, so we can still access it if the global is overwritten
  var jsx = global && global.jsxv2 || window.jsxv2;

;

function toResult(jsObj) {
  var match = jsObj.type;
  if (match == null) {
    return /* Ok */Block.__(0, [/* record */[/* code */jsObj.ocaml_code]]);
  } else if (match === "error") {
    return /* Error */Block.__(1, [/* record */[
                /* message */jsObj.text,
                /* from : record */[
                  /* line */jsObj.row,
                  /* column */jsObj.column
                ],
                /* until : record */[
                  /* line */jsObj.endRow,
                  /* column */jsObj.endColumn
                ]
              ]]);
  } else {
    return /* Ok */Block.__(0, [/* record */[/* code */jsObj.ocaml_code]]);
  }
}

var InternalResult = /* module */[/* toResult */toResult];


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

;

function rewrite(code) {
  var match = _captureConsoleOutput((function () {
          return jsx.rewrite(code);
        }));
  return toResult(JSON.parse(match[0]));
}

exports.InternalResult = InternalResult;
exports.rewrite        = rewrite;
/*  Not a pure module */
