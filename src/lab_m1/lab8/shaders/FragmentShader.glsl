#version 330

// Input
in vec3 world_position;
in vec3 world_normal;

// Uniforms for light properties
uniform vec3 light_direction;
uniform vec3 light_position;
uniform vec3 light_position2;
uniform vec3 eye_position;

uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;

uniform vec3 object_color;

// TODO(student): Declare any other uniforms
uniform int isSpotlight;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Define ambient, diffuse and specular light components
    float ambient_light = 0.25 * material_kd;

    vec3 N = normalize(world_normal);
    vec3 L = normalize(light_position - world_position);
    vec3 L2 = normalize(light_position2 - world_position);
    vec3 V = normalize(eye_position - world_position);

    float diffuse_light = material_kd * max(dot(N, L), 0.0);
    float diffuse_light2 = material_kd * max(dot(N, L2), 0.0);

    float specular_light = 0;
    // It's important to distinguish between "reflection model" and
    // "shading method". In this shader, we are experimenting with the Phong
    // (1975) and Blinn-Phong (1977) reflection models, and we are using the
    // Phong (1975) shading method. Don't mix them up!
    if (diffuse_light > 0)
    {
		vec3 H = normalize(L + V);
		specular_light = material_ks * pow(max(dot(H, N), 0.0), material_shininess);
    }

    float dist = length(light_position - world_position);
    float dist2 = length(light_position2 - world_position);

    float att = 1.0 / (dist * dist);
    float att2 = 1.0 / (dist2 * dist2);

    // TODO(student): If (and only if) the light is a spotlight, we need to do
    // some additional things.

    if(isSpotlight == 1) {
        float cut_off = radians(30);

        float spot_light = dot(-L, light_direction);
        float spot_light2 = dot(-L2, light_direction);

        float spot_light_limit = cos(cut_off);

        if(spot_light > spot_light_limit) {
			// Quadratic attenuation
            float linear_att = (spot_light - spot_light_limit) / (1.0f - spot_light_limit);
            att = pow(linear_att, 2);
		} else {
			att = 0;
		}

        if(spot_light2 > spot_light_limit) {
			// Quadratic attenuation
            float linear_att = (spot_light2 - spot_light_limit) / (1.0f - spot_light_limit);
            att2 = pow(linear_att, 2);
		} else {
			att2 = 0;
		}
    }

    // TODO(student): Compute the total light. You can just add the components
    // together, but if you're feeling extra fancy, you can add individual
    // colors to the light components. To do that, pick some vec3 colors that
    // you like, and multiply them with the respective light components.

    float light = ambient_light + att * (diffuse_light + specular_light);
    float light2 = ambient_light + att2 * (diffuse_light2 + specular_light);

    // TODO(student): Write pixel out color
	vec3 colour = object_color * light + object_color * light2;
	out_color = vec4(colour, 1.f);

}
