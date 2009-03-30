float4x4 viewProjectionMatrix : VIEWPROJECTION;
float4x4 viewMatrix : VIEW;
float4x4 worldMatrix : WORLD;
float4 diffuseColor;
float explosion;
const float pi = 3.14159;

texture particleTexture;

sampler2D particleSampler = sampler_state
{
   Texture = (particleTexture);
};

struct VS_INPUT 
{
   float4 Position : POSITION0;
};

struct VS_OUTPUT 
{
   float4 Position : POSITION0;
   float2 Texture  : TEXCOORD0;
};

VS_OUTPUT vs_main( VS_INPUT Input )
{
   VS_OUTPUT Output;
   
   float3 pos = Input.Position;
   float g = pos.z / ( 10 * pi );

   float extend = g * 3.8f;

   pos.x = sin(g) * extend;
   pos.y = 0;   
   pos.z = cos(g) * extend;

   // add some randomization
   pos.x += sin( pos.z * g * 7 ) * 0.103 * extend;
   pos.y += cos( pos.z * g * 3 ) * 0.102 * extend * 1.5f;
   pos.z += cos( pos.z * g * 2 ) * 0.106 * extend;

   // transform to object space
   pos = mul( pos, worldMatrix );

   // transform to view space
   pos += 4.0f * (Input.Position.x * viewMatrix[0] + Input.Position.y * viewMatrix[1]);
   
   // sprite transformation
   Output.Position = mul( viewProjectionMatrix, float4(pos, 1) );
   
   // use xy as texture coordinate
   Output.Texture = Input.Position.xy;
   
   return Output;
}

float4 ps_main(float2 texCoord : TEXCOORD) : COLOR0
{
   return (1 - pow( dot(texCoord, texCoord), explosion ) ) * tex2D( particleSampler, texCoord ).a * diffuseColor;
}

technique Position
{
   pass Pass_0
   {
      DestBlend = ONE;
      SrcBlend = ONE;
      ZEnable = TRUE;
      ZWriteEnable = FALSE;
      CullMode = NONE;
      AlphaBlendEnable = TRUE;

      VertexShader = compile vs_2_0 vs_main();
      PixelShader = compile ps_2_0 ps_main();
   }
}