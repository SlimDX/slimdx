// ParticleEffect.fx
// Renders particles for particle systems.
// Original effect by the XNA team.

float4x4 View;
float4x4 Projection;
float ViewportHeight;

float CurrentTime;

float Duration;
float DurationRandomness;
float3 Gravity;
float EndVelocity;
float4 MinColor;
float4 MaxColor;

float2 RotateSpeed;
float2 StartSize;
float2 EndSize;

texture Texture;

sampler Sampler = sampler_state
{
    Texture = (Texture);
    
    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Point;
    
    AddressU = Clamp;
    AddressV = Clamp;
};

struct VertexShaderInput
{
    float3 Position : POSITION0;
    float3 Velocity : NORMAL0;
    float4 Random : COLOR0;
    float Time : TEXCOORD0;
};

struct VertexShaderOutput
{
    float4 Position : POSITION0;
    float Size : PSIZE0;
    float4 Color : COLOR0;
    float4 Rotation : COLOR1;
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

    return size * Projection._m11 / projectedPosition.w * ViewportHeight / 2;
}

float4 ComputeParticleColor(float4 projectedPosition,
                            float randomValue, float normalizedAge)
{
    float4 color = lerp(MinColor, MaxColor, randomValue);
    color.a *= normalizedAge * (1-normalizedAge) * (1-normalizedAge) * 6.7;

    return color;
}

float4 ComputeParticleRotation(float randomValue, float age)
{
    float rotateSpeed = lerp(RotateSpeed.x, RotateSpeed.y, randomValue);

    float rotation = rotateSpeed * age;
    float c = cos(rotation);
    float s = sin(rotation);
    
    float4 rotationMatrix = float4(c, -s, s, c);
    
    rotationMatrix *= 0.5;
    rotationMatrix += 0.5;

    return rotationMatrix;
}

VertexShaderOutput VertexShader(VertexShaderInput input)
{
    VertexShaderOutput output;

    float age = CurrentTime - input.Time;
    age *= 1 + input.Random.x * DurationRandomness;
    float normalizedAge = saturate(age / Duration);
    
    output.Position = ComputeParticlePosition(input.Position, input.Velocity,
                                              age, normalizedAge);
    
    output.Size = ComputeParticleSize(output.Position, input.Random.y, normalizedAge);
    output.Color = ComputeParticleColor(output.Position, input.Random.z, normalizedAge);
    output.Rotation = ComputeParticleRotation(input.Random.w, age);
    
    return output;
}

struct NonRotatingPixelShaderInput
{
    float4 Color : COLOR0;
    float2 TextureCoordinate : TEXCOORD0;
};

float4 NonRotatingPixelShader(NonRotatingPixelShaderInput input) : COLOR0
{
    return tex2D(Sampler, input.TextureCoordinate) * input.Color;
}

struct RotatingPixelShaderInput
{
    float4 Color : COLOR0;
    float4 Rotation : COLOR1;
    float2 TextureCoordinate : TEXCOORD0;
};

float4 RotatingPixelShader(RotatingPixelShaderInput input) : COLOR0
{
    float2 textureCoordinate = input.TextureCoordinate;

    textureCoordinate -= 0.5;
    float4 rotation = input.Rotation * 2 - 1;
    textureCoordinate = mul(textureCoordinate, float2x2(rotation));
    textureCoordinate *= sqrt(2);
    textureCoordinate += 0.5;

    return tex2D(Sampler, textureCoordinate) * input.Color;
}

technique NonRotatingParticles
{
    pass P0
    {
        VertexShader = compile vs_1_1 VertexShader();
        PixelShader = compile ps_1_1 NonRotatingPixelShader();
    }
}

technique RotatingParticles
{
    pass P0
    {
        VertexShader = compile vs_1_1 VertexShader();
        PixelShader = compile ps_2_0 RotatingPixelShader();
    }
}
