#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vColor;
out vec3 vPos;

uniform float circ_center_x;
uniform float circ_center_y;

void main()
{
   vColor = aColor;
   vPos = aPos;
   gl_Position = vec4(aPos.x +circ_center_x, aPos.y +circ_center_y, aPos.z,  1.0);
}