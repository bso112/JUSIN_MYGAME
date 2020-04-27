#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CWorld;
class CStageUIMgr;
class CStage final : public CScene
{
private:
	explicit CStage(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CStage() = default;

public:
	virtual HRESULT Initialize();
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render();


private:
	CWorld*			m_pWorld;
	CStageUIMgr*	m_pStageUIMgr;

private:
	HRESULT	Initalize_World();
	HRESULT Initalize_Prototypes();
	HRESULT	Initalize_Layers();


public:
	static CStage* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void Free() override;
};
END
