#include "stdafx.h"
#include "..\Headers\TextureLoader.h"
#include "ModuleMgr.h"


USING(MyGame)

IMPLEMENT_SINGLETON(CTextureLoader)

HRESULT CTextureLoader::Create_Textrues_From_Folder(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, const _tchar* _pFolderPath)
{

	Safe_AddRef(_pGraphic_Device);

	//파일정보
	WIN32_FIND_DATA ffd;
	_tchar szDir[MAX_PATH] = L"";
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	//경로를 복사하고, 원하는 확장자를 붙인다.

	StringCchCopy(szDir, MAX_PATH, &_pFolderPath[0]);
	StringCchCat(szDir, MAX_PATH, TEXT("*.png"));

	//폴더 안에 있는 첫번째 파일을 로드한다.
	hFind = FindFirstFile(szDir, &ffd);


	if (INVALID_HANDLE_VALUE == hFind)
	{
		MSG_BOX("Fail to load textures");
		return E_FAIL;
	}

	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;

	Safe_AddRef(pModuleMgr);


	do
	{
		//파일경로
		_tchar szFileDir[MAX_PATH] = L"";
		StringCchCopy(szFileDir, MAX_PATH, &_pFolderPath[0]);
		StringCchCat(szFileDir, MAX_PATH, ffd.cFileName);

		wchar_t pFileName[MAX_PATH];
#pragma region 확장자 빼서 파일이름만 추출하기
		ZeroMemory(pFileName, sizeof(pFileName));
		_uint	index = 0;
		wchar_t* pTmp = ffd.cFileName;

		//후위나 전위나 똑같이 원본은 증가.
		while (++pTmp)
		{
			//일단 넣고
			pFileName[index] = ffd.cFileName[index];
			++index;

			//다음꺼 문자 확인하기
			if (*pTmp == L'.')
				break;
		}
#pragma endregion

		pModuleMgr->Add_Module(pFileName, _eSceneID,
			CTexture::Create(_pGraphic_Device, szFileDir));


	} while (FindNextFile(hFind, &ffd) != 0);


	Safe_Release(pModuleMgr);
	Safe_Release(_pGraphic_Device);
	FindClose(hFind);

	return S_OK;



}

void CTextureLoader::Free()
{
}
