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
		Safe_Release(_pGraphic_Device);
		return E_FAIL;
	}

	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
	{
		Safe_Release(_pGraphic_Device);
		return E_FAIL;
	}

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

HRESULT CTextureLoader::Create_Textrues_From_Folder_Anim(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, const _tchar* _pFolderPath)
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
		Safe_Release(_pGraphic_Device);
		return E_FAIL;
	}

	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
	{
		Safe_Release(_pGraphic_Device);
		return E_FAIL;
	}

	Safe_AddRef(pModuleMgr);


	int callCnt = 0;
	_tchar finalDir[MAX_PATH] = L"";

	do
	{
		//���ϰ��
		_tchar szFileDir[MAX_PATH] = L"";
		StringCchCopy(szFileDir, MAX_PATH, &_pFolderPath[0]);
		StringCchCat(szFileDir, MAX_PATH, ffd.cFileName);

		wchar_t pFileName[MAX_PATH];

#pragma region �ִϸ��̼� ī��Ʈ �̾Ƴ���, Ȯ���� �����ϰ� �����̸� �̾Ƴ���
		ZeroMemory(pFileName, sizeof(pFileName));
		_uint	index = 0;
		wchar_t* pTmp = ffd.cFileName;
		//���� ���
		_uint	exponent = 1;

		//������ �ִϸ��̼� ��ȣ
		_uint iCurrAniNum = 0;
		//������ ������ �Ȱ��� ������ ����.
		while (pTmp)
		{

			if (*pTmp == L'.')
				break;

			//���� ���ڰ� ������ �ִϸ��̼� ��ȣ�� �ν��ϰ� ����.
			if (48 <= *pTmp && 57 >= *pTmp)
			{

				//�о���� ����
				int digit = *pTmp - 48;

				//�ڸ��� ���ϱ�
				int exp = 1;
				for (int i = 0; i < exponent; ++i)
					exp *= 10;

				//������ �ڸ����� ����
				iCurrAniNum *= exp;
				//�о���� ���� ���ϱ�
				iCurrAniNum += digit;

				++exponent;
			}
			else
			{
				pFileName[index] = ffd.cFileName[index];
				++index;
			}
			++pTmp;
		}
#pragma endregion 

		//ù��° �����̸��� �� �̸������Ѵ�.
		if (callCnt == 0)
			StringCchCopy(m_pPrvName, MAX_PATH, pFileName);
		++callCnt;

		//�����̸��� �޶����� ��
		if (0 != lstrcmp(m_pPrvName, pFileName))
		{	
			ZeroMemory(finalDir, sizeof(finalDir));
			_tchar* tmp = m_szPrvDir;
			_uint	index2 = 0;
			while (*tmp != '\0')
			{
				//���ڸ�
				if (48 <= *tmp && 57 >= *tmp)
				{
					StringCchCat(finalDir, MAX_PATH, L"%d.png");
					break;
				}

				finalDir[index2] = m_szPrvDir[index2];
				++index2;
				++tmp;
			}
			//���� 
			//m_szPrvDir�� %d�� �ٲ����. ���������� ���������� cat�ϸ� �ɵ�.
	
			if (m_iPrvAniNum == 0)
				m_iPrvAniNum = 1;

			pModuleMgr->Add_Module(m_pPrvName, _eSceneID,
				CTexture::Create(_pGraphic_Device, finalDir, m_iPrvAniNum));
		}

		//���� �̸��� �� �̸�����		
		StringCchCopy(m_pPrvName, MAX_PATH, pFileName);
		//���� ��θ� �� ��η�
		StringCchCopy(m_szPrvDir, MAX_PATH, szFileDir);

		//���� �ִϸ��̼� ��ȣ�� ������ �ִϸ��̼� ��ȣ�� 
		m_iPrvAniNum = iCurrAniNum;


	} while (FindNextFile(hFind, &ffd) != 0);

#pragma region ������ ����ó��
	//������ ���Ͽ� ���ؼ�
	ZeroMemory(finalDir, sizeof(finalDir));
	_tchar* tmp = m_szPrvDir;
	_uint	index2 = 0;
	while (*tmp != '\0')
	{
		//���ڸ�
		if (48 <= *tmp && 57 >= *tmp)
		{
			StringCchCat(finalDir, MAX_PATH, L"%d.png");
			break;
		}

		finalDir[index2] = m_szPrvDir[index2];
		++index2;
		++tmp;
	}
	//���� 
	//m_szPrvDir�� %d�� �ٲ����. ���������� ���������� cat�ϸ� �ɵ�.

	if (m_iPrvAniNum == 0)
		m_iPrvAniNum = 1;

	pModuleMgr->Add_Module(m_pPrvName, _eSceneID,
		CTexture::Create(_pGraphic_Device, finalDir, m_iPrvAniNum));
#pragma endregion

	Safe_Release(pModuleMgr);
	Safe_Release(_pGraphic_Device);
	FindClose(hFind);

	return S_OK;



}

void CTextureLoader::Free()
{
}
