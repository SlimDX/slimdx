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
        public const string EmptyVertexShader = @"
struct GSIn {
	float3 PositionIndex : POSITIONINDEX;
	float4 GlyphColor : GLYPHCOLOR;
};

GSIn VS(GSIn Input) {
	return Input;
}
";
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
        public const string SimpleGeometryShader = @"
cbuffer ShaderConstants : register(b0) {
	float4x4 TransformMatrix : packoffset(c0);
};

Buffer<float4> tex0 : register(t0);

struct GSIn {
	float3 PositionIndex : POSITIONINDEX;
	float4 GlyphColor : GLYPHCOLOR;
};

struct GSOut {
	float4 Position : SV_Position;
	float4 GlyphColor : COLOR;
	float2 TexCoord : TEXCOORD;
};

[maxvertexcount(4)]
void GS(point GSIn Input[1], inout TriangleStream<GSOut> TriStream) {
	const float2 basePosition = Input[0].PositionIndex.xy;
	const uint glyphIndex = asuint(Input[0].PositionIndex.z);
	
	float4 texCoords = tex0.Load(uint2(glyphIndex*2, 0));
	float4 offsets = tex0.Load(uint2(glyphIndex*2+1, 0));
	
	GSOut Output;
	Output.GlyphColor = Input[0].GlyphColor;
	
	float4 positions = basePosition.xyxy + offsets;
	
	Output.Position = mul(TransformMatrix, float4(positions.xy, 0.0f, 1.0f));
	Output.TexCoord = texCoords.xy;
	TriStream.Append(Output);
	
	Output.Position = mul(TransformMatrix, float4(positions.zy, 0.0f, 1.0f));
	Output.TexCoord = texCoords.zy;
	TriStream.Append(Output);
	
	Output.Position = mul(TransformMatrix, float4(positions.xw, 0.0f, 1.0f));
	Output.TexCoord = texCoords.xw;
	TriStream.Append(Output);
	
	Output.Position = mul(TransformMatrix, float4(positions.zw, 0.0f, 1.0f));
	Output.TexCoord = texCoords.zw;
	TriStream.Append(Output);
	
	TriStream.RestartStrip();
}
";
        public const string ClippingGeometryShader = @"
cbuffer ShaderConstants : register(b0) {
	float4x4 TransformMatrix : packoffset(c0);
	float4 ClipRect : packoffset(c4);
};

Buffer<float4> tex0 : register(t0);

struct GSIn {
	float3 PositionIndex : POSITIONINDEX;
	float4 GlyphColor : GLYPHCOLOR;
};

struct GSOut {
	float4 Position : SV_Position;
	float4 GlyphColor : COLOR;
	float2 TexCoord : TEXCOORD;
	float4 ClipDistance : SV_ClipDistance;
};

[maxvertexcount(4)]
void GS(point GSIn Input[1], inout TriangleStream<GSOut> TriStream) {
	const float2 basePosition = Input[0].PositionIndex.xy;
	const uint glyphIndex = asuint(Input[0].PositionIndex.z);
	
	float4 texCoords = tex0.Load(uint2(glyphIndex*2, 0));
	float4 offsets = tex0.Load(uint2(glyphIndex*2+1, 0));
	
	GSOut Output;
	Output.GlyphColor = Input[0].GlyphColor;
	
	float4 positions = basePosition.xyxy + offsets;
	
	Output.Position = mul(TransformMatrix, float4(positions.xy, 0.0f, 1.0f));
	Output.TexCoord = texCoords.xy;
	Output.ClipDistance = ClipRect + float4(positions.xy, -positions.xy);
	TriStream.Append(Output);
	
	Output.Position = mul(TransformMatrix, float4(positions.zy, 0.0f, 1.0f));
	Output.TexCoord = texCoords.zy;
	Output.ClipDistance = ClipRect + float4(positions.zy, -positions.zy);
	TriStream.Append(Output);
	
	Output.Position = mul(TransformMatrix, float4(positions.xw, 0.0f, 1.0f));
	Output.TexCoord = texCoords.xw;
	Output.ClipDistance = ClipRect + float4(positions.xw, -positions.xw);
	TriStream.Append(Output);
	
	Output.Position = mul(TransformMatrix, float4(positions.zw, 0.0f, 1.0f));
	Output.TexCoord = texCoords.zw;
	Output.ClipDistance = ClipRect + float4(positions.zw, -positions.zw);
	TriStream.Append(Output);
	
	TriStream.RestartStrip();
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
