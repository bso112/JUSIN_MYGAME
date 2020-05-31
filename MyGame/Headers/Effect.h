#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "ParticleSystem.h"
BEGIN(MyGame)
class CClock_Delay;
class CEffect abstract : public CGameObject
{
protected:
	explicit CEffect(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CEffect(CEffect& _rhs);
	virtual ~CEffect() = default;


protected:
	CParticleSystem*	m_pParticleSystem = nullptr;
	CTransform*			m_pTransform = nullptr;
	//쫒아다닐 타겟
	CTransform*			m_pTarget = nullptr;

	//이펙트의 지속시간 (파티클시스템이 아님)
	_int				m_iDuration = 0;
	//지금까지 센 턴
	_int				m_iTurnCnt = 0;
	
	_bool	m_bCollidable = false;

public:
	virtual _int StartAct() override;
	virtual _int Update(_double _timeDelta);
	virtual void Play() = 0;
public:
	void	Set_Collidable(_bool _bCollidable) { m_bCollidable = _bCollidable; }
public:
	void	Set_Target(CTransform* _pTarget) { if (nullptr == _pTarget) return; m_pTarget = _pTarget; }


	virtual void Free() override;
};
END

