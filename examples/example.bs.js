// Generated by BUCKLESCRIPT VERSION 2.1.0, PLEASE EDIT WITH CARE
'use strict';

var Jsx = require("../src/Jsx.bs.js");

var code = "\n  let _ =\n    ((div ~children:[\n      ((span ~children:[ReasonReact.stringToElement \"hello\"] ()) [@JSX])\n    ] ()) [@JSX])\n";

var param = Jsx.rewrite(code);

if (param.tag) {
  console.log("error");
} else {
  console.log(param[0][/* code */0]);
}

exports.code = code;
/* param Not a pure module */
