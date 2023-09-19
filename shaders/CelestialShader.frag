#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;

layout(location = 0) out vec4 outColor;

layout(binding = 1) uniform GlobalUniformBufferObject {
    vec3 selector;	// selector
    vec3 lightDir;
    vec4 lightColor;
    vec3 eyePos;
} gubo;

layout(binding = 2) uniform sampler2D tex;


void main() {
	vec3 Norm = normalize(fragNorm);
	vec3 EyeDir = normalize(gubo.eyePos - fragPos);
	vec3 LightDir = normalize(gubo.lightDir);
    vec3 LightColor = gubo.lightColor.rgb;
	vec3 Ambient = vec3(0.39f, 0.37f, 0.25f);

   
    // Very light specular component
    vec3 reflectDir = reflect(-LightDir, fragNorm);
    float spec = pow(max(dot(EyeDir, reflectDir), 0.0), 0.7); // Adjust the shininess value (32.0)
    vec3 specularColor = 0.3f * spec * gubo.lightColor.rgb;

    // Ambient, diffuse, and soft shadow
    float AmbientStrength = 0.3; // Adjust the ambient strength as needed
    float DiffuseIntensity = max(dot(Norm, LightDir), 0.0);
    float SoftShadowIntensity = smoothstep(0.0, 0.2, DiffuseIntensity); // Experiment with the values
    vec3 AmbientColor = AmbientStrength * Ambient;
    vec3 DiffuseColorFinal = DiffuseIntensity * Ambient;
    
    vec3 FinalColor = AmbientColor + SoftShadowIntensity * DiffuseColorFinal + specularColor;

    outColor = vec4(clamp(texture(tex,  fragUV).rgb * FinalColor, 0.0f, 1.0f), 1.0);


}
