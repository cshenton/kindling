// Per Fragment Operations
extern fn glBlendColor(_: f32, _: f32, _: f32, _: f32) void;
extern fn glBlendEquation(_: c_uint) void;
extern fn glBlendEquationSeparate(_: c_uint, _: c_uint) void;
extern fn glBlendFunc(_: c_uint, _: c_uint) void;
extern fn glBlendFuncSeparate(_: c_uint, _: c_uint, _: c_uint, _: c_uint) void;
extern fn glDepthFunc(_: c_uint) void;
extern fn glSampleCoverage(_: f32, _: c_uint) void;
extern fn glStencilFunc(_: c_uint, _: c_int, _: c_uint) void;
extern fn glStencilFuncSeparate(_: c_uint, _: c_uint, _: c_int, _: c_uint) void;
extern fn glStencilOp(_: c_uint, _: c_uint, _: c_uint) void;
extern fn glStencilOpSeparate(_: c_uint, _: c_uint, _: c_uint, _: c_uint) void;

// Buffer Objects
extern fn glCreateBuffer() c_uint;
extern fn glDeleteBuffer(_: c_uint) void;
extern fn glBindBuffer(_: c_uint, _: c_uint) void;
extern fn glBufferData(_: c_uint, _: c_uint, _: [*c]const c_void, _: c_uint) void;
extern fn glBufferSubData(_: c_uint, _: c_uint, _: c_uint, [*c]const c_void) void;

// Programs and Shaders
extern fn glAttachShader(_: c_uint, _: c_uint) void;
extern fn glCompileShader(_: c_uint) void;
extern fn glCreateProgram() c_uint;
extern fn glCreateShader() c_uint;
extern fn glDeleteProgram(_: c_uint) void;
extern fn glDeleteShader(_: c_uint) void;
extern fn glDetachShader(_: c_uint, _: c_uint) void;
extern fn glLinkProgram(_: c_uint) void;
extern fn glShaderSource(_: c_uint, _: [*]const u8 , _: c_uint, _: c_uint) void;
extern fn glUseProgram(_: c_uint) void;
extern fn glValidateProgram(_: c_uint) void;

// Special Functions
// TODO: This

// Rasterization
extern fn glCullFace(_: c_uint) void;
extern fn glFrontFace(_: c_uint) void;
const glLineWidth = (width) => gl.lineWidth(width);
const glPolygonOffset = (factor, units) => gl.polygonOffset(factor, units);

// View and Clip
const glDepthRange = (zNear, zFar) => gl.DepthRange(zNear, zFar);
const glScissor = (x, y, width, height) => gl.scissor(x, y, width, height);
const glViewport = (x, y, width, height) => gl.viewport(x, y, width, height);

// Writing to the Draw Buffer
const glDrawArrays = (mode, first, count) => gl.drawArrays(mode, size, count);
const glDrawElements = (mode, count, type, offset) => gl.drawElements(mode, count, type, offset);
const glVertexAttribDivisor = (index, divisor) => gl.vertexAttribDivisor(index, divisor);
const glDrawArraysInstanced = (mode, first, count, instanceCount) => gl.drawArraysInstanced(mode, first, count, instanceCount);
const glDrawElementsInstanced = (mode, count, type, offset, instanceCount) => gl.drawElementsInstanced(mode, count, type, offset, instanceCount);
const glDrawRangeElements = (mode, start, end, count, type, offset) => gl.drawRangeElements(mode, start, end, count, type, offset);

// Detect context lost events
const glIsContextLost = () => gl.isContextLost();

// Uniforms and Attributes
const glDisableVertexAttribArray = (index) => gl.disableVertexAttribArray(index);
const glEnableVertexAttribArray = (index) => gl.enableVertexAttribArray(index);
const glUniform1fv = (location, data) => gl.uniform1fv(location, data);
const glUniform2fv = (location, data) => gl.uniform2fv(location, data);
const glUniform3fv = (location, data) => gl.uniform3fv(location, data);
const glUniform4fv = (location, data) => gl.uniform4fv(location, data);
const glUniform1iv = (location, data) => gl.uniform1iv(location, data);
const glUniform2iv = (location, data) => gl.uniform2iv(location, data);
const glUniform3iv = (location, data) => gl.uniform3iv(location, data);
const glUniform4iv = (location, data) => gl.uniform4iv(location, data);
const glUniform1uiv = (location, data) => gl.uniform1uiv(location, data);
const glUniform2uiv = (location, data) => gl.uniform2uiv(location, data);
const glUniform3uiv = (location, data) => gl.uniform3uiv(location, data);
const glUniform4uiv = (location, data) => gl.uniform4uiv(location, data);
const glUniformMatrix2fv = (location, transpose, data) => gl.uniformMatrix2fv(location, transpose, data);
const glUniformMatrix3fv = (location, transpose, data) => gl.uniformMatrix2fv(location, transpose, data);
const glUniformMatrix4fv = (location, transpose, data) => gl.uniformMatrix2fv(location, transpose, data);
const glVertexAttribPointer = (index, size, type, normalized, stride, offset) => gl.vertexAttribPointer(index, size, type, normalized, stride, offset);
const glVertexAttribIPointer = (index, size, type, stride, offset) => gl.vertexAttribIPointer(index, size, type, stride, offset);

// Vertex Array Objects
const glBindVertexArray = (vertexArray) => gl.bindVertexArray(glVertexArrays[vertexArray]);
const glCreateVertexArray = () => {
  glVertexArrays.push(gl.createVertexArray());
  return glVertexArrays.length - 1;
}
const glDeleteVertexArray = (vertexArray) => {
  gl.deleteVertexArray(glVertexArrays[vertexArray]);
  glVertexArrays[vertexArray] = undefined;
}

// Texture Objects
const glActiveTexture = (texture) => gl.activeTexture(texture);
const glBindTexture = (target, texture) => gl.bindTexture(target, glTextures[texture]);
// TODO: The rest

// Framebuffer Objects
// TODO: This

// Renderbuffer Objects
// TODO: This

// Whole Framebuffer Operations
const glClear = (mask) => gl.clear(mask);
const glClearColor = (r, g, b, a) => gl.clearColor(r, g, b, a);
const glClearDepth = (depth) => gl.clearDepth(depth);
const glClearStencil = (s) => gl.clearStencil(s);
const glColorMask = (r, g, b, a) => gl.colorMask(r, g, b, a);
const glDepthMask = (flag) => gl.depthMask(flag);
const glStencilMask = (mask) => gl.stencilMask(mask);
const glStencilMaskSeparate = (face) => gl.stencilMaskSeparate(face);

// Multiple Render Targets
// TODO: This

// Sampler Objects
// TODO: This

// Query Objects
// TODO: This

// Transform Feedback
// TODO: This

// Sync Objects
// TODO: This

// Uniform Buffer Objects
// TODO: This




// Shaders
pub extern fn glInitShader(source: [*]const u8 , len: c_uint, type: c_uint) c_uint;
pub extern fn glLinkShaderProgram(vertexShaderId: c_uint, fragmentShaderId: c_uint) c_uint;

// GL
pub extern fn glViewport(_: c_int, _: c_int, _: c_int, _: c_int) void;
pub extern fn glClearColor(_: f32, _: f32, _: f32, _: f32) void;
pub extern fn glEnable(_: c_uint) void;
pub extern fn glDepthFunc(_: c_uint) void;
pub extern fn glBlendFunc(_: c_uint, _: c_uint) void;
pub extern fn glClear(_: c_uint) void;
pub extern fn glGetAttribLocation(_: c_uint, _: [*]const u8, _: c_uint) c_int;
pub extern fn glGetUniformLocation(_: c_uint, _: [*]const u8, _: c_uint) c_int;
pub extern fn glUniform4fv(_: c_int, _: f32, _: f32, _: f32, _: f32) void;
pub extern fn glUniform1i(_: c_int, _: c_int) void;
pub extern fn glUniform1f(_: c_int, _: f32) void;
pub extern fn glUniformMatrix4fv(_: c_int, _: c_int, _: c_uint, _: [*]const f32) void;
pub extern fn glCreateVertexArray() c_uint;
pub extern fn glGenVertexArrays(_: c_int, [*c]c_uint) void;
pub extern fn glDeleteVertexArrays(_: c_int, [*c]c_uint) void;
pub extern fn glBindVertexArray(_: c_uint) void;
pub extern fn glCreateBuffer() c_uint;
pub extern fn glGenBuffers(_: c_int, _: [*c]c_uint) void;
pub extern fn glDeleteBuffers(_: c_int, _: [*c]c_uint) void;
pub extern fn glDeleteBuffer(_: c_uint) void;
pub extern fn glBindBuffer(_: c_uint, _: c_uint) void;
pub extern fn glBufferData(_: c_uint, _: c_uint, _: [*c]const f32, _: c_uint) void;
pub extern fn glPixelStorei(_: c_uint, _: c_int) void;
pub extern fn glAttachShader(_: c_uint, _: c_uint) void;
pub extern fn glDetachShader(_: c_uint, _: c_uint) void;
pub extern fn glDeleteShader(_: c_uint) void;
pub extern fn glUseProgram(_: c_uint) void;
pub extern fn glDeleteProgram(_: c_uint) void;
pub extern fn glEnableVertexAttribArray(_: c_uint) void;
pub extern fn glVertexAttribPointer(_: c_uint, _: c_uint, _: c_uint, _: c_uint, _: c_uint, _: [*c]const c_uint) void;
pub extern fn glDrawArrays(_: c_uint, _: c_uint, _: c_uint) void;
pub extern fn glCreateTexture() c_uint;
pub extern fn glGenTextures(_: c_int, _: [*c]c_uint) void;
pub extern fn glDeleteTextures(_: c_int, _: [*c]const c_uint) void;
pub extern fn glDeleteTexture(_: c_uint) void;
pub extern fn glBindTexture(_: c_uint, _: c_uint) void;
pub extern fn glTexImage2D(_: c_uint, _: c_uint, _: c_uint, _: c_int, _: c_int, _: c_uint, _: c_uint, _: c_uint, _: [*]const u8, _: c_uint) void;
pub extern fn glTexParameteri(_: c_uint, _: c_uint, _: c_uint) void;
pub extern fn glActiveTexture(_: c_uint) void;
pub extern fn glGetError() c_int;

// Types
pub const GLuint = c_uint;
pub const GLenum = c_uint;
pub const GLint = c_int;
pub const GLfloat = f32;

// Identifier constants pulled from WebGLRenderingContext
pub const GL_VERTEX_SHADER: c_uint = 35633;
pub const GL_FRAGMENT_SHADER: c_uint = 35632;
pub const GL_ARRAY_BUFFER: c_uint = 34962;
pub const GL_TRIANGLES: c_uint = 4;
pub const GL_TRIANGLE_STRIP = 5;
pub const GL_STATIC_DRAW: c_uint = 35044;
pub const GL_FLOAT: c_uint = 5126;
pub const GL_DEPTH_TEST: c_uint = 2929;
pub const GL_LEQUAL: c_uint = 515;
pub const GL_COLOR_BUFFER_BIT: c_uint = 16384;
pub const GL_DEPTH_BUFFER_BIT: c_uint = 256;
pub const GL_STENCIL_BUFFER_BIT = 1024;
pub const GL_TEXTURE_2D: c_uint = 3553;
pub const GL_RGBA: c_uint = 6408;
pub const GL_UNSIGNED_BYTE: c_uint = 5121;
pub const GL_TEXTURE_MAG_FILTER: c_uint = 10240;
pub const GL_TEXTURE_MIN_FILTER: c_uint = 10241;
pub const GL_NEAREST: c_uint = 9728;
pub const GL_TEXTURE0: c_uint = 33984;
pub const GL_BLEND: c_uint = 3042;
pub const GL_SRC_ALPHA: c_uint = 770;
pub const GL_ONE_MINUS_SRC_ALPHA: c_uint = 771;
pub const GL_ONE: c_uint= 1;
pub const GL_NO_ERROR = 0;
pub const GL_FALSE = 0;
pub const GL_TRUE = 1;
pub const GL_UNPACK_ALIGNMENT = 3317;

pub const GL_TEXTURE_WRAP_S = 10242;
pub const GL_CLAMP_TO_EDGE = 33071;
pub const GL_TEXTURE_WRAP_T = 10243;
pub const GL_PACK_ALIGNMENT = 3333;

const AUDIO_BUFFER_SIZE = 8192;
var beep = []f32 { 0 } ** AUDIO_BUFFER_SIZE;
var boop = []f32 { 0 } ** AUDIO_BUFFER_SIZE;
var bloop = []f32 { 0 } ** AUDIO_BUFFER_SIZE;

pub const KEY_BACKSPACE = 8;
pub const KEY_TAB = 9;
pub const KEY_ENTER = 13;
pub const KEY_SHIFT = 16;
pub const KEY_CTRL = 17;
pub const KEY_ALT = 18;
pub const KEY_PAUSE = 19;
pub const KEY_CAPS_LOCK = 20;
pub const KEY_ESCAPE = 27;
pub const KEY_SPACE = 32;
pub const KEY_PAGEUP = 33;
pub const KEY_PAGEDOWN = 34;
pub const KEY_END = 35;
pub const KEY_HOME = 36;
pub const KEY_LEFT = 37;
pub const KEY_UP = 38;
pub const KEY_RIGHT = 39;
pub const KEY_DOWN = 40;
pub const KEY_INSERT = 45;
pub const KEY_DELETE = 46;
pub const KEY_0 = 48;
pub const KEY_1 = 49;
pub const KEY_2 = 50;
pub const KEY_3 = 51;
pub const KEY_4 = 52;
pub const KEY_5 = 53;
pub const KEY_6 = 54;
pub const KEY_7 = 55;
pub const KEY_8 = 56;
pub const KEY_9 = 57;
pub const KEY_A = 65;
pub const KEY_B = 66;
pub const KEY_C = 67;
pub const KEY_D = 68;
pub const KEY_E = 69;
pub const KEY_F = 70;
pub const KEY_G = 71;
pub const KEY_H = 72;
pub const KEY_I = 73;
pub const KEY_J = 74;
pub const KEY_K = 75;
pub const KEY_L = 76;
pub const KEY_M = 77;
pub const KEY_N = 78;
pub const KEY_O = 79;
pub const KEY_P = 80;
pub const KEY_Q = 81;
pub const KEY_R = 82;
pub const KEY_S = 83;
pub const KEY_T = 84;
pub const KEY_U = 85;
pub const KEY_V = 86;
pub const KEY_W = 87;
pub const KEY_X = 88;
pub const KEY_Y = 89;
pub const KEY_Z = 90;
pub const KEY_META_LEFT = 91;
pub const KEY_META_RIGHT = 92;
pub const KEY_SELECT = 93;
pub const KEY_NP0 = 96;
pub const KEY_NP1 = 97;
pub const KEY_NP2 = 98;
pub const KEY_NP3 = 99;
pub const KEY_NP4 = 100;
pub const KEY_NP5 = 101;
pub const KEY_NP6 = 102;
pub const KEY_NP7 = 103;
pub const KEY_NP8 = 104;
pub const KEY_NP9 = 105;
pub const KEY_NPMULTIPLY = 106;
pub const KEY_NPADD = 107;
pub const KEY_NPSUBTRACT = 109;
pub const KEY_NPDECIMAL = 110;
pub const KEY_NPDIVIDE = 111;
pub const KEY_F1 = 112;
pub const KEY_F2 = 113;
pub const KEY_F3 = 114;
pub const KEY_F4 = 115;
pub const KEY_F5 = 116;
pub const KEY_F6 = 117;
pub const KEY_F7 = 118;
pub const KEY_F8 = 119;
pub const KEY_F9 = 120;
pub const KEY_F10 = 121;
pub const KEY_F11 = 122;
pub const KEY_F12 = 123;
pub const KEY_NUM_LOCK = 144;
pub const KEY_SCROLL_LOCK = 145;
pub const KEY_SEMICOLON = 186;
pub const KEY_EQUAL_SIGN = 187;
pub const KEY_COMMA = 188;
pub const KEY_MINUS = 189;
pub const KEY_PERIOD = 190;
pub const KEY_SLASH = 191;
pub const KEY_BACKQUOTE = 192;
pub const KEY_BRACKET_LEFT = 219;
pub const KEY_BACKSLASH = 220;
pub const KEY_BRAKET_RIGHT = 221;
pub const KEY_QUOTE = 22;
