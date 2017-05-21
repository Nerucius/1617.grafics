#version 430

// Per-Vertex parameters
in vec4 vPosition;
in vec4 vNormal;

out vec4 worldPos;
out vec4 fragNormal;
out vec4 fragPos;
out vec4 camFragPos;

// Uniforms
uniform vec4 vrp;
uniform vec4 camPos;
uniform mat4 modelViewMat;
uniform mat4 projectionMat;


void main(){

    fragPos = modelViewMat * vPosition;
    camFragPos = modelViewMat * camPos;

    fragNormal = vNormal;

    worldPos = vPosition;

    gl_Position = projectionMat * modelViewMat  * vPosition;
}
