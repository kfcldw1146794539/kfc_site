#version 120
varying mediump	vec3 FragPos;
varying mediump vec2 TexCoords;
varying mediump vec3 TangentLightPos;
varying mediump vec3 TangentLightPos1;
varying mediump vec3 TangentViewPos;
varying mediump vec3 TangentFragPos;

uniform vec4 Ambient;
uniform vec4 Diffuse;
uniform vec4 SpecularColor;
uniform float SpecularExponent;

uniform sampler2D texture_diffuse1;
uniform sampler2D texture_normal1;

void main()
{           
     // obtain normal from normal map in range [0,1]
    vec3 normal = texture2D(texture_normal1, TexCoords).rgb;
    // transform normal vector to range [-1,1]
    normal = normalize(normal * 2.0 - 1.0);  // this normal is in tangent space
   
    // get diffuse color
    vec3 color =texture2D(texture_diffuse1,TexCoords).rgb;// vec3(0.5,0.5,0.5);
    // ambient
    vec3 ambient = 0.1 * color;
    // diffuse
    vec3 lightDir = normalize(TangentLightPos - TangentFragPos);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(TangentViewPos - TangentFragPos);
    vec3 reflectDir = reflect(-lightDir, normal);
    vec3 halfwayDir = normalize(lightDir + viewDir);  
    float spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
	
	{
	   vec3 lightDir1 = normalize(TangentLightPos1 - TangentFragPos);
       float diff1 = max(dot(lightDir1, normal), 0.0);
	   diffuse += diff1 * color;

        vec3 reflectDir1 = reflect(-lightDir1, normal);
        vec3 halfwayDir1 = normalize(lightDir1 + viewDir);  
        spec += pow(max(dot(normal, halfwayDir1), 0.0), 32.0);
	}


    vec3 specular = vec3(0.2) * spec;
    gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}