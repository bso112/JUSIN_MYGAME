#pragma once
#include "Module.h"
#include "State.h"
BEGIN(MyGame)

class CStateCon final : public CModule
{
private:
	explicit CStateCon(PDIRECT3DDEVICE9 _pGraphic_Device) : CModule(_pGraphic_Device) {};
	explicit CStateCon(CStateCon& _rhs) : CModule(_rhs) {};
	virtual ~CStateCon() = default;

private:
	list<CState*>	m_listState;
	CState*			m_pCurrState = nullptr;
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);

public:
	_int	Update(_double _timeDelta);
	HRESULT	Set_Defualt_State(CState* _pState) { if (_pState == nullptr) return E_FAIL; m_pCurrState = _pState; return S_OK; }

public:
	HRESULT	AddState(CState* _pState) { m_listState.push_back(_pState); return S_OK; }
public:
	static CStateCon* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CModule* Clone(void * _pArg = nullptr) override;
	virtual void Free();
};

END