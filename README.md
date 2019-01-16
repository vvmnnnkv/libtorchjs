# LibtorchJS

Simple [Node.js N-API module](https://nodejs.org/api/n-api.html) that wraps few pieces of pytorch C++ library ([libtorch](https://pytorch.org/cppdocs/)) to allow loading and running pytorch-trained models in Node.js.

Node.js [non-blocking model](https://nodejs.org/en/docs/guides/dont-block-the-event-loop/) is great for scheduling heavy computational tasks such as NN inference.
This wrapper provides async methods that do not block event loop, so it's possible to use it in a web-service.

This module was made just for fun, to check if it's easily possible to create [image style transfer app with Node.js](https://github.com/vvmnnnkv/nodejs-style-transfer).

## Installation

With npm: `npm i --save libtorchjs`

Module binary is pre-built and published using `node-pre-gyp` so it's not required to download libtorch/pytorch 
or install build tools.

Currently, Linux & Windows builds are available.

## Usage Example

```javascript
const torch = require('libtorchjs');

const input = torch.randn([1, 3, 224, 224]);
torch.load('model.pt', function(err, model) {
    model.forward(input, function(err, result) {
        const output = result.toUint8Array();
        console.log(output);
    });
});
```

## API
The overall goal is to mirror pytorch API where possible. Currently just a few methods are exposed.

#### Tensor
##### ones(Array shape)
Create tensor of specified shape filled with 1's (autograd is disabled) and return Tensor object.

##### randn(Array shape)
Create tensor of specified shape (autograd is disabled) filled with random values in (0..1) range.

#### ScriptModule
##### load(String filename, callback)
Load traced model async from file and return resulting ScripModule. 

##### forward(Tensor tensor, callback)
Forward tensor async and return resulting Tensor.

## Acknowledgments
Following resources were extremely useful for creating this module:
 * Inspiration: https://www.udacity.com/facebook-pytorch-scholarship
 * Libtorch tutorial: https://pytorch.org/tutorials/advanced/cpp_export.html
 * Blog post about similar thing: http://blog.christianperone.com/2018/10/pytorch-1-0-tracing-jit-and-libtorch-c-api-to-integrate-pytorch-into-nodejs
 * N-API examples: https://github.com/nodejs/node-addon-examples
 * Pre-built module distribution: https://github.com/mapbox/node-pre-gyp

## Possible Future
 * Expose more of libtorch
 * Promisify libtorchjs API
 * GPU support
 * ~~Windows~~ :heavy_check_mark:, Mac support
 * Use travis/appveyor for automatic builds
