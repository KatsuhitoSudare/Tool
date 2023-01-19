#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<math.h>
#include<Windows.h>
#include<memory>


int main()
{
	bool Loop1 = true;

	while (Loop1)
	{
		std::string FileName;
		std::cout << "�t�@�C���������" << std::endl;
		//�t�@�C���������
		std::cin >> FileName;

		//�w�b�_�t�@�C���̖��O
		std::string HeaderFileName;

		//cpp�t�@�C���̖��O
		std::string CPPFileName;

		//�t�@�C��������p�ϐ�
		std::ostringstream iss;

		//�t�@�C�����Ɋg���q������
		iss << FileName << ".h";
		HeaderFileName = iss.str();
		iss.str("");//��x�폜


		iss << FileName << ".cpp";
		CPPFileName = iss.str();
		iss.str("");

		//==========================================================
		//�w�b�_�[�t�@�C���̍쐬
		//==========================================================
		std::ofstream File;
		//�o�͌`���Ńt�@�C�����J��
		File.open(HeaderFileName, std::ios::out);

		std::ostringstream oss;

		//�C���N���[�h�K�[�h����������
		std::string  Filecontent = "#pragma once\n\n";

		//���L�������e�̍X�V
		oss << Filecontent;

		std::cout << "�t�@�C���̍�҂̖��O" << std::endl;

		std::string CreaterName;

		std::cin >> CreaterName;

		SYSTEMTIME ST{};

		GetLocalTime(&ST);

		oss << "////////////////////////////////////////////////////////////////////////////////\n";
		oss << "/// @file           " << FileName << "\n";
		oss << "/// @brief          �t�@�C���̐���\n";
		oss << "/// @author         " << CreaterName << "\n";
		oss << "/// @date           " << "����" << ST.wYear << "�N" << ST.wMonth << "��" << ST.wDay << "��\n";
		oss << "/// $Version:       �t�@�C���o�[�W����$\n";
		oss << "/// @note           �t�@�C���ɔ��l�Ȃǂ𖾋L����ꍇ�͂����֏�������\n";
		oss << "/// @attention      �t�@�C���ɒ��ӏ����Ȃǂ𖾋L����ꍇ�͂����֏�������\n";
		oss << "////////////////////////////////////////////////////////////////////////////////\n\n";

		bool QLoopFLG = true;

		std::string keisyou;

		while (QLoopFLG)
		{
			std::cout << "�N���X�̌p�����s���܂����H�@Yes�Ȃ�y No�Ȃ�n����͂��Ă�������" << std::endl;

			std::string senntaku;

			std::cin >> senntaku;

			if (senntaku == "y")
			{
				std::cout << "�p������N���X���̓���" << std::endl;

				std::cin >> keisyou;

				//��[�Ղ̏I��
				QLoopFLG = false;
			}
			else if (senntaku == "n")
			{
				keisyou = " ";

				QLoopFLG = false;
			}
			else
			{
				std::cout << "���͂��Ԉ���Ă��܂�" << std::endl;
			}

		}

		QLoopFLG = true;

		while (QLoopFLG)
		{
			std::cout << "��v�ȃC���N���[�h�t�@�C�����g�p���܂����H�@Yes�Ȃ�y No�Ȃ�n����͂��Ă�������" << std::endl;

			std::string senntaku;

			std::cin >> senntaku;

			if (senntaku == "y")
			{
				oss << "//======================================================================\n";
				oss << "//includes\n";
				oss << "//======================================================================\n";
				oss << "#include<string>\n";
				oss << "#include<vector>\n";
				oss << "#include<map>\n";
				oss << "#include<iostream>\n";
				oss << "#include<math.h>\n";
				oss << "#include<memory>\n";
				if (keisyou != " ")
				{
					oss << "#include"<<"\"" << keisyou << ".h" << "\"\n\n";
				}
				else
				{
					oss << "\n";
				}

				oss << "//======================================================================\n";
				oss << "//usings\n";
				oss << "//======================================================================\n";
				oss << "using std::string;\n";
				oss << "using std::vector;\n";
				oss << "using std::map;\n";
				oss << "using std::unique_ptr;\n";
				oss << "using std::shared_ptr;\n";
				oss << "using std::weak_ptr;\n";
				oss << "using std::endl;\n";
				oss << "using std::cout;\n";
				oss << "using std::cin;\n\n";
				

				//��[�Ղ̏I��
				QLoopFLG = false;
			}
			else if (senntaku == "n")
			{
				QLoopFLG = false;
			}
			else
			{
				std::cout << "���͂��Ԉ���Ă��܂�" << std::endl;
			}
		}

		oss << "//======================================================================\n" << "//namespace\n" << "//======================================================================\n";

		Filecontent = "namespace";

		oss << Filecontent;

		QLoopFLG = true;

		std::string namespaceName;

		while (QLoopFLG)
		{
			std::cout << "���O��Ԃ��g�p���܂��� Yes�Ȃ�y No�Ȃ�n����͂��Ă�������" << std::endl;

			std::string senntaku;

			std::cin >> senntaku;

			if (senntaku == "y")
			{
				std::cout << "���O��Ԗ�����͂��Ă�������" << std::endl;

				std::cin >> namespaceName;

				oss << " " << namespaceName << "\n{\n";

				QLoopFLG = false;
			}
			else if (senntaku == "n")
			{
				namespaceName = " ";

				oss << "\n{\n";

				QLoopFLG = false;
			}
			else
			{
				std::cout << "���͂��Ԉ���Ă��܂�" << std::endl;
			}

		}



		oss << "	////////////////////////////////////////////////////////////////////////////////\n";
		oss << "	/// @class      " << FileName << "\n";
		oss << "	/// @brief      class�̐���\n";
		oss << "	/// \n";
		oss << "	////////////////////////////////////////////////////////////////////////////////\n";
		oss << "	class " << FileName <<" : public " << keisyou << "\n	{\n";
		oss << "	public:\n";
		oss << "		//======================================================================\n";
		oss << "		//public : function\n";
		oss << "		//======================================================================\n\n";
		oss << "		////////////////////////////////////////////////////////////////////////////////\n";
		oss << "		/// @brief          �R���X�g���N�^\n";
		oss << "		/// @author         " << CreaterName << "\n";
		oss << "		/// @date           " << "����" << ST.wYear << "�N" << ST.wMonth << "��" << ST.wDay << "��\n";
		oss << "		////////////////////////////////////////////////////////////////////////////////\n";
		oss << "		" << FileName << "();\n\n";
		oss << "		////////////////////////////////////////////////////////////////////////////////\n";
		oss << "		/// @brief          �f�X�g���N�^\n";
		oss << "		/// @author         " << CreaterName << "\n";
		oss << "		/// @date           " << "����" << ST.wYear << "�N" << ST.wMonth << "��" << ST.wDay << "��\n";
		oss << "		////////////////////////////////////////////////////////////////////////////////\n";
		oss << "		~" << FileName << "();\n\n";
		oss << "		//======================================================================\n";
		oss << "		//public : variables\n";
		oss << "		//======================================================================\n\n";
		oss << "		//--Noting--\n\n";
		oss << "		//======================================================================\n";
		oss << "		//public : friend class&function\n";
		oss << "		//======================================================================\n\n";
		oss << "		//--Noting--\n\n";
		oss << "	private:\n";
		oss << "		//======================================================================\n";
		oss << "		//private : function\n";
		oss << "		//======================================================================\n\n";
		oss << "		//--Noting--\n\n";
		oss << "		//======================================================================\n";
		oss << "		//private : variables\n";
		oss << "		//======================================================================\n\n";
		oss << "		//--Noting--\n\n";
		oss << "		//======================================================================\n";
		oss << "		//private : friend class&function\n";
		oss << "		//======================================================================\n\n";
		oss << "		//--Noting--\n\n";
		oss << "	};\n";


		//���O��Ԃ̍Ō�̂�����
		oss << "\n}\n";

		Filecontent = oss.str();

		File << Filecontent << std::endl;

		File.close();

		//==========================================================
		//CPP�t�@�C���̍쐬
		//==========================================================

		//�o�͌`���ŊJ��
		File.open(CPPFileName, std::ios::out);

		//�����̍폜
		Filecontent.clear();
		oss.str("");
		oss.clear();

		oss << "#include " << " \"" << HeaderFileName << "\"\n\n";

		oss << "namespace " << namespaceName << "\n" << "{\n";

		oss << "	" << FileName << "::" << FileName << "()\n" << "	{\n" << "	}\n\n";

		oss << "	" << FileName << "::" << "~" << FileName << "()\n" << "	{\n" << "	}\n\n";

		oss << "}";

		File << oss.str() << std::endl;

		File.close();

		Loop1 = false;
	}
	return 0;
}