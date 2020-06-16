/**/
#version 430

layout(location = 0) out vec4 OutColor;

in vec4 DrawColor;
in vec2 DrawTexCoord;
in vec3 DrawNormal;
in vec3 DrawPos;

uniform vec3 Ka, Kd, Ks;
uniform float Ph, Trans;
uniform vec3 CamLoc;
uniform float Time;

vec3 Shade( vec3 P, vec3 N, vec3 L )
{
  vec3 V = normalize(P - CamLoc);
  vec3 color = vec3(0);
  // Ambient
  color += Ka;
 
  // Duffuse
  float nl = max(0.1, dot(N, L));

  color += Kd * nl;
    
  // Specular
  vec3 R = reflect(V, N);
  float rl = dot(R, L);
  if (rl > 0)
    color += Ks * pow(rl, Ph);

  return color;
}

void main( void )
{
  vec3 N = normalize(DrawNormal);
  vec3 L = normalize(vec3(sin(Time * 2), sin(Time) + 4, cos(Time * 2)));  // light source

  OutColor = vec4(DrawColor.rgb * Shade(DrawPos, N, L) * 8, Trans);
}
