#version 120
uniform sampler2D texture_diffuse1;
uniform samplerCube TextureCube;

uniform mediump vec3 SpotLightDirection[2];
uniform mediump vec4 SpotLightColor[2];
uniform mediump vec3 SpotLightAttenuation[2];
uniform mediump float SpotLightExponent[2];

uniform mediump vec4 DirectionalLightColor[2];
uniform mediump vec3 DirectionalLightDirection[2];

uniform mediump vec4 PointLightColor[2];
uniform mediump vec3 PointLightAttenuation[2];

uniform mediump vec4 CubemapColor;
uniform mediump vec4 Ambient;
uniform mediump vec4 Diffuse;
uniform mediump vec4 SpecularColor;
uniform mediump float SpecularExponent;
uniform mediump float BlendIntensity;
uniform mediump vec4 Emissive;
uniform mediump float ReflectIntensity;

varying mediump vec3 vNormal;
varying mediump vec3 vViewDirection;
varying mediump vec3 vPointLightDirection[2];
varying mediump vec3 vSpotLightDirection[2];
varying mediump float vSpotCutoff[2];
varying mediump vec2 vTexCoord;

void main()
{
    precision mediump float;

    vec3 L[6];
    vec3 H[6];
    float LdotN, NdotH;
    float specular;
    vec3 lightColor;
    vec3 c;
    float d, attenuation;
   
    vec3 color = vec3(0.0);
    vec3 N = normalize(vNormal);
    vec3 V = normalize(vViewDirection);
    vec3 R = reflect(V, N);
   
    L[0] = normalize(-DirectionalLightDirection[0]);
    H[0] = normalize(-V + L[0]);
   
    L[1] = normalize(-vPointLightDirection[0]);
    H[1] = normalize(-V + L[1]);
   
    L[2] = normalize(-vSpotLightDirection[0]);
    H[2] = normalize(-V + L[2]);
   
    L[3] = normalize(-DirectionalLightDirection[1]);
    H[3] = normalize(-V + L[3]);
   
    L[4] = normalize(-vPointLightDirection[1]);
    H[4] = normalize(-V + L[4]);
   
    L[5] = normalize(-vSpotLightDirection[1]);
    H[5] = normalize(-V + L[5]); 
      
    vec4 baseColor =texture2D(texture_diffuse1,vTexCoord).rgba;//vec4(1.0,1.0,1.0,1.0); 
    vec3 diffuse = Diffuse.rgb * baseColor.rgb;
    color += Ambient.rgb * baseColor.rgb;
   
    // Apply directional light 0.
    if(length(DirectionalLightColor[0].rgb) > 0.01)
    {
        LdotN = max(0.0, dot(L[0], N));
        NdotH = max(0.0, dot(N, H[0]));
        specular = pow(NdotH, SpecularExponent);
        lightColor = (LdotN * diffuse) + SpecularColor.rgb * specular;
        lightColor *= DirectionalLightColor[0].rgb;
        color += lightColor;
    }
   
    // Apply directional light 1.
    if(length(DirectionalLightColor[1].rgb) > 0.01)
    {
        LdotN = max(0.0, dot(L[3], N));
        NdotH = max(0.0, dot(N, H[3]));
        specular = pow(NdotH, SpecularExponent);
        lightColor = (LdotN * diffuse) + SpecularColor.rgb * specular;
        lightColor *= DirectionalLightColor[1].rgb;
        color += lightColor;
    }
   
    // Apply point light 0.
    if(length(PointLightColor[0].rgb) > 0.01)
    {
        LdotN = max(0.0, dot(L[1], N));
        NdotH = max(0.0, dot(N, H[1]));
        specular = pow(NdotH, SpecularExponent);
        c = PointLightAttenuation[0];
        d = length(vPointLightDirection[0]);
        attenuation = 1.0 / max(0.001,(c.x + c.y * d + c.z * d * d));
        lightColor = (LdotN * diffuse) + SpecularColor.rgb * specular;
        lightColor *= attenuation;
        lightColor *= PointLightColor[0].rgb;
        color += lightColor;
    }

    // Apply point light 1.
    if(length(PointLightColor[1].rgb) > 0.01)
    {
        LdotN = max(0.0, dot(L[4], N));
        NdotH = max(0.0, dot(N, H[4]));
        specular = pow(NdotH, SpecularExponent);
        c = PointLightAttenuation[1];
        d = length(vPointLightDirection[1]);
        attenuation = 1.0 / max(0.001, (c.x + c.y * d + c.z * d * d));
        lightColor = (LdotN * diffuse) + SpecularColor.rgb * specular;
        lightColor *= attenuation;
        lightColor *= PointLightColor[1].rgb;
        color += lightColor;
    }
   
    // Apply spot light 0.
    if(length(SpotLightColor[0].rgb) > 0.01)
    {
        LdotN = dot(L[2], N);
        if(LdotN > 0.0)
        {
        LdotN = max(0.0, LdotN);
        NdotH = max(0.0, dot(N, H[2]));
        
            vec3 D = normalize(SpotLightDirection[0]);
            float spotEffect = dot(D, -L[2]);
            c = SpotLightAttenuation[0];
            d = length(L[2]);
            specular = pow(NdotH, SpecularExponent);
         
            if(spotEffect > vSpotCutoff[0])
            {
          spotEffect = pow(spotEffect, SpotLightExponent[0]);
             attenuation = spotEffect / (c.x + c.y * d + c.z * d * d);
          lightColor = (diffuse * LdotN) + SpecularColor.rgb * specular;
             lightColor *= attenuation;
             lightColor *= SpotLightColor[0].rgb;
             color += lightColor;
            }
        }
    }
   
    // Apply spot light 1.
    if(length(SpotLightColor[1].rgb) > 0.01)
    {
        LdotN = dot(L[5], N);
        if(LdotN > 0.0)
        {
        LdotN = max(0.0, LdotN);
        NdotH = max(0.0, dot(N, H[5]));
        
            vec3 D = normalize(SpotLightDirection[1]);
            float spotEffect = dot(D, -L[5]);
            c = SpotLightAttenuation[1];
            d = length(L[5]);
            specular = pow(NdotH, SpecularExponent);
         
            if(spotEffect > vSpotCutoff[1])
            {
          spotEffect = pow(spotEffect, SpotLightExponent[1]);
             attenuation = spotEffect / (c.x + c.y * d + c.z * d * d);
          lightColor = (diffuse * LdotN) + SpecularColor.rgb * specular;
             lightColor *= attenuation;
             lightColor *= SpotLightColor[1].rgb;
             color += lightColor;
            }
        }
    }   
    color += ReflectIntensity*textureCube(TextureCube, R).rgb* CubemapColor.rgb;//*vec3(1.0,1.0,1.0) ;
    color += Emissive.rgb;//vec3(0.1,0.1,0.1);
	// gl_FragColor = vec4(color, baseColor.a) * BlendIntensity;
    gl_FragColor.rgb = color * BlendIntensity;
    gl_FragColor.a = baseColor.a * BlendIntensity;
}