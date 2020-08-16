pub extern fn getCanvasWidth() c_int;
pub extern fn getCanvasHeight() c_int;
pub extern fn consoleLogFloat(_: f32) void;
pub extern fn consoleLogInt(_: c_int) void;
pub extern fn consoleLogUint(_: c_uint) void;
pub extern fn consoleLogString(_: [*]const u8, _: c_uint) void;
