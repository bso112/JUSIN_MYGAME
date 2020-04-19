#pragma once
#include "Base.h"

BEGIN(MyGame)

class CTexture;
class CTextureLoader : public CBase
{
	DECLARE_SINGLETON(CTextureLoader)
private:
	explicit CTextureLoader() {};
	virtual ~CTextureLoader() = default;

public:
	//������ �ִ� ��� png������ �ε��ؼ� �ؽ��ķ� ���� �� ���Ŵ����� �Ѱ��ش�.
	HRESULT	Create_Textrues_From_Folder(PDIRECT3DDEVICE9	pGraphic_Device,const _tchar* _pFolderPath);

public:
	virtual void Free() override;
};

END