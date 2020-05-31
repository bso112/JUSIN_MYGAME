#pragma once
#include "Item.h"
#include "DialogMgr.h"
BEGIN(MyGame)
class CTexture;
class CPotion abstract : public CItem
{

protected:
	explicit CPotion(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CPotion(CPotion& _rhs);
	virtual ~CPotion() = default;

protected:
	Vector2 m_vOriginalSize;
	STATEDESC m_tDesc;

public:
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT	Use(CHero* _pHero, const _tchar** _pAction) override;
protected:
	virtual	void OnThrowEnd() override;
	virtual	void OnShatter();
	virtual	void OnDrink(CHero * _pHero);

protected:
	//�ʵ忡 �������� ����� �����´�.(�ڽ��� ��������� ������������)
	virtual Vector3 Get_OriginalSize();

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);


public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};
END
