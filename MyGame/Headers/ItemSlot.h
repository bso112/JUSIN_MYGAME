#pragma once
#include "MyButton.h"
BEGIN(MyGame)
class CItem;
class CTransform;
class CVIBuffer;
//이거 버튼이잖아?
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
	//마우스클릭을 받는다.
	_int	Update();
	
public:
	HRESULT	Remove_Item(CItem* _pItem);
	HRESULT	Add_Item(CItem* _pItem);

private:
	//팝업창을 띄운다. (버튼에 아이템 사용함수를 연결한다)
	void	OnClick();


public:
	static CItemSlot* Create();
	virtual void Free() override;
};
END
