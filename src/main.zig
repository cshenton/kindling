const std = @import("std");
usingnamespace @import("c.zig");

pub fn main() !void {
    const width = 2160;
    const height = 1440;

    if (glfwInit() == 0) return error.GlfwError;
    defer glfwTerminate();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    var window = glfwCreateWindow(width, height, "Kindling", null, null) orelse return error.GlfwError;
    const resize_callback = glfwSetFramebufferSizeCallback(window, resizeCallback);

    glfwMakeContextCurrent(window);
    if (gladLoadGLLoader(@ptrCast(GLADloadproc, glfwGetProcAddress)) == 0) return error.GladError;

    while (glfwWindowShouldClose(window) == 0) {
        glClearColor(0.1, 0.1, 0.2, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

pub fn resizeCallback(window: ?*GLFWwindow, width: c_int, height: c_int) callconv(.C) void {
    glViewport(0, 0, width, height);
}
