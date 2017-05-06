#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

struct Material{
    vec3 ka;
    vec3 kd;
    vec3 ks;
    float shine;
};

uniform Material mat;

IN vec4 vPosition;
OUT vec4 color;

void main()
{
    gl_Position = vPosition;

    color.rgb = mat.kd.rgb;
    color.a = 1;
}
