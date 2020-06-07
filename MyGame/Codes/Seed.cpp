#include "stdafx.h"
#include "..\Headers\Seed.h"
#include "TurnMgr.h"

USING(MyGame)
CSeed::CSeed(PDIRECT3DDEVICE9 _pGrahic_Device)
	:CItem(_pGrahic_Device)
{
}

CSeed::CSeed(CSeed & _rhs)
	: CItem(_rhs)
{
}

HRESULT CSeed::Initialize(void * _param)
{
	m_bStackable = true;
	CItem::Initialize();
	m_vecActions.push_back(AC_PLANT);

	Set_Module(L"seed", SCENE_STAGE, (CModule**)&m_pTexture);
	m_pTextureTag = L"seed";
	Set_Module(L"Transform", SCENE_STATIC, (CModule**)&m_pTransform, L"Transform", &CTransform::STATEDESC(300.0, 300.0));
	Set_Module(L"VIBuffer", SCENE_STATIC, (CModule**)&m_pVIBuffer);

	m_vOriginalSize = Vector2(30.f, 25.f);
	m_pTransform->Set_Size(m_vOriginalSize);
	m_pTransform->Set_ColliderSize(COLLIDER_SIZE);

	return S_OK;
}

void CSeed::OnThrowEnd()
{
	//꽃으로 변한다
	++m_iTextureID;
	//텍스쳐의 한도를 넘어가지 않게
	if (m_iTextureID >= m_pTexture->Get_TextureSize())
		m_iTextureID = m_pTexture->Get_TextureSize() - 1;

	m_bFlower = true;

	//턴이동
	CTurnMgr::Get_Instance()->MoveTurn_Simultaneously(1);
}

HRESULT CSeed::Use(CHero * _pHero, const _tchar ** _pAction)
{
	CItem::Use(_pHero, _pAction);
	if (0 == lstrcmp(*_pAction, AC_PLANT))
	{
		if (nullptr == m_pTransform)
			return E_FAIL;

		//사용됨
		m_bUsed = true;
		m_bDrop = true;
		m_bFlower = true;
		++m_iTextureID;
		//턴이동
		CTurnMgr::Get_Instance()->MoveTurn_Simultaneously(1);
	}
	return S_OK;
}



Vector3 CSeed::Get_OriginalSize()
{
	return m_vOriginalSize;
}



void CSeed::Free()
{
	CItem::Free();
}
