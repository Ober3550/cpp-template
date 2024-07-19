#version 330 core

layout (location = 0) in vec3 Pos;
layout (location = 1) in vec3 Norm;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

out vec3 Normal;
out vec3 fragPos;

void main(void) {
	gl_Position = projection * view * model * vec4(Pos, 1.0);
	fragPos = vec3(model * vec4(Pos, 1.0));
	Normal = mat3(transpose(inverse(model))) * Norm;
}
