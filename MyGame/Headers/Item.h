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
	explicit CItem(CItem& _rhs);
	virtual ~CItem() = default;

protected:
	vector<const _tchar*>	m_vecActions;
	CVIBuffer*				m_pVIBuffer = nullptr;
	CTransform*				m_pTransform = nullptr;
	CTexture*				m_pTexture = nullptr;
	CShader*				m_pShader = nullptr;
	//사용되었는가? 사용되었으면 슬롯에서 사라진다.
	_bool					m_bUsed = false;
	//던져졌는가? 던져졌으면 Update에서 아이템이 스스로를 움직인다.
	_bool					m_bThrown = false;
	//기본은 드롭된 상태
	_bool					m_bDrop = true;
protected:
	const _tchar*			m_pDescription = nullptr;
	_int					m_iTextureID = 0;
	const _tchar*			m_pTextureTag = nullptr;
	const _tchar*			m_pItemName = nullptr;
	//던져졌을때 도착지점
	Vector3					m_vDest;
public:
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual HRESULT	Render() override;

	

public:
	virtual vector<const _tchar*>* Get_Actions() { return &m_vecActions; }
	virtual const _tchar* Get_Description() { return m_pDescription; }
	virtual HRESULT	Use(CHero* _pHero, const _tchar* _pAction);
	_int	Get_TextureID() { return m_iTextureID; }
	const _tchar*	Get_TextureTag() { return m_pTextureTag; }
	const _tchar*	Get_Name(){ return m_pItemName; }
	_bool	IsDrop() { return m_bDrop; }
	_bool	IsUsed() { return m_bUsed; }
private:
	void	Drop(Vector3 _vDropPos);

public:
	void	Throw(POINT& _pt);

protected:
	virtual	void OnThrow();

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;
};
END
