#pragma once
#include "Base.h"

BEGIN(MyGame)

class CRenderer;
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
public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);
	virtual _int	Update(_double _timeDelta);
	virtual _int	LateUpate(_double _timeDelta);
	virtual HRESULT	Render();


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