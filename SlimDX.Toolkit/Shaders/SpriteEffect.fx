cbuffer Parameters : register(b0)
{
    row_major float4x4 MatrixTransform;
};

Texture2D<float4> Texture : register(t0);
sampler TextureSampler : register(s0);

void VS(inout float4 color : COLOR0,
        inout float2 texCoord : TEXCOORD0,
        inout float4 position : SV_Position)
{
    position = mul(position, MatrixTransform);
}

float4 PS(float4 color : COLOR0,
          float2 texCoord : TEXCOORD0) : SV_Target0
{
    return Texture.Sample(TextureSampler, texCoord) * color;
}