#version 300 es

precision mediump float;
 
in vec3 v_color;
in vec2 fragCoord;

out vec4 fragColor;

void main() {
  fragColor = vec4(v_color, 1.0);
}
