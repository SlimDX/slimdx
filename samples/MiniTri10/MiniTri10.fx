
struct VS_INPUT
{
    float4 Pos : POSITION;
};

struct PS_INPUT
{
    float4 Pos : SV_POSITION;
};

PS_INPUT VS(VS_INPUT input)
{
  PS_INPUT output = (PS_INPUT)0;
  output.Pos = input.Pos;
  return output;
}

float4 PS(PS_INPUT input) : SV_Target
{
  return float4(1.0,0.0,0.0,1.0);
}


//--------------------------------------------------------------------------------------
technique10 Render
{
  pass Pass0
  {
    SetVertexShader(CompileShader(vs_4_0,VS()));
    SetGeometryShader(NULL);
    SetPixelShader(CompileShader(ps_4_0,PS()));
  }
}
