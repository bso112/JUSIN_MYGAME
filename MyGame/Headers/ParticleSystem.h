#pragma once
#include "GameObject.h"
#include "Particle.h"
BEGIN(MyGame)
class CTransform;
class CClock_Delay;
class CObjMgr;
class CParticleSystem final: public CGameObject
{
public:
	//������Ÿ��, ���ӽð�, �ӵ�(��)
	typedef struct tagStateDesc
	{
		//��ƼŬ�ý��� ��ġ
		BASEDESC		m_tBaseDesc;
		Vector2			m_vParticleSize = {};
		//��ƼŬ�� ������Ÿ��
		_double			m_dLifeTime = 0.0;
		//��ƼŬ �ý����� ���ӽð�
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
	CTransform*			m_pTransform = nullptr;
	tagStateDesc		m_tDesc;
	list<CGameObject*>	m_listParticle;
	bool				m_bLoop;
	CClock_Delay*		m_pDeadClock = nullptr; 
	CObjMgr*			m_pObjMgr = nullptr;

public:
	_int		Update(_double _timeDelta) override;
	_int		LateUpate(_double _timeDelta) override;
	HRESULT		Render();


public:
	HRESULT	Initialize_Prototype();
	HRESULT	Initialize(void* _pArg);

public:
	//������ ��ä�ø������ ����
	void Spread(Vector2 _dir, _double _timeDelta, _uint _iParticleCnt);
	//�� �ڸ����� �Ǿ���� (��, ����..). _rc�� �Ǿ���� ����
	void RollUp(RECT& _rc, _uint _iParticleCnt);

public:
	static CParticleSystem* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual CGameObject * Clone(void * _pArg = nullptr) override;

private:
	CParticle::STATEDESC CreateParticleDesc();

public:
	virtual void Free() override;

};
END