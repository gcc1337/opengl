#version 330 core
in vec3 vColor;
in vec3 vPos;
out vec4 FragColor;

uniform float circ_radius;

void main()
{
	if(length(vPos) < circ_radius)
	{
		FragColor = vec4(vColor, 1.0);
	}
	else{
		discard;
	}

}