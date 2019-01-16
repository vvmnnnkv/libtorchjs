const expect = require('chai').expect;

describe('binding', function() {

    it('module should load', function() {
        const torch = require('../lib/binding');
        expect(torch).not.empty;
        console.log(torch);
    });

});