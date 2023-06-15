// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

#pragma once
#include "ShellHelpers.h"
#include "RegisterExtension.h"
#include <strsafe.h>
#include <new>  // std::nothrow

void DllAddRef();
void DllRelease();

// use UUDIGEN.EXE to generate unique CLSID values for your objects

class __declspec(uuid("5202149C-DD51-4CA1-B23D-4C1407F2514E")) CExplorerCommandVerb;
class __declspec(uuid("34498D80-4B5A-430D-AD4D-19B7D7F67FC0")) CExplorerCommandStateHandler;
class __declspec(uuid("97226282-7601-47C0-A953-F9E9206D93DF")) CThumbnailProvider;	// Note: 해당 확장자가 'EmptyMFCApp'를 기본 프로그램 사용해야 호출됨

HRESULT CExplorerCommandVerb_CreateInstance(REFIID riid, void **ppv);
HRESULT CExplorerCommandStateHandler_CreateInstance(REFIID riid, void **ppv);
HRESULT CThumbnailProvider_CreateInstance(REFIID riid, void** ppv);
HRESULT CExplorerCommandVerb_RegisterUnRegister(bool fRegister);
HRESULT CExplorerCommandStateHandler_RegisterUnRegister(bool fRegister);
HRESULT CThumbnailProvider_RegisterUnRegister(bool fRegister);
