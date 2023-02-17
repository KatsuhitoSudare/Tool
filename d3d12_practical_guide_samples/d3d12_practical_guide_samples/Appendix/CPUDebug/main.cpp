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
            return "1�̎���2";

        case 2:
            return "2�̎���3";

        case 3:
            return "3�̎���";

        case 4:
            return "�E�[�b4!!";

        case 5:
            return "5�̑O��";

        case 6:
            return "6�̑O��5";

        case 7:
            return "7�̑O��6";

        default:
            return "Die!!";
        }
    }

private:
    int m_Index     = 1;
    int m_Increment = 1;
};

//-----------------------------------------------------------------------------
//      ���C���G���g���[�|�C���g�ł�.
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
