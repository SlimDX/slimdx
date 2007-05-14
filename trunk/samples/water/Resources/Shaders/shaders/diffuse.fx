float4x4 ModelViewProj;
float4 lightPos;

struct a2v
{ 
	float4 position : POSITION;
	float4 normal : NORMAL;
	float4 tex : TEXCOORD0;
};

struct v2p
{
	float4 position : POSITION;
	float4 color : COLOR0;
	float4 tex : TEXCOORD0;
};


void main( in a2v IN, out v2p OUT ) 
{
	OUT.position = mul(IN.position, ModelViewProj);
	float4 light = lit(dot(normalize((lightPos - IN.position)), IN.normal), 0, 10);
	OUT.color = light.yyyz;
	OUT.tex = IN.tex;
}

technique test
{
	pass p0
	{
		vertexshader = compile vs_2_0 main();
	}
}