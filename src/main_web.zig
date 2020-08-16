usingnamespace @import("webgl.zig");
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
    glViewport(0, 0, width, height);

    // Create Shader Program
    const vert_shader = glInitShader(vert_src, vert_src.len, GL_VERTEX_SHADER);
    const frag_shader = glInitShader(frag_src, frag_src.len, GL_FRAGMENT_SHADER);
    program = glLinkShaderProgram(vert_shader, frag_shader);

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
    vao = glCreateVertexArray();
    vbo = glCreateBuffer();
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, @sizeOf(f32) * vertices.len, &vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * @sizeOf(f32), null);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * @sizeOf(f32), @intToPtr(*c_uint, 2*@sizeOf(f32)));
    glEnableVertexAttribArray(1);
}

export fn onAnimationFrame(now_time: c_int) void {
    //glClearColor(@sin(@intToFloat(f32, now_time) / 1000.0), 0.4, 0.4, 1.0);
    //glClear(GL_COLOR_BUFFER_BIT);

    glBindVertexArray(vao);
    glUseProgram(program);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

export fn onResize(width: c_int, height: c_int) void {
    glViewport(0, 0, width, height);
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
    wasm.consoleLogS("Mouse Clicked", 13);
}

export fn onMouseUp(button: c_int, x: c_int, y: c_int) void {
    // Need left / right defs
}

export fn onMouseMove(x: c_int, y: c_int) void {
    // What's the coordinate system on the web?
}
