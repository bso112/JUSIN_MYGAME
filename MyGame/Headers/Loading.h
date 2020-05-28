#pragma once
#include "Base.h"
BEGIN(MyGame)
/*
�� ��ȯ��, �����͸� �ε��Ҷ� ���� Initialize���� ���� �ϰ� �Ǹ� 
�����Ͱ� ���ſ���, Initialize���� �ڵ��� �帧�� ��ü�Ǿ� ȭ���� ���ߴ� ������ �߻��Ѵ�.
�̸� �����ϱ� ���� ��Ƽ�����带 �̿��� �����͸� �ε��ϴ� ���ÿ� ȭ���� �����Ѵ�.
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
	_bool				m_bFinish = false;
public:
	//�����带 �����Ѵ�.
	HRESULT	Initialize(SCENEID _eSceneID);

public:
	HRESULT				Initialize_Stage();
public:
	SCENEID				Get_SceneID(){ return m_eSceneID; }
	CRITICAL_SECTION	Get_CriticalSection() { return m_CriticalSection; }
	_bool				IsFinish() { return m_bFinish; }
	void				Set_Finish() { m_bFinish = true; }
public:
	static CLoading* Create(PDIRECT3DDEVICE9 _pGraphic_Device, SCENEID _eSceneID);
	virtual void Free() override;

};

END