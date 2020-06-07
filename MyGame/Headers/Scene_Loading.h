#pragma once
#include "Scene.h"
BEGIN(MyGame)
#define ARC1X 7
#define ARC1Y 5
#define ARC1CX 200
#define ARC1CY 200

class CImage;
class CLoading;
class CScene_Loading :
	public CScene
{
protected:
	explicit CScene_Loading(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CScene_Loading() = default;

private:
	CLoading*	m_pLoading = nullptr;
	//배경
	CImage*					m_pImgArc1[ARC1Y][ARC1X];
public:
	virtual HRESULT Initialize();
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render();



public:
	static CScene_Loading* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};
END
