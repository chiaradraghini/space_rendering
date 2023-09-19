#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec3 fragNorm;
layout(location = 2) in vec2 fragUV;


layout(location = 0) out vec4 outColor;


layout(binding = 2) uniform sampler2D tex;

layout(binding = 1) uniform GlobalUniformBufferObject {
    vec3 selector;
	vec3 lightDir;
	vec4 lightColor;
	vec3 eyePos;
} gubo;


void main() {
	vec3 sunColor = 0.5f*texture(tex, fragUV).rgb; // Use the sun's texture or set a uniform color

    outColor = vec4(sunColor, 1.0f);
}