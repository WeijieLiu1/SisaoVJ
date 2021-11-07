#version 330

uniform vec4 color;
uniform sampler2D tex;
uniform vec2 seaPosition;
uniform int seaAnim;


in vec2 texCoordFrag;
out vec4 outColor;

void main()
{
	// Discard fragment if texture sample has alpha < 0.5
	// otherwise compose the texture sample with the fragment's interpolated color
	vec4 texColor;
	if(gl_FragCoord.y < seaPosition.y) 
	{
		float angle = float(seaAnim)*3200.0/720.0;
		float s =0.001* sin(-angle + 0.2*gl_FragCoord.x);
		texColor = texture(tex, vec2(texCoordFrag.x, texCoordFrag.y+s));
	}
	else
	{
		texColor = texture(tex, texCoordFrag);
		if(texColor.a < 0.5f)
			discard;
	}
	outColor = texColor;
}

