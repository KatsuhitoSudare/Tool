﻿//-----------------------------------------------------------------------------
// File : ComPtr.h
// Desc : ComPtr Module.
// Copyright(c) Pocol. All right reserved.
//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include <wrl/client.h>

//-----------------------------------------------------------------------------
// Type Alias
//-----------------------------------------------------------------------------
template<typename T>
using ComPtr = Microsoft::WRL::ComPtr<T>;
