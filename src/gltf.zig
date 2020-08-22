const std = @import("std");
const Allocator = std.mem.Allocator;
const json = std.json;

const gl = @import("webgl.zig");

/// A gltf buffer
pub const BufferView = struct {
    vbo: usize,
    stride: usize,

    /// Creates a buffer view given a gltf json buffer view, also uploads the data as a vbo.
    pub fn fromJson(view: json.ObjectMap, buffers: []const []const u8) BufferView {
        const buffer = if (view.get("buffer")) |d| @intCast(usize, d.Integer) else 0;
        const offset = if (view.get("byteOffset")) |d| @intCast(usize, d.Integer) else 0;
        const length = if (view.get("byteLength")) |d| @intCast(usize, d.Integer) else 0;
        const stride = if (view.get("byteStride")) |d| @intCast(usize, d.Integer) else 0;
        const target = if (view.get("target")) |d| @intCast(usize, d.Integer) else gl.ARRAY_BUFFER;

        const vbo = gl.createBuffer();
        gl.bindBuffer(target, vbo);
        gl.bufferData(target, length, @ptrCast([*]const u8, &buffers[buffer][offset]), gl.STATIC_DRAW);

        return .{ .vbo = vbo, .stride = stride };
    }
};

/// A gltf accessor
pub const Accessor = struct {
    view: usize,
    offset: usize,
    count: usize,
    glType: usize,

    /// Creates an accessor given a gltf json accessor.
    pub fn fromJson(accessor: json.ObjectMap) Accessor {
        return .{
            .view = if (accessor.get("bufferView")) |d| @intCast(usize, d.Integer) else 0,
            .offset = if (accessor.get("byteOffset")) |d| @intCast(usize, d.Integer) else 0,
            .count = if (accessor.get("count")) |d| @intCast(usize, d.Integer) else 0,
            .glType = if (accessor.get("componentType")) |d| @intCast(usize, d.Integer) else 0,
        };
    }
};

/// A gltf primitive
pub const Primitive = struct {
    position: ?usize,
    normal: ?usize,
    tangent: ?usize,
    texcoord_0: ?usize,
    texcoord_1: ?usize,
    color_0: ?usize,
    joints_0: ?usize,
    weights_0: ?usize,
    indices: ?usize,
    material: ?usize,
    mode: usize,

    /// Creates a primitive given a gltf json accessor.
    pub fn fromJson(primitive: json.ObjectMap) !Primitive {
        const attributes = if (primitive.get("attributes")) |d| d.Object else return error.BadGltf;
        return Primitive{
            .position = if (attributes.get("POSITION")) |d| @intCast(usize, d.Integer) else null,
            .normal = if (attributes.get("NORMAL")) |d| @intCast(usize, d.Integer) else null,
            .tangent = if (attributes.get("TANGENT")) |d| @intCast(usize, d.Integer) else null,
            .texcoord_0 = if (attributes.get("TEXCOORD_0")) |d| @intCast(usize, d.Integer) else null,
            .texcoord_1 = if (attributes.get("TEXCOORD_1")) |d| @intCast(usize, d.Integer) else null,
            .color_0 = if (attributes.get("COLOR_0")) |d| @intCast(usize, d.Integer) else null,
            .joints_0 = if (attributes.get("JOINTS_0")) |d| @intCast(usize, d.Integer) else null,
            .weights_0 = if (attributes.get("WEIGHTS_0")) |d| @intCast(usize, d.Integer) else null,
            .indices = if (primitive.get("indices")) |d| @intCast(usize, d.Integer) else null,
            .material = if (primitive.get("material")) |d| @intCast(usize, d.Integer) else null,
            .mode = if (primitive.get("mode")) |d| @intCast(usize, d.Integer) else 0,
        };
    }
};

/// A gltf Mesh
pub const Mesh = struct {
    primitives: []Primitive,
    weights: ?[]f32,

    pub fn fromJson(allocator: *Allocator, mesh: json.ObjectMap) !Mesh {
        const gltf_primitives = if (mesh.get("primitives")) |d| d.Array.items else return error.BadGltf;
        var primitives = try allocator.alloc(Primitive, gltf_primitives.len);
        {
            var i: usize = 0;
            while (i < primitives.len) : (i += 1) {
                primitives[i] = try Primitive.fromJson(gltf_primitives[i].Object);
            }
        }

        var weights: ?[]f32 = null;
        if (mesh.get("weights")) |d| {
            const gltf_weights = d.Array.items;
            weights = try allocator.alloc(f32, gltf_weights.len);
            var i: usize = 0;
            while (i < weights.?.len) : (i += 1) {
                weights.?[i] = @floatCast(f32, gltf_weights[i].Float);
            }
        }

        return Mesh{ .primitives = primitives, .weights = weights };
    }

    pub fn deinit(self: *Mesh, allocator: *Allocator) void {
        allocator.free(self.primitives);
        if (self.weights) |weights| {
            allocator.free(weights);
        }
    }
};

pub const PerspectiveCamera = struct {
    aspect_ratio: f32,
    yfov: f32,
    znear: f32,
    zfar: f32,

    pub fn fromJson(camera: json.ObjectMap) !Camera {

    }
}

pub const Camera = struct {

};


pub const Scene = struct {};
pub const Node = struct {};
pub const Material = struct {};
pub const Texture = struct {};
pub const Image = struct {};
pub const Sampler = struct {};
pub const Skin = struct {};
pub const Animation = struct {};

// A fully loaded gltf file
pub const Gltf = struct {
    allocator: *Allocator,

    buffer_views: []BufferView,
    accessors: []Accessor,
    meshes: []Mesh,

    pub fn fromJson(allocator: *Allocator, gltf: json.ObjectMap, buffers: []const []const u8) !Gltf {
        const gltf_buffer_views = if (gltf.get("bufferViews")) |d| d.Array.items else return error.BadGltf;
        const gltf_accessors = if (gltf.get("accessors")) |d| d.Array.items else return error.BadGltf;
        const gltf_meshes = if (gltf.get("meshes")) |d| d.Array.items else return error.BadGltf;

        var buffer_views = try allocator.alloc(BufferView, gltf_buffer_views.len);
        {
            var i: usize = 0;
            while (i < buffer_views.len) : (i += 1) {
                buffer_views[i] = BufferView.fromJson(gltf_buffer_views[i].Object, buffers);
            }
        }

        var accessors = try allocator.alloc(Accessor, gltf_accessors.len);
        {
            var i: usize = 0;
            while (i < accessors.len) : (i += 1) {
                accessors[i] = Accessor.fromJson(gltf_accessors[i].Object);
            }
        }

        var meshes = try allocator.alloc(Mesh, gltf_meshes.len);
        {
            var i: usize = 0;
            while (i < meshes.len) : (i += 1) {
                meshes[i] = try Mesh.fromJson(allocator, gltf_meshes[i].Object);
            }
        }

        return Gltf{
            .allocator = allocator,
            .buffer_views = buffer_views,
            .accessors = accessors,
            .meshes = meshes,
        };
    }

    pub fn fromBytes(allocator: *Allocator, bytes: []const u8, buffers: []const []const u8) !Gltf {
        var parser = json.Parser.init(allocator, false);
        defer parser.deinit();
        const value_tree = try parser.parse(bytes);
        const root = value_tree.root.Object;

        return fromJson(allocator, root, buffers);
    }

    pub fn deinit(self: *Gltf) void {
        for (self.meshes) |mesh| {
            mesh.deinit();
        }

        self.allocator.free(self.buffer_views);
        self.allocator.free(self.accessors);
        self.allocator.free(self.meshes);
    }
};