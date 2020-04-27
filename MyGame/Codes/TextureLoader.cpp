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

HRESULT CTextureLoader::Create_Textrues_From_Folder_Anim(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, const _tchar* _pFolderPath)
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
		//파일경로
		_tchar szFileDir[MAX_PATH] = L"";
		StringCchCopy(szFileDir, MAX_PATH, &_pFolderPath[0]);
		StringCchCat(szFileDir, MAX_PATH, ffd.cFileName);

		wchar_t pFileName[MAX_PATH];

#pragma region 애니메이션 카운트 뽑아내기, 확장자 제외하고 파일이름 뽑아내기
		ZeroMemory(pFileName, sizeof(pFileName));
		_uint	index = 0;
		wchar_t* pTmp = ffd.cFileName;
		//십의 몇승
		_uint	exponent = 1;

		//마지막 애니메이션 번호
		_uint iCurrAniNum = 0;
		//후위나 전위나 똑같이 원본은 증가.
		while (pTmp)
		{

			if (*pTmp == L'.')
				break;

			//만약 숫자가 있으면 애니메이션 번호라 인식하고 저장.
			if (48 <= *pTmp && 57 >= *pTmp)
			{

				//읽어들인 숫자
				int digit = *pTmp - 48;

				//자리수 구하기
				int exp = 1;
				for (int i = 0; i < exponent; ++i)
					exp *= 10;

				//적절한 자리수로 지정
				iCurrAniNum *= exp;
				//읽어들인 숫자 더하기
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

		//첫번째 파일이름을 전 이름으로한다.
		if (callCnt == 0)
			StringCchCopy(m_pPrvName, MAX_PATH, pFileName);
		++callCnt;

		//파일이름이 달라졌을 때
		if (0 != lstrcmp(m_pPrvName, pFileName))
		{	
			ZeroMemory(finalDir, sizeof(finalDir));
			_tchar* tmp = m_szPrvDir;
			_uint	index2 = 0;
			while (*tmp != '\0')
			{
				//숫자면
				if (48 <= *tmp && 57 >= *tmp)
				{
					StringCchCat(finalDir, MAX_PATH, L"%d.png");
					break;
				}

				finalDir[index2] = m_szPrvDir[index2];
				++index2;
				++tmp;
			}
			//생성 
			//m_szPrvDir에 %d로 바꿔야함. 숫자전까지 읽은다음에 cat하면 될듯.
	
			if (m_iPrvAniNum == 0)
				m_iPrvAniNum = 1;

			pModuleMgr->Add_Module(m_pPrvName, _eSceneID,
				CTexture::Create(_pGraphic_Device, finalDir, m_iPrvAniNum));
		}

		//현재 이름을 전 이름으로		
		StringCchCopy(m_pPrvName, MAX_PATH, pFileName);
		//현재 경로를 전 경로로
		StringCchCopy(m_szPrvDir, MAX_PATH, szFileDir);

		//현재 애니메이션 번호를 마지막 애니메이션 번호로 
		m_iPrvAniNum = iCurrAniNum;


	} while (FindNextFile(hFind, &ffd) != 0);

#pragma region 마지막 파일처리
	//마지막 파일에 대해서
	ZeroMemory(finalDir, sizeof(finalDir));
	_tchar* tmp = m_szPrvDir;
	_uint	index2 = 0;
	while (*tmp != '\0')
	{
		//숫자면
		if (48 <= *tmp && 57 >= *tmp)
		{
			StringCchCat(finalDir, MAX_PATH, L"%d.png");
			break;
		}

		finalDir[index2] = m_szPrvDir[index2];
		++index2;
		++tmp;
	}
	//생성 
	//m_szPrvDir에 %d로 바꿔야함. 숫자전까지 읽은다음에 cat하면 될듯.

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
