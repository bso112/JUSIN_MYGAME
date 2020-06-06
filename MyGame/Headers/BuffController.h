#pragma once
#include "Base.h"
#include "Buff.h"
BEGIN(MyGame)
#define MAX_BUFFICON 10
class CImage;
class CBuffController final :public CBase
{
private:
	explicit CBuffController(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CBuffController() = default;

private:
	PDIRECT3DDEVICE9 m_pGraphic_Device = nullptr;
	list<CBuff*>	m_listBuff;
	CImage*			m_pBuffIcons[MAX_BUFFICON];
	_bool			m_isPlayer = false;

public:
	HRESULT	Initialize(_bool _isPlayer);
	_int	Act(CCharacter* _pTarget);
	HRESULT	Update_BuffIcon();
	
public:
	HRESULT Add_Buff(CBuff* _pBuff);
	void	Set_IsPlayer(bool _bPlayer) { m_isPlayer = _bPlayer; }

public:
	static CBuffController* Create(PDIRECT3DDEVICE9 _pGraphic_Device, _bool _isPlayer = false);

public:
	virtual void Free() override;

};
END
