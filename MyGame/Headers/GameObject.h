#pragma once
#include "Base.h"
#include "Renderer.h"
#include "Pipline.h"
BEGIN(MyGame)

class CModule;
class CGameObject abstract : public CBase
{
protected:
	explicit CGameObject() {};
	explicit CGameObject(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CGameObject(CGameObject& _rhs);
	virtual ~CGameObject() = default;

protected:
	CRenderer*				m_pRenderer = nullptr;
	PDIRECT3DDEVICE9		m_pGraphic_Device = nullptr;
	map<const _tchar*, CModule*>	m_mapModule;
	CPipline*						m_pPipline = nullptr;

protected:
	bool	m_bDying = false;
	bool	m_bDead = false;
	bool	m_bActive = true;
	//���� ���� (�������� �� �����׷�����)
	_int	m_iDepth = 0;
	//�Ȱ� �ӿ��� ���̴°�
	_bool			m_bVisuable = false;
	//�ѹ� �����°�
	_bool			m_bVisited = false;

private:
	//�浹�߳�
	bool	m_bCollided = false;
	//�浹�� ������Ʈ ��
	set<CGameObject*> m_setCollided;

protected:
	SCENEID		m_eSceneID = SCENE_END;
	//���� ��������
	bool		m_bTurnEnd = false;
	//����Ǿ ���� �׳� �ѱ����
	_bool		m_bParalyze = false;

private:
	static _uint	m_iMaxInstanceID;
	_uint	m_iInstanceID = 0;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _pArg = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();

public:
	virtual _int		StartAct();
	virtual _int		UpdateAct();
	virtual	_int	Interact(CGameObject* _pOther);
	void		Set_Visuable(_bool _bVisuable) { m_bVisuable = _bVisuable; }
	void		Set_Visited(_bool _bVisited) { m_bVisited = _bVisited; }

public:
	virtual	void	SetTurnState(_bool _bTurnEnd) { m_bTurnEnd = _bTurnEnd; }
	virtual	_bool	IsTurnEnd() { return m_bTurnEnd; }
	virtual	_bool	IsParalyzed() { return m_bParalyze; }
public:
	map<const _tchar*, CModule*>* Get_Modules() { return &m_mapModule; }
public:
	bool Get_isCollided() { return m_bCollided; }
	void Set_isCollided(bool _bCollided) { m_bCollided = _bCollided; }
	//�浹�� ������Ʈ�� �����Ѵ�.
	void Add_Collided(CGameObject* _pColided) { m_setCollided.insert(_pColided); }
	//�浹�� ������Ʈ ���� ����� �����´�.
	size_t Get_CollidedSize() { return m_setCollided.size(); }
	//�浹�� ������Ʈ �¿� _pCollied�� �ִ��� �˻��Ѵ�.
	bool Contain_Collided(CGameObject* _pCollided)
	{
		return m_setCollided.find(_pCollided) != m_setCollided.end();
	}

	bool Erase_Collided(CGameObject* _pCollided)
	{
		//returns the number of elements removed
		return m_setCollided.erase(_pCollided) ? true : false;

	}
	void Set_Dead() { m_bDead = true; OnDead(); }
	const bool& Get_Dead() const { return m_bDead; }


public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollisionStay(CGameObject* _pOther);
	virtual void OnCollisionExit(CGameObject* _pOther);

protected:
	virtual	void OnSetActive(_bool _bActive);
	virtual void OnDead();


public:
	HRESULT		Set_Module(const _tchar* _pModulePrototypeTag, SCENEID _eSceneID, CModule** _ppModule, const _tchar* _pModuleTag = nullptr, void* _pArg = nullptr);
	CModule*	Get_Module(const _tchar* _eModuleTag);
	_uint		Get_InstanceID() { return m_iInstanceID; }
	HRESULT		Add_Module(const _tchar* _pModuleTag, CModule* _pModule);
	void		Set_Active(_bool _bActive) { m_bActive = _bActive; OnSetActive(_bActive); }
	_bool		Get_Active() { return m_bActive; }
	void		Set_Depth(_int _iDepth) { m_iDepth = _iDepth; }
	_int		Get_Depth() { return m_iDepth; }
	//ppOut�� �������ϰ�, _pOldModuleTag�� �ش��ϴ� m_mapModule�� ��Ҹ� �������ѵ� ppOut�� ���ο� ����� �����Ѵ�.
	HRESULT		Replace_Module(const _tchar* _pOldModuleTag, const _tchar* _pNewModulePrototypeTag, SCENEID _eNewModulePrototypeSceneID, CModule** _ppOutModule, const _tchar* _pNewModuleTag = nullptr);

public:
	virtual CGameObject* Clone(void * _pArg = nullptr) = 0;

public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;


};

END