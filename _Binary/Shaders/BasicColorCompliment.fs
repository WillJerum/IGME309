#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool Complimentary = false;

out vec4 Fragment;

void main()
{

	vec3 result = Color;

	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
	{
		result = SolidColor;
	}
	
	if(Complimentary == true)
	{
		result = vec3(1.0, 1.0, 1.0) - result;
	}
	
	Fragment = vec4(result,1);
		
	return;
}
