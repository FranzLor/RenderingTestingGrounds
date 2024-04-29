#version 330 core

//positions
layout (location = 0) in vec3 aPos;
//colors
layout (location = 1) in vec3 aColor;

//outputs color for frag shader
out vec3 color;

//scale of verts
uniform float scale;

void main() {
   gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
   color = aColor;
}