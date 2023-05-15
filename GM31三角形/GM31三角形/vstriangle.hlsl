//--------------------------------------------------------------------------------------
// Vertex Shader
//--------------------------------------------------------------------------------------


float4 main( float4 Pos : POSITION ) : SV_POSITION
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
    
    float4 output;
    
    output = mul(Pos, routateZ);//‰ñ“]
    //output = mul(Pos, s);//Šg‘å
    
    return output;
}
