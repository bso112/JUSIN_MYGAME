#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "ParticleSystem.h"
#include "Buff.h"
BEGIN(MyGame)
class CClock_Delay;
class CCharacter;
class CEffect abstract : public CGameObject
{
public:
	typedef	struct tagStateDesc
	{
		BASEDESC	m_tBaseDesc = {};
		//�ϳ��� ����Ʈ������ ������ Ÿ���� �ٸ� �� �ִ�. CFire�� �̸��� �� �߸�������.
		CBuff::TYPE	m_tBuffType = CBuff::TYPE_END;
	}STATEDESC;
protected:
	explicit CEffect(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CEffect(CEffect& _rhs);
	virtual ~CEffect() = default;


protected:
	CParticleSystem*	m_pParticleSystem = nullptr;
	CTransform*			m_pTransform = nullptr;
	//�i�ƴٴ� Ÿ��
	CTransform*			m_pTarget = nullptr;

	//����Ʈ�� ���ӽð� (��ƼŬ�ý����� �ƴ�)
	_int				m_iDuration = 0;
	//���ݱ��� �� ��
	_int				m_iTurnCnt = 0;
	
	_bool	m_bCollidable = false;

	STATEDESC	m_tDesc;

public:
	virtual _int StartAct() override;
	virtual _int Update(_double _timeDelta);
	virtual void Play() = 0;
public:
	void	Set_Collidable(_bool _bCollidable) { m_bCollidable = _bCollidable; }
public:
	void	Set_Target(CTransform* _pTarget) { if (nullptr == _pTarget) return; m_pTarget = _pTarget; }

public:
	virtual HRESULT	EffectOn(CCharacter* _pTarget);

	virtual void Free() override;
};
END

