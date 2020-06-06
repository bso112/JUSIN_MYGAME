#pragma once
#include "MyButton.h"
BEGIN(MyGame)
class CItem;
class CTransform;
class CVIBuffer;
class CItemInfoPanel;


class CItemSlot final: public CMyButton
{
private:
	explicit CItemSlot(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CItemSlot(CItemSlot& _rhs);
	virtual ~CItemSlot() = default;


private:
	function<void(CItem*)>	m_pSlotListener = nullptr;
	list<CItem*>			m_listItem;
	_uint					m_iTextureID = 0;
	RECT					m_tItemCntPlaceHolder;
	_bool					m_bEquipmentslot = false;
	_bool					m_bQuickSlot = false;

	//������ �ִ� �ð�
	_double					m_dClickTimeAcc = 0.0;
	//���빰 ũ��
	_float					m_fContentCX = 70.f;
	_float					m_fContentCY = 70.f;
	
	
public:
	virtual HRESULT Initialize(Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag, SCENEID _eTextureSceneID, _uint _iTextureID);
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
	//��� ������ �ϳ��� �����۸��� ������.
	void	Equip(CItem* _pItem);
	CItem*	UnEquip();
	void	Set_Equipmentslot() { m_bEquipmentslot = true; }
	void	Set_QuickSlot();
public:
	_bool	IsEmpty(){ return m_listItem.empty(); }
	_bool	Has_Item(CItem* _pItem);
	size_t	Get_ItemCnt() { return m_listItem.size(); }
	CItem*	Get_Item() { if (m_listItem.size() <= 0) return nullptr; return m_listItem.back(); }
	void	Clear();
protected:
	virtual	void OnSetActive(_bool _bActive);

protected:
	virtual HRESULT	OnKeyDown(_int KeyCode) override;
	virtual HRESULT OnKeyPressing(_int KeyCode);
	virtual HRESULT	OnKeyUp(_int KeyCode);
	


public:
	static CItemSlot*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, Vector4 _vPos, Vector2 _vSize, _tchar* _pTextureTag,SCENEID _eTextureSceneID ,_uint _iTextureID =0 );
	virtual void Free() override;
};
END
