#pragma once
#include "Base.h"
BEGIN(MyGame)
/*
씬 전환시, 데이터를 로드할때 만약 Initialize에서 전부 하게 되면 
데이터가 무거운경우, Initialize에서 코드의 흐름이 정체되어 화면이 멈추는 현상이 발생한다.
이를 방지하기 위해 멀티스레드를 이용해 데이터를 로드하는 동시에 화면을 렌더한다.
*/
class CLoading :
	public CBase
{
private:
	explicit CLoading(PDIRECT3DDEVICE9 _pGraphic_Device);
	virtual ~CLoading() = default;

private:	
	PDIRECT3DDEVICE9	m_pGraphic_Device = nullptr;
	CRITICAL_SECTION	m_CriticalSection;
	HANDLE				m_Handle;
	SCENEID				m_eSceneID = SCENE_END;
public:
	//스레드를 생성한다.
	HRESULT	Initialize(SCENEID _eSceneID);
	HRESULT	Load_Scene(SCENEID _eSceneID);

public:
	SCENEID				Get_SceneID(){ return m_eSceneID; }
	CRITICAL_SECTION	Get_CriticalSection() { return m_CriticalSection; }

public:
	static CLoading* Create(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID);
	virtual void Free() override;

};

END