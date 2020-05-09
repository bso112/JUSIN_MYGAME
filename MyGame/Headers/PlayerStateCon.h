#pragma once
#include "StateCon.h"
#include "PlayerState.h"
BEGIN(MyGame)

class CPlayerStateCon final : public CStateCon
{

private:
	explicit CPlayerStateCon(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CPlayerStateCon(CPlayerStateCon& _rhs) : CStateCon(_rhs) {};
	virtual ~CPlayerStateCon() = default;

private:
	CPlayerState*			m_pStateArr[CPlayerState::STATE_END];
	CPlayerState*			m_pCurrState = nullptr;
	CPlayerState::STATE		m_eCurrState = CPlayerState::STATE_END;


public:
	HRESULT Initialize_Prototype();
	HRESULT Initialize(void* _pArg);

public:
	//턴당 한번 실행함
	_int	Start(_bool _canAttack, _bool _isAlerted);
	//프레임마다 판정 체크
	_int	Update(_bool _canAttack, _bool _isAlerted);
	HRESULT	Set_State(CPlayerState::STATE _eState, CPlayerState* _pAIState);
	HRESULT	Set_Default_State(CPlayerState::STATE _eState);

public:
	static CPlayerStateCon* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CModule* Clone(void * _pArg = nullptr) override;
	virtual void Free();
};

END