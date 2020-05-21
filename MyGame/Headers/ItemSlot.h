#pragma once
#include "MyButton.h"
BEGIN(MyGame)
class CItem;
class CTransform;
class CVIBuffer;
class CItemInfoPanel;

//���빰 ũ��
#define CONTENTX 20.f
#define CONTENTY 20.f
class CItemSlot final: public CMyButton
{
private:
	explicit CItemSlot(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CItemSlot(CItemSlot& _rhs);
	virtual ~CItemSlot() = default;


private:
	function<void(CItem*)> m_pSlotListener = nullptr;
	list<CItem*>	m_listItem;
	
public:
	virtual HRESULT Initialize(Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	virtual _int	Update(_double _timeDelta)	override;
	virtual _int	LateUpate(_double _timeDelta)override;
	virtual HRESULT	Render() override;
	


public:
	HRESULT	Add_Item(CItem* _pItem);
	virtual HRESULT	Set_Listener(function<void(CItem*)> _listener);
	//������ ������ �ִ� �������� ���Ǹ� �������� �����.
	HRESULT	Remove_Item();
	//������ ������ �ִ� �������� ������Ʈ �Ŵ����� ����ϰ�, ������ ������ ����Ʈ���� ������.
	HRESULT	Drop_Item();
public:
	_bool	IsEmpty(){ return m_listItem.empty(); }
	size_t	Get_ItemCnt() { return m_listItem.size(); }
	CItem*	Get_Item() { return m_listItem.back(); }

protected:
	virtual	void OnSetActive(_bool _bActive);

protected:
	virtual HRESULT	OnKeyDown(_int KeyCode) override;
	

public:
	static CItemSlot*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID);
	virtual void Free() override;
};
END
