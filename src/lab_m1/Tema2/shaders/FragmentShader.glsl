#version 330

// Input
// TODO(student): Get values from vertex shader

in vec3 color;
flat in int damage_out;

// Output
layout(location = 0) out vec4 out_color;

void main()
{
    if(damage_out > 0)
	{
        float darkening_factor = 0.9f / damage_out;
		out_color = vec4(color * darkening_factor, 1);
	}
    else 
        out_color = vec4(color, 1);
    
}
