#version 330

// TODO: get vertex attributes from each location

layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_coord;
layout(location = 3) in vec3 v_normal;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

// TODO: output values to fragment shader
out vec3 normal;
out vec2 coord;
out vec3 color;

void main()
{
	color = Time * v_color;
	if (color.x < 0.2) color.xyz += 0.8;
	normal = v_normal;
	coord = v_coord;
	normal.y = color.y / 3.0;
	vec4 pos = Projection * View * Model * vec4(v_position, 1.0);	
	gl_Position = pos;
	
}
