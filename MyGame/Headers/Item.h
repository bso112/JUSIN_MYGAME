#pragma once
#include "GameObject.h"

#include "Transform.h"
#include "VIBuffer.h"
#include "Texture.h"
BEGIN(MyGame)
class CHero;
class CItem abstract : public CGameObject
{
protected:
	explicit CItem(PDIRECT3DDEVICE9 _pGrahic_Device) : CGameObject(_pGrahic_Device){};
	explicit CItem(CItem& _rhs) : CGameObject(_rhs) {};
	virtual ~CItem() = default;

protected:
	vector<const _tchar*>	m_vecActions;
	CVIBuffer*				m_pVIBuffer = nullptr;
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_pTexture = nullptr;

protected:
	const _tchar*			m_pDescription;



public:
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);

public:
	virtual vector<const _tchar*>* Get_Actions() { return &m_vecActions; }
	virtual const _tchar* Get_Description() { return m_pDescription; }
	virtual HRESULT	Use(CHero* _pHero, const _tchar* _pAction);

public:
	void RemoveFormInventory();
public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
