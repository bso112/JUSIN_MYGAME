#pragma once
#include "Item.h"
#include "Buff.h"
#include "Equipment.h"
BEGIN(MyGame)
class CScroll final : public CItem
{
public:
	enum TYPE { TYPE_ENCHANT, TYPE_END };

public:
	typedef struct tagStateDesCScroll
	{
		CItem::STATEDESC m_tItemDesc;
		CBuff::TYPE			m_eImmune = CBuff::TYPE_END;
	}STATEDESC;
protected:
	explicit CScroll(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CScroll(CScroll& _rhs);
	virtual ~CScroll() = default;

private:
	CScroll::STATEDESC	m_tStateDesc;
	//모두 사용했는가.
	_int				m_iUseCnt = 0;
	_bool				m_bRunOut = false;
public:
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT	Use(CHero* _pHero, const _tchar** _pAction) override;

public:
	HRESULT	Enchant(CEquipment* _pItem);

private:


public:
	static CScroll * Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	CGameObject * Clone(void * _param = nullptr);
	virtual void Free() override;

	// CItem을(를) 통해 상속됨
	virtual Vector3 Get_OriginalSize() override;
};

END