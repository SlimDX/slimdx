// SkinnedMesh.fx
// Effect processing for skinned mesh

float4 LightDirection	= {0.0f, 0.0f, -1.0f, 1.0f};
float4 LightDiffuse		= {0.6f, 0.6f, 0.6f, 1.0f};
float4 MaterialAmbient	= {0.1f, 0.1f, 0.1f, 1.0f};
float4 MaterialDiffuse	= {0.8f, 0.8f, 0.8f, 1.0f};

static const int MaxMatrices = 26;
float4x3 WorldMatrices[MaxMatrices];
float4x1 ViewProjectionMatrix;

struct VSInput
{
	float4 Position				: POSITION;
	float4 BlendWeights			: BLENDWEIGHT;
	float4 BlendIndices			: BLENDINDICES;
	float3 Normal				: NORMAL;
	float3 TextureCoordinates	: TEXCOORD0;
};

struct VSOutput
{
	float4 Position				: POSITION;
	float4 Diffuse				: COLOR0;
	float2 TextureCoordinates	: TEXCOORD0; 
};

float3 Diffuse(float3 normal)
{
	float cosTheta;

	cosTheta = max(0.0f, dot(normal, LightDirection.xyz));
	
	return (cosTheta);
}

VSOutput VS(VSInput input, uniform int boneCount)
{
	VSOutput output = (VSOutput)0;

	float blendWeights[4] = (float[4])input.BlendWeights;
	int indices[4] = (int[4])D3DCOLORtoUBYTE4(input.BlendIndices);
	
	float lastWeight = 0.0f;
	float3 position = 0.0f;
	float3 normal = 0.0f;
	
	for (int i = 0; i < boneCount - 1; i++)
	{
		lastWeight += blendWeights[i];
		position += mul(input.Position, WorldMatrices[indices[i]]) * blendWeights[i];
		normal += mul(input.Normal, WorldMatrices[indices[i]]) * blendWeights[i];
	}
	
	lastWeight = 1.0f - lastWeight;
	
	position += mul(input.Position, WorldMatrices[indices[boneCount - 1]]) * lastWeight;
	normal += mul(input.Normal, WorldMatrices[indices[boneCount - 1]]) * lastWeight;
	normal = normalize(normal);
	
	output.Position = mul(float4(position.xyz, 1.0f), ViewProjectionMatrix);
	
	output.Diffuse.xyz = MaterialAmbient.xyz + Diffuse(normal) * MaterialDiffuse.xyz;
	output.Diffuse.w = 1.0f;
	
	output.TextureCoordinates = input.TextureCoordinates.xy;
	
	return output;
}

int CurrentBoneCount = 2;
VertexShader shaderArray[4] = { compile vs_1_1 VS(1),
								compile vs_1_1 VS(2),
								compile vs_1_1 VS(3),
								compile vs_1_1 VS(4)
							  };

technique SkinnedMesh
{
	pass P0
	{
		VertexShader = (shaderArray[CurrentBoneCount]);
	}
}
