#pragma once
#include "Monster.h"

BEGIN(MyGame)
class CTexture;
class CAIStateCon;
class CTengu final : public CMonster
{
private:
	explicit CTengu(PDIRECT3DDEVICE9 _pGraphic_Device) :CMonster(_pGraphic_Device) {};
	explicit CTengu(CTengu& _rhs);
	virtual ~CTengu() = default;


private:
	//���ݹ��� ��
	_int	m_iHitCnt = 0;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);



public:
	static CTengu* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CMonster��(��) ���� ��ӵ�
	virtual CGameObject * Clone(void * _param = nullptr) override;


public:
	void OnDead() override;
	virtual void OnTakeDamage(float _fDamage) override;
public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
