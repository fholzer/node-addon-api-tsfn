const { Consumer } = require("../lib/binding.js");

const forceGC = function() {
    if (global.gc) {
        global.gc();
    } else {
        console.warn('No GC hook! Start your program as `node --expose-gc file.js`.');
    }
};

function testSimple() {
    try{
        forceGC();
        var c = new Consumer(null, null, function() {
            forceGC();
            console.log("js callback called");
        });
        forceGC();
        c.close();
        forceGC();
    } catch(ex) {
        console.log(ex);
        throw ex;
    }
}

forceGC();
testSimple();
forceGC();
