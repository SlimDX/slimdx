float4x4 ModelViewProj; //our world view projection matrix
float4x4 ModelViewIT; //our inverse transpose matrix
float4x4 ModelWorld; //our world matrix
float4 lightPos; //our light position
float4 vEye;

sampler2D texSampler0 = sampler_state
{
	MIPFILTER = LINEAR;
	MAGFILTER = LINEAR;
	MINFILTER = LINEAR;
};
sampler2D texSampler1 = sampler_state
{
	MIPFILTER = LINEAR;
	MAGFILTER = LINEAR;
	MINFILTER = LINEAR;
};

//application to vertex structure
struct a2v
{ 
	float4 position : POSITION;
	float4 normal	: NORMAL;
	float2 tex0		: TEXCOORD0;
	float4 tangent	: TANGENT;
};

//vertex to pixel shader structure
struct v2p
{
	float4 position : POSITION;
	float4 color	: COLOR0;
	float2 tex0		: TEXCOORD0;
	float2 tex1		: TEXCOORD1;
	float3 lightVec : TEXCOORD2;
};

//pixel shader to screen
struct p2f
{
	float4 color	: COLOR0;
};

//constant materials
const float4 diffuseMaterial	= float4( 1.0, 1.0, 1.0, 1.0 );
const float4 specularMaterial	= float4( 1.0, 0.5, 0.5, 0.5);
const float4 ambient			= float4( 1.0, 1.0, 1.0, 1.0);
//VERTEX SHADER
void vs( in a2v IN, out v2p OUT ) 
{
    OUT.position	= mul( IN.position, ModelViewProj );
    float4 posWorld = mul(IN.position, ModelWorld);
    ModelViewIT		= transpose( ModelViewIT );    
    
    float4 tangent	= mul(float4(IN.tangent.xyz, 0.0), ModelWorld);
    float4 normal	= mul(float4(IN.normal.xyz, 0.0), ModelWorld);
    float3 binormal = cross(normal.xyz, tangent.xyz);
    
    float3 light	= normalize( lightPos - posWorld);
    float3 eye		= normalize (vEye - light );
    float3 vHalf	= normalize( eye - lightPos );
    
    float3 L = float3(dot(tangent, light), 
                      dot(binormal, light.xyz), 
                      dot(normal, light));
    float3 H = float3(dot(tangent, vHalf), 
                      dot(binormal, vHalf.xyz), 
                      dot(normal, vHalf));

    float diffuse	= dot( normal, L );
    float specular	= pow( dot(normal, H), 32 );
    
	OUT.color = 2.0 * (diffuse * diffuseMaterial + specular * specularMaterial) + 2.0 + ambient;
    
    OUT.lightVec = L;
    
	OUT.tex0 = IN.tex0;
	OUT.tex1 = IN.tex0;
}

//PIXEL SHADER
void ps( in v2p IN, out p2f OUT )
{
	//calculate the color and the normal
	float4 color = tex2D(texSampler0, IN.tex0);
	float4 normal = tex2D(texSampler1, IN.tex1);
	
	//set the output color
	OUT.color = color * dot(normal, IN.lightVec) * IN.color;
}

technique test
{
	pass p0
	{
		vertexshader = compile vs_2_0 vs();
		pixelshader = compile ps_2_0 ps();
	}
}