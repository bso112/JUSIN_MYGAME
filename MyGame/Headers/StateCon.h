#pragma once
#include "Module.h"
#include "State.h"
#include "AIState.h"
BEGIN(MyGame)

class CStateCon final : public CModule
{
private:
	explicit CStateCon(PDIRECT3DDEVICE9 _pGraphic_Device) : CModule(_pGraphic_Device) {};
	explicit CStateCon(CStateCon& _rhs) : CModule(_rhs) {};
	virtual ~CStateCon() = default;

private:
	list<CState*>					m_listState;
	CState*							m_pCurrState = nullptr;


public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);


public:
	//턴당 한번 실행함
	_int	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt);
	HRESULT	Set_Defualt_State(CState* _pState);

public:
	HRESULT	AddState(CState* _pState) { m_listState.push_back(_pState); return S_OK; }
public:
	static CStateCon* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CModule* Clone(void * _pArg = nullptr) override;
	virtual void Free();
};

END