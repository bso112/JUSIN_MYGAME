#pragma once

#include "Base.h"

BEGIN(MyGame)
class CSceneMgr;
class CTriggerClock;
class CDelayClock;
class CSingleClock;
class CReversalClock;

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

	CTriggerClock*	m_pTriggerClock;
	CDelayClock*	m_pDelayClock;
	CSingleClock*	m_pSingleClock;
	CReversalClock*	m_pReversalClock;


#if _DEBUG
	_tchar	m_szFPS[MAX_PATH] = L"";
	_double	m_dwTimeAcc = 0;
	_uint	m_iRenderCnt = 0;
#endif

private:
	HRESULT Initalize_Default_Setting();
	HRESULT	Initalize_Scene();
public:
	static CMainApp* Create();
private:
	virtual void Free() override;
};

END
