type location = { line: int, column: int }
and  success = { code: string }
and  error = { message: string, from: location, until: location }
and  result = Js.Result.t(success, error);

let rewrite : string => result;