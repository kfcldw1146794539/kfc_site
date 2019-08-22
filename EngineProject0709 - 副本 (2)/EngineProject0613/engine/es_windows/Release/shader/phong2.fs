

precision mediump float;


varying vec2 TexCoords;

varying vec3 Normal;  
varying vec3 FragPos;

uniform float BlendIntensity;
uniform vec4 Emissive;

uniform vec4 Ambient;
uniform vec4 Diffuse;
uniform vec4 SpecularColor;
uniform float SpecularExponent;

uniform vec3 viewPos;



uniform  vec3 Lposition;
uniform  vec3 Lambient;
uniform  vec3 Ldiffuse;
uniform  vec3 Lspecular;






void main()
{   
	vec3 ambient =  Lambient*Ambient.rgb;

	// diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(Lposition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = Ldiffuse * (diff * Diffuse.rgb);

	 // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), SpecularExponent);
    vec3 specular = Lspecular * (spec * SpecularColor.rgb);  

	vec4 result;
	result.rgb = (ambient + diffuse + specular + Emissive.rgb)*BlendIntensity;

	
	result.a = BlendIntensity;




	gl_FragColor = result;
}



