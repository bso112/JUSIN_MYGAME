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
	//������ �ִ� ��� png������ �ε��ؼ� �ؽ��ķ� ���� �� ���Ŵ����� �Ѱ��ش�.
	HRESULT	Create_Textrues_From_Folder(PDIRECT3DDEVICE9 pGraphic_Device, SCENEID _eSceneID, const _tchar* _pFolderPath);
	HRESULT	Create_Textrues_From_Folder_Anim(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID, const _tchar* _pFolderPath);


public:
	virtual void Free() override;
};

END