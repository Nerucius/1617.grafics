#version 430

#define MAX_LIGHTS 3
#define POS 0
#define DIR 1
#define SPOT 2

// Interpolated surface data
in vec4 fragNormal;
in vec4 fragWorldPos;
in vec4 viewDir;

// Final Color Output
out vec4 FragColor;

struct Material{
    vec3 ka;
    vec3 kd;
    vec3 ks;
    float shine;
    float alpha;
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

uniform vec4 camPos;

/**
 * Phong-Shading using world-coordinates.
 * @param l: Light
 * @param pos: world-space position to calculate lighting on
 * @param norm: world-space surface normal at pos
 */
void lighting(Light l, vec3 pos, vec3 norm, out vec3 amb, out vec3 diff, out vec3 spec){
    vec3 L = normalize(l.pos.xyz - pos);
    vec3 V = normalize(camPos.xyz - pos);
    vec3 N = normalize(norm);

    vec3 R = reflect(-L, N);
    //vec3 H = normalize(L+V);

    float NdotL = max(dot(N, L),0);
    float VdotR = max(dot(R, V),0);
    //float NdotH = dot(N, H);
    float VdotN = max(dot(viewDir.xyz, N), 0);

    // fake Ambient occlusion
    float AO = clamp(VdotN/2.,0,1);

    // Distance attenuation
    float d = distance(pos, l.pos.xyz);
    float attf = 1. / 1. + (l.coef.x + l.coef.y * d + l.coef.z * d*d);


    amb = mat.ka * l.ia * attf ;
    diff =  mat.kd * l.id * NdotL * attf * AO;
    spec = mat.ks * l.is * pow (VdotR, mat.shine) * attf;

}



void main()
{

    vec3 ambientSum = ambientLight;
    vec3 diffuseSum = vec3(0);
    vec3 specularSum = vec3(0);
    vec3 amb, diff, spec;

    for(int i = 0; i< MAX_LIGHTS; i++){
        Light l = lights[i];

        lighting(l, fragWorldPos.xyz, fragNormal.xyz, amb, diff, spec);
        ambientSum += amb;
        diffuseSum += diff;
        specularSum += spec;
    }


    vec3 color = ambientSum + diffuseSum + specularSum;

    FragColor = vec4(color, mat.alpha);
}
