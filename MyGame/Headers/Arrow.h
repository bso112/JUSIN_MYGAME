#pragma once
#include "Item.h"

BEGIN(MyGame)
class CArrow : public CItem
{
public:

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
