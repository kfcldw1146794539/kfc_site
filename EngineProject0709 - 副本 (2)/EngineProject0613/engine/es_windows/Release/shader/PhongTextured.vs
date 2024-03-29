#version 120
attribute vec3 aPos;
attribute vec3 aNormal;
attribute vec2 aTexCoords;

uniform highp mat4 kzProjectionCameraWorldMatrix;
uniform highp mat4 kzWorldMatrix;
uniform highp mat4 kzNormalMatrix;
uniform highp vec3 kzCameraPosition;
uniform mediump vec3 SpotLightPosition[2];
uniform mediump vec3 PointLightPosition[2];
uniform mediump float SpotLightCutoffAngle[2];

varying mediump vec3 vNormal;
varying mediump vec3 vViewDirection;
varying mediump vec3 vPointLightDirection[2];
varying mediump vec3 vSpotLightDirection[2];
varying mediump float vSpotCutoff[2];
varying mediump vec2 vTexCoord;

void main()
{
    precision mediump float;
   
    vec4 positionWorld = kzWorldMatrix * vec4(aPos.xyz, 1.0);
    vViewDirection = positionWorld.xyz - kzCameraPosition;
   
    vPointLightDirection[0] = positionWorld.xyz - PointLightPosition[0];
    vPointLightDirection[1] = positionWorld.xyz - PointLightPosition[1];
    vSpotLightDirection[0] = positionWorld.xyz - SpotLightPosition[0];
    vSpotLightDirection[1] = positionWorld.xyz - SpotLightPosition[1];
   
    vSpotCutoff[0] = cos(SpotLightCutoffAngle[0] * 3.14159 / 180.0);
    vSpotCutoff[1] = cos(SpotLightCutoffAngle[1] * 3.14159 / 180.0);
   
    vec4 N = kzNormalMatrix * vec4(aNormal, 1.0);
    vNormal = N.xyz;
    vTexCoord = aTexCoords;
    gl_Position = kzProjectionCameraWorldMatrix * vec4(aPos.xyz, 1.0);
}