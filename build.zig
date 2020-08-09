const std = @import("std");
const Builder = std.build.Builder;
const LibExeObjStep = std.build.LibExeObjStep;

pub fn build(b: *Builder) void {
    // Standard target options allows the person running `zig build` to choose
    // what target to build for. Here we do not override the defaults, which
    // means any target is allowed, and the default is native. Other options
    // for restricting supported target set are available.
    const target = b.standardTargetOptions(.{});

    // Standard release options allow the person running `zig build` to select
    // between Debug, ReleaseSafe, ReleaseFast, and ReleaseSmall.
    const mode = b.standardReleaseOptions();

    const exe = b.addExecutable("kindling", "src/main.zig");
    exe.setTarget(target);
    exe.setBuildMode(mode);
    addDeps(exe);
    exe.install();

    const run_cmd = exe.run();
    run_cmd.step.dependOn(b.getInstallStep());

    const run_step = b.step("run", "Run the app");
    run_step.dependOn(&run_cmd.step);
}

fn addDeps(step: *LibExeObjStep) void {
    const c_opts = &[_][]const u8{"-std=c99"};
    step.linkLibC();
    step.linkSystemLibrary("kernel32");
    step.linkSystemLibrary("user32");
    step.linkSystemLibrary("shell32");
    step.linkSystemLibrary("gdi32");

    step.addLibPath("deps/lib");
    step.addIncludeDir("deps/include");
    //step.addCSourceFile("deps/src/enet.c", c_opts);
    step.addCSourceFile("deps/src/glad.c", c_opts);
    step.addCSourceFile("deps/src/librg.c", c_opts);
    step.addCSourceFile("deps/src/miniaudio.c", c_opts);
    step.linkSystemLibrary("glfw3");
}
