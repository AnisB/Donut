#version 410 

// Scenes matrices
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;

uniform mat4 uProjectionMatrix;
uniform mat4 uWorldToCameraMatrix;

in vec3 position;

out vec3 eyeDirection;

void main() 
{
    mat4 inverseProjection = inverse(projection);
    mat3 inverseModelview = transpose(mat3(view));
    vec3 unprojected = (inverseProjection * vec4(position,1.0)).xyz;
    eyeDirection = inverseModelview * unprojected;

    gl_Position = vec4(position,1.0);
} 