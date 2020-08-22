// The below code assumes the existence of a `memory` webassembly memory variable, which can be used to
// create JS array views into the wasm module's memory for zero copy sharing of data.

// Setup the WebGL 2.0 context
let gl;

let webglOptions = {
  alpha: true,
  antialias: true,
  depth: 32,
  failIfMajorPerformanceCaveat: false,
  powerPreference: "default",
  premultipliedAlpha: true,
  preserveDrawingBuffer: true,
  stencil: true,
}

gl = $canvas.getContext('webgl2', webglOptions);
if (!gl) {
  throw new Error('The browser does not support WebGL 2.0');
}

// Certain opaque handles must remain on the JS side, so we reference them with our own handle system.
// As much as possible, we try to maintain the WebGL 2.0 api on the native side, however there will be
// inconsistencies.
const glShaders = [];
const glPrograms = [];
const glVertexArrays = [];
const glBuffers = [];
const glTextures = [];
const glUniformLocations = [];

// Create the function declarations to pass to wasm. These are prefixed with gl to ensure no namespace
// clashes, but are aliased by the wasm code to match the JS gl.fooBar convention.

// Per Fragment Operations
const glBlendColor = (red, green, blue, alpha) => gl.blendColor(red, green, blue, alpha);
const glBlendEquation = (mode) => gl.blendEquation(mode);
const glBlendEquationSeparate = (modeRGB, modeAlpha) => gl.blendEquationSeparate(modeRGB, modeAlpha);
const glBlendFunc = (sfactor, dfactor) => gl.blendFunc(sfactor, dfactor);
const glBlendFuncSeparate = (srcRGB, dstRGB, srcAlpha, dstAlpha) => gl.blendFuncSeparate(srcRGB, dstRGB, srcAlpha, dstAlpha);
const glDepthFunc = (func) => gl.depthFunc(func);
const glSampleCoverage = (func) => gl.sampleCoverage(func);
const glStencilFunc = (func, ref, mask) => gl.stencilFunc(func, ref, mask);
const glStencilFuncSeparate = (face, func, ref, mask) => gl.stencilFuncSeparate(face, func, ref, mask);
const glStencilOp = (fail, zfail, zpass) => gl.stencilOp(fail, zfail, zpass);
const glStencilOpSeparate = (face, fail, zfail, zpass) => gl.stencilOpSeparate(face, fail, zfail, zpass);

// Buffer Objects
const glCreateBuffer = () => {
  glBuffers.push(gl.createBuffer());
  return glBuffers.length - 1;
}
const glDeleteBuffer = (buffer) => {
  gl.deleteBuffer(glBuffers[buffer]);
  glBuffers[buffer] = undefined;
}
const glBindBuffer = (target, buffer) => gl.bindBuffer(target, glBuffers[buffer]);
const glBufferData = (target, size, ptr, usage) => {
  const bytes = new Uint8Array(memory.buffer, ptr, size);
  gl.bufferData(target, bytes, usage);
}
const glBufferSubData = (target, offset, size, ptr) => {
  const bytes = new Uint8Array(memory.buffer, ptr, size);
  gl.bufferSubData(target, offset, bytes, 0, size);
}

// Programs and Shaders
const glAttachShader = (program, shader) => gl.attachShader(glPrograms[program], glShaders[shader]);
const glCompileShader = (shader) => {
  gl.compileShader(glShaders[shader]);
  if (!gl.getShaderParameter(glShaders[shader], gl.COMPILE_STATUS)) {
    throw "Error compiling shader:" + gl.getShaderInfoLog(glShaders[shader]);
  }
  // error check with info log
}
const glCreateProgram = () => {
  glPrograms.push(gl.createProgram());
  return glPrograms.length - 1;
}
const glCreateShader = (type) => {
  glShaders.push(gl.createShader(type));
  return glShaders.length - 1;
}
const glDeleteProgram = (program) => {
  gl.deleteProgram(glProgams[program]);
  glPrograms[program] = undefined;
}
const glDeleteShader = (shader) => {
  gl.deleteShader(glShaders[shader]);
  glShaders[shader] = undefined;
}
const glDetachShader = (program, shader) => gl.detachShader(glPrograms[program], glShaders[shader]);
const glLinkProgram = (program) => {
  gl.linkProgram(glPrograms[program]);
  if (!gl.getProgramParameter(glPrograms[program], gl.LINK_STATUS)) {
    throw ("Error linking program:" + gl.getProgramInfoLog(glPrograms[program]));
  }
}
const glShaderSource = (shader, sourcePtr, sourceLen) => gl.shaderSource(glShaders[shader], readCharStr(sourcePtr, sourceLen));
const glUseProgram = (program) => gl.useProgram(glPrograms[program]);
const glValidateProgram = (program) => gl.validateProgram(glPrograms[program]);

// Special Functions
// const glFoo = (bar) => gl.foo(bar)

// Rasterization
const glCullFace = (mode) => gl.cullFace(mode);
const glFrontFace = (mode) => gl.frontFace(mode);
const glLineWidth = (width) => gl.lineWidth(width);
const glPolygonOffset = (factor, units) => gl.polygonOffset(factor, units);

// View and Clip
const glDepthRange = (zNear, zFar) => gl.DepthRange(zNear, zFar);
const glScissor = (x, y, width, height) => gl.scissor(x, y, width, height);
const glViewport = (x, y, width, height) => gl.viewport(x, y, width, height);

// Writing to the Draw Buffer
const glDrawArrays = (mode, first, count) => gl.drawArrays(mode, first, count);
const glDrawElements = (mode, count, type, offset) => gl.drawElements(mode, count, type, offset);
const glVertexAttribDivisor = (index, divisor) => gl.vertexAttribDivisor(index, divisor);
const glDrawArraysInstanced = (mode, first, count, instanceCount) => gl.drawArraysInstanced(mode, first, count, instanceCount);
const glDrawElementsInstanced = (mode, count, type, offset, instanceCount) => gl.drawElementsInstanced(mode, count, type, offset, instanceCount);
const glDrawRangeElements = (mode, start, end, count, type, offset) => gl.drawRangeElements(mode, start, end, count, type, offset);

// Uniforms and Attributes
const glDisableVertexAttribArray = (index) => gl.disableVertexAttribArray(index);
const glEnableVertexAttribArray = (index) => gl.enableVertexAttribArray(index);
const glGetUniformLocation = (program, namePtr, nameLen) => {
  glUniformLocations.push(gl.getUniformLocation(glPrograms[program], readCharStr(namePtr, nameLen)));
  return glUniformLocations.length - 1;
}
const glUniform1f = (location, x) => gl.uniform1f(glUniformLocations[location], x);
const glUniform2fv = (location, x, y) => gl.uniform2fv(location, [x, y]);
const glUniform3fv = (location, x, y, z) => gl.uniform3fv(location, [x, y, z]);
const glUniform4fv = (location, x, y, z, w) => gl.uniform4fv(location, [x, y, z, w]);
const glUniform1i = (location, x) => gl.uniform1i(location, x);
const glUniform2iv = (location, x, y) => gl.uniform2iv(location, [x, y]);
const glUniform3iv = (location, x, y, z) => gl.uniform3iv(location, [x, y, z]);
const glUniform4iv = (location, x, y, z, w) => gl.uniform4iv(location, [x, y, z, w]);
const glUniform1ui = (location, x) => gl.uniform1ui(location, x);
const glUniform2uiv = (location, x, y) => gl.uniform2uiv(location, [x, y]);
const glUniform3uiv = (location, x, y, z) => gl.uniform3uiv(location, [x, y, z]);
const glUniform4uiv = (location, x, y, z, w) => gl.uniform4uiv(location, [x, y, z, w]);
const glUniformMatrix2fv = (location, transpose, dataPtr) => {
  const floats = new Float32Array(memory.buffer, dataPtr, 4);
  gl.uniformMatrix2fv(location, transpose, floats);
};
const glUniformMatrix3fv = (location, transpose, dataPtr) => {
  const floats = new Float32Array(memory.buffer, dataPtr, 9);
  gl.uniformMatrix3fv(location, transpose, floats);
};
const glUniformMatrix4fv = (location, transpose, dataPtr) => {
  const floats = new Float32Array(memory.buffer, dataPtr, 16);
  gl.uniformMatrix4fv(location, transpose, floats);
};
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
const glStencilMaskSeparate = (face, mask) => gl.stencilMaskSeparate(face, mask);

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

var webgl = {
  glBlendColor,
  glBlendEquation,
  glBlendEquationSeparate,
  glBlendFunc,
  glBlendFuncSeparate,
  glDepthFunc,
  glSampleCoverage,
  glStencilFunc,
  glStencilFuncSeparate,
  glStencilOp,
  glStencilOpSeparate,
  glCreateBuffer,
  glDeleteBuffer,
  glBindBuffer,
  glBufferData,
  glBufferSubData,
  glAttachShader,
  glCompileShader,
  glCreateProgram,
  glCreateShader,
  glDeleteProgram,
  glDeleteShader,
  glDetachShader,
  glLinkProgram,
  glShaderSource,
  glUseProgram,
  glValidateProgram,
  glCullFace,
  glFrontFace,
  glLineWidth,
  glPolygonOffset,
  glDepthRange,
  glScissor,
  glViewport,
  glDrawArrays,
  glDrawElements,
  glVertexAttribDivisor,
  glDrawArraysInstanced,
  glDrawElementsInstanced,
  glDrawRangeElements,
  glDisableVertexAttribArray,
  glEnableVertexAttribArray,
  glGetUniformLocation,
  glUniform1f,
  glUniform2fv,
  glUniform3fv,
  glUniform4fv,
  glUniform1i,
  glUniform2iv,
  glUniform3iv,
  glUniform4iv,
  glUniform1ui,
  glUniform2uiv,
  glUniform3uiv,
  glUniform4uiv,
  glUniformMatrix2fv,
  glUniformMatrix3fv,
  glUniformMatrix4fv,
  glVertexAttribPointer,
  glVertexAttribIPointer,
  glBindVertexArray,
  glCreateVertexArray,
  glDeleteVertexArray,
  glActiveTexture,
  glBindTexture,
  glClear,
  glClearColor,
  glClearDepth,
  glClearStencil,
  glColorMask,
  glDepthMask,
  glStencilMask,
  glStencilMaskSeparate,
};
