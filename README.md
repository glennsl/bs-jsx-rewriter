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

## Usage

### Bundling

The package has been tested to work with `webpack`, but requires a tiny bit of configuration because it depends on a few
ndoe modules in code paths that aren't actually used in practice. To stub these out, just put the following in your
`webpack.config.js`:

```javascript
  node: {
    fs: 'empty',
    child_process: 'empty'
  }
```

##Licensing

The vendor directory contains files built from code in the BuckleScript repository, but which originates from the Reason repository, which is licensed under the MIT license. The rest of this repostiory is also licensed under the MIT license.

## Acknowledgement

[The Reason team](https://github.com/facebook/reason/graphs/contributors) for creating the PPX (and, you know, Reason and all that), and [Alessandro Strada](https://github.com/astrada) for adding the JS API and build process.