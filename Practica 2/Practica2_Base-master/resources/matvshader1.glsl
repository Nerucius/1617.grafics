#if __VERSION__<130
#define IN attribute
#define OUT varying
#else
#define IN in
#define OUT out
#endif

struct mat_spec{
    vec3 ka;
    vec3 kd;
    vec3 ks;
    float shine;
};

uniform mat_spec mat;

IN vec4 vPosition;
OUT vec4 color;

void main()
{
    gl_Position = vPosition;

    color.r = mat.kd.r;
    color.g = mat.kd.g;
    color.b = mat.kd.b;
    color.a = 1;
}
