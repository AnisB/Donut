#version 410 

// Scenes matrices
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 projection;
uniform mat4 modelviewprojection;
uniform vec3 camera_position;

in layout(location=0) vec3 position;

out vec3 eyeDirection;

void main() 
{
    eyeDirection = normalize(position);
	gl_Position = projection * view * vec4(position - camera_position, 1.0f);
} 