#version 330

const int MAX_POINT_LIGHTS = 4;

in vec2 texCoord0;
in vec3 normal0;
in vec3 worldPos0;

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

struct Attenuation
{
	float constant;
	float linear;
	float exponent;
};

struct PointLight
{
	BaseLight base;
	Attenuation attenuation;
	vec3 position;
	float range;
};

uniform vec3 ambientLight;
uniform vec3 baseColor;
uniform sampler2D sampler;
uniform sampler2D SpecularMapSampler;
uniform sampler2D NormalMapSampler;

//specular
uniform vec3 eyePos;
uniform float specularIntensity;
uniform float specularPower;

uniform DirectionalLight directionalLight;
uniform PointLight pointLights[MAX_POINT_LIGHTS];
uniform bool useTexture;
uniform bool useSpecularTexture;
uniform bool useNormalTexture;

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

vec4 calcDirectionalLight(DirectionalLight directionalLight, vec3 normal)
{
	return calcLight(directionalLight.base, -directionalLight.direction, normal);
}

vec4 calcPointLight(PointLight pointLight, vec3 normal)
{
	vec3 lightDirection = worldPos0 - pointLight.position;
	float distanceToPoint = length(lightDirection);
	
	if(distanceToPoint > pointLight.range)
		return vec4(0,0,0,0);
	
	lightDirection = normalize(lightDirection);
	
	vec4 color = calcLight(pointLight.base, lightDirection, normal);
	float attenuation = pointLight.attenuation.constant +
						pointLight.attenuation.linear * distanceToPoint + 
						pointLight.attenuation.exponent * distanceToPoint * distanceToPoint
						+ 0.0001;
						
	//0.0001 to make sure division is never by 0
	return color / attenuation;					
}

vec3 CalculateNormal(vec3 tangent, vec3 normal, vec2 texCoord)
{
vec3 newNormal = normal;
	

		vec3 binormal = cross(tangent, normal);
		binormal = normalize(binormal);
		
		//flip
		//binormal = -binormal;
		
		mat3 localAxis = mat3(tangent, binormal, normal);
	
		//vec3 sampledNormal = 2.0f * NormalMapSampler.Sample(m_TextureSampler,texCoord)-1.0f;
		//newNormal =  mul(sampledNormal, localAxis);

	
	return newNormal;
}


void main()
{   
	vec4 totalLight = vec4(ambientLight, 1);
	vec4 color = vec4(baseColor, 1);
	
	vec4 specularColor = vec4(0,0,0,0);

	if(useTexture)
	{
		vec4 textureColor = texture2D(sampler,texCoord0.xy);
		color *= textureColor;
	}

	vec3 normal = normalize(normal0);
	
	specularColor = calcSpecularLight(directionalLight.base, -directionalLight.direction, normal, texCoord0);
	
	
	totalLight += calcDirectionalLight(directionalLight, normal) + specularColor;
	
	//don't make uniform because GLSL doesn't handle it well in loops
	for(int i = 0; i < MAX_POINT_LIGHTS; i++)
	{	
		if(pointLights[i].base.intensity > 0)
			totalLight += calcPointLight(pointLights[i], normal);
	}
	
	fragColor =  color * totalLight;
}