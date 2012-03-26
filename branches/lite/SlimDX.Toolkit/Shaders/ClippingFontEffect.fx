cbuffer ShaderConstants : register(b0)
{
	row_major float4x4 TransformMatrix : packoffset(c0);
	float4 ClipRect : packoffset(c4);
};

SamplerState sampler0 : register(s0);
Texture2D<float> tex0 : register(t0);

struct VSIn 
{
	float4 Position : POSITION;
	float4 GlyphColor : GLYPHCOLOR;
};

struct VSOut
{
	float4 Position : SV_Position;
	float4 GlyphColor : COLOR;
	float2 TexCoord : TEXCOORD;
	float4 ClipDistance : CLIPDISTANCE;
};

VSOut VS(VSIn Input)
{
	VSOut Output;
	
	Output.Position = mul(TransformMatrix, float4(Input.Position.xy, 0.0f, 1.0f));
	Output.GlyphColor = Input.GlyphColor;
	Output.TexCoord = Input.Position.zw;
	Output.ClipDistance = ClipRect + float4(Input.Position.xy, -Input.Position.xy);
	
	return Output;
}

struct PSIn 
{
	float4 Position : SV_Position;
	float4 GlyphColor : COLOR;
	float2 TexCoord : TEXCOORD;
	float4 ClipDistance : CLIPDISTANCE;
};

float4 PS(PSIn Input) : SV_Target
{
	clip(Input.ClipDistance);
	
	float a = tex0.Sample(sampler0, Input.TexCoord);
	
	if(a == 0.0f)
		discard;
	
	return (a * Input.GlyphColor.a) * float4(Input.GlyphColor.rgb, 1.0f);
}