#pragma once

////////////////////////////////////////////////////////////////////////////////
/// @file           test
/// @brief          �t�@�C���̐���
/// @author         inopinp
/// @date           ����2023�N1��17��
/// $Version:       �t�@�C���o�[�W����$
/// @note           �t�@�C���ɔ��l�Ȃǂ𖾋L����ꍇ�͂����֏�������
/// @attention      �t�@�C���ɒ��ӏ����Ȃǂ𖾋L����ꍇ�͂����֏�������
////////////////////////////////////////////////////////////////////////////////

//======================================================================
//includes
//======================================================================
#include<string>
#include<vector>
#include<map>
#include<iostream>
#include<math.h>
#include<memory>
#include"GameObject.h"

//======================================================================
//usings
//======================================================================
using std::string;
using std::vector;
using std::map;
using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::endl;
using std::cout;
using std::cin;

//======================================================================
//namespace
//======================================================================
namespace awefawef
{
	////////////////////////////////////////////////////////////////////////////////
	/// @class      test
	/// @brief      class�̐���
	/// 
	////////////////////////////////////////////////////////////////////////////////
	class test : public GameObject
	{
	public:
		//======================================================================
		//public : function
		//======================================================================

		////////////////////////////////////////////////////////////////////////////////
		/// @brief          �R���X�g���N�^
		/// @author         inopinp
		/// @date           ����2023�N1��17��
		////////////////////////////////////////////////////////////////////////////////
		test();

		////////////////////////////////////////////////////////////////////////////////
		/// @brief          �f�X�g���N�^
		/// @author         inopinp
		/// @date           ����2023�N1��17��
		////////////////////////////////////////////////////////////////////////////////
		~test();

		//======================================================================
		//public : variables
		//======================================================================

		//--Noting--

		//======================================================================
		//public : friend class&function
		//======================================================================

		//--Noting--

	private:
		//======================================================================
		//private : function
		//======================================================================

		//--Noting--

		//======================================================================
		//private : variables
		//======================================================================

		//--Noting--

		//======================================================================
		//private : friend class&function
		//======================================================================

		//--Noting--

	};

}
