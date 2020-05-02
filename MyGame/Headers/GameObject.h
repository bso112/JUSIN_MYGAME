#pragma once
#include "Base.h"
#include "Renderer.h"

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

protected:
	bool	m_bDead = false;

private:
	//충돌했나
	bool	m_bCollided = false;
	//충돌한 오브젝트 셋
	set<CGameObject*> m_setCollided;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();


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

		return m_setCollided.erase(_pCollided) ? true : false;

	}
	void Set_Dead() { m_bDead = true; }
	const bool& Get_Dead() const { return m_bDead; }


public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollisionStay(CGameObject* _pOther);
	virtual void OnCollisionExit(CGameObject* _pOther);


public:
	HRESULT		Set_Module(const _tchar* _eModuleTag, SCENEID _eSceneID, CModule** _ppModule, void* _pArg = nullptr);
	CModule*	Get_Module(const _tchar* _eModuleTag);
public:
	virtual CGameObject* Clone(void * _param = nullptr) = 0;

public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};

END