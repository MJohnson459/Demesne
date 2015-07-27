#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
// Notice that the "1" here equals the "1" in glVertexAttribPointer
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec3 UV;

uniform mat4 MVP;

// Output data ; will be interpolated for each fragment.
out vec3 fragmentColor;

void main(){
	// Output position of the vertex, in clip space : MVP * position
    vec4 v = vec4(vertexPosition_modelspace,1); // Transform an homogeneous 4D vector, remember ?
    gl_Position = MVP * v;

	// The color of each vertex will be interpolated
    // to produce the color of each fragment
    fragmentColor = vertexColor;

	// UV of the vertex. No special space for this one.
    UV = vertexUV;
}

