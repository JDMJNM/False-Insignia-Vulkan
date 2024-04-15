#version 450

layout(location = 0) in vec2 texCoords;

layout(location = 0) out vec4 outFrag;

layout(binding = 1) uniform sampler2D tex;

void main() {
	outFrag = texture(tex, texCoords);
}

