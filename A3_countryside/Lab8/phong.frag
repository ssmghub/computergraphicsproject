#version 450 core

layout(location = 0) out vec4 fColour;

in vec3 col;
in vec3 nor;
in vec3 FragPosWorldSpace;
in vec4 FragPosProjectedLightSpace;

in vec2 tex;

uniform sampler2D shadowMap;
uniform sampler2D Texture;

uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 lightPos;

uniform vec3 lightDirection1;
uniform vec3 lightColour1;
uniform vec3 lightPos1;

uniform vec3 lightDirection2;
uniform vec3 lightColour2;
uniform vec3 lightPos2;

uniform int isSpotLight;

uniform vec3 camPos;


float shadowOnFragment(vec4 FragPosProjectedLightSpace)
{
	vec3 ndc = FragPosProjectedLightSpace.xyz / FragPosProjectedLightSpace.w;
	vec3 ss = (ndc+1)*0.5;

	float fragDepth = ss.z;

	float shadow = 0.f;
	float litDepth = texture(shadowMap, ss.xy).r;

	vec3 Nnor = normalize(nor);
	vec3 Ntolight = normalize(-lightDirection);
	float bias = max(0.05 * (1.0 - dot(Nnor, Ntolight)), 0.005);

	vec3 Ntolight2 = normalize(-lightDirection2);
	float bias2 = max(0.05 * (1.0 - dot(Nnor, Ntolight2)), 0.005);


	shadow = fragDepth > (litDepth+bias+bias2) ? 1.0 : 0.0;

	if(fragDepth > 1)
		shadow = 0.f; 

	return shadow;
	
}


float CalculateDirectionalIllumination()
{
	float ambient = 0.1f;
	
	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(-lightDirection);
	float diffuse = max(dot(Nnor, Nto_light), 0.0f);

	vec3 Nfrom_light = normalize(lightDirection);
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	float specular = pow(max(dot(NcamDirection, NrefLight), 0.0), 128);

	float shadow = shadowOnFragment(FragPosProjectedLightSpace); 

	float phong = ambient + (1.f-shadow) * (diffuse + specular);

	return phong; 

}

float CalculateDirectionalIllumination_1()
{
	float ambient = 0.1f;
	
	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(-lightDirection1);
	float diffuse = max(dot(Nnor, Nto_light), 0.0f);

	vec3 Nfrom_light = normalize(lightDirection1);
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	float specular = pow(max(dot(NcamDirection, NrefLight), 0.0), 128);

	float shadow = shadowOnFragment(FragPosProjectedLightSpace); 

	float phong = ambient + (1.f-shadow) * (diffuse + specular);

	return phong; 

}

float CalculateSpotIllumination()
{
	float ambient = 0.1f;
	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(lightPos2 - FragPosWorldSpace); 

	float diffuse = max(dot(Nnor, Nto_light), 0.0f);

	vec3 Nfrom_light = -Nto_light;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);

	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);

	float specular = pow(max(dot(NcamDirection, NrefLight), 0.0), 128);

	float d = length(lightPos2 - FragPosWorldSpace); 
	float attenuation = 1 / (1.5f + (0.05f * d) + (0.02f * d * d));

	float cutoff = radians(15); 
	float phi = cos(cutoff);

	vec3 NSpotDir = normalize(-lightDirection2);

	float theta = dot(Nto_light, NSpotDir); 

	float phong; 

	if(theta > phi)
	{
		phong =  (ambient + diffuse + specular) * attenuation;
	}
	else
	{
		phong =  ambient * attenuation;
	}
		
	return phong;

}

void main()
{
	float phong = CalculateDirectionalIllumination();
	float phong1 = CalculateDirectionalIllumination_1();
	float phong2 = isSpotLight == 1 ? CalculateSpotIllumination() : 0;

	vec3 color = lightColour * phong;
	vec3 color1 = lightColour1 * phong;
	vec3 color2 = lightColour2 * phong2;

	vec3 finalColor = color + color1 + color2;


	if(col == glm::vec3(0,0,0))
	{
		fColour = texture(Texture, tex); 
	}
	else
	{
		fColour = vec4(finalColor * col, 1.f);

	}

}