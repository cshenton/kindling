var memory;

const getCanvasWidth = () => $canvas.width;
const getCanvasHeight = () => $canvas.height;
const getRandomSeed = () => Math.floor(Math.random() * 2147483647);
const getRandomString = () => Math.random().toString(36).substring(5, 15) + Math.random().toString(36).substring(5, 15);
const readCharStr = (ptr, len) => {
    const bytes = new Uint8Array(memory.buffer, ptr, len);
    let s = "";
    for (let i = 0; i < len; ++i) {
        s += String.fromCharCode(bytes[i]);
    }
    return s;
}
const consoleLogS = (ptr, len) => console.log(readCharStr(ptr, len));
const consoleLog = (value) => console.log(value);

var wasm = {
    consoleLog,
    getCanvasHeight,
    getCanvasWidth,
    getRandomSeed,
    getRandomString,
    consoleLogF: consoleLog,
    consoleLogI: consoleLog,
    consoleLogS,
    readCharStr,
}
