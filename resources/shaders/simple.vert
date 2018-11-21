#version 150
#extension GL_ARB_explicit_attrib_location : require
// vertex attributes of VAO
layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;

//Matrix Uniforms as specified with glUniformMatrix4fv
uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 NormalMatrix;


// Assignment 3
uniform vec3 SunPosition;
uniform vec3 DiffuseColor;
uniform float ShaderMode;


out vec3 pass_Normal;
out vec3 pass_VertexViewPosition;
out vec3 pass_LightSourceViewPosition;
out vec3 pass_DiffuseColor;
out float pass_ShaderMode;



void main(void)
{
	gl_Position = (ProjectionMatrix  * ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0);
	pass_Normal = (NormalMatrix * vec4(in_Normal, 0.0)).xyz;
	
	// Assignment 3
	pass_VertexViewPosition = vec3((ViewMatrix * ModelMatrix) * vec4(in_Position, 1.0));
	pass_LightSourceViewPosition = SunPosition;
	pass_DiffuseColor = DiffuseColor;
	pass_ShaderMode= ShaderMode;
}
