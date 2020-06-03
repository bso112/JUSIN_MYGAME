#pragma once
#include "Item.h"
BEGIN(MyGame)
class CWand final : public CItem
{
public:
	enum TYPE {TYPE_LIGHTING, TYPE_END};

public:
	typedef struct tagStateDescWand
	{
		CItem::STATEDESC m_tItemDesc;
		TYPE	m_eType;
		_uint	m_iMaxZapCnt;
	}STATEDESC;
protected:
	explicit CWand(PDIRECT3DDEVICE9 _pGrahic_Device);
	explicit CWand(CWand& _rhs);
	virtual ~CWand() = default;

private:
	CWand::STATEDESC	m_tStateDesc;
	//모두 사용했는가.
	_int				m_iUseCnt = 0;
	_bool				m_bRunOut = false;
public:
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT	Use(CHero* _pHero, const _tchar** _pAction) override;
public:
	HRESULT	Zap(Vector2 _vOrigin, POINT _pt);

private:
	HRESULT Zap_Lighting(Vector2 _vOrigin, POINT _pt);


public:
	static CWand * Create(PDIRECT3DDEVICE9 _pGrahic_Device, _tchar* _pFilePath = nullptr);
	CGameObject * Clone(void * _param = nullptr);
	virtual void Free() override;

	// CItem을(를) 통해 상속됨
	virtual Vector3 Get_OriginalSize() override;
};

END