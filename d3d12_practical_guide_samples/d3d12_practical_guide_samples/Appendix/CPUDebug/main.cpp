//-----------------------------------------------------------------------------
// File : main.cpp
// Desc : Debug Test.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <cstdio>

///////////////////////////////////////////////////////////////////////////////
// DebugTest class
//////////////////////////////////////////////////////////////////////////////
class DebugTest
{
public:
    void HeyHey()
    { m_Index += m_Increment; }

    void SetIndex(int count)
    { m_Index = count; }

    const char* GetString() const
    {
        switch(m_Index)
        {
        case 1:
            return "1の次は2";

        case 2:
            return "2の次は3";

        case 3:
            return "3の次は";

        case 4:
            return "ウーッ4!!";

        case 5:
            return "5の前は";

        case 6:
            return "6の前は5";

        case 7:
            return "7の前は6";

        default:
            return "Die!!";
        }
    }

private:
    int m_Index     = 1;
    int m_Increment = 1;
};

//-----------------------------------------------------------------------------
//      メインエントリーポイントです.
//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
    DebugTest test;

    printf_s("%s\n", test.GetString());
    test.HeyHey();

    printf_s("%s\n", test.GetString());
    test.HeyHey();

    printf_s("%s\n", test.GetString());
    test.HeyHey();

    printf_s("%s\n", test.GetString());
    test.HeyHey();

    test.SetIndex(7);

    printf_s("%s\n", test.GetString());
    test.HeyHey();

    printf_s("%s\n", test.GetString());
    test.HeyHey();

    printf_s("%s\n", test.GetString());
    test.HeyHey();

    printf_s("%s\n", test.GetString());

    printf_s("444!! 444!! 444!! 444!!\n");

    return 0;
}
