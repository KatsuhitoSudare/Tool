//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------
struct VS_IN
{
    float4 Pos : POSITION;
    float4 Color : COLOR;
};

struct VS_OUT
{
    float4 Pos : SV_POSITION;
    float4 Color : COLOR;
};


VS_OUT main(VS_IN input)
{
    matrix routateZ =
    {
        cos(3.14), -sin(3.14), 0, 0,
        sin(3.14), cos(3.14), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };
    
    float4x4 s =
    {
        2.0f, 0, 0, 0,
        0, 2.0f, 0, 0,
        0, 0, 0.0, 0,
        0, 0,   0, 1,
    };
    
    VS_OUT output;
    
    output.Pos = input.Pos; //mul(input.Pos, routateZ); //‰ñ“]
    //output = mul(Pos, s);//Šg‘å
    output.Color = input.Color;
    
    return output;
}
