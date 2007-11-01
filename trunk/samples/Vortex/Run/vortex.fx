/*

% Description of my shader.
% Second line of description for my shader.

keywords: material classic

date: YYMMDD

*/

shared float4x4 WorldMatrix;
shared float4x4 ViewMatrix;
shared float4x4 ProjectionMatrix;
shared float4x4 WorldViewProjectionMatrix;

shared float Clock;

texture ScreenTexture;
sampler2D ScreenSampler = sampler_state
{
    texture = <ScreenTexture>;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MIPFILTER = LINEAR;
};


texture DiffuseMap;
sampler2D DiffuseSampler = sampler_state
{
    texture = <DiffuseMap>;
    ADDRESSU = WRAP;
    ADDRESSV = WRAP;
    MINFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MIPFILTER = LINEAR;
};


struct VS_INPUT
{
    float3 Position : POSITION;
    float2 UV : TEXCOORD0;
};

struct VS_OUTPUT_20 
{
    float4 Position : POSITION;
    float2 UV : TEXCOORD0;
    float3 LocalSpace : TEXCOORD1;
};

VS_OUTPUT_20 mainVS(VS_INPUT In)
{
    VS_OUTPUT_20 Out;
    
    float3 WorldPosition = mul( float4( In.Position.xyz, 1 ), WorldMatrix );
    Out.Position = mul( mul( float4( WorldPosition, 1 ), ViewMatrix ), ProjectionMatrix );
    
    Out.LocalSpace = float3(In.UV.x - 0.5, 0.5 - In.UV.y,0);
    Out.UV = In.UV;
    
    return Out;
}

float4 LocalToClipSpace( float3 local_space )
{
    return mul( float4( local_space, 1 ), WorldViewProjectionMatrix );
}

float2 ClipToScreenTextureSpace( float4 clip_space )
{
    float2 result;
    
    result.x = clip_space.x / clip_space.w;
    result.y = clip_space.y / clip_space.w;
    
    result.x = result.x * 0.5 + 0.5;
    result.y = result.y * 0.5 + 0.5;
    
    // Offset by half a texel
    result.x += 0.5 / 1024.0;
    result.y -= 0.5 / 1024.0;
    
    result.y = 1 - result.y;
    
    return result;
}

float2 RotatePoint( float2 pt, float angle )
{
    float2 result;
    float s;
    float c;
    sincos( angle, s, c );
    
    result.x = c * pt.x + s * pt.y;
    result.y =-s * pt.x + c * pt.y;
    
    return result;
}

float Ease(float a, float b, float t)
{
    float u = 1 - t;
    return b + (a-b)*u*u*u;
}

float4 mainPS(VS_OUTPUT_20 In) : COLOR 
{
    float distance_to_center;
    
    distance_to_center = length( In.LocalSpace * 2 );
    distance_to_center = clamp( distance_to_center, 0, 1 );
    
    float theta = Ease( 1, 0, distance_to_center ) * 2 * 3.14159 * sin(Clock);
    
    float3 rotated = In.LocalSpace;
    rotated.xy = RotatePoint( In.LocalSpace.xy, theta );
    
    float2 screen_texcoord = ClipToScreenTextureSpace( LocalToClipSpace( rotated ) ).xy;

    //return float4(screen_texcoord,0,1);
    return tex2D( ScreenSampler, screen_texcoord );
}
 
technique technique0 {
	pass p0 {
		VertexShader = compile vs_2_0 mainVS();
		PixelShader = compile ps_2_0 mainPS();
	}
}
