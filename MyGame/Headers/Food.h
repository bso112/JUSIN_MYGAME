#pragma once
#include "Item.h"

BEGIN(MyGame)
class CTexture;
class CFood : public CItem
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
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual _int	Update(_double _timeDelta) override;
	virtual _int	LateUpate(_double _timeDelta) override;
	virtual HRESULT	Render() override;
public:
	static CFood*	Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	virtual CGameObject * Clone(void * _param = nullptr) override;
public:
	virtual HRESULT	Use(CHero* _pHero, const _tchar* _pAction) override;

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
