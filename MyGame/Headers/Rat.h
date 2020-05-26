#pragma once
#include "Monster.h"

BEGIN(MyGame)
class CTexture;
class CAIStateCon;
class CRat final : public CMonster
{
private:
	explicit CRat(PDIRECT3DDEVICE9 _pGraphic_Device) :CMonster(_pGraphic_Device) {};
	explicit CRat(CRat& _rhs);
	virtual ~CRat() = default;
	

	
public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);


public:
	static CRat* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CMonster��(��) ���� ��ӵ�
	virtual CGameObject * Clone(void * _param = nullptr) override;

protected:
	virtual void OnDead();


public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};


END
