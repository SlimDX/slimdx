// VectorModel.fx
// Renders vector styled models.
// Original effect and design by Trent Polack.

float4x4 ViewMatrix;
float4x4 ProjectionMatrix;
float4 InstanceData[20];

struct VSInput
{
	float2 position : POSITION;
	float4 color	: COLOR0;
	float instance	: TEXCOORD;
};

struct VSOutput
{
	float4 position : POSITION;
	float4 color	: COLOR0;
	float alpha		: TEXCOORD0;
};

VSOutput VectorModelVertexShader( VSInput input )
{
	VSOutput output = (VSOutput)0;
	
	float4 instance = InstanceData[input.instance];
	float r = instance.z;
	
	float4 col1 = float4( cos( r ),		-sin( r ),	0,	0 );
	float4 col2 = float4( sin( r ),		cos( r ),	0,	0 );
	float4 col3 = float4( 0,			0,			1,	0 );
	float4 col4 = float4( instance.x,	instance.y,	0,	1 );

	float4x4 world = float4x4( col1, col2, col3, col4 );
	
	float4 worldPosition = mul( float4( input.position.x, input.position.y, 0, 1 ), world );
	float4 viewPosition = mul( worldPosition, ViewMatrix );
	
	output.position = mul( viewPosition, ProjectionMatrix );
	output.color = input.color;
	output.alpha = instance.w;
	
	return output;
}

float4 VectorModelPixelShader( VSOutput input ) : COLOR0
{
	return( float4( input.color.rgb, input.color.a * input.alpha ) );
}

technique VectorModelTechnique
{
	pass P0
	{
		VertexShader = compile vs_2_0 VectorModelVertexShader();
		PixelShader = compile ps_2_0 VectorModelPixelShader();
	}
}