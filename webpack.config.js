module.exports = {
  entry: './examples/example.bs.js',
  output: {
    filename: 'examples/browserBundle.js'
  },
  node: {
    "fs": "empty",
    "child_process": "empty"
  }
};