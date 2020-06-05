#pragma once
#include "Item.h"
#include "Buff.h"
BEGIN(MyGame)
class CStat;
class CEquipment abstract : public CItem
{

protected:
	STATEDESC	m_tDesc;
	BODYPART	m_eBodyPart = BODY_END;	
	//저항속성
	CBuff::TYPE	m_eImmune = CBuff::TYPE_END;

protected:
	explicit CEquipment(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CEquipment(CEquipment& _rhs);
	virtual ~CEquipment() = default;

public:
	virtual HRESULT Initialize(void * _param = nullptr);
public:
	virtual HRESULT	Use(CHero* _pHero, const _tchar** _pAction) override;

protected:
	virtual HRESULT	OnEquip(CHero* _pHero);
	virtual HRESULT OnUnEquip(CHero* _pHero);
public:
	STATS			Get_Stats() { return m_tDesc.m_tStats; }
	CBuff::TYPE		Get_Immune() { return m_eImmune; }
	void			Set_Immune(CBuff::TYPE _eImmune) { m_eImmune = _eImmune; }
protected:
	virtual Vector3 Get_OriginalSize() override;
public:
	virtual void Free() override;


};

END