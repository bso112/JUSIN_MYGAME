#pragma once
#include "Module.h"
#include "PlayerState.h"
BEGIN(MyGame)

class CPlayerStateCon final : public CModule
{

private:
	explicit CPlayerStateCon(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CPlayerStateCon(CPlayerStateCon& _rhs) : CModule(_rhs) {};
	virtual ~CPlayerStateCon() = default;

private:
	CPlayerState*			m_pStateArr[CPlayerState::STATE_END];
	CPlayerState*			m_pCurrState = nullptr;


public:
	HRESULT Initialize_Prototype();
	HRESULT Initialize(void* _pArg);

public:
	//�ϴ� �ѹ� ������
	_int	Act(_bool _canAttack, _bool _isAlerted, _int _iTurnCnt);
	//�����Ӹ��� ���� üũ
	_int	LateUpdate(_bool _canAttack, _bool _isAlerted);
	HRESULT	Set_State(CPlayerState::STATE _eState, CPlayerState* _pAIState);
	HRESULT	Set_Default_State(CPlayerState::STATE _eState);

public:
	static CPlayerStateCon* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CModule* Clone(void * _pArg = nullptr) override;
	virtual void Free();
};

END