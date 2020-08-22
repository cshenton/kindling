const gl = @import("webgl.zig");

pub const Program = struct {
    id: c_uint,

    pub fn init(vert_src: []const u8, frag_src: []const u8) Program {
        const vert_shader = gl.createShader(gl.VERTEX_SHADER);
        gl.shaderSource(vert_shader, vert_src.ptr, vert_src.len);
        gl.compileShader(vert_shader);

        const frag_shader = gl.createShader(gl.FRAGMENT_SHADER);
        gl.shaderSource(frag_shader, frag_src.ptr, frag_src.len);
        gl.compileShader(frag_shader);

        const id = gl.createProgram();
        gl.attachShader(id, vert_shader);
        gl.attachShader(id, frag_shader);
        gl.linkProgram(id);

        gl.deleteShader(vert_shader);
        gl.deleteShader(frag_shader);

        return Program{ .id = id };
    }

    pub fn use(self: Program) void {
        gl.useProgram(self.id);
    }

    pub fn getUniformLocation(self: Program, name: []const u8) c_uint {
        return gl.getUniformLocation(self.id, name.ptr, @intCast(c_int, name.len));
    }
};