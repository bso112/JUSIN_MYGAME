#pragma once
#include "Scene.h"

BEGIN(MyGame)
class CLevelMgr;
class CStageUIMgr;
class CHero;
class CTurnMgr;
class CTexture;
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
	CLevelMgr*		m_pLevelMgr = nullptr;
	CStageUIMgr*	m_pStageUIMgr = nullptr;
	CTurnMgr*		m_pTurnMgr = nullptr;


private:
	HRESULT Initalize_Prototypes();
	HRESULT	Initalize_Layers();


public:
	static CStage* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual void Free() override;
};
END
