#pragma once
#include "MyButton.h"
BEGIN(MyGame)
class CItem;
class CTransform;
class CVIBuffer;
//�̰� ��ư���ݾ�?
class CItemSlot : public CMyButton
{
public:
	explicit CItemSlot();
	virtual ~CItemSlot() = default;


private:
	CItem*	m_pItem = nullptr;
	CTransform*	m_pTransform = nullptr;
	CVIBuffer*	m_pVIBuffer = nullptr;
	_uint	m_iItemCnt = 0;

public:
	//���콺Ŭ���� �޴´�.
	_int	Update();
	
public:
	HRESULT	Remove_Item(CItem* _pItem);
	HRESULT	Add_Item(CItem* _pItem);

private:
	//�˾�â�� ����. (��ư�� ������ ����Լ��� �����Ѵ�)
	void	OnClick();


public:
	static CItemSlot* Create();
	virtual void Free() override;
};
END
