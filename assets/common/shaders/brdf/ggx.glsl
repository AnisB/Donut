#version 410

// Texture sampler
uniform sampler1D brdf;

// Convert a direction to euler angles
vec2 to_angles(vec3 _dir)
{
	return vec2(atan(_dir.y, _dir.x), acos(_dir.z));
}


// Given a pair of incoming/outgoing angles, look up the BRDF.
vec3 lookupBRDF(float _theta_o, float _phi_o, float _theta_i, float _phi_i)
{
	// Convert to halfangle / difference angle coordinates
	float theta_half, fi_half, theta_diff, fi_diff;
	
	std_coords_to_half_diff_coords(theta_in, fi_in, theta_out, fi_out,
		       theta_half, fi_half, theta_diff, fi_diff);


	// Find index.
	// Note that phi_half is ignored, since isotropic BRDFs are assumed
	int ind = phi_diff_index(fi_diff) +
		  theta_diff_index(theta_diff) * BRDF_SAMPLING_RES_PHI_D / 2 +
		  theta_half_index(theta_half) * BRDF_SAMPLING_RES_PHI_D / 2 *
					         BRDF_SAMPLING_RES_THETA_D;

	red_val = brdf[ind] * RED_SCALE;
	green_val = brdf[ind + BRDF_SAMPLING_RES_THETA_H*BRDF_SAMPLING_RES_THETA_D*BRDF_SAMPLING_RES_PHI_D/2] * GREEN_SCALE;
	blue_val = brdf[ind + BRDF_SAMPLING_RES_THETA_H*BRDF_SAMPLING_RES_THETA_D*BRDF_SAMPLING_RES_PHI_D] * BLUE_SCALE;

	
	if (red_val < 0.0 || green_val < 0.0 || blue_val < 0.0)
		fprintf(stderr, "Below horizon.\n");

}
// Fonction that returns the actual brdf given two directions 
vec3 getBRDF(vec3 _wo, vec3 _wi, vec3 _no)
{
	vec2 angles_o =  to_angles(_wo);
	vec2 angles_i =  to_angles(_wi);

	return lookupBRDF(angles_o.x, angles_o.y, angles_i.x, angles_i.y);
}

void main()
{

}
