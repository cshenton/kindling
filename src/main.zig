const Game = @import("game.zig").Game;

var game: Game = undefined;

export fn onInit() void {
    game = Game.init() catch |err| return; // Probably console log here or something
}

export fn onAnimationFrame(now_time: c_int) void {
    game.frame(now_time);
}

export fn onResize(width: c_int, height: c_int) void {
    game.resize(width, height);
}

export fn onDestroy() void {
    // Clean up gl objects
}

export fn onKeyDown(keyCode: c_int) void {
    // We probably need some c defs for the key names
}

export fn onKeyUp(keyCode: c_int) void {
    // Need some keys
}

export fn onMouseDown(button: c_int, x: c_int, y: c_int) void {
    // Need left / right defs
}

export fn onMouseUp(button: c_int, x: c_int, y: c_int) void {
    // Need left / right defs
}

export fn onMouseMove(x: c_int, y: c_int) void {
    // What's the coordinate system on the web?
}
