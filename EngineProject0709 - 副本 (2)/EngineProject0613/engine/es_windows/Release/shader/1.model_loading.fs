
#version 120

precision mediump float;
varying vec2 TexCoords;



uniform lowp float BlendIntensity;
uniform lowp vec4 Emissive;

uniform lowp vec4 Ambient;
uniform lowp vec4 Diffuse;
uniform lowp vec4 SpecularColor;
uniform mediump float SpecularExponent;

uniform sampler2D texture_diffuse1;

void main()
{   
	vec3 ambient =  Ambient.rgb;
	vec3 diffuse =  Diffuse.rgb;
	vec3 specularColor = SpecularColor.rgb;
	vec4 baseColor = texture2D(texture_diffuse1, TexCoords);
	vec3 color = Diffuse.rgb + baseColor.rgb;
	gl_FragColor = texture2D(texture_diffuse1, TexCoords);
	//gl_FragColor = vec4(color, 1.0);
}