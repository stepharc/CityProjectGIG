#version 300 es

uniform mat4 mvp_matrix;

in vec4 a_position;

void main( void ){
	gl_Position = mvp_matrix * a_position;
}
