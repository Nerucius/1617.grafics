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
uniform mat4 modelViewMat;
uniform mat4 projectionMat;

uniform Material mat;
uniform vec3 ambientLight;
uniform Light lights[MAX_LIGHTS];


vec3 lighting(Light l, vec3 pos, vec3 norm){
    vec3 s = normalize( l.pos.xyz - pos );
    vec3 v = normalize( -pos.xyz );
    vec3 r = reflect( -s, norm);

    vec3 ambient = l.ia * mat.ka;

    float sDotN = max( dot(s, norm), 0);
    vec3 diffuse = l.id * mat.kd * sDotN;

    vec3 spec = vec3(0);
    if(sDotN > 0){
        spec = l.is * mat.ks * pow( max(dot(r,v),0), mat.shine );
    }

    return ambient + diffuse + spec;
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


    //vec4 lightDir = normalize(lightPos - vPosition);
    //float cosTheta = clamp(dot(normalize(lightDir), vNormal), 0,1);
    //color.rgb = (cosTheta * mat.kd).rgb + mat.ka.rgb + ambientLight.rgb;
    color.a = 1;

    gl_Position = modelViewMat * vPosition;
}
