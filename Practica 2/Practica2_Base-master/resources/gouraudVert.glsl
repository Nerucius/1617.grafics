#version 430

#define MAX_LIGHTS 3
#define POS 0
#define DIR 1
#define SPOT 2

// Per-Vertex parameters
in vec4 vPosition;
in vec4 vNormal;

// Fragment-shader output
out vec4 color;

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

// Uniforms
uniform vec4 vrp;
uniform vec4 camPos;
uniform mat4 modelViewMat;
uniform mat4 projectionMat;

uniform Material mat;
uniform vec3 ambientLight;
uniform Light lights[MAX_LIGHTS];


/**
 * Phong-Shading using world-coordinates.
 * @param l: Light
 * @param pos: world-space position to calculate lighting on
 * @param norm: world-space surface normal at pos
 */
vec3 lighting(Light l, vec3 pos, vec3 norm){
    vec3 L = normalize(l.pos.xyz - pos);
    vec3 V = normalize(camPos.xyz - pos);
    vec3 N = normalize(norm);

    vec3 R = reflect(-L, N);

    float NdotL = max(dot(N, L),0);
    float VdotR = max(dot(R, V),0);

    vec3 amb = mat.ka * l.ia;
    vec3 diff = mat.kd * l.id * NdotL;
    vec3 spec = mat.ks * l.is * pow ( VdotR, mat.shine);

    // Distance attenuation
    float d = distance(pos, l.pos.xyz);
    float attf = 1. / 1. + (l.coef.x + l.coef.y*d + l.coef.z*d*d);

    return (amb + diff + spec) * attf;
}


void main(){

    color.rgb = ambientLight;

    for(int i = 0; i < MAX_LIGHTS; i++){
        Light l = lights[i];
        if (l.enabled == 0)
            continue;

        // Directional type light: Place at infitiny, and no attenuation
        if(l.type == DIR){
            l.pos.xyz *= 1e16;
            l.coef = vec3(0);
        }

        color.rgb += lighting(l, vPosition.xyz, vNormal.xyz);
    }

    color.a = 1;

    gl_Position = projectionMat * modelViewMat  * vPosition;
}
