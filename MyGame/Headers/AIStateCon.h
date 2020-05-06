#pragma once
#include "Module.h"
#include "AIState.h"
BEGIN(MyGame)

class CAIStateCon final : public CModule
{
	
private:
	explicit CAIStateCon(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CAIStateCon(CAIStateCon& _rhs) : CModule(_rhs) {};
	virtual ~CAIStateCon() = default;

private:
	CAIState*			m_pStateArr[CAIState::STATE_END];
	CAIState*			m_pCurrState = nullptr;


public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);


public:
	//�ϴ� �ѹ� ������
	_int	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt);
	HRESULT	Set_State(CAIState::STATE _eState, CAIState* _pAIState);
	HRESULT	Set_Default_State(CAIState::STATE _eState);

public:
	static CAIStateCon* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CModule* Clone(void * _pArg = nullptr) override;
	virtual void Free();
};

END