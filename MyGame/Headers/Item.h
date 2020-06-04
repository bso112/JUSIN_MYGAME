#pragma once
#include "GameObject.h"

#include "Transform.h"
#include "VIBuffer.h"
#include "Texture.h"
BEGIN(MyGame)
#define COLLIDER_SIZE Vector2(15.f, 15.f)
class CHero;
class CInventory;
class CItem abstract : public CGameObject
{
public:
	typedef struct tagStats
	{
		float	m_fMaxHP = 0.f;
		float	m_fHp = 0.f;
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
		D3DXCOLOR		m_Color = 0xffffffff;
	}STATEDESC;
	friend class CItemFactory;
protected:
	explicit CItem(PDIRECT3DDEVICE9 _pGrahic_Device) : CGameObject(_pGrahic_Device){};
	explicit CItem(CItem& _rhs);
	virtual ~CItem() = default;

protected:
	vector<const _tchar*>	m_vecActions;
	CVIBuffer*				m_pVIBuffer = nullptr;
	CTransform*				m_pTransform = nullptr;
	CTransform::STATEDESC	m_tTransformDesc = CTransform::STATEDESC(300.f, 300.f);
	CTexture*				m_pTexture = nullptr;
	CShader*				m_pShader = nullptr;
	//���Ǿ��°�? ���Ǿ����� ���Կ��� �������.
	_bool					m_bUsed = false;
	//�������°�? ���������� Update���� �������� �����θ� �����δ�.
	_bool					m_bThrown = false;
	//�⺻�� ��ӵ� ����
	_bool					m_bDrop = true;

protected:
	const _tchar*			m_pDescription = nullptr;
	_int					m_iTextureID = 0;
	const _tchar*			m_pTextureTag = nullptr;
	const _tchar*			m_pItemName = nullptr;
	//���������� ��������
	Vector3					m_vDest;
	_bool					m_bStackable = false;


public:
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual _int	Update(_double _timeDelta) ;
	virtual _int	LateUpate (_double _timeDelta) override;
	virtual HRESULT	Render() override;

	

public:
	virtual vector<const _tchar*>* Get_Actions() { return &m_vecActions; }
	virtual const _tchar* Get_Description() { return m_pDescription; }
	//Equip�� ��� Use�� �Ŀ� UnEquip���� �ٲ� �� ������ action�� ���������ͷ� �޴´�.
	virtual HRESULT	Use(CHero* _pHero, const _tchar** _pAction);
	//���谰�� ���, �׳� ���� ������ �����.
	void	Use() { m_bUsed = true; }
public:
	_int	Get_TextureID() { return m_iTextureID; }
	const _tchar*	Get_TextureTag() { return m_pTextureTag; }
	const _tchar*	Get_Name(){ return m_pItemName; }
	_bool	IsDrop() { return m_bDrop; }
	_bool	IsUsed() { return m_bUsed; }
	
public:
	virtual	_int	Interact(CGameObject* _pOther) override;
	virtual	void	OnPickUp(CHero*	_pHero, CInventory* _pInventory);

protected:
	virtual _bool	IsInteractable() { return true; }

public:
	void	Drop(Vector3 _vDropPos);
	virtual void	Throw(POINT& _pt);
	_bool	CanStackWith(CItem* pItem);
protected:
	virtual	void OnThrowStart();
	virtual	void OnThrowEnd();
	
protected:
	//�ʵ忡 �������� ����� �����´�.(�ڽ��� ��������� ������������)
	virtual Vector3 Get_OriginalSize() = 0;
public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};
END
