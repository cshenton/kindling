#version 300 es

precision mediump float;

in vec3 v_color;
in vec2 fragCoord;

uniform float time;

out vec4 fragColor;

void main() {
  fragColor = vec4(v_color + vec3(sin(time), cos(time), 0.0), 1.0);
}
