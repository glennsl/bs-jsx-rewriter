# bs-react-jsx

BuckleScript bindings to Reason's JSX PPX rewriter.

## Installation

Run `npm install --save glennsl/bs-jsx-rewriter` and add `bs-jsx-rewriter` to the `bs-dependencies` in `bsconfig.json`. 

## Example

```reason
let code = {|
  let _ =
    ((div ~children:[
      ((span ~children:[ReasonReact.stringToElement "hello"] ()) [@JSX])
    ] ()) [@JSX])
|};

let () =
  code |> Jsx.rewrite
       |> fun | Ok({ code }) => Js.log(code)
              | Error(_) => Js.log("error");

/* Output:

let _ =
  ReactDOMRe.createElement "div"
    [|(ReactDOMRe.createElement "span"
         [|(ReasonReact.stringToElement "hello")|])|]
*/
```

## Acknowledgement

[The Reason team](https://github.com/facebook/reason/graphs/contributors) for creating the PPX (and, you know, Reason and all that), and [Alessandro Strada](https://github.com/astrada) for adding the JS API and build process.