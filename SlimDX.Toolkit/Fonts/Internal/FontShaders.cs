using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Runtime.InteropServices;
using SlimMath;
using System.Drawing;

namespace SlimDX.Toolkit
{
    static class FontShaders
    {
        public const string SimpleVertexShader = @"
cbuffer ShaderConstants : register(b0) {
    float4x4 TransformMatrix : packoffset(c0);
};

struct VSIn {
	float4 Position : POSITION;
	float4 GlyphColor : GLYPHCOLOR;
};

struct VSOut {
	float4 Position : SV_Position;
	float4 GlyphColor : COLOR;
	float2 TexCoord : TEXCOORD;
};

VSOut VS(VSIn Input) {
	VSOut Output;

	Output.Position = mul(TransformMatrix, float4(Input.Position.xy, 0.0f, 1.0f));
	Output.GlyphColor = Input.GlyphColor;
	Output.TexCoord = Input.Position.zw;

	return Output;
}
";
        public const string ClippingVertexShader = @"
cbuffer ShaderConstants : register(b0) {
	float4x4 TransformMatrix : packoffset(c0);
	float4 ClipRect : packoffset(c4);
};

struct VSIn {
	float4 Position : POSITION;
	float4 GlyphColor : GLYPHCOLOR;
};

struct VSOut {
	float4 Position : SV_Position;
	float4 GlyphColor : COLOR;
	float2 TexCoord : TEXCOORD;
	float4 ClipDistance : CLIPDISTANCE;
};

VSOut VS(VSIn Input) {
	VSOut Output;
	
	Output.Position = mul(TransformMatrix, float4(Input.Position.xy, 0.0f, 1.0f));
	Output.GlyphColor = Input.GlyphColor;
	Output.TexCoord = Input.Position.zw;
	Output.ClipDistance = ClipRect + float4(Input.Position.xy, -Input.Position.xy);
	
	return Output;
}
";
        public const string SimplePixelShader = @"
SamplerState sampler0 : register(s0);
Texture2D<float> tex0 : register(t0);

struct PSIn {
	float4 Position : SV_Position;
	float4 GlyphColor : COLOR;
	float2 TexCoord : TEXCOORD;
};

float4 PS(PSIn Input) : SV_Target {
	float a = tex0.Sample(sampler0, Input.TexCoord);
	
	if(a == 0.0f)
		discard;
	
	return (a * Input.GlyphColor.a) * float4(Input.GlyphColor.rgb, 1.0f);
}
";
        public const string ClippingPixelShader = @"
SamplerState sampler0 : register(s0);
Texture2D<float> tex0 : register(t0);

struct PSIn {
	float4 Position : SV_Position;
	float4 GlyphColor : COLOR;
	float2 TexCoord : TEXCOORD;
	float4 ClipDistance : CLIPDISTANCE;
};

float4 PS(PSIn Input) : SV_Target {
	clip(Input.ClipDistance);
	
	float a = tex0.Sample(sampler0, Input.TexCoord);
	
	if(a == 0.0f)
		discard;
	
	return (a * Input.GlyphColor.a) * float4(Input.GlyphColor.rgb, 1.0f);
}
";
    }
}
