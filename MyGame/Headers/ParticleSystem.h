#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CParticle;
class CTransform;
class CClock_Delay;
class CParticleSystem final: public CGameObject
{
public:
	//라이프타임, 지속시간, 속도(힘)
	typedef struct tagStateDesc
	{
		//파티클시스템 위치
		BASEDESC		m_tBaseDesc;
		Vector2			m_vParticleSize = {};
		//파티클의 라이프타임
		_double			m_dLifeTime = 0.0;
		//파티클 시스템의 지속시간
		_double			m_dDuration = 0.0;
		_float			m_fSpeed = 0.f;
		const _tchar*	m_pTextureTag = L"";
		SCENEID			m_eTextureSceneID = SCENE_END;
	}STATEDESC;

	
private:
	explicit CParticleSystem(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CParticleSystem(CParticleSystem& _rhs);
	virtual ~CParticleSystem() = default;

private:
	CTransform*		m_pTransform = nullptr;
	tagStateDesc	m_tDesc;
	list<CParticle*>	m_listParticle;
	bool			m_bLoop;
	CClock_Delay*	m_pDeadClock = nullptr; 

public:
	_int		Update(_double _timeDelta) override;
	_int		LateUpate(_double _timeDelta) override;
	HRESULT		Render();


public:
	HRESULT	Initialize_Prototype();
	HRESULT	Initialize(void* _pArg);

public:
	void Spread(Vector2 _dir, _double _timeDelta, _uint _iParticleCnt);
	

public:
	static CParticleSystem* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject * Clone(void * _pArg = nullptr) override;

public:
	virtual void Free() override;

};
END
