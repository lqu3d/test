#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec2 vertexUV;

out vec3 vcolor;
out vec2 UV;

uniform mat4 MVP;

void main(){
	gl_Position = MVP * vec4(vertexPosition_modelspace,1);
	vcolor = vertexColor;
	UV = vertexUV;
}
