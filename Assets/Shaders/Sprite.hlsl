cbuffer PerObject : register(b0)
{
    float4x4 worldViewProj;
    float4 color;
};

struct VS_INPUT
{
    float3 position : POSITION;
    float2 texcoord : TEXCOORD;
};

struct PS_INPUT
{
    float4 position : SV_POSITION;
    float2 texcoord : TEXCOORD;
    float4 color : COLOR;
};

PS_INPUT VS(VS_INPUT input)
{
    PS_INPUT output;
    output.position = mul(float4(input.position, 1.0f), worldViewProj);
    output.texcoord = input.texcoord;
    output.color = color;
    return output;
}

float4 PS(PS_INPUT input) : SV_TARGET
{
    return input.color;
}
