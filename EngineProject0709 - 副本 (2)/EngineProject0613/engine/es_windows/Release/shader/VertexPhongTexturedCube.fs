#version 120
uniform lowp float BlendIntensity;
uniform lowp vec4 Ambient;
varying lowp vec3 vN;
varying mediump vec3 vViewDirection;

varying mediump vec2 vTexCoord;
uniform sampler2D texture_diffuse1;

varying lowp vec3 vAmbDif;
varying lowp vec3 vSpec;

uniform lowp samplerCube TextureCube;
uniform lowp vec4        CubemapColor;

void main()
{
    precision lowp float;       
    lowp vec3 color = vec3(0.0); 

    lowp vec4 baseColor = texture2D(texture_diffuse1, vTexCoord).rgba;

    color += baseColor.rgb;

    vec3 R = reflect(normalize(vViewDirection), normalize(vN));
    color += textureCube(TextureCube, R).rgb * CubemapColor.rgb;

    gl_FragColor = vec4(color, baseColor.a) * BlendIntensity;
}