
let code = {|
  let _ =
    ((div ~children:[
      ((span ~children:[ReasonReact.stringToElement "hello"] ()) [@JSX])
    ] ()) [@JSX])
|};

let () =
  code |> Jsx.rewrite
       |> fun | Ok({ code })  => Js.log(code)
              | Error(_)      => Js.log("error");