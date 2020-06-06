#pragma once
#include "Effect.h"
#include "Buff.h"
BEGIN(MyGame)
#define PARTICLE_CNT_FIRE 10
#define RANGE 3
#define DURAION_IN_TURN 8
class CClock_Trigger;
class CSmoke : public CEffect
{
private:
	explicit CSmoke(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CSmoke(CSmoke& _rhs);
	virtual ~CSmoke() = default;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _pArg = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render() override;


private:
	CClock_Trigger*				m_pSpawnTimer = nullptr;
	CParticleSystem::STATEDESC	m_tParticleDesc;
	_bool						m_bPlaying = false;

private:
	CBuff::STATEDESC	m_BuffDesc;

public:
	void	Play()		override;
	void	Set_Collidable(_bool _bCollidable) { m_bCollidableEffect = _bCollidable; }
	HRESULT	EffectOn(CCharacter* _pTarget) override;

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
public:
	static CSmoke* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	CGameObject*	Clone(void* _pArg)override;
	virtual void Free() override;
};
END
