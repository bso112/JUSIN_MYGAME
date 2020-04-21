#include "stdafx.h"
#include "..\Headers\TextureLoader.h"
#include "ModuleMgr.h"


USING(MyGame)

IMPLEMENT_SINGLETON(CTextureLoader)

HRESULT CTextureLoader::Create_Textrues_From_Folder(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, const _tchar* _pFolderPath)
{

	Safe_AddRef(_pGraphic_Device);

	//��������
	WIN32_FIND_DATA ffd;
	_tchar szDir[MAX_PATH] = L"";
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	//��θ� �����ϰ�, ���ϴ� Ȯ���ڸ� ���δ�.

	StringCchCopy(szDir, MAX_PATH, &_pFolderPath[0]);
	StringCchCat(szDir, MAX_PATH, TEXT("*.png"));

	//���� �ȿ� �ִ� ù��° ������ �ε��Ѵ�.
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
		//���ϰ��
		_tchar szFileDir[MAX_PATH] = L"";
		StringCchCopy(szFileDir, MAX_PATH, &_pFolderPath[0]);
		StringCchCat(szFileDir, MAX_PATH, ffd.cFileName);

		wchar_t pFileName[MAX_PATH];
#pragma region Ȯ���� ���� �����̸��� �����ϱ�
		ZeroMemory(pFileName, sizeof(pFileName));
		_uint	index = 0;
		wchar_t* pTmp = ffd.cFileName;

		//������ ������ �Ȱ��� ������ ����.
		while (++pTmp)
		{
			//�ϴ� �ְ�
			pFileName[index] = ffd.cFileName[index];
			++index;

			//������ ���� Ȯ���ϱ�
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
