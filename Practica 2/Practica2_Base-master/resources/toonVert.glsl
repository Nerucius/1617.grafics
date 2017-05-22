#version 430

// Per-Vertex parameters
in vec4 vPosition;
in vec4 vNormal;

out vec4 fragNormal;
out vec4 fragWorldPos;
out vec4 viewDir;

// Uniforms
uniform vec4 vrp;
uniform mat4 modelViewMat;
uniform mat4 projectionMat;


void main(){
    // Iterpolate Normals and Position over Surface
    fragNormal = vNormal;
    fragWorldPos = vPosition;

    // De-project a constant orthogonal vector into the screen
    viewDir = vec4(0,0,1,0) * modelViewMat;

    gl_Position = projectionMat * modelViewMat  * vPosition;
}
