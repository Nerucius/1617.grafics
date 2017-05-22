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
    vec3 V = normalize(viewDir.xyz);
    vec3 N = normalize(norm);

    vec3 R = reflect(-L, N);
    //vec3 H = normalize(L+V);

    float NdotL = max(dot(N, L),0);
    //float NdotH = max(dot(N, L),0);
    float VdotR = max(dot(R, V),0);
    float VdotN = max(dot(V, N),0);

    // sillouete
    float sl = clamp(VdotN*4,0,1);
    sl = step(0.95, sl);

    amb = vec3(0);
    diff = vec3(0);
    spec = vec3(0);

    // Diffuse
    const float A = 0.1;
    const float B = 0.3;
    const float C = 0.6;
    const float D = 1.0;

    float df = NdotL;
    if (df < A) df = A;
    else if (df < B) df = B;
    else if (df < C) df = C;
    else df = D;

    // Specular
    float sf = VdotR;
    sf = pow(sf, mat.shine);
    sf = step(0.9, sf);
    //spec = vec3(sf);

    // Ambient + sillouete
    amb = mat.ka * l.ia + mat.ka*0.1*(1-sl) ;
    diff = mat.kd * l.id * df;
    spec = mat.ks * l.is * sf;

//    diff = vec3(1-sl);


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
