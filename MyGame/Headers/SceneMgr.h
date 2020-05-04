#pragma once
#include "Base.h"

BEGIN(MyGame)
class CScene;
class CSceneMgr final : public CBase
{
	DECLARE_SINGLETON(CSceneMgr)

private:
	explicit CSceneMgr() {};
	virtual ~CSceneMgr() = default;

private:
	SCENEID m_eCurrSceneID = SCENE_END;
	CScene* m_pCurrScene = nullptr;
	CScene*	m_pPrvScene = nullptr;
public:
	HRESULT Scene_Change(SCENEID _eID, PDIRECT3DDEVICE9 _pGraphic_Device);
	_int	Update(_double _timeDelta);
	HRESULT	Render();

public:
	SCENEID	Get_CurrScene() { return m_eCurrSceneID; }
	HRESULT	Clear_PrvScene();

private:
	virtual void Free() override;

};

END