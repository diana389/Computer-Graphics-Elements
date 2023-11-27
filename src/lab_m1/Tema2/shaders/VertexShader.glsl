#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform vec3 object_color;
uniform int damage;
uniform int component;

// Output
out vec3 color;
flat out int damage_out;

void main()
{
	vec3 v_pos = v_position;

    switch(damage)
	{
		case 1:
			switch(component)
			{
				case 3: // turret
					if(v_pos.y > 0.48 && v_pos.x < -0.13)
						v_pos = vec3(v_pos.x, 0.43, v_pos.z);
					break;
				case 4:  // gun
					if(v_pos.z > 0.9)
						v_pos = vec3(v_pos.x, v_pos.y, 0.9);
					break;
			}
			break;
		case 2:
			switch(component)
			{
				case 3: // turret
					if(v_pos.y > 0.43 && v_pos.x < 0.13)
						v_pos = vec3(v_pos.x, 0.41, v_pos.z);
					break;
				case 4:  // gun
					if(v_pos.z > 0.8)
						v_pos = vec3(v_pos.x, v_pos.y, 0.8);
					break;
			}
			break;
	}

    vec3 world_position = vec3(Model * vec4(v_pos, 1.0));
    vec3 world_normal = normalize(mat3(Model) * v_normal);
    vec3 L = normalize(light_position - world_position);
    vec3 V = normalize(eye_position - world_position);

    float ambient_light = material_kd * 0.25;

    // Compute diffuse light component
    float diffuse_light = material_kd * max(dot(world_normal, L), 0.0);

    // Compute specular light component
    float specular_light = 0;

    if (diffuse_light > 0)
    {
        specular_light = material_ks * pow(max(dot(world_normal, normalize(L + V)), 0.0), material_shininess);
    }

    float dist = length(light_position - world_position);
	float Kc = 1.0;;
	float Kl = 0.02;
	float Kq = 0.001;
    float att = 1.0 / (Kc + Kl * dist + Kq * dist * dist);

	float emisive_light = 0.3f;

	// Compute light
    float light = emisive_light + ambient_light + att * (diffuse_light + specular_light);

    color = object_color * light;
    damage_out = damage;

    // Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_pos, 1.0);
}
