#pragma once
#include "GameObject.h"

#define ACT_DROP	L"DROP"
#define ACT_THROW	L"THROW"
#define ACT_USE		L"USE"


BEGIN(MyGame)
class CItem abstract : public CGameObject
{
protected:
	explicit CItem(PDIRECT3DDEVICE9 _pGrahic_Device) : CGameObject(_pGrahic_Device){};
	explicit CItem(CItem& _rhs) : CGameObject(_rhs) {};
	virtual ~CItem() = default;

protected:
	vector<const _tchar*> m_vecActions;

public:
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);

public:
	const vector<const _tchar*>* Get_Actions() { return &m_vecActions; }
};
END
