#version 140
attribute vec3 aPos;
attribute vec3 aNormal;



uniform highp mat4 kzProjectionCameraWorldMatrix;
uniform highp mat4 kzWorldMatrix;
uniform highp mat4 kzNormalMatrix;
uniform highp vec3 kzCameraPosition;


uniform mediump vec3 PointLightPosition[2];
uniform mediump vec4 PointLightColor[2];
uniform mediump vec3 PointLightAttenuation[2];
uniform mediump vec4 DirectionalLightColor[1];
uniform mediump vec3 DirectionalLightDirection[1];
uniform mediump float BlendIntensity;
uniform mediump vec4 Emissive;

uniform mediump vec4 Ambient;
uniform mediump vec4 Diffuse;
uniform mediump vec4 SpecularColor;
uniform mediump float SpecularExponent;

varying lowp vec4 vColor;

void main()
{
    precision mediump float;
    
    vec3 pointLightDirection[2];
    vec4 positionWorld = kzWorldMatrix * vec4(aPos.xyz, 1.0);
    vec3 V = normalize(positionWorld.xyz - kzCameraPosition);
    vec4 Norm = kzNormalMatrix * vec4(aNormal, 1.0);
    vec3 N = normalize(Norm.xyz);

    pointLightDirection[0] = positionWorld.xyz - PointLightPosition[0];
    pointLightDirection[1] = positionWorld.xyz - PointLightPosition[1];
    
    vec3 L[3];
    vec3 H[3];
    float LdotN, NdotH;
    float specular;
    vec3 c;
    float d, attenuation;
    
    vec3 vAmbDif = vec3(0.0);
    vec3 vSpec = vec3(0.0);
    
    L[0] = vec3(-1.0, 100.0, 0.0);
    if(length(DirectionalLightDirection[0]) > 0.01)
    {
        L[0] = normalize(-DirectionalLightDirection[0]);
    }
    H[0] = normalize(-V + L[0]);
    
    L[1] = normalize(-pointLightDirection[0]);
    H[1] = normalize(-V + L[1]);
    
    L[2] = normalize(-pointLightDirection[1]);
    H[2] = normalize(-V + L[2]);

    vAmbDif += Ambient.rgb;
  
    // Apply directional light 0.
    {
        LdotN = max(0.0, dot(L[0], N));
        NdotH = max(0.0, dot(N, H[0]));
        specular = pow(NdotH, SpecularExponent);
        vAmbDif += (LdotN * Diffuse.rgb) * DirectionalLightColor[0].rgb;
        vSpec += SpecularColor.rgb * specular * DirectionalLightColor[0].rgb;
    }
    
    // Apply point light 0.
    {
        LdotN = max(0.0, dot(L[1], N));
        NdotH = max(0.0, dot(N, H[1]));
        specular = pow(NdotH, SpecularExponent);
        c = PointLightAttenuation[0];
        d = length(pointLightDirection[0]);
        attenuation = 1.0 / max(0.001, (c.x + c.y * d + c.z * d * d));
        vAmbDif += (LdotN * Diffuse.rgb) * attenuation * PointLightColor[0].rgb;
        vSpec +=  SpecularColor.rgb * specular * attenuation * PointLightColor[0].rgb;
    }

    // Apply point light 1.
    {
        LdotN = max(0.0, dot(L[2], N));
        NdotH = max(0.0, dot(N, H[2]));
        specular = pow(NdotH, SpecularExponent);
        c = PointLightAttenuation[1];
        d = length(pointLightDirection[1]);
        attenuation = 1.0 / max(0.001, (c.x + c.y * d + c.z * d * d));
        vAmbDif += (LdotN * Diffuse.rgb) * attenuation * PointLightColor[1].rgb;
        vSpec +=  SpecularColor.rgb * specular * attenuation * PointLightColor[1].rgb;
    }

   // vColor.rgb = (vAmbDif.rgb + vSpec.rgb + Emissive.rgb) * BlendIntensity;
	vColor = vec4(0.1,0.1,0.1,0.7);
    //vColor.a = BlendIntensity;
    gl_Position = kzProjectionCameraWorldMatrix * vec4(aPos.xyz, 1.0);
}