#version 330				


struct AmbientLightParameters{
	vec3 colour;
	float intensity; 
};

struct DirectionalLightParameters{
	vec3 colour;
	float intensity; 
	vec3 direction; 
};
			
in vec4 vertexColor;
in vec2 pixelPointer;
in vec3 vNormal;

out vec4 colour;

uniform sampler2D theTexture;
uniform AmbientLightParameters ambientLightParam;
uniform DirectionalLightParameters directionalLightParam;
void main(){		

	vec4 ambientInfluence = vec4(ambientLightParam.colour, 1.0f) * ambientLightParam.intensity;

	float diffuseFactor = max(dot(normalize(vNormal), normalize(directionalLightParam.direction)), 0.0f);
	vec4 diffuseColor = vec4(directionalLightParam.colour, 0.0f) * directionalLightParam.intensity * diffuseFactor;

	colour = texture(theTexture, pixelPointer) * (ambientInfluence + diffuseColor);					
}					