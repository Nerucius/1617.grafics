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

struct Light{
    vec4 pos;
    vec4 ia;
    vec4 id;
    vec4 is;
    vec3 attn;
};

uniform Material mat;
uniform vec3 ambientLight;


IN vec4 vPosition;
IN vec4 vNormal;
OUT vec4 color;

//vec4 lightDir = vec4(0.75,0.5,0,0);

vec4 lightPos = vec4(-.5,+.5,+.5,1);

void main()
{
    gl_Position = vPosition;

    vec4 lightDir = normalize(lightPos - vPosition);

    float cosTheta = clamp(dot(normalize(lightDir), vNormal), 0,1);

    color.rgb = (cosTheta * mat.kd).rgb + mat.ka.rgb + ambientLight.rgb;
    color.a = 1;
}
