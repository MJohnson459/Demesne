#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragmentColor;

// Interpolated values from the vertex shaders
in vec3 UV;
 
// Ouput data
out vec3 color;
 
// Values that stay constant for the whole mesh.
uniform sampler2DArray textureSampler;

void main()
{

	// Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices
    // color = fragmentColor;

	// Output color = color of the texture at the specified UV
	color = texture(textureSampler, UV).rgb + fragmentColor;
	//color = texture(textureSampler, vec3(0.5,0.5,1)).rgb + fragmentColor;
	//color = texture(textureSampler, UV).rgb + UV;

}