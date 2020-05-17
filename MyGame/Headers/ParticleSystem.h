#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CImage;
class CTransform;
class CParticleSystem final: public CGameObject
{

public:
	//라이프타임, 지속시간, 속도(힘)
	typedef struct tagStateDesc
	{
		//파티클시스템 위치
		BASEDESC		m_tBaseDesc;
		Vector2			m_vParticleSize = {};
		_double			m_dLifeTime = 0.0;
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
	list<CImage*>	m_listParticle;
	bool			m_bLoop;

public:
	_int		Update(_double _timeDelta);
	_int		LateUpdate(_double _timeDelta);
	HRESULT		Render();

public:
	HRESULT		Play(_double _timeDelta, _uint _iParticleCnt);
public:
	HRESULT	Initialize_Prototype();
	HRESULT	Initialize(void* _pArg);

private:
	void Spread(_double _timeDelta, _uint _iParticleCnt);
	

public:
	static CParticleSystem* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject * Clone(void * _pArg = nullptr) override;

public:
	virtual void Free() override;

};
END
