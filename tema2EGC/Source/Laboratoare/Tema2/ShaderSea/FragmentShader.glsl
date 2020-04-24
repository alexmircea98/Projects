#version 330

// TODO: get values from fragment shader

in vec3 normal;
in vec3 color;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

layout(location = 0) out vec4 out_color;



void main()
{
	// TODO: write pixel out color
	out_color = vec4(color, 1);
}