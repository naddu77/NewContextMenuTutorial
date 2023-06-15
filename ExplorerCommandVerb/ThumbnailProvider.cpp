// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//
// Copyright (c) Microsoft Corporation. All rights reserved

// ExplorerCommand handlers are an inproc verb implementation method that can provide
// dynamic behavior including computing the name of the command, its icon and its visibility state.
// only use this verb implemetnation method if you are implementing a command handler on
// the commands module and need the same functionality on a context menu.
//
// each ExplorerCommand handler needs to have a unique COM object, run uuidgen to
// create new CLSID values for your handler. a handler can implement multiple
// different verbs using the information provided via IInitializeCommand (the verb name).
// your code can switch off those different verb names or the properties provided
// in the property bag

#include "Dll.h"
#include <iostream>
#include <Windows.h>
#include <thumbcache.h>

static WCHAR const c_szVerbDisplayName[] = L"Cpp Thumbnail Provider";
static WCHAR const c_szVerbName[] = L"Sample.ThumbnailProvider";

class CThumbnailProvider 
	: public IInitializeWithStream, public IThumbnailProvider
{
public:
	CThumbnailProvider() : _cRef(1), _punkSite(NULL), _hwnd(NULL), _pstmShellItemArray(NULL)
	{
		DllAddRef();
	}

	// IUnknown
	IFACEMETHODIMP QueryInterface(REFIID riid, void** ppv)
	{
		static const QITAB qit[] =
		{
			QITABENT(CThumbnailProvider, IInitializeWithStream),       // required
			QITABENT(CThumbnailProvider, IThumbnailProvider),     // required
			{ 0 },
		};
		return QISearch(this, qit, riid, ppv);
	}

	IFACEMETHODIMP_(ULONG) AddRef()
	{
		return InterlockedIncrement(&_cRef);
	}

	IFACEMETHODIMP_(ULONG) Release()
	{
		long cRef = InterlockedDecrement(&_cRef);
		if (!cRef)
		{
			delete this;
		}
		return cRef;
	}

private:
	~CThumbnailProvider()
	{
		DllRelease();
	}

	long _cRef;
	IUnknown* _punkSite;
	HWND _hwnd;
	IStream* _pstmShellItemArray;

	// Inherited via IInitializeWithStream
	virtual HRESULT __stdcall Initialize([[maybe_unused]]IStream* pstream, [[maybe_unused]]DWORD grfMode) override
	{
		MessageBox(_hwnd, L"ttt", L"123", MB_OK);
		return S_OK;
		//return E_NOTIMPL;
	}

	// Inherited via IThumbnailProvider
	virtual HRESULT __stdcall GetThumbnail([[maybe_unused]] UINT cx, [[maybe_unused]] HBITMAP* phbmp, [[maybe_unused]] WTS_ALPHATYPE* pdwAlpha) override
	{
		return S_OK;
		//return E_NOTIMPL;
	}
};

HRESULT CThumbnailProvider_RegisterUnRegister(bool fRegister)
{
	CRegisterExtension re(__uuidof(CThumbnailProvider));

	HRESULT hr;
	if (fRegister)
	{
		hr = re.RegisterInProcServer(c_szVerbDisplayName, L"Apartment");
		if (SUCCEEDED(hr))
		{
			// register this verb on .txt files ProgID
			hr = re.RegisterThumbnailHandler(L".jpg");
			//if (SUCCEEDED(hr))
			//{
			//	hr = re.RegisterVerbAttribute(c_szProgID, c_szVerbName, L"NeverDefault");
			//}
		}
	}
	else
	{
		// best effort
		//hr = re.UnRegisterVerb(c_szProgID, c_szVerbName);
		hr = re.UnRegisterObject();
	}
	return hr;
}

HRESULT CThumbnailProvider_CreateInstance(REFIID riid, void** ppv)
{
	*ppv = NULL;
	CThumbnailProvider* pVerb = new (std::nothrow) CThumbnailProvider();
	HRESULT hr = pVerb ? S_OK : E_OUTOFMEMORY;
	if (SUCCEEDED(hr))
	{
		pVerb->QueryInterface(riid, ppv);
		pVerb->Release();
	}
	return hr;
}
