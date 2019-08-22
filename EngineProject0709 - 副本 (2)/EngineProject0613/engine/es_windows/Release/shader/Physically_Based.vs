#version 120
attribute vec3 aPos;
attribute vec3 aNormal;
attribute vec2 aTexCoords;
attribute vec3 aTangent;
attribute vec3 aBitangent;

varying mediump	vec3 FragPos;
varying mediump vec2 TexCoords;
varying mediump vec3 TangentLightPos;
varying mediump vec3 TangentLightPos1;
varying mediump vec3 TangentViewPos;
varying mediump vec3 TangentFragPos;

uniform highp mat4 kzProjectionCameraWorldMatrix;
uniform highp mat3 kzNormalMatrix;
uniform highp mat4 kzWorldMatrix;
uniform highp vec3 kzCameraPosition;
uniform mediump vec3 PointLightPosition[2];

varying vec3 lightPos;
varying vec3 lightPos1;
varying vec3 viewPos;

void main()
{
	lightPos=PointLightPosition[0];
	lightPos1=PointLightPosition[1];//vec3(100.0, 10.0, -100.0);
	viewPos=kzCameraPosition;//vec3(100.0, 10.0, 100.0);
    FragPos = vec3(kzWorldMatrix * vec4(aPos, 1.0));   
    TexCoords = aTexCoords;
    
   // mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(kzNormalMatrix * aTangent);
    vec3 N = normalize(kzNormalMatrix * aNormal);
    T = normalize(T - dot(T, N) * N);
    vec3 B = cross(N, T);
    
    mat3 TBN = transpose(mat3(T,aBitangent, N));    
    TangentLightPos = TBN * lightPos;
	TangentLightPos1= TBN * lightPos1;
    TangentViewPos  = TBN * viewPos;
    TangentFragPos  = TBN * FragPos;
        
    gl_Position = kzProjectionCameraWorldMatrix * vec4(aPos, 1.0);
}