#pragma once
#include "Item.h"

BEGIN(MyGame)
class CTexture;
class CPotion final : public CItem
{

protected:
	explicit CPotion(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CPotion(CPotion& _rhs);
	virtual ~CPotion() = default;

protected:
	Vector2 m_vOriginalSize = Vector3(20.f, 20.f);
	STATEDESC m_tDesc;

public:
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT	Use(CHero* _pHero, const _tchar** _pAction) override;
protected:

	virtual	void OnThrowEnd() override;
	virtual HRESULT	Render() override;

protected:
	//�ʵ忡 �������� ����� �����´�.(�ڽ��� ��������� ������������)
	virtual Vector3 Get_OriginalSize();

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);

public:
	static CPotion* Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	CPotion * Clone(void * _param = nullptr);

public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};
END
