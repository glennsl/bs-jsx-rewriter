
let code = {|
  let x =
    match 42 with 
    | .1 -> 4
    | _ -> 2
|};

let () =
  code |> Jsx.rewrite
       |> fun | Ok(_) =>
                failwith("unreachable")

              | Error(`JsxRewriteError({ Jsx.message, from: { line, column } })) =>
                Js.log({j|Error: $message\nLine $line, column $column|j});
