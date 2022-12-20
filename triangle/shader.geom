#version 150

layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

in vec3 pass_colour[];
in float angle;

out vec3 finalColour;

uniform mat4 projectionViewMatrix;

const float size = 0.1;
void createVertex(vec3 offset) {
	vec4 actualOffset = vec4(offset, 0.0);
	vec4 worldPosition = gl_in[0].gl_Position + actualOffset;
	//gl_Position = projectionViewMatrix * worldPosition;
	gl_Position = worldPosition;
	finalColour = pass_colour[0];
	EmitVertex();
}

const float PI = 3.1415926535897932384626433832795;
const float wings = 0.2;
void main(void) {
	createVertex(vec3(cos(angle)*size, sin(angle)*size, 0.0));
    createVertex(vec3(cos(angle + PI - 0.2)*size, sin(angle + PI - 0.2)*size, 0.0));
    createVertex(vec3(cos(angle + PI + 0.2)*size, sin(angle + PI + 0.2)*size, 0.0));
	EndPrimitive();
}
