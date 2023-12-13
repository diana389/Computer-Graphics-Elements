#version 330

// Input
in vec2 texcoord;

// Uniform properties
uniform sampler2D texture_1;
uniform sampler2D texture_2;
// TODO(student): Declare various other uniforms
uniform int isMix;
uniform float time;

// Output
layout(location = 0) out vec4 out_color;


void main()
{
    // TODO(student): Calculate the out_color using the texture2D() function.
    float coord = texcoord.x;

    if(time > 0.f)
        coord = texcoord.x + time;

    vec4 color1 = texture2D(texture_1, vec2(coord, texcoord.y));
    vec4 color2 = texture2D(texture_2, vec2(coord, texcoord.y));

    
    
    float alpha = color1.a;

    if (alpha < 0.5f) 
    {
	    discard;
    }

    if(isMix == 0)
	{
	    out_color = color1;
	}
    else {
	    out_color = vec4(mix(color1, color2, 0.5f).xyz, 1);
	}
}
