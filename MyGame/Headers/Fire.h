#pragma once
#include "Effect.h"
#include "Buff.h"

BEGIN(MyGame)
#define PARTICLE_CNT_FIRE 10
class CClock_Trigger;
class CFire : public CEffect
{
private:
	explicit CFire(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CFire(CFire& _rhs);
	virtual ~CFire() = default;

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
	CBuff::STATEDESC	m_BurnDesc;

public:
	void	Play()		override;
	void	Set_Collidable(_bool _bCollidable) { m_bCollidable = _bCollidable; }
	HRESULT	EffectOn(CCharacter* _pTarget) override;

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
public:
	static CFire* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	CGameObject*	Clone(void* _pArg)override;
	virtual void Free() override;
};
END
