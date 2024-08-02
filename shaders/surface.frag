#version 410 core

precision highp float;

layout (location=0) out vec4 FragColor;

uniform vec3 u_camera;
uniform float u_roughness;
uniform float u_metallic;

uniform sampler2D u_skybox;

in float v_height;
in vec3 v_normal;
in vec3 v_position;

#define PI 3.141592653589
float myatan(float z, float x) {
	float ang = atan(z, x);
	if(ang < 0.f) {
		ang = 2.f * PI + ang;
	}

	return ang;
}

void main() {
	vec3 sunpos = normalize(vec3(0.f, 1.f, -1.f));
	vec3 view = normalize(u_camera - v_position);
	vec3 halfway = normalize(sunpos + view);

	float f0 = 0.5f;
	float fresnel = f0 + (1.f - f0) * pow((1.f - max(dot(view, v_normal), 0.f)), 5.f);

	vec3 specular = vec3(0.8f) * pow(dot(halfway, v_normal), 1.f);
	vec3 ambient = vec3(0.5f);

	//float fresnel = 

	vec3 sample_light = normalize(reflect(-view, v_normal));
	float u = myatan(sample_light.z, sample_light.x) / (2 * PI);
	float v = acos(sample_light.y) / PI;
	vec4 texel = texture(u_skybox, vec2(u, v));

	//vec3 col = (specular + ambient) * vec3(0.53f, 0.8f, 0.92f);
	//vec3 color = fresnel * texel.rgb + (1.f - fresnel) * vec3(0.188f, 0.38f, 1.f);
	//vec3 color = fresnel * texel.rgb + specular + ambient;
	vec3 color = (specular + ambient) * vec3(0.34f, 0.7f, 1.f) + (texel.rgb * 0.2f);

	//vec3 gamma_corrected = pow(color, vec3(1.0 / 2.2));
	vec3 gamma_corrected = color;
	FragColor = vec4(gamma_corrected, 1.0);
	
	//FragColor = vec4(clamp(v_normal, vec3(0.f), vec3(1.f)), 1.0);
}















