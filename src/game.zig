const std = @import("std");
const allocator = std.heap.page_allocator;
const json = std.json;

const Gltf = @import("gltf.zig").Gltf;

const gl = @import("webgl.zig");
const wasm = @import("wasm.zig");

const vert_src = @embedFile("shaders/color.vert");
const frag_src = @embedFile("shaders/color.frag");

const gltf_json = @embedFile("assets/buster_drone/scene.gltf");
const gltf_bin = @embedFile("assets/buster_drone/scene.bin");


pub const Game = struct {
    program: c_uint,
    vao: c_uint,
    vbo: c_uint,
    time_location: c_uint,

    gltf: Gltf,

    pub fn init() !Game {
        // Set Viewport
        const width = wasm.getCanvasWidth();
        const height = wasm.getCanvasHeight();
        gl.viewport(0, 0, width, height);

        // Create a bunch of buffer views

        // Create Shader Program
        const vert_shader = gl.createShader(gl.VERTEX_SHADER);
        gl.shaderSource(vert_shader, vert_src, vert_src.len);
        gl.compileShader(vert_shader);

        const frag_shader = gl.createShader(gl.FRAGMENT_SHADER);
        gl.shaderSource(frag_shader, frag_src, frag_src.len);
        gl.compileShader(frag_shader);

        const program = gl.createProgram();
        gl.attachShader(program, vert_shader);
        gl.attachShader(program, frag_shader);
        gl.linkProgram(program);

        // Vertex data
        const vertices = [_]f32{
            -1.0, -1.0, 1.0, 0.0, 0.0,
            1.0,  1.0,  0.0, 1.0, 0.0,
            1.0,  -1.0, 0.0, 0.0, 1.0,
            -1.0, -1.0, 1.0, 0.0, 0.0,
            1.0,  1.0,  0.0, 1.0, 0.0,
            -1.0, 1.0,  1.0, 1.0, 1.0,
        };

        // Create vertex buffer with fullscreen quad
        const vao = gl.createVertexArray();
        const vbo = gl.createBuffer();
        gl.bindVertexArray(vao);
        gl.bindBuffer(gl.ARRAY_BUFFER, vbo);

        gl.bufferData(gl.ARRAY_BUFFER, @sizeOf(f32) * vertices.len, @ptrCast([*]const u8, &vertices[0]), gl.STATIC_DRAW);

        gl.vertexAttribPointer(0, 2, gl.FLOAT, gl.FALSE, 5 * @sizeOf(f32), null);
        gl.enableVertexAttribArray(0);
        gl.vertexAttribPointer(1, 3, gl.FLOAT, gl.FALSE, 5 * @sizeOf(f32), @intToPtr(*c_uint, 2 * @sizeOf(f32)));
        gl.enableVertexAttribArray(1);

        // Get uniform locations
        const time_location = gl.getUniformLocation(program, "time", 4);

        // Load gltf from embedded file
        const gltf = try Gltf.fromBytes(allocator, gltf_json, (&[_][]const u8 { gltf_bin })[0..]);

        return Game{
            .program = program,
            .vao = vao,
            .vbo = vbo,
            .time_location = time_location,
            .gltf = gltf,
        };
    }

    pub fn deinit(self: *Game) void {
        self.gltf.deinit();
    }

    pub fn frame(self: Game, now_time: c_int) void {
        const time = @intToFloat(f32, now_time) / 1000.0;

        gl.bindVertexArray(self.vao);
        gl.useProgram(self.program);
        gl.uniform1f(self.time_location, time);
        gl.drawArrays(gl.TRIANGLES, 0, 6);
    }

    pub fn resize(self: Game, width: c_int, height: c_int) void {
        gl.viewport(0, 0, width, height);
    }
};
