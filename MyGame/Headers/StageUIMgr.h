#pragma once
#include "Base.h"

BEGIN(MyGame)
class CObjMgr;
class CHero;
class CInventoryUIMgr;
class CStatsPanel;
class CDialogPanel;
class CStageUIMgr : public CBase
{
	DECLARE_SINGLETON(CStageUIMgr)
private:
	explicit CStageUIMgr();
	virtual ~CStageUIMgr() = default;

private:
	CObjMgr*			m_pObjMgr			= nullptr;
	CInventoryUIMgr*	m_pInventoryUIMgr	= nullptr;
	CStatsPanel*		m_pStatsPanel = nullptr;
	CDialogPanel*		m_pDialogPanel = nullptr;
	vector<RECT>		m_vecUIRect;
	
public:
	HRESULT	Initialize(LPDIRECT3DDEVICE9 _pGraphic_Device, CHero* _pHero);
	vector<RECT>	GetUIRect();

public:
	HRESULT	SetActiveDialogPanel(_bool _bActive);

private:
	HRESULT Initialize_Prototype(LPDIRECT3DDEVICE9 pGraphic_Device, CHero* _pHero);

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};


END