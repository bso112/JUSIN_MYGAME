#pragma once

#include "Base.h"
#include "SceneMgr.h"

BEGIN(MyGame)

class CMainApp final : public CBase
{
private:
	explicit CMainApp();
	virtual ~CMainApp() = default;

private:
	PDIRECT3DDEVICE9	m_pGraphic_Device =nullptr;
	CSceneMgr*			m_pSceneMgr = nullptr;

public:
	HRESULT Initalize();
	_int	Update(_double _timeDelta);
	HRESULT	Render();



#if _DEBUG
	_tchar	m_szFPS[MAX_PATH] = L"";
	_double	m_dwTimeAcc = 0.0;
	_uint	m_iRenderCnt = 0;
#endif

private:
	HRESULT Initalize_Default_Setting();
	HRESULT	Initalize_Scene();
	HRESULT Initalize_Module();

public:
	static CMainApp* Create();
private:
	virtual void Free() override;
};

END
