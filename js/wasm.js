// Helper Functions
const readCharStr = (ptr, len) => {
    const bytes = new Uint8Array(memory.buffer, ptr, len);
    let s = "";
    for (let i = 0; i < len; ++i) {
        s += String.fromCharCode(bytes[i]);
    }
    return s;
}

// Global Variables
var memory;

// Core Platform Functions
const getCanvasWidth = () => $canvas.width;
const getCanvasHeight = () => $canvas.height;
const consoleLog = (value) => console.log(value);
const consoleLogString = (ptr, len) => console.log(readCharStr(ptr, len));

var wasm = {
    getCanvasHeight,
    getCanvasWidth,
    consoleLogFloat: consoleLog,
    consoleLogInt: consoleLog,
    consoleLogUint: consoleLog,
    consoleLogString,
    readCharStr,
}
