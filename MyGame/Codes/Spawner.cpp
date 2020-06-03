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
#include "Pipline.h"
#include "Fire.h"
#include "FireFlower.h"
#include "IceFlower.h"
#include "ShieldFlower.h"
#include "TextureLoader.h"
#include "Key.h"
#include "ItemFactory.h"
#include "Smoke.h"
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

	CTextureLoader* pLoader = CTextureLoader::Get_Instance();
	if (nullptr == pLoader)
		return E_FAIL;
	Safe_AddRef(pLoader);

#pragma region legacy
	//몬스터 프로토타입을 만든다.
	pObjMgr->Add_Prototype(L"Rat", SCENE_STAGE, CRat::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Gnoll", SCENE_STAGE, CGnoll::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Crab", SCENE_STAGE, CCrab::Create(_pGraphic_Device));

	//레벨에 필요한 텍스쳐를 생성한다.
	if (FAILED(pModuleMgr->Add_Module(L"Texture_Food", SCENE_STAGE, CTexture::Create(_pGraphic_Device, L"../Bin/Resources/Textures/Item/Food/%d.png", 1))))
		return E_FAIL;

	pLoader->Create_Textrues_From_Folder_Anim(_pGraphic_Device, SCENE_STAGE, L"../Bin/Resources/Textures/Item/");

	//음식 프로토타입을 만든다.
	pObjMgr->Add_Prototype(L"Cheese", SCENE_STAGE, CCheese::Create(_pGraphic_Device));
	//씨앗 프로토타입을 만든다.
	pObjMgr->Add_Prototype(L"FireFlower", SCENE_STAGE, CFireFlower::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"IceFlower", SCENE_STAGE, CIceFlower::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"ShieldFlower", SCENE_STAGE, CShieldFlower::Create(_pGraphic_Device));
	//열쇠 프로토타입을 만든다.
	pObjMgr->Add_Prototype(L"Key", SCENE_STAGE, CKey::Create(_pGraphic_Device));

#pragma endregion

	CItemFactory::Make_Prototpyes(_pGraphic_Device);



	//이펙트 프로토타입
	pObjMgr->Add_Prototype(L"Effect_Fire", SCENE_STAGE, CFire::Create(_pGraphic_Device));
	pObjMgr->Add_Prototype(L"Effect_Smoke", SCENE_STAGE, CSmoke::Create(_pGraphic_Device));




	Safe_Release(pLoader);
	Safe_Release(pObjMgr);
	Safe_Release(pModuleMgr);
	return S_OK;
}

HRESULT CSpawner::Spawn(_uint _iLevel)
{

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr)
		return E_FAIL;

	CLevel* pWorld = CLevelMgr::Get_Instance()->Get_Level(_iLevel);
	if (nullptr == pWorld)
		return E_FAIL;



	m_listCharacter[_iLevel].push_back(pObjMgr->Get_Player(SCENE_STAGE));

	//레벨마다 다른 몬스터를 피킹할 수 있어야한다.
	if (0 == _iLevel)
	{

		Vector3 ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Rat", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[0].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"FireFlower", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"IceFlower", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"ShieldFlower", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Key", SCENE_STAGE, L"Item", SCENE_STAGE, &ranPos));


		////아이템 만들기
		ranPos = pWorld->Get_RandomPos();
		CItem* pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_SHORTSWORD, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_BATTLEAXE, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LONGSWORD, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LETHERARMOR, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_HEALPOTION, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_POSIONPOTION, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_PARALYZEPOTION, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_FIREPOTION, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_HEALPOTION, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LIGHTNINGWAND, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LIGHTNINGWAND, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LIGHTNINGWAND, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LIGHTNINGWAND, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);


		for (auto& GO : m_listGO[_iLevel])
		{
			Safe_AddRef(GO);
		}
		for (auto& GO : m_listCharacter[_iLevel])
		{
			Safe_AddRef(GO);
		}
	}
	//레벨마다 다른 몬스터를 피킹할 수 있어야한다.
	if (1 == _iLevel)
	{

		Vector3 ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Rat", SCENE_STAGE, L"Monster_lv2", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster_lv2", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster_lv2", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Gnoll", SCENE_STAGE, L"Monster_lv2", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Crab", SCENE_STAGE, L"Monster_lv2", SCENE_STAGE, &ranPos));
		m_listCharacter[_iLevel].push_back(m_listGO[1].back());
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item_lv2", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item_lv2", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Cheese", SCENE_STAGE, L"Item_lv2", SCENE_STAGE, &CFood::STATEDESC(BASEDESC(ranPos, Vector3(20.f, 15.f)), 10.f)));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"FireFlower", SCENE_STAGE, L"Item_lv2", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"IceFlower", SCENE_STAGE, L"Item_lv2", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"ShieldFlower", SCENE_STAGE, L"Item_lv2", SCENE_STAGE, &ranPos));
		ranPos = pWorld->Get_RandomPos();
		m_listGO[_iLevel].push_back(pObjMgr->Add_GO_To_Layer(L"Key", SCENE_STAGE, L"Item_lv2", SCENE_STAGE, &ranPos));


		////아이템 만들기
		ranPos = pWorld->Get_RandomPos();
		CItem* pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_SHORTSWORD, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_BATTLEAXE, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LONGSWORD, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_ARROW, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_HEALPOTION, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LIGHTNINGWAND, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LIGHTNINGWAND, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);
		ranPos = pWorld->Get_RandomPos();
		pItem = CItemFactory::Make_Item(BASEDESC(ranPos, Vector2(20.f, 20.f)), CItemFactory::ITEM_LIGHTNINGWAND, _iLevel);
		if (nullptr != pItem) m_listGO[_iLevel].push_back(pItem);


		for (auto& GO : m_listGO[_iLevel])
		{
			Safe_AddRef(GO);
		}
		for (auto& GO : m_listCharacter[_iLevel])
		{
			Safe_AddRef(GO);
		}
	}
	return S_OK;
}

HRESULT CSpawner::Add_Interact(CGameObject * _pInteractor, _uint _iDepth)
{
	if (nullptr == _pInteractor ||
		MAX_DEPTH <= _iDepth)
		return E_FAIL;

	//중복 불허용
	for (auto& go : m_listGO[_iDepth])
	{
		if (_pInteractor == go)
			return E_FAIL;
	}
	m_listGO[_iDepth].push_back(_pInteractor);
	//맞지?
	Safe_AddRef(_pInteractor);
	return S_OK;
}

HRESULT CSpawner::Set_Visuable(Vector3 _vPlayerPos, _int _iRange, _int _iDepth)
{
	if (MAX_DEPTH <= _iDepth)
		return E_FAIL;

	for (auto& GO : m_listGO[_iDepth])
	{
		RECT rc = Make_Rect(_vPlayerPos, Vector2(TILECX * ((_iRange << 1) + 1), TILECY * ((_iRange << 1) + 1)));
		CTransform* pTransform = (CTransform*)GO->Get_Module(L"Transform");
		if (nullptr == pTransform)
			continue;
		POINT pt;
		pt.x = pTransform->Get_Position().x;
		pt.y = pTransform->Get_Position().y;

		if (PtInRect(&rc, pt))
		{
			GO->Set_Visuable(true);
			GO->Set_Visited(true);
		}

	}

	return S_OK;
}

CGameObject* CSpawner::PickObject(POINT& _pt, _uint _iLevel)
{
	if (MAX_DEPTH <= _iLevel)
		return nullptr;

	vector<RECT> UIRect = CStageUIMgr::Get_Instance()->GetUIRect();
	for (auto& rc : UIRect)
	{
		//만약 마우스 포인트가 UI위에 있으면 무시
		if (PtInRect(&rc, _pt))
		{
			return nullptr;
		}
	}

	//마우스 좌표 변환
	Vector4 dst = Vector4((float)_pt.x, (float)_pt.y, 0.f, 1.f);
	D3DXVec4Transform(&dst, &dst, &CPipline::Get_Instance()->Get_CameraMatrix_inverse());
	POINT pt;
	pt.x = (LONG)dst.x;
	pt.y = (LONG)dst.y;


	auto& iter = m_listGO[_iLevel].begin();
	while (iter != m_listGO[_iLevel].end())
	{
		//만약 지워진 오브젝트면 리스트에 지운다.
		if (nullptr == *iter)
		{
			Safe_Release(*iter);
			iter = m_listGO[_iLevel].erase(iter);
		}
		else
		{
			//오브젝트를 피킹한다.
			CTransform* pTransform = dynamic_cast<CTransform*>((*iter)->Get_Module(L"Transform"));
			if (nullptr != pTransform)
			{
				if (PtInRect(&pTransform->Get_Collider(), pt))
					return *iter;
			}

			++iter;
		}


	}


	return nullptr;
}

CGameObject * CSpawner::PickCharacter(Vector3 _vPos, _uint _iLevel, CTransform * pSelfTransform)
{

	if (MAX_DEPTH <= _iLevel)
		return nullptr;


	POINT pt;
	pt.x = (LONG)_vPos.x;
	pt.y = (LONG)_vPos.y;


	auto& iter = m_listCharacter[_iLevel].begin();
	while (iter != m_listCharacter[_iLevel].end())
	{
		//죽은 몬스터는 피킹안함
		CMonster* pMonster = dynamic_cast<CMonster*>(*iter);
		if (nullptr != pMonster)
		{
			if (pMonster->Get_Dying() || pMonster->Get_Dead())
				return nullptr;
		}

		//만약 지워진 오브젝트면 리스트에 지운다.
		if (nullptr == *iter)
		{
			Safe_Release(*iter);
			iter = m_listGO[_iLevel].erase(iter);
		}
		else
		{
			//오브젝트를 피킹한다.
			CTransform* pTransform = dynamic_cast<CTransform*>((*iter)->Get_Module(L"Transform"));
			if (nullptr != pTransform && pSelfTransform != pTransform)
			{
				
				if (PtInRect(&pTransform->Get_Collider(), pt))
				{
					return *iter;
				}
			}

			++iter;
		}

	}

	return nullptr;

}

CGameObject * CSpawner::PickCharacter(POINT& _pt, _uint _iLevel, CTransform * pSelfTransform)
{

	if (MAX_DEPTH <= _iLevel)
		return nullptr;


	//마우스 좌표 변환
	Vector4 dst = Vector4((float)_pt.x, (float)_pt.y, 0.f, 1.f);
	D3DXVec4Transform(&dst, &dst, &CPipline::Get_Instance()->Get_CameraMatrix_inverse());
	POINT pt;
	pt.x = (LONG)dst.x;
	pt.y = (LONG)dst.y;

	auto& iter = m_listCharacter[_iLevel].begin();
	while (iter != m_listCharacter[_iLevel].end())
	{
		//죽은 몬스터는 피킹안함
		CMonster* pMonster = dynamic_cast<CMonster*>(*iter);
		if (nullptr != pMonster)
		{
			if (pMonster->Get_Dying() || pMonster->Get_Dead())
				return nullptr;
		}
		//만약 지워진 오브젝트면 리스트에 지운다.
		if (nullptr == *iter)
		{
			Safe_Release(*iter);
			iter = m_listGO[_iLevel].erase(iter);
		}
		else
		{
			//오브젝트를 피킹한다.
			CTransform* pTransform = dynamic_cast<CTransform*>((*iter)->Get_Module(L"Transform"));
			if (nullptr != pTransform && pSelfTransform != pTransform)
			{
				if (PtInRect(&pTransform->Get_Collider(), pt))
				{
					return *iter;
				}
			}

			++iter;
		}

	}

	return nullptr;

}



vector<pair<int, int>> CSpawner::Get_CharacterTileIndexs()
{
	vector<pair<int, int>> indexs;
	for (auto& character : m_listCharacter[CLevelMgr::Get_Instance()->Get_CurrDepth()])
	{
		CMonster* pMonster = dynamic_cast<CMonster*>(character);
		if (nullptr != pMonster)
		{
			if (pMonster->Get_Dying() || pMonster->Get_Dead())
				continue;
		}
		CTransform* pTransform = (CTransform*)character->Get_Module(L"Transform");
		if (nullptr != pTransform)
		{
			Vector2 vPos = pTransform->Get_Position();
			pair<int, int> index = pair<int, int>((int)vPos.x / TILECX, (int)vPos.y / TILECY);
			indexs.push_back(index);
		}
	}
	return indexs;
}

void CSpawner::SetActive(_bool _bActive, _uint _iLevel)
{
	for (auto& GO : m_listGO[_iLevel])
	{
		GO->Set_Active(_bActive);
	}
}

_int CSpawner::Clear_DeadObjects(_uint _iLevel)
{
	if (MAX_DEPTH <= _iLevel)
		return -1;

	auto& iter = m_listGO[_iLevel].begin();
	while (iter != m_listGO[_iLevel].end())
	{
		if ((*iter)->Get_Dead())
		{
			Safe_Release(*iter);
			iter = m_listGO[_iLevel].erase(iter);
		}
		else
			++iter;
	}


	auto& iter2 = m_listCharacter[_iLevel].begin();
	while (iter2 != m_listCharacter[_iLevel].end())
	{
		if ((*iter2)->Get_Dead())
		{
			Safe_Release(*iter2);
			iter2 = m_listCharacter[_iLevel].erase(iter2);
		}
		else
			++iter2;
	}

	return 0;
}



void CSpawner::Free()
{

	for (auto& list : m_listCharacter)
	{
		for (auto& GO : list)
		{
			Safe_Release(GO);
		}
	}
	for (auto& list : m_listGO)
	{
		for (auto& GO : list)
		{
			Safe_Release(GO);
		}
	}
}
