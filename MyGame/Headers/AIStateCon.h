#pragma once
#include "StateCon.h"
#include "AIState.h"
BEGIN(MyGame)

class CAIStateCon final : public CStateCon
{
	
private:
	explicit CAIStateCon(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CAIStateCon(CAIStateCon& _rhs) : CStateCon(_rhs) { ZeroMemory(m_pStateArr, sizeof(m_pStateArr)); };
	virtual ~CAIStateCon() = default;

private:
	CAIState*			m_pStateArr[CAIState::STATE_END];
	CAIState*			m_pCurrState = nullptr;
	CAIState::STATE		m_eCurrState = CAIState::STATE_END;


public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);


public:
	//턴당 한번 실행함
	_int	Start(_bool _canAttack, _bool _isAlerted);
	_int	Update(_bool _canAttack, _bool _isAlerted);
	HRESULT	Set_State(CAIState::STATE _eState, CAIState* _pAIState);
	HRESULT	Set_Default_State(CAIState::STATE _eState, _bool _canAttack, _bool _isAlerted);

public:
	static CAIStateCon* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CModule* Clone(void * _pArg = nullptr) override;
	virtual void Free();
};

END