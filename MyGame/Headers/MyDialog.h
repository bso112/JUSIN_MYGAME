#pragma once
#include "GameObject.h"

BEGIN(MyGame)
#define	MAX_SENTENCE 5
class CMyDialog final :public CGameObject
{
private:
	explicit CMyDialog(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CMyDialog(CMyDialog& _rhs);
	virtual ~CMyDialog() = default;

private:
	RECT m_pPlaceHolder[MAX_SENTENCE];
	list<wstring*> m_senetencs;

public:
	virtual HRESULT Initialize(void * _pArg = nullptr);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();
public:
	void	Log(wstring* _pLog);
public:
	static CMyDialog * Create(PDIRECT3DDEVICE9 _pGrahic_Device);
	virtual CGameObject * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};
END
