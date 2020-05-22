#pragma once
#include "Item.h"

BEGIN(MyGame)
class CTexture;
class CSeed abstract : public CItem
{
protected:
	explicit CSeed(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CSeed(CSeed& _rhs);
	virtual ~CSeed() = default;

protected:
	Vector2 m_vOriginalSize;
	//���� �Ǿ��°�
	_bool	m_bFlower = false;

public:
	virtual HRESULT Initialize(void * _param = nullptr);

protected:
	virtual	void OnThrow();
	virtual HRESULT	Render() override;

protected:
	//�ʵ忡 �������� ����� �����´�.(�ڽ��� ��������� ������������)
	virtual Vector3 Get_OriginalSize();

public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;
};
END
