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
		std::cout << "ファイル名を入力" << std::endl;
		//ファイル名を入力
		std::cin >> FileName;

		//ヘッダファイルの名前
		std::string HeaderFileName;

		//cppファイルの名前
		std::string CPPFileName;

		//ファイル名操作用変数
		std::ostringstream iss;

		//ファイル名に拡張子をつける
		iss << FileName << ".h";
		HeaderFileName = iss.str();
		iss.str("");//一度削除


		iss << FileName << ".cpp";
		CPPFileName = iss.str();
		iss.str("");

		//==========================================================
		//ヘッダーファイルの作成
		//==========================================================
		std::ofstream File;
		//出力形式でファイルを開く
		File.open(HeaderFileName, std::ios::out);

		std::ostringstream oss;

		//インクルードガードを書き込む
		std::string  Filecontent = "#pragma once\n\n";

		//下記公務内容の更新
		oss << Filecontent;

		std::cout << "ファイルの作者の名前" << std::endl;

		std::string CreaterName;

		std::cin >> CreaterName;

		SYSTEMTIME ST{};

		GetLocalTime(&ST);

		oss << "////////////////////////////////////////////////////////////////////////////////\n";
		oss << "/// @file           " << FileName << "\n";
		oss << "/// @brief          ファイルの説明\n";
		oss << "/// @author         " << CreaterName << "\n";
		oss << "/// @date           " << "西暦" << ST.wYear << "年" << ST.wMonth << "月" << ST.wDay << "日\n";
		oss << "/// $Version:       ファイルバージョン$\n";
		oss << "/// @note           ファイルに備考などを明記する場合はここへ書き込む\n";
		oss << "/// @attention      ファイルに注意書きなどを明記する場合はここへ書き込む\n";
		oss << "////////////////////////////////////////////////////////////////////////////////\n\n";

		bool QLoopFLG = true;

		std::string keisyou;

		while (QLoopFLG)
		{
			std::cout << "クラスの継承を行いますか？　Yesならy Noならnを入力してください" << std::endl;

			std::string senntaku;

			std::cin >> senntaku;

			if (senntaku == "y")
			{
				std::cout << "継承するクラス名の入力" << std::endl;

				std::cin >> keisyou;

				//るーぷの終了
				QLoopFLG = false;
			}
			else if (senntaku == "n")
			{
				keisyou = " ";

				QLoopFLG = false;
			}
			else
			{
				std::cout << "入力が間違っています" << std::endl;
			}

		}

		QLoopFLG = true;

		while (QLoopFLG)
		{
			std::cout << "主要なインクルードファイルを使用しますか？　Yesならy Noならnを入力してください" << std::endl;

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
				

				//るーぷの終了
				QLoopFLG = false;
			}
			else if (senntaku == "n")
			{
				QLoopFLG = false;
			}
			else
			{
				std::cout << "入力が間違っています" << std::endl;
			}
		}

		oss << "//======================================================================\n" << "//namespace\n" << "//======================================================================\n";

		Filecontent = "namespace";

		oss << Filecontent;

		QLoopFLG = true;

		std::string namespaceName;

		while (QLoopFLG)
		{
			std::cout << "名前空間を使用しますか Yesならy Noならnを入力してください" << std::endl;

			std::string senntaku;

			std::cin >> senntaku;

			if (senntaku == "y")
			{
				std::cout << "名前空間名を入力してください" << std::endl;

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
				std::cout << "入力が間違っています" << std::endl;
			}

		}



		oss << "	////////////////////////////////////////////////////////////////////////////////\n";
		oss << "	/// @class      " << FileName << "\n";
		oss << "	/// @brief      classの説明\n";
		oss << "	/// \n";
		oss << "	////////////////////////////////////////////////////////////////////////////////\n";
		oss << "	class " << FileName <<" : public " << keisyou << "\n	{\n";
		oss << "	public:\n";
		oss << "		//======================================================================\n";
		oss << "		//public : function\n";
		oss << "		//======================================================================\n\n";
		oss << "		////////////////////////////////////////////////////////////////////////////////\n";
		oss << "		/// @brief          コンストラクタ\n";
		oss << "		/// @author         " << CreaterName << "\n";
		oss << "		/// @date           " << "西暦" << ST.wYear << "年" << ST.wMonth << "月" << ST.wDay << "日\n";
		oss << "		////////////////////////////////////////////////////////////////////////////////\n";
		oss << "		" << FileName << "();\n\n";
		oss << "		////////////////////////////////////////////////////////////////////////////////\n";
		oss << "		/// @brief          デストラクタ\n";
		oss << "		/// @author         " << CreaterName << "\n";
		oss << "		/// @date           " << "西暦" << ST.wYear << "年" << ST.wMonth << "月" << ST.wDay << "日\n";
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


		//名前空間の最後のかっこ
		oss << "\n}\n";

		Filecontent = oss.str();

		File << Filecontent << std::endl;

		File.close();

		//==========================================================
		//CPPファイルの作成
		//==========================================================

		//出力形式で開く
		File.open(CPPFileName, std::ios::out);

		//履歴の削除
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