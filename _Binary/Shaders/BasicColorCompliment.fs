#version 330

in vec3 Color;

uniform vec3 SolidColor = vec3(-1,-1,-1);
uniform bool Complimentary = false;

out vec4 Fragment;

void main()
{
	if(SolidColor.r != -1.0 && SolidColor.g != -1.0 && SolidColor.b != -1.0)
	{
		Color = SolidColor;
	}
	
	if(Complimentary == true)
	{
		Color = vec3(1.0f, 1.0f, 1.0f) - Color;
	}
	
	Fragment = vec4(Color,1);
		
	return;
}
