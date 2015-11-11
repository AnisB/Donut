#version 410 

vec3 sample_sphere[16] = vec3[](vec3( 0.5381, 0.1856,-0.4319), vec3( 0.1379, 0.2486, 0.4430),
  vec3( 0.3371, 0.5679,-0.0057), vec3(-0.6999,-0.0451,-0.0019),
  vec3( 0.0689,-0.1598,-0.8547), vec3( 0.0560, 0.0069,-0.1843),
  vec3(-0.0146, 0.1402, 0.0762), vec3( 0.0100,-0.1924,-0.0344),
  vec3(-0.3577,-0.5301,-0.4358), vec3(-0.3169, 0.1063, 0.0158),
  vec3( 0.0103,-0.5869, 0.0046), vec3(-0.0897,-0.4940, 0.3287),
  vec3( 0.7119,-0.0154,-0.0918), vec3(-0.0533, 0.0596,-0.5411),
  vec3( 0.0352,-0.0631, 0.5460), vec3(-0.4776, 0.2847,-0.0271)
);

out vec4 frag_color;
uniform sampler2D albedo;
uniform sampler2D normal;
uniform sampler2D specular;
uniform sampler2D position;
uniform sampler2D depth;
uniform sampler2D random;
uniform int width;
uniform int lenght;

in vec2 texCoord;

void main()
{ 
  const float total_strength = 1.0;
  const float base = 0.2;
  
  const float area = 0.075;
  const float falloff = 0.000001;
  
  const float radius = 0.01;
  
  const int samples = 16;

  vec3 randomV = normalize( texture(random, texCoord * 8).rgb );
  
  float depthV = texture(depth, texCoord).r;
 
  vec3 positionV = vec3(texCoord, depthV);
  vec3 normalV = texture(normal, texCoord).xyz;
  
  float radius_depth = radius/depthV;
  float occlusion = 0.0;
  for(int i=0; i < samples; i++) 
  {
  
    vec3 ray = radius_depth * reflect(sample_sphere[i], randomV);
    vec3 hemi_ray = positionV + sign(dot(ray,normalV)) * ray;
    
    float occ_depth = texture(depth, clamp(hemi_ray.xy, 0.0,1.0)).r;
    float difference = depthV - occ_depth;
    
    occlusion += step(falloff, difference) * (1.0-smoothstep(falloff, area, difference));
  }
  
  float ao = 1.0 - total_strength * occlusion * (1.0 / samples);
  frag_color =  vec4(vec3(ao),1.0);

}
