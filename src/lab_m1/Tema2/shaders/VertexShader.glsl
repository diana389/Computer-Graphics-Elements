#version 330

// Input
layout(location = 0) in vec3 v_position;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;

// Uniform properties
uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;
uniform float Time;

uniform vec3 light_position;
uniform vec3 eye_position;
uniform float material_kd;
uniform float material_ks;
uniform int material_shininess;
uniform vec3 object_color;

// Output
out vec3 color;

void main()
{
    vec3 world_position = vec3(Model * vec4(v_position, 1.0));
    vec3 world_normal = normalize(vec3(Model * vec4(v_normal, 0.0)));
    vec3 L = normalize(light_position - world_position);
    vec3 V = normalize(eye_position - world_position);

    float ambient_light = material_kd * 0.25;

    // Compute diffuse light component
    float diffuse_light = material_kd * max(dot(world_normal, L), 0.0);

    // Compute specular light component
    float specular_light = 0;

    if (diffuse_light > 0)
    {
        specular_light = material_ks * object_color.r * pow(max(dot(world_normal, normalize(L + V)), 0.0), material_shininess);
    }

    // Compute light
    float light = ambient_light + diffuse_light + specular_light;

    color = object_color * light;

    // Compute gl_Position
    gl_Position = Projection * View * Model * vec4(v_position, 1.0);
}
