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
	//폴더에 있는 모든 png파일을 로드해서 텍스쳐로 만든 뒤 모듈매니저에 넘겨준다.
	HRESULT	Create_Textrues_From_Folder(PDIRECT3DDEVICE9	pGraphic_Device,const _tchar* _pFolderPath);

public:
	virtual void Free() override;
};

END