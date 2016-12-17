#version 330 core
out vec4 FragColor;
in vec2 TexCoords;
in vec3 WorldPos;
in vec3 Normal;
in mat3 TBN;

// material parameters
uniform vec3 albedo;
uniform float metallic;
uniform float roughness;
uniform float ao;

// lights
uniform vec3 lightPositions[4];
uniform vec3 lightColors[4];

uniform vec3 camPos;
uniform float exposure;

const float PI    = 3.14159265359;

vec3 getNormal(vec3 worldNormal, vec3 tangentNormal)
{
    vec3 Q1  = dFdx(WorldPos);
    vec3 Q2  = dFdy(WorldPos);
    vec2 st1 = dFdx(TexCoords);
    vec2 st2 = dFdy(TexCoords);

    vec3 normal   = normalize(worldNormal);
    vec3 tangent  = normalize(Q1*st2.t - Q2*st1.t);
    vec3 binormal = -normalize(cross(normal, tangent));
    mat3 TBN      = mat3(tangent, binormal, normal);

    return normalize(TBN * tangentNormal);
}

float DistributionGGX(vec3 N, vec3 H, float roughness)
{
	float a = roughness*roughness;
	float a2 = a*a;
	float NdotH = max(dot(N, H), 0.0);
	float NdotH2 = NdotH*NdotH;
	
	float nom    = a2;
	float denom = (NdotH2 * (a2 - 1.0) + 1.0);
	denom = PI * denom * denom;
	
	return nom / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
	float r = (roughness + 1.0);
	float k = (r*r) / 8.0;

	float nom    = NdotV;
	float denom = NdotV * (1.0 - k) + k;
	
	return nom / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
	float ggx2 = GeometrySchlickGGX(NdotV, roughness);
	float ggx1 = GeometrySchlickGGX(NdotL, roughness);
	
	return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
	return F0 + (1.0 - F0) * pow(1.0 - cosTheta, 5.0);
}
// ----------------------------------------------------------------------------
vec3 fresnelSchlickRoughness(float cosTheta, vec3 F0, float roughness)
{
	return F0 + (max(vec3(1.0 - roughness), F0) - F0) * pow(1.0 - cosTheta, 5.0);
}



void main()
{		
    vec3 N = normalize(Normal);
	vec3 V = normalize(camPos - WorldPos);
	vec3 R = reflect(-V, N); 

    // NOTE(Joey): calculate color/reflectance at normal incidence
    // NOTE(Joey): if dia-electric (like plastic) use F0 as 0.04 and
    // if it's a metal, use their albedo color as F0 (metallic workflow)    
	vec3 F0 = vec3(0.04); // NOTE(Joey): base reflectance at incident angle for non-metallic (dia-conductor) surfaces 
	F0 = mix(F0, albedo, metallic);
    // NOTE(Joey): calculate reflectance w/ (modified for roughness) Fresnel
	vec3 F   = fresnelSchlickRoughness(max(dot(N, V), 0.0), F0, roughness);
	
    // NOTE(Joey): kS is equal to Fresnel
     vec3 kS = F;
	 // NOTE(Joey): for energy conservation, the diffuse and specular light can't
    // be above 1.0 (unless the surface emits light) so to preserve this
    // relationship the diffuse component (kD) equals 1.0 - kS.
	vec3 kD = vec3(1.0) - kS;
	// multiply kD by the inverse metalness such that only non-metals
    // have diffuse lighting, or a linear blend if partly metal (pure metals have
    // no diffuse light).
	kD *= 1.0 - metallic;	
    
    // first do ambient lighting (note that the next IBL tutorial will replace the ambient
    // lighting with environment lighting).
    vec3 ambient = vec3(0.01) * albedo * ao;
    
    // for every light, calculate their contribution to the reflectance equation
   vec3 Lo = vec3(0.0);
    for(int i = 0; i < 4; ++i) 
    {
        vec3 L = normalize(lightPositions[i] - WorldPos);
        vec3 H = normalize(V + L);
        float distance = length(lightPositions[i] - WorldPos);
        float attenuation = 1.0 / distance * distance;
        vec3 radiance = lightColors[i] * attenuation;
        
        // NDF
        float ndf = DistributionGGX(N, H, roughness);
        
        // Geometry
        float g = GeometrySmith(N, V, L, roughness);      
        
        // cook-torrance brdf
        vec3 nominator    = ndf * g * F;
        float denominator = 4 * max(dot(V, N), 0.0) * max(dot(L, N), 0.0) + 0.001; // 0.001 to prevent divide by zero.
        vec3 brdf = nominator / denominator;
            
        // NOTE(Joey): scale light by NdotL
        float NdotL = max(dot(N, L), 0.0);        

         // NOTE(Joey): reflectance equation
        
        Lo += (kD * albedo / PI + kS * brdf) * radiance * NdotL; 
    }   
    
    vec3 color = ambient + Lo;
	
	// NOTE(Joey): HDR tonemapping
	// color = vec3(1.0) - exp(-color * exposure);
	color = color / (color + vec3(1.0));
	// NOTE(Joey): gamma correct
	color = pow(color, vec3(1.0/2.2)); 
    
   
	FragColor = vec4(color, 1.0);
}
