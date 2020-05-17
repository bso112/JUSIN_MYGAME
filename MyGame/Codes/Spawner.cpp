#include "stdafx.h"
#include "..\Headers\Spawner.h"
#include "LevelMgr.h"
#include "ObjMgr.h"
#include "Rat.h"
#include "Gnoll.h"
#include "Crab.h"
#include "Food.h"
#include "Cheese.h"
#include "Texture.h"
#include "ModuleMgr.h"
#include "StageUIMgr.h"
#include "Image.h"

USING(MyGame)

IMPLEMENT_SINGLETON(CSpawner)

CSpawner::CSpawner()
{
}

HRESULT CSpawner::Ready_Prototypes(PDIRECT3DDEVICE9 _pGraphic_Device, _uint level)
{

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;
	Safe_AddRef(pObjMgr);

	CModuleMgr* pModuleMgr = CModuleMgr::Get_Instance();
	if (nullptr == pModuleMgr)
		return E_FAIL;
	Safe_AddRef(pModuleMgr);

	//�ش� ������ �غ��Ѵ�.
	if (0 == level)
	{
		//���� ������Ÿ���� �����.
		pObjMgr->Add_Prototype(L"Rat", SCENE_STAGE, CRat::Create(_pGraphic_Device));
		pObjMgr->Add_Prototype(L"Gnoll", SCENE_STAGE, CGnoll::Create(_pGraphic_Device));
		pObjMgr->Add_Prototype(L"Crab", SCENE_STAGE, CCrab::Create(_pGraphic_Device));

		//������ �ʿ��� �ؽ��ĸ� �����Ѵ�.
		if (FAILED(pModuleMgr->Add_Module(L"Texture_Food", SCENE_STAGE, CTexture::Create(_pGraphic_Device, L"../Bin/Resources/Textures/Item/Food/%d.png", 1))))
			return E_FAIL;

		//���� ������Ÿ���� �����.
		pObjMgr->Add_Prototype(L"Food", SCENE_STAGE, CCheese::Create(_pGraphic_Device));

	}

	//����Ʈ ������Ÿ��
	pObjMgr->Add_Prototype(L"Image_Blood", SCENE_STAGE, CImage::Create(_pGraphic_Device, Vector3(), Vector3(), L"Blood", SCENE_STAGE));

	Safe_Release(pObjMgr);
	Safe_Release(pModuleMgr);
	return S_OK;
}

HRESULT CSpawner::Spawn(_uint _iLevel)
{

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	CLevel* pWorld = CLevelMgr::Get_Instance()->Get_CurrLevel();
	if (nullptr == pWorld)
		return E_FAIL;


	if (0 == _iLevel)
	{

		Vector3 ranPos = pWorld->Get_RandomPos();
		m_listGO[0].push_back(pObjMgr->Add_GO_To_Layer(L"Rat", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[0].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[0].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[0].push_back(pObjMgr->Add_GO_To_Layer(L"Food", SCENE_STAGE, L"Food", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(25.f, 20.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[0].push_back(pObjMgr->Add_GO_To_Layer(L"Food", SCENE_STAGE, L"Food", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(25.f, 20.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[0].push_back(pObjMgr->Add_GO_To_Layer(L"Food", SCENE_STAGE, L"Food", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(25.f, 20.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[0].push_back(pObjMgr->Add_GO_To_Layer(L"Food", SCENE_STAGE, L"Food", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(25.f, 20.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[0].push_back(pObjMgr->Add_GO_To_Layer(L"Food", SCENE_STAGE, L"Food", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(25.f, 20.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[0].push_back(pObjMgr->Add_GO_To_Layer(L"Food", SCENE_STAGE, L"Food", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(25.f, 20.f)), 10.f)));

		for (auto& GO : m_listGO[0])
		{
			Safe_AddRef(GO);
		}
	}

	return S_OK;
}

CGameObject * CSpawner::PickObject(POINT& _pt, _uint _iLevel)
{
	if (DEPTH <= _iLevel)
		return nullptr;

	vector<RECT> UIRect = CStageUIMgr::Get_Instance()->GetUIRect();
	for (auto& rc : UIRect)
	{
		//���� ���콺 ����Ʈ�� UI���� ������ ����
		if (PtInRect(&rc, _pt))
		{
			return nullptr;
		}
	}

	auto& iter = m_listGO[_iLevel].begin();
	while (iter != m_listGO[_iLevel].end())
	{
		//���� ������ ������Ʈ�� ����Ʈ�� �����.
		if (nullptr == *iter)
		{
			Safe_Release(*iter);
			iter = m_listGO[_iLevel].erase(iter);
		}
		else
		{
			//������Ʈ�� ��ŷ�Ѵ�.
			CTransform* pTransform = dynamic_cast<CTransform*>((*iter)->Get_Module(L"Transform"));
			if (nullptr != pTransform)
			{
				if (PtInRect(&pTransform->Get_Collider(), _pt))
					return *iter;
			}
			
			++iter;
		}


	}


	return nullptr;
}



void CSpawner::Free()
{
	for (auto& list : m_listGO)
	{
		for (auto& GO : list)
		{
			Safe_Release(GO);
		}
	}
}
