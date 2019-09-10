#version 330

in vec2 texCoord0;
in mat3 tbnMatrix;
in vec3 worldPos0;
in vec3 normy;

out vec4 fragColor;

struct BaseLight
{
	vec3 color;
	float intensity;
};

struct DirectionalLight
{
	BaseLight base;
	vec3 direction;
};


//samplers 
uniform sampler2D DiffuseMapSampler;
uniform sampler2D SpecularMapSampler;
uniform sampler2D NormalMapSampler;

//base
uniform vec3 baseColor;
uniform bool useTexture;

//specular
uniform vec3 eyePos;
uniform float specularIntensity;
uniform float specularPower;
uniform bool useSpecularTexture;


//normal mapping
uniform bool useNormalTexture;

uniform DirectionalLight directionalLight;

vec4 calcLight(BaseLight base, vec3 direction, vec3 normal)
{
	//attenuation
	float diffuseFactor = dot(normal, -direction);
	
	vec4 diffuseColor = vec4(0,0,0,0); 
	
	if(diffuseFactor > 0)
	{
		diffuseColor = vec4(base.color, 1.0) * base.intensity * diffuseFactor;
		
	}
	
	return diffuseColor;
}

vec4 calcSpecularLight(BaseLight base, vec3 direction, vec3 normal, vec2 texCoord)
{
		//specular
		vec4 specularColor = vec4(0,0,0,0);
		vec3 directionToEye = normalize(eyePos - worldPos0);
		vec3 reflectDirection = normalize(reflect(direction, normal));
		
		float specularFactor = dot(directionToEye,reflectDirection);
		specularFactor = pow(specularFactor, specularPower);
		
		if(specularFactor > 0)
		{
			specularColor = vec4(base.color, 1.0) * specularIntensity * specularFactor;
			
			if(useSpecularTexture)
				specularColor *= texture2D(SpecularMapSampler,texCoord.xy).r;
			
		
		}
		
		return specularColor;
}

vec4 calcDirectionalLight(DirectionalLight dirLight, vec3 normal)
{
	return calcLight(dirLight.base, -dirLight.direction, normal);
}


void main()
{   
	vec4 totalLight = vec4(0,0,0, 1);
	vec4 color = vec4(baseColor, 1);
	vec4 specularColor = vec4(0,0,0,0);
	
	if(useTexture)
	{
		vec4 textureColor = texture2D(DiffuseMapSampler,texCoord0.xy);
		color *= textureColor;
	}
	
	vec3 normal = normy;
	
	//if(useNormalTexture)
		//normal = normalize(tbnMatrix * (2 * texture2D(NormalMapSampler,texCoord0.xy).xyz - 1));

	if(useSpecularTexture)
		specularColor = calcSpecularLight(directionalLight.base, -directionalLight.direction, normal, texCoord0);
	
	totalLight += calcDirectionalLight(directionalLight, normal) + specularColor;
	fragColor =  color * totalLight;
}
