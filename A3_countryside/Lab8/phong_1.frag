#version 450 core

layout (location = 0) out vec4 fColour;

in vec3 col;
in vec3 nor;
in vec3 FragPosWorldSpace;
in vec4 FragPosProjectedLightSpace;

uniform sampler2D shadowMap; 

uniform vec3 lightDirection;
uniform vec3 lightColour;
uniform vec3 lightPos;
uniform vec3 camPos;


float shadowOnFragment(vec4 FragPosProjectedLightSpace)
{
	vec3 ndc = FragPosProjectedLightSpace.xyz / FragPosProjectedLightSpace.w;
	vec3 ss = (ndc+1)*0.5;

	float fragDepth = ss.z;

	float shadow = 0.f;
	float litDepth = texture(shadowMap, ss.xy).r;

	//1
	vec3 Nnor = normalize(nor);
	vec3 Ntolight = normalize(-lightDirection);
	float bias = max(0.05 * (1.0 - dot(Nnor, Ntolight)), 0.005);

	shadow = fragDepth > (litDepth+bias) ? 1.0 : 0.0;

	if(fragDepth > 1)
		shadow = 0.f; 

	//1

	//shadow = fragDepth > litDepth ? 1.0 : 0.0;

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
	//float phong = ambient + diffuse + specular;

	return phong; 

}

float CalculatePositionalIllumination()
{
	float ambient = 0.1f;
	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(lightPos - FragPosWorldSpace); 
	float diffuse = max(dot(Nnor, Nto_light), 0.0f);
	vec3 Nfrom_light = -Nto_light;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	float specular = pow(max(dot(NcamDirection, NrefLight), 0.0), 128);

	float d = length(lightPos - FragPosWorldSpace); 
	// float d = length(lightPos, FragPosWorldSpace); 

	float attenuation = 1 / (1.5f + (0.05f * d) + (0.02f * d * d));
	//float attenuation = 1 / (0.015f + (0.05f * d) + (0.02f * d * d));

	float phong =  (ambient + diffuse + specular) * attenuation;
	// float phong =  (ambient + diffuse + specular);

	return phong; 

}

float CalculateSpotIllumination()
{
	float ambient = 0.1f;
	vec3 Nnor = normalize(nor);
	vec3 Nto_light = normalize(lightPos - FragPosWorldSpace); 
	float diffuse = max(dot(Nnor, Nto_light), 0.0f);
	vec3 Nfrom_light = -Nto_light;
	vec3 NrefLight = reflect(Nfrom_light, Nnor);
	vec3 camDirection = camPos - FragPosWorldSpace;
	vec3 NcamDirection = normalize(camDirection);
	float specular = pow(max(dot(NcamDirection, NrefLight), 0.0), 128);
	float d = length(lightPos - FragPosWorldSpace); 
	float attenuation = 1 / (1.5f + (0.05f * d) + (0.02f * d * d));
	//float attenuation = 1 / (0.015f + (0.05f * d) + (0.02f * d * d));
	//float attenuation = 1 / (15f + (0.05f * d) + (0.02f * d * d));

	float cutoff = radians(15); 
	//float cutoff = radians(30); 
	float phi = cos(cutoff);

	vec3 NSpotDir = normalize(-lightDirection);

	float theta = dot(Nto_light, NSpotDir); 
	//float theta = dot(Nfrom_light, NSpotDir); 

	float phong; 

	if(theta > phi) // why not 2*phi???
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
	//float phong = CalculatePositionalIllumination();
	//float phong = CalculateSpotIllumination();
	fColour = vec4(phong * col * lightColour, 1.f);

}
