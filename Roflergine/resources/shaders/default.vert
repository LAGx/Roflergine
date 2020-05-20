#version 330				
				
layout (location = 0) in vec3 pos;	
layout (location = 1) in vec2 uv;	
layout (location = 2) in vec3 in_normal;
					
out vec4 vertexColor;
out vec2 pixelPointer;
out vec3 vNormal;

uniform mat4 model;		
uniform mat4 view;
uniform mat4 projection;
			
void main(){

	gl_Position = projection * view * model * vec4(pos, 1.0f);	
	pixelPointer = uv;

	vNormal = mat3(transpose(inverse(model))) * in_normal;
}					