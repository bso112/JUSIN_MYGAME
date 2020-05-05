#pragma once
#include "Monster.h"

BEGIN(MyGame)
class CTexture;
class CStateCon;
class CRat final : public CMonster
{
private:
	explicit CRat(PDIRECT3DDEVICE9 _pGraphic_Device) :CMonster(_pGraphic_Device) {};
	explicit CRat(CRat& _rhs);
	virtual ~CRat() = default;
	
private:
	CAnimator*		m_pAnimator = nullptr;
	CStateCon*		m_pStateCon = nullptr;
public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT Act(_int _iTurnCnt) override;
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

public:
	static CRat* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CMonster��(��) ���� ��ӵ�
	virtual CGameObject * Clone(void * _param = nullptr) override;

private:
	virtual void Process() override;
	virtual void Update_State() override;
	virtual void OnDead() override;
	virtual void OnTakeDamage() override;
	virtual void Scene_Change() override;


public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};

class CHunting_Jump : public Hunting
{
private:
	explicit CHunting_Jump(CCharacter* _pActor) :Hunting(_pActor) {};
private:
	Vector3 m_vJumpVelo;
	
public:
	virtual HRESULT Initialize(Vector3 _vJumpVelo);
	virtual CState*	Update(_double _timeDelta) override;
public:
	static CHunting_Jump* Create(CCharacter* _pActor, Vector3 _vJumpVelo);
	virtual void Free() override;
};
END
