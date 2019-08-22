#version 120
attribute vec3 aPos;
attribute vec3 aNormal;
attribute vec2 aTexCoords;

varying vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

varying mediump vec3 vNormal;



void main()
{
    TexCoords = aTexCoords;    
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}