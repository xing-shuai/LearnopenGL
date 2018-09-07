#version 130

in vec4 fragmentColor;
in vec2 fragmentPosition;
in vec2 fragmentUV;

out vec4 color;

//uniform float time;
uniform sampler2D mySampler;


void main(){
	vec4 textureColor = texture(mySampler,fragmentUV);

	//color = vec4(fragmentColor.r*(cos(fragmentPosition.x*1.2+time)+1.0)*0.5,
	//			 fragmentColor.g*(cos(fragmentPosition.y*2+time)+1.0)*0.5,
	//			 fragmentColor.b*(cos(fragmentPosition.x+time)+1.0)*0.5,
	//			 1.0);

	//color = textureColor + fragmentColor;
	color = textureColor;
}