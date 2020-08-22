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
extern fn glBufferData(_: c_uint, _: c_uint, _: [*]const u8, _: c_uint) void;
extern fn glBufferSubData(_: c_uint, _: c_uint, _: c_uint, [*]const u8) void;

// Programs and Shaders
extern fn glAttachShader(_: c_uint, _: c_uint) void;
extern fn glCompileShader(_: c_uint) void;
extern fn glCreateProgram() c_uint;
extern fn glCreateShader(_: c_uint) c_uint;
extern fn glDeleteProgram(_: c_uint) void;
extern fn glDeleteShader(_: c_uint) void;
extern fn glDetachShader(_: c_uint, _: c_uint) void;
extern fn glLinkProgram(_: c_uint) void;
extern fn glShaderSource(_: c_uint, _: [*]const u8, _: c_uint) void;
extern fn glUseProgram(_: c_uint) void;
extern fn glValidateProgram(_: c_uint) void;

// Special Functions
// TODO: This

// Rasterization
extern fn glCullFace(_: c_uint) void;
extern fn glFrontFace(_: c_uint) void;
extern fn glLineWidth(_: f32) void;
extern fn glPolygonOffset(_: f32, _: f32) void;

// View and Clip
extern fn glDepthRange(_: f32, _: f32) void;
extern fn glScissor(_: c_int, _: c_int, _: c_long, _: c_long) void;
extern fn glViewport(_: c_int, _: c_int, _: c_long, _: c_long) void;

// Writing to the Draw Buffer
extern fn glDrawArrays(_: c_uint, _: c_uint, _: c_uint) void;
extern fn glDrawElements(_: c_uint, _: c_uint, _: c_uint, _: c_uint) void;
extern fn glVertexAttribDivisor(_: c_uint, _: c_uint) void;
extern fn glDrawArraysInstanced(_: c_uint, _: c_uint, _: c_uint, _: c_uint) void;
extern fn glDrawElementsInstanced(_: c_uint, _: c_uint, _: c_uint, _: c_uint, _: c_uint) void;
extern fn glDrawRangeElements(_: c_uint, _: c_uint, _: c_uint, _: c_uint, _: c_uint, _: c_uint) void;

// Uniforms and Attributes
extern fn glDisableVertexAttribArray(_: c_uint) void;
extern fn glEnableVertexAttribArray(_: c_uint) void;
extern fn glGetUniformLocation(_: c_uint, _: [*]const u8, _: c_int) c_uint;
extern fn glUniform1f(_: c_uint, _: f32) void;
extern fn glUniform2fv(_: c_int, _: f32, _: f32) void;
extern fn glUniform3fv(_: c_int, _: f32, _: f32, _: f32) void;
extern fn glUniform4fv(_: c_int, _: f32, _: f32, _: f32, _: f32) void;
extern fn glUniform1i(_: c_int, _: c_int) void;
extern fn glUniform2iv(_: c_int, _: c_int, _: c_int) void;
extern fn glUniform3iv(_: c_int, _: c_int, _: c_int, _: c_int) void;
extern fn glUniform4iv(_: c_int, _: c_int, _: c_int, _: c_int, _: c_int) void;
extern fn glUniform1ui(_: c_int, _: c_uint) void;
extern fn glUniform2uiv(_: c_int, _: c_uint, _: c_uint) void;
extern fn glUniform3uiv(_: c_int, _: c_uint, _: c_uint, _: c_uint) void;
extern fn glUniform4uiv(_: c_int, _: c_uint, _: c_uint, _: c_uint, _: c_uint) void;
extern fn glUniformMatrix2fv(_: c_int, _: c_uint, [*]const f32) void;
extern fn glUniformMatrix3fv(_: c_int, _: c_uint, [*]const f32) void;
extern fn glUniformMatrix4fv(_: c_int, _: c_uint, [*]const f32) void;
extern fn glVertexAttribPointer(_: c_uint, _: c_uint, _: c_uint, _: c_uint, _: c_uint, _: [*c]const c_uint) void;
extern fn glVertexAttribIPointer(_: c_uint, _: c_uint, _: c_uint, _: c_uint, _: [*c]const c_uint) void;

// Vertex Array Objects
extern fn glBindVertexArray(_: c_uint) void;
extern fn glCreateVertexArray() c_uint;
extern fn glDeleteVertexArray(_: c_uint) void;

// Texture Objects
extern fn glActiveTexture(_: c_uint) void;
extern fn bindTexture(_: c_uint, _: c_uint) void;
// TODO: The rest

// Framebuffer Objects
// TODO: This

// Renderbuffer Objects
// TODO: This

// Whole Framebuffer Operations
extern fn glClear(_: c_uint) void;
extern fn glClearColor(_: f32, _: f32, _: f32, _: f32) void;
extern fn glClearDepth(_: f32) void;
extern fn glClearStencil(s: c_int) void;
extern fn glColorMask(_: c_uint, _: c_uint, _: c_uint, _: c_uint) void;
extern fn glDepthMask(_: c_uint) void;
extern fn glStencilMask(_: c_uint) void;
extern fn glStencilMaskSeparate(_: c_uint, _: c_uint) void;

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

// Types
pub const GLuint = c_uint;
pub const GLenum = c_uint;
pub const GLint = c_int;
pub const GLfloat = f32;

// Identifier constants pulled from WebGLRenderingContext
const GL_VERTEX_SHADER: c_uint = 35633;
const GL_FRAGMENT_SHADER: c_uint = 35632;
const GL_ARRAY_BUFFER: c_uint = 34962;
const GL_TRIANGLES: c_uint = 4;
const GL_TRIANGLE_STRIP = 5;
const GL_STATIC_DRAW: c_uint = 35044;
const GL_FLOAT: c_uint = 5126;
const GL_DEPTH_TEST: c_uint = 2929;
const GL_LEQUAL: c_uint = 515;
const GL_COLOR_BUFFER_BIT: c_uint = 16384;
const GL_DEPTH_BUFFER_BIT: c_uint = 256;
const GL_STENCIL_BUFFER_BIT = 1024;
const GL_TEXTURE_2D: c_uint = 3553;
const GL_RGBA: c_uint = 6408;
const GL_UNSIGNED_BYTE: c_uint = 5121;
const GL_TEXTURE_MAG_FILTER: c_uint = 10240;
const GL_TEXTURE_MIN_FILTER: c_uint = 10241;
const GL_NEAREST: c_uint = 9728;
const GL_TEXTURE0: c_uint = 33984;
const GL_BLEND: c_uint = 3042;
const GL_SRC_ALPHA: c_uint = 770;
const GL_ONE_MINUS_SRC_ALPHA: c_uint = 771;
const GL_ONE: c_uint = 1;
const GL_NO_ERROR = 0;
const GL_FALSE = 0;
const GL_TRUE = 1;
const GL_UNPACK_ALIGNMENT = 3317;

const GL_TEXTURE_WRAP_S = 10242;
const GL_CLAMP_TO_EDGE = 33071;
const GL_TEXTURE_WRAP_T = 10243;
const GL_PACK_ALIGNMENT = 3333;

pub const blendColor = glBlendColor;
pub const blendEquation = glBlendEquation;
pub const blendEquationSeparate = glBlendEquationSeparate;
pub const blendFunc = glBlendFunc;
pub const blendFuncSeparate = glBlendFuncSeparate;
pub const depthFunc = glDepthFunc;
pub const sampleCoverage = glSampleCoverage;
pub const stencilFunc = glStencilFunc;
pub const stencilFuncSeparate = glStencilFuncSeparate;
pub const stencilOp = glStencilOp;
pub const stencilOpSeparate = glStencilOpSeparate;
pub const createBuffer = glCreateBuffer;
pub const deleteBuffer = glDeleteBuffer;
pub const bindBuffer = glBindBuffer;
pub const bufferData = glBufferData;
pub const bufferSubData = glBufferSubData;
pub const attachShader = glAttachShader;
pub const compileShader = glCompileShader;
pub const createProgram = glCreateProgram;
pub const createShader = glCreateShader;
pub const deleteProgram = glDeleteProgram;
pub const deleteShader = glDeleteShader;
pub const detachShader = glDetachShader;
pub const linkProgram = glLinkProgram;
pub const shaderSource = glShaderSource;
pub const useProgram = glUseProgram;
pub const validateProgram = glValidateProgram;
pub const cullFace = glCullFace;
pub const frontFace = glFrontFace;
pub const lineWidth = glLineWidth;
pub const polygonOffset = glPolygonOffset;
pub const depthRange = glDepthRange;
pub const scissor = glScissor;
pub const viewport = glViewport;
pub const drawArrays = glDrawArrays;
pub const drawElements = glDrawElements;
pub const vertexAttribDivisor = glVertexAttribDivisor;
pub const drawArraysInstanced = glDrawArraysInstanced;
pub const drawElementsInstanced = glDrawElementsInstanced;
pub const drawRangeElements = glDrawRangeElements;
pub const disableVertexAttribArray = glDisableVertexAttribArray;
pub const enableVertexAttribArray = glEnableVertexAttribArray;
pub const getUniformLocation = glGetUniformLocation;
pub const uniform1f = glUniform1f;
pub const uniform2fv = glUniform2fv;
pub const uniform3fv = glUniform3fv;
pub const uniform4fv = glUniform4fv;
pub const uniform1i = glUniform1i;
pub const uniform2iv = glUniform2iv;
pub const uniform3iv = glUniform3iv;
pub const uniform4iv = glUniform4iv;
pub const uniform1ui = glUniform1ui;
pub const uniform2uiv = glUniform2uiv;
pub const uniform3uiv = glUniform3uiv;
pub const uniform4uiv = glUniform4uiv;
pub const uniformMatrix2fv = glUniformMatrix2fv;
pub const uniformMatrix3fv = glUniformMatrix3fv;
pub const uniformMatrix4fv = glUniformMatrix4fv;
pub const vertexAttribPointer = glVertexAttribPointer;
pub const vertexAttribIPointer = glVertexAttribIPointer;
pub const bindVertexArray = glBindVertexArray;
pub const createVertexArray = glCreateVertexArray;
pub const deleteVertexArray = glDeleteVertexArray;
pub const activeTexture = glActiveTexture;
pub const ndTexture = bindTexture;
pub const clear = glClear;
pub const clearColor = glClearColor;
pub const clearDepth = glClearDepth;
pub const clearStencil = glClearStencil;
pub const colorMask = glColorMask;
pub const depthMask = glDepthMask;
pub const stencilMask = glStencilMask;
pub const stencilMaskSeparate = glStencilMaskSeparate;

pub const VERTEX_SHADER = GL_VERTEX_SHADER;
pub const FRAGMENT_SHADER = GL_FRAGMENT_SHADER;
pub const ARRAY_BUFFER = GL_ARRAY_BUFFER;
pub const TRIANGLES = GL_TRIANGLES;
pub const TRIANGLE_STRIP = GL_TRIANGLE_STRIP;
pub const STATIC_DRAW = GL_STATIC_DRAW;
pub const FLOAT = GL_FLOAT;
pub const DEPTH_TEST = GL_DEPTH_TEST;
pub const LEQUAL = GL_LEQUAL;
pub const COLOR_BUFFER_BIT = GL_COLOR_BUFFER_BIT;
pub const DEPTH_BUFFER_BIT = GL_DEPTH_BUFFER_BIT;
pub const STENCIL_BUFFER_BIT = GL_STENCIL_BUFFER_BIT;
pub const TEXTURE_2D = GL_TEXTURE_2D;
pub const RGBA = GL_RGBA;
pub const UNSIGNED_BYTE = GL_UNSIGNED_BYTE;
pub const TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER;
pub const TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER;
pub const NEAREST = GL_NEAREST;
pub const TEXTURE0 = GL_TEXTURE0;
pub const BLEND = GL_BLEND;
pub const SRC_ALPHA = GL_SRC_ALPHA;
pub const ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA;
pub const ONE = GL_ONE;
pub const NO_ERROR = GL_NO_ERROR;
pub const FALSE = GL_FALSE;
pub const TRUE = GL_TRUE;
pub const UNPACK_ALIGNMENT = GL_UNPACK_ALIGNMENT;

pub const TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S;
pub const CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE;
pub const TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T;
pub const PACK_ALIGNMENT = GL_PACK_ALIGNMENT;
