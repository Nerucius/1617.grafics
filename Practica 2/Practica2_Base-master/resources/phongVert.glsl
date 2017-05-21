#version 430

// Per-Vertex parameters
in vec4 vPosition;
in vec4 vNormal;

out vec4 fragNormal;
out vec4 fragWorldPos;

// Uniforms
uniform vec4 vrp;
uniform mat4 modelViewMat;
uniform mat4 projectionMat;


void main(){
    // Iterpolate Normals and Position over Surface
    fragNormal = vNormal;
    fragWorldPos = vPosition;

    gl_Position = projectionMat * modelViewMat  * vPosition;
}
