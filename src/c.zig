pub usingnamespace @cImport({
    @cDefine("_POSIX_C_SOURCE", "199309");
    @cInclude("glad/glad.h");
    @cInclude("GLFW/glfw3.h");
    @cInclude("enet.h");
    @cInclude("librg.h");
    @cInclude("miniaudio.h");
});
