#version 410 core

layout (location=0) in vec3 a_position;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform float u_time;

out float v_height;
out vec3 v_normal;
out vec3 v_position;

#define PI 3.14159265f

void main()
{
	float dir[32] = float[](1.9891, 3.5761, 4.6339, 2.4745, 0.9422, 5.7762, 0.8844, 5.8013, 2.4747, 1.4858, 5.8211, 6.1632, 0.5832, 3.789, 2.9289, 3.5984, 3.5903, 4.4767, 2.6153, 0.8599, 3.5821, 1.4204, 0.1132, 1.9547, 5.3155, 1.1342, 2.6258, 1.6757, 3.9294, 2.7729, 3.2508, 0.1401);

	float t = u_time / 2.5f;

	float period = 1000.f;
	float amplitude = 25.f;
	vec3 apos = a_position;

	vec3 xnorm = vec3(0.0);
	vec3 znorm = vec3(0.0);

	for(int i=0;i<10;++i)
	{
		float s = (1.f / 22.f) * i;
		float p = period;
		float a = amplitude;

		int offset_idx = (i + 7) % 32;
		float offsetpos = dir[offset_idx] / (2.f * PI) * period;

		float x = cos(dir[i]);
		float z = sin(dir[i]);

		float j = a_position.x * x + a_position.z * z;
		apos.x += (s * p) * cos(2.f * PI * j / p + t + offsetpos) / (2.f * PI) * x;
		apos.z += (s * p) * cos(2.f * PI * j / p + t + offsetpos) / (2.f * PI) * z;
		apos.y += a * sin(2.f * PI * j / p + t + offsetpos);

		vec3 txnorm = vec3(0.f);
		txnorm.x += -s * x * x * sin(2.f * PI * j / p + t + offsetpos);
		txnorm.y += 2.f * PI * a * x / p * cos(2.f * PI * j / p + t + offsetpos);
		txnorm.z += -s * x * z * sin(2.f * PI * j / p + t + offsetpos);

		vec3 tznorm = vec3(0.f);
		tznorm.x += -s * x * z * sin(2.f * PI * j / p + t + offsetpos);
		tznorm.y += 2.f * PI * a * z / p * cos(2.f * PI * j / p + t + offsetpos);
		tznorm.z += -s * z * z * sin(2.f * PI * j / p + t + offsetpos);

		if(txnorm.x < 0.f) txnorm.x *= -1.f;
		if(tznorm.z < 0.f) tznorm.z *= -1.f;
		xnorm += txnorm;
		znorm += tznorm;

		amplitude *= 0.85;
		period *= 0.76;
	}

	v_normal = normalize(cross(znorm, xnorm));
	v_position = apos;

	gl_Position = u_projection * u_view * vec4(apos, 1.0);
}
