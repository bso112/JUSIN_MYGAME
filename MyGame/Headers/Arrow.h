#pragma once
#include "Item.h"

BEGIN(MyGame)
class CArrow : public CItem
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
protected:
	explicit CArrow(PDIRECT3DDEVICE9 _pGrahic_Device) : CItem(_pGrahic_Device) {};
	explicit CArrow(CArrow& _rhs) : CItem(_rhs) {};
	virtual ~CArrow() = default;

private:
	STATEDESC	m_tDesc = {};
	_bool		m_bDamagable = false;
public:
	HRESULT Initialize(void * _param);

public:
	static CArrow * Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	CGameObject * Clone(void * _param);
	void	Free();

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
protected:
	virtual	void OnThrowStart();
	virtual	void OnThrowEnd();

	// CItem을(를) 통해 상속됨
	virtual Vector3 Get_OriginalSize() override;
};
END
