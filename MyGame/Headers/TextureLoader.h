#pragma once
#include "Base.h"

BEGIN(MyGame)

class CTexture;
class CTextureLoader : public CBase
{
	DECLARE_SINGLETON(CTextureLoader)
private:
	explicit CTextureLoader() { ZeroMemory(m_pPrvName, sizeof(m_pPrvName)); };
	virtual ~CTextureLoader() = default;

private:
	_tchar		m_pPrvName[MAX_PATH] = L"";
	_uint		m_iPrvAniNum = 0;
	_tchar		m_szPrvDir[MAX_PATH] = L"";

public:
	//폴더에 있는 모든 png파일을 로드해서 텍스쳐로 만든 뒤 모듈매니저에 넘겨준다. 모듈의 키는 파일이름이다.
	HRESULT	Create_Textrues_From_Folder(PDIRECT3DDEVICE9 pGraphic_Device, SCENEID _eSceneID, const _tchar* _pFolderPath);
	/*
	애니메이션에 쓸 텍스쳐 로드용.
	Create_Textrues_From_Folder는 파일이름을 자유롭게 해도되지만 이 함수는 규칙이 있음.
	이 함수로 로드하는 텍스쳐는 파일이름[애니메이션 번호].png 라는 규칙을 따라야함. 번호가 없어도 상관없음.
	이미지파일의 경로에 있는 숫자는 애니메이션 번호를 뜻해야됨. 그 이외에는 숫자가 있어서는 안됨.
	*/
	HRESULT	Create_Textrues_From_Folder_Anim(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, const _tchar* _pFolderPath);


public:
	virtual void Free() override;
};

END