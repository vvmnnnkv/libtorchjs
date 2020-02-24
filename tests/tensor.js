const expect = require('chai').expect;
const torch = require('../lib/');
const path = require('path');

describe('LibtorchJS', function() {

    it('ones', function() {
        const ones = torch.ones([2, 2]);
        expect([...ones.toUint8Array()]).to.deep.equal([1, 1, 1, 1]);
    });

    it('tensor', function() {
        const arr = new Float32Array([1, 2, 3.3, 4]);
        const tensor = torch.tensor(arr);
        expect([...tensor.toUint8Array()]).to.deep.equal([1, 2, 3, 4]);
    });

    it('load', function(done) {
        const input = torch.tensor(new Float32Array([2.5, 3.5]));
        torch.load(path.join(__dirname, 'data', 'mul2.pt'), function(err, model) {
          model.forward(input, function(err, result) {
            const output = result.toUint8Array();
            expect([...output]).to.deep.equal([5, 7]);
            done();
          });
        });
    });

});
