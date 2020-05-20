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
	bool	m_bDead = false;
	bool	m_bActive = true;
	//렌더 깊이 (작을수록 더 먼저그려진다)
	_int	m_iDepth = 0;

private:
	//충돌했나
	bool	m_bCollided = false;
	//충돌한 오브젝트 셋
	set<CGameObject*> m_setCollided;

protected:
	SCENEID		m_eSceneID = SCENE_END;

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
	virtual	_int	Interact(CGameObject* _pOther);


public:
	map<const _tchar*, CModule*>* Get_Modules() { return &m_mapModule; }
public:
	bool Get_isCollided() { return m_bCollided; }
	void Set_isCollided(bool _bCollided) { m_bCollided = _bCollided; }
	//충돌한 오브젝트를 저장한다.
	void Add_Collided(CGameObject* _pColided) { m_setCollided.insert(_pColided); }
	//충돌한 오브젝트 셋의 사이즈를 가져온다.
	size_t Get_CollidedSize() { return m_setCollided.size(); }
	//충돌한 오브젝트 셋에 _pCollied가 있는지 검사한다.
	bool Contain_Collided(CGameObject* _pCollided)
	{
		return m_setCollided.find(_pCollided) != m_setCollided.end();
	}

	bool Erase_Collided(CGameObject* _pCollided)
	{
		//returns the number of elements removed
		return m_setCollided.erase(_pCollided) ? true : false;

	}
	void Set_Dead() { m_bDead = true; }
	const bool& Get_Dead() const { return m_bDead; }


public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollisionStay(CGameObject* _pOther);
	virtual void OnCollisionExit(CGameObject* _pOther);

protected:
	virtual	void OnSetActive(_bool _bActive);


public:
	HRESULT		Set_Module(const _tchar* _pModulePrototypeTag, SCENEID _eSceneID, CModule** _ppModule, const _tchar* _pModuleTag = nullptr, void* _pArg = nullptr);
	CModule*	Get_Module(const _tchar* _eModuleTag);
	_uint		Get_InstanceID() { return m_iInstanceID; }
	HRESULT		Add_Module(const _tchar* _pModuleTag, CModule* _pModule);
	void		Set_Active(_bool _bActive) { m_bActive = _bActive; OnSetActive(_bActive); }
	_bool		Get_Active() { return m_bActive; }
	void		Set_Depth(_int _iDepth) { m_iDepth = _iDepth; }
	_int		Get_Depth() { return m_iDepth; }
	//ppOut을 릴리즈하고, _pOldModuleTag에 해당하는 m_mapModule의 요소를 릴리즈한뒤 ppOut에 새로운 모듈을 셋팅한다.
	HRESULT		Replace_Module(const _tchar* _pOldModuleTag, const _tchar* _pNewModulePrototypeTag, SCENEID _eNewModulePrototypeSceneID, CModule** _ppOutModule, const _tchar* _pNewModuleTag = nullptr);

public:
	virtual CGameObject* Clone(void * _pArg = nullptr) = 0;

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;


};

END