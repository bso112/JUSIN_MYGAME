#pragma once
#include "Item.h"
BEGIN(MyGame)
class CStat;
class CEquipment abstract : public CItem
{

protected:
	STATEDESC	m_tDesc;
	BODYPART	m_eBodyPart = BODY_END;
protected:
	explicit CEquipment(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CEquipment(CEquipment& _rhs);
	virtual ~CEquipment() = default;

public:
	virtual HRESULT Initialize(void * _param = nullptr);
public:
	virtual HRESULT	Use(CHero* _pHero, const _tchar** _pAction) override;
public:
	STATS Get_Stats() { return m_tDesc.m_tStats; }
protected:
	virtual Vector3 Get_OriginalSize() override;
public:
	virtual void Free() override;


};

END