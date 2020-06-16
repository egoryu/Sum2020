/**/
#version 430

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec2 DrawTexCoord;

layout(binding = 0) uniform sampler2D Texture0;
uniform bool IsTexture0;

void main( void )
{
  OutColor = texture(Texture0, DrawTexCoord);
}
