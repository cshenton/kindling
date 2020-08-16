const gl = @import("webgl.zig");
const wasm = @import("wasm.zig");

const vert_src = @embedFile("shader.vert");
const frag_src = @embedFile("shader.frag");

var program: c_uint = undefined;
var vao: c_uint = undefined;
var vbo: c_uint = undefined;

export fn onInit() void {
    // Set Viewport
    const width = wasm.getCanvasWidth();
    const height = wasm.getCanvasHeight();
    gl.viewport(0, 0, width, height);

    // Create Shader Program
    const vert_shader = gl.createShader(gl.VERTEX_SHADER);
    gl.shaderSource(vert_shader, vert_src, vert_src.len);
    gl.compileShader(vert_shader);

    const frag_shader = gl.createShader(gl.FRAGMENT_SHADER);
    gl.shaderSource(frag_shader, frag_src, frag_src.len);
    gl.compileShader(frag_shader);

    program = gl.createProgram();
    gl.attachShader(program, vert_shader);
    gl.attachShader(program, frag_shader);
    gl.linkProgram(program);

    // Vertex data
    const vertices = [_]f32{
        -1.0, -1.0, 1.0, 0.0, 0.0,
        1.0, 1.0, 0.0, 1.0, 0.0,
        1.0, -1.0, 0.0, 0.0, 1.0,
        -1.0, -1.0, 1.0, 0.0, 0.0,
        1.0, 1.0, 0.0, 1.0, 0.0,
        -1.0, 1.0, 1.0, 1.0, 1.0,
    };

    // Create vertex buffer with fullscreen quad
    vao = gl.createVertexArray();
    vbo = gl.createBuffer();
    gl.bindVertexArray(vao);
    gl.bindBuffer(gl.ARRAY_BUFFER, vbo);

    gl.bufferData(gl.ARRAY_BUFFER, @sizeOf(f32) * vertices.len, @ptrCast([*]const u8, &vertices[0]), gl.STATIC_DRAW);

    gl.vertexAttribPointer(0, 2, gl.FLOAT, gl.FALSE, 5 * @sizeOf(f32), null);
    gl.enableVertexAttribArray(0);
    gl.vertexAttribPointer(1, 3, gl.FLOAT, gl.FALSE, 5 * @sizeOf(f32), @intToPtr(*c_uint, 2*@sizeOf(f32)));
    gl.enableVertexAttribArray(1);
}

export fn onAnimationFrame(now_time: c_int) void {
    //glClearColor(@sin(@intToFloat(f32, now_time) / 1000.0), 0.4, 0.4, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    gl.bindVertexArray(vao);
    gl.useProgram(program);
    gl.drawArrays(gl.TRIANGLES, 0, 6);
}

export fn onResize(width: c_int, height: c_int) void {
    gl.viewport(0, 0, width, height);
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
