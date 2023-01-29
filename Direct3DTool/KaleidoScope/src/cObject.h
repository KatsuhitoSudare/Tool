#pragma once
#include<vector>
#include<string>
#include<unordered_map>
#include<DirectXMath.h>
#include<memory>

using std::unique_ptr;
using std::shared_ptr;
using std::weak_ptr;
using std::vector;
using std::string;
using std::unordered_map;
using namespace DirectX;

namespace KALEIDOSCOPE
{
	class cObject
	{
	public:
		cObject();
		virtual ~cObject();

	};
}



