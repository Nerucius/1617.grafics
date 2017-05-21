#version 430

#define MAX_LIGHTS 3
#define POS 0
#define DIR 1
#define SPOT 2

in vec4 worldPos;
in vec4 fragNormal;
in vec4 fragPos;
in vec4 camFragPos;

out vec4 FragColor;

struct Material{
    vec3 ka;
    vec3 kd;
    vec3 ks;
    float shine;
};

struct Light{
    int enabled;
    int type;
    vec4 pos;
    vec4 dir;
    vec3 ia;
    vec3 id;
    vec3 is;
    vec3 coef;
};

uniform Material mat;
uniform vec3 ambientLight;
uniform Light lights[MAX_LIGHTS];


void lighting(Light l, vec3 pos, vec3 norm, out vec3 amb, out vec3 diff, out vec3 spec){

    vec3 L = normalize(l.pos.xyz - camFragPos.xyz);
    vec3 V = normalize(- worldPos.xyz);

    vec3 N = normalize(norm);
    vec3 R = reflect(L, N);

    // Distance attenuation
    float d = distance(worldPos, l.pos);
    float attf = 1. / 1. + (l.coef.x + l.coef.y*d + l.coef.z*d*d);


    float lDotN = dot(L,N);

    diff *=0;
    diff += step(0.0, lDotN) * vec3(0,.1,0);
    diff += step(0.2, lDotN) * vec3(0,.1,0);
    diff += step(0.6, lDotN) * vec3(0,.1,0);
    diff += step(0.9, lDotN) * vec3(0,.1,0);
    diff += step(0.98, lDotN) * vec3(0,.1,0);

//    amb = mat.ka * l.ia * attf;
//    diff = mat.kd * l.id * dot(L,N) * attf;
//    spec = mat.ks * l.is * pow ( max(dot(V,R),0), mat.shine) * attf;


}



void main()
{

    vec3 ambientSum = ambientLight;
    vec3 diffuseSum = vec3(0);
    vec3 specularSum = vec3(0);
    vec3 amb, diff, spec;

    for(int i = 0; i< MAX_LIGHTS; i++){
        Light l = lights[i];

        lighting(l, worldPos.xyz, fragNormal.xyz, amb, diff, spec);
        ambientSum += amb;
        diffuseSum += diff;
        specularSum += spec;

    }


    vec3 color = ambientSum + diffuseSum + specularSum;

    FragColor = vec4(color, 1);
}
