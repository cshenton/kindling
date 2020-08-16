const std = @import("std");
const Builder = std.build.Builder;

pub fn build(b: *Builder) !void {
    b.install_path = "./";
    
    const target = try std.zig.CrossTarget.parse(.{ .arch_os_abi = "wasm32-freestanding" });
    const mode = b.standardReleaseOptions();

    const wasm = b.addStaticLibrary("kindling", "src/main.zig");
    wasm.setTarget(target);
    wasm.setBuildMode(mode);
    wasm.install();

    const wasm_step = b.step("wasm", "Build the web assembly module");
    wasm_step.dependOn(b.getInstallStep());
}
