#pragma once
#include "Item.h"
BEGIN(MyGame)
class CStat;
class CEquipment abstract : public CItem
{
public:
	typedef struct tagStats
	{
		float	m_fMaxHP = 0.f;
		float	m_fArmor = 0.f;
		float	m_fAtt = 0.f;
		int		m_iGold = 0;

	}STATS;

	typedef struct tagSTATEDESC
	{
		BASEDESC		m_tBaseDesc;
		STATS			m_tStats;
		_uint			m_iTextureID = 1;
		const _tchar*	m_pDescription;
		const _tchar*	m_pItemName;

	}STATEDESC;
public:

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