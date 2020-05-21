#pragma once
#include "Item.h"

BEGIN(MyGame)
class CTexture;
class CFood abstract : public CItem
{
public:
	typedef struct tagSTATEDESC
	{
		BASEDESC tBaseDesc;
		_float	fHealAmount;
		tagSTATEDESC() {};
		tagSTATEDESC(BASEDESC _tBaseDesc, _float	_fHealAmount)
		{
			tBaseDesc = _tBaseDesc;
			fHealAmount = _fHealAmount;
		}
	}STATEDESC;
protected:
	explicit CFood(PDIRECT3DDEVICE9 _pGrahic_Device) : CItem(_pGrahic_Device) {};
	explicit CFood(CFood& _rhs);
	virtual ~CFood() = default;

protected:
	STATEDESC	m_tDesc;
public:
	virtual HRESULT Initialize(void * _param = nullptr) override;

public:
	virtual HRESULT	Use(CHero* _pHero, const _tchar* _pAction) override;



public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
