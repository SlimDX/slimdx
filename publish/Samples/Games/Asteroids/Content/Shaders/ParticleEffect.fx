// ParticleEffect.fx
// Renders particles for particle systems.

float4x4 View;
float4x4 Projection;

float CurrentTime;

float Duration;
float DurationRandomness;
float3 Gravity;
float EndVelocity;
float4 MinColor;
float4 MaxColor;

float2 StartSize;
float2 EndSize;

struct VertexShaderInput
{
    float3 Position : POSITION;
    float3 Velocity : NORMAL0;
    float3 Random : COLOR0;
    float Time : TEXCOORD0;
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;
    float  Size : PSIZE0;
    float4 Color : COLOR0;
};

float4 ComputeParticlePosition(float3 position, float3 velocity,
                               float age, float normalizedAge)
{
    float startVelocity = length(velocity);
    float endVelocity = startVelocity * EndVelocity;
    
    float velocityIntegral = startVelocity * normalizedAge +
                             (endVelocity - startVelocity) * normalizedAge *
                                                             normalizedAge / 2;
     
    position += normalize(velocity) * velocityIntegral * Duration;
    position += Gravity * age * normalizedAge;
    
    return mul(mul(float4(position, 1), View), Projection);
}

float ComputeParticleSize(float4 projectedPosition,
                          float randomValue, float normalizedAge)
{
    float startSize = lerp(StartSize.x, StartSize.y, randomValue);
    float endSize = lerp(EndSize.x, EndSize.y, randomValue);

    float size = lerp(startSize, endSize, normalizedAge);

    return size;
}

float4 ComputeParticleColor(float4 projectedPosition,
                            float randomValue, float normalizedAge)
{
    float4 color = lerp(MinColor, MaxColor, randomValue);
    color.a *= normalizedAge * (1-normalizedAge) * (1-normalizedAge) * 6.7;

    return color;
}

VertexShaderOutput ParticleVertexShader(VertexShaderInput input)
{
    VertexShaderOutput output;

    float age = CurrentTime - input.Time;
    age *= 1 + input.Random.x * DurationRandomness;
    float normalizedAge = saturate(age / Duration);
    
    output.Position = ComputeParticlePosition(input.Position, input.Velocity,
                                              age, normalizedAge);
    
    output.Size = ComputeParticleSize(output.Position, input.Random.y, normalizedAge);
    output.Color = ComputeParticleColor(output.Position, input.Random.z, normalizedAge);
    
    return output;
}

float4 ParticlePixelShader(float4 color : COLOR0) : COLOR0
{
    return color;
}

technique ParticleTechnique
{
    pass P0
    {
        VertexShader = compile vs_2_0 ParticleVertexShader();
        PixelShader = compile ps_2_0 ParticlePixelShader();
    }
}
