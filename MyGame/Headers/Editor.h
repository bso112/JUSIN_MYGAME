#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CTexture;
class CVIBuffer;
class CEditor final: public CScene
{
private:
	explicit CEditor(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CEditor() = default;


public:
	virtual HRESULT Initalize();
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render();



protected:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;



};
END
