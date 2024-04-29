#version 330 core

//outputs color in RGBA
out vec4 FragColor;

//inputs color from vert shader
in vec3 color;

void main() {
   FragColor = vec4(color, 1.0f);
}
