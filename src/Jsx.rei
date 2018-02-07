type success = { code: string };
type location = { line: int, column: int }
and  error = { message: string, from: location, until: location };

let rewrite : string => Js.Result.t(success, [> `JsxRewriteError(error)]);