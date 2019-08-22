#version 120
attribute vec3 aPos;
attribute vec3 aNormal;
attribute vec2 aTexCoords;

uniform highp mat4 kzProjectionCameraWorldMatrix;
uniform highp mat4 kzWorldMatrix;
uniform highp mat4 kzNormalMatrix;
uniform highp vec3 kzCameraPosition;


varying mediump vec2 vTexCoord;
uniform mediump vec2 TextureOffset;
uniform mediump vec2 TextureTiling;

uniform lowp vec4 PointLightColor[2];
uniform mediump vec3 PointLightAttenuation[2];
uniform mediump vec3 PointLightPosition[2];

uniform lowp float BlendIntensity;
uniform lowp vec4 Emissive;
uniform lowp vec4 Ambient;
uniform lowp vec4 Diffuse;
uniform lowp vec4 SpecularColor;
uniform mediump float SpecularExponent;

varying mediump vec3 vViewDirection;
varying lowp vec3 vAmbDif;
varying lowp vec3 vSpec;
varying lowp vec3 vN; 
void main()
{
    precision mediump float;
   
    gl_Position = kzProjectionCameraWorldMatrix * vec4(aPos.xyz, 1.0);  
    vec4 positionWorld = kzWorldMatrix * vec4(aPos.xyz, 1.0);
    vViewDirection = positionWorld.xyz - kzCameraPosition;
    vec3 V = normalize(vViewDirection);
    vec4 Norm = kzNormalMatrix * vec4(aNormal, 0.0);
    vN = normalize(Norm.xyz);

    vec3 L = vec3(1.0, 0.0, 0.0);
    vec3 H = vec3(1.0, 0.0, 0.0);
    float LdotN, NdotH;
    float specular;
    vec3 c;
    float d, attenuation;
    vAmbDif = Ambient.rgb;
    vSpec = vec3(0.0);    
    vec3 pointLightDirection;  
    vec3 spotLightDirection;

   for (int i = 0; i < 1; ++i)
    {
        pointLightDirection = positionWorld.xyz - PointLightPosition[i];
        L = normalize(-pointLightDirection);
        H = normalize(-V + L);
        LdotN = max(0.0, dot(L, vN));
        NdotH = max(0.0, dot(vN, H));
        specular = pow(NdotH, SpecularExponent);
        c = PointLightAttenuation[i];
        d = length(pointLightDirection);
        attenuation = 1.0 / max(0.001, (c.x + c.y * d + c.z * d * d));        
        vAmbDif += (LdotN * Diffuse.rgb) * attenuation * PointLightColor[i].rgb;
        vSpec +=  SpecularColor.rgb * specular * attenuation * PointLightColor[i].rgb;
        
    }
   vSpec += Emissive.rgb;

  vTexCoord = aTexCoords /** TextureTiling + TextureOffset*/;
}