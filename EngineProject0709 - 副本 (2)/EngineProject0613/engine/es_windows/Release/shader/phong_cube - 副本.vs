#version 120
attribute vec3 aPos;
attribute vec3 aNormal;
uniform highp mat4 kzProjectionCameraWorldMatrix;
uniform highp mat4 kzWorldMatrix;
uniform highp mat4 kzNormalMatrix;
uniform highp vec3 kzCameraPosition;
uniform mediump vec3 PointLightPosition[2];
uniform mediump vec3 DirectionalLightDirection[1];
uniform lowp vec4 Emissive;
uniform lowp vec4 Ambient;

varying mediump vec3 vNormal;
varying mediump vec3 vViewDirection;
varying mediump vec3 vDirectionalLightDirection;
varying mediump vec3 vPointLightDirection[2];
varying lowp vec3 vBaseColor;

void main()
{
    precision mediump float;
    
    vec4 positionWorld = kzWorldMatrix * vec4(aPos.xyz, 1.0);
    vViewDirection = positionWorld.xyz - kzCameraPosition;
    
    vPointLightDirection[0] = positionWorld.xyz - PointLightPosition[0];
    vPointLightDirection[1] = positionWorld.xyz - PointLightPosition[1];
    vDirectionalLightDirection = vec3(1.0, 0.0, 0.0);
    if(length(DirectionalLightDirection[0]) > 0.01)
    {
        vDirectionalLightDirection = normalize(-DirectionalLightDirection[0]);
    }
    
    vec4 N = kzNormalMatrix * vec4(aNormal, 1.0);
    vNormal = N.xyz;
	//vec3(1.0, 0.0, 0.0)
    vBaseColor = Ambient.rgb + Emissive.rgb;
    gl_Position = kzProjectionCameraWorldMatrix * vec4(aPos.xyz, 1.0);
}