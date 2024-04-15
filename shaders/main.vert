#version 450

layout(location = 0) in uvec4 inData;

layout(location = 0) out vec2 texCoords;

const uint texMapCountH = 4;
vec2 getTexture(uint texI, uint coordI) {
	vec2 result = vec2(texI % texMapCountH, texI / texMapCountH);

	switch (coordI) {
		case 4:
			result.x += 1;
		case 3:
		case 1:
			result.y += 1;
			break;
		case 2:
			result.x += 1;
			break;
	}

	return result;
}


void main() {
	gl_Position = vec4(inData[0] + inData[3] & 100, inData[1] + inData[3] & 10, inData[2] + inData[3] & 1, 1.0);
	texCoords = getTexture(inData[3] & 11111000, gl_VertexIndex);
}

