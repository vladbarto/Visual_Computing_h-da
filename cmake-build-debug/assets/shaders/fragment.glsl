#version 330 core

in vec3 colorVS;

//fragment shader output
out vec4 color;
uniform float animation;

in vec3 Normal, LightDir, ViewDir;
uniform vec3 matDiffuse, lightColor;
uniform vec3 lightColorAmbient;
uniform vec3 matEmissive;

uniform vec3 matSpecular;
uniform float matShininess;

void main(){
    color = vec4(colorVS, 1.0);

    // normalise everything necessary
    vec3 N = normalize(Normal);
    vec3 L = normalize(LightDir);

    // diffuse component
    float cosa = max(0.0, dot(N, L));
    vec3 DiffuseTerm = matDiffuse * lightColor;
    //color += vec4(DiffuseTerm * cosa, 1.0);

    // ambient emissive component
    vec3 AmbientEmissiveTerm = matEmissive + matDiffuse * lightColorAmbient;
    color += vec4(AmbientEmissiveTerm, 0.0);

    // specular component
    vec3 V = normalize(ViewDir);
    vec3 R = normalize(reflect(-L, N));

    float cosBeta = max(0.0, dot(R, V));
    float cosBetak = pow(cosBeta, matShininess);

    vec3 SpecularTerm = matSpecular * lightColor;
    color += vec4(SpecularTerm * cosBetak, 0.0);
}

