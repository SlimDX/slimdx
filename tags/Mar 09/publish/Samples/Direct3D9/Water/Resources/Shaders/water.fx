float4x4 ModelViewProj	: WORLDVIEWPROJ; //our world view projection matrix
float4x4 ModelWorld;
float4 eyePos;
float4 lightPos; 
float time;
 
texture texture0;
texture texture1;
 
sampler2D texSampler : TEXUNIT0 = sampler_state
{
	Texture	  = (texture0);
    MIPFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MINFILTER = LINEAR;
};

samplerCUBE cubeSampler : TEXUNIT1 = sampler_state
{
	Texture	  = (texture1);
    MIPFILTER = LINEAR;
    MAGFILTER = LINEAR;
    MINFILTER = LINEAR;
};
 
//application to vertex structure
struct a2v
{ 
    float4 position   : POSITION;
    float3 normal	  : NORMAL;
    float2 tex0       : TEXCOORD0;
    float3 tangent    : TANGENT;
    float3 binormal	  : BINORMAL;
};
 
//vertex to pixel shader structure
struct v2p
{
    float4 position	   : POSITION;
    float2 tex0        : TEXCOORD0;
    float2 tex1        : TEXCOORD1;
    float3 eyeVec      : TEXCOORD2;
    float3 lightVec    : TEXCOORD3;
    float att		   : TEXCOORD4;
};
 
//pixel shader to screen
struct p2f
{
    float4 color    : COLOR0;
};
 
//VERTEX SHADER
void vs( in a2v IN, out v2p OUT ) 
{
    //getting to position to object space
    OUT.position    = mul(IN.position, ModelViewProj);
 
    //getting the position of the vertex in the world
    float4 posWorld = mul(IN.position, ModelWorld); //IN.position;
 
    //getting vertex -> light vector
    float3 eye    = eyePos.xyz - posWorld.xyz;
    float3 light    = lightPos.xyz - posWorld.xyz;
 
    //calculating the binormal and setting the Tangent Binormal and Normal matrix
    float3x3 TBNMatrix = float3x3(IN.tangent, IN.binormal , IN.normal); 
 
    //setting the lightVector
    OUT.eyeVec = normalize(mul(TBNMatrix, eye));
    OUT.lightVec = normalize(mul(TBNMatrix, light));

    //float vHalf = normalize(eye, lightPos);
    //OUT.vHalf = mul(TBNMatrix, vHalf);
	
	OUT.att = 1/( 1 + ( 0.0001 * distance(lightPos.xyz, posWorld) ) );
	
    OUT.tex0 = IN.tex0;
    OUT.tex1 = IN.tex0;
}
 
//PIXEL SHADER
void ps( in v2p IN, out p2f OUT )
{
	float3 normal  = 2.0f * tex2D(texSampler, (0.2 * IN.tex0) + (time * 0.5)).rgb - 1.0f; //the normal map
	float3 normal1 = 2.0f * tex2D(texSampler, (1 * IN.tex0) + (time * 1)).rgb - 1.0f; //the normal2nd map
	float3 normal2 = 2.0f * tex2D(texSampler, (2 * IN.tex0) + (time * 2)).rgb - 1.0f; //the normal3rd map
	
	float3 eye   = normalize(IN.eyeVec); //our eye vector normalized
	
	float3 finalNormal = normalize(normal + normal1 * 2 + normal2 * 4);
	
	float3 reflectVector = reflect(eye, finalNormal); //getting the reflection vector and a surface to eye vector
	
	float4 color = texCUBE(cubeSampler, reflectVector); //our cube sampler
	
	float3 light = normalize(IN.lightVec);

	//calculating the specular component
	//float specular = pow(dot( normal, IN.vHalf) , 16);
	
	float diffuse = saturate(dot(finalNormal, light));
    
	//setting ds(diffuse * specular)Color
    	//float dsColor = 2.0 * (diffuse * specular) + 1.0; //last part is ambient

    	//multiply the attenuation with the color
	OUT.color = 2.0 * IN.att * color * diffuse;
	
}
 
technique water
{
    pass p0
    {
        vertexshader = compile vs_1_1 vs();
        pixelshader = compile ps_2_0 ps();
    }
} 