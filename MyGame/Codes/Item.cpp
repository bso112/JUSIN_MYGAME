#include "stdafx.h"
#include "..\Headers\Item.h"
#include "Hero.h"
#include "TimerMgr.h"
#include "InventoryUIMgr.h"
#include "Shader.h"
#include "DialogMgr.h"

USING(MyGame)

CItem::CItem(CItem & _rhs)
	: CGameObject(_rhs),
	m_pDescription(_rhs.m_pDescription),
	m_bDrop(_rhs.m_bDrop),
	m_bUsed(_rhs.m_bUsed),
	m_bThrown(_rhs.m_bThrown)
{

};
HRESULT CItem::Initialize(void * _param)
{
	m_vecActions.push_back(AC_DROP);
	m_vecActions.push_back(AC_THROW);

	return S_OK;
}

HRESULT CItem::Initialize_Prototype(_tchar * _pFilePath)
{
	m_bDrop = true;
	return S_OK;
}

_int CItem::Update(_double _timeDelta)
{

	if (!m_bActive)
		return 0;

	if (nullptr == m_pTransform ||
		m_bDead)
		return -1;

	if (m_bThrown && m_bDrop)
	{
		//�� �����ϸ�
		if (m_pTransform->MoveToDst(m_vDest, _timeDelta, 3.0))
		{
			//���������� �� �ൿ�� �Ѵ�.
			OnThrow();
			m_bThrown = false;
		}
	}
	return 0;
}

_int CItem::LateUpate(_double _timeDelta)
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pTransform)
		return -1;


	m_pTransform->Update_Transform();
	//�κ��丮�� ���� UI���
	if (m_bDrop)
	{
		m_iDepth = 0;
		m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_YSORT);
	}
	else
	{
		m_iDepth = 2;
		m_pRenderer->Add_To_RenderGrop(this, CRenderer::RENDER_UI);
	}

	return 0;
}



HRESULT CItem::Use(CHero* _pHero, const _tchar * _pAction)
{
	if (nullptr == _pHero)
		return E_FAIL;

	CTransform* pHeroTransform = (CTransform*)_pHero->Get_Module(L"Transform");
	if (nullptr == pHeroTransform)
		return E_FAIL;

	if (0 == lstrcmp(_pAction, AC_DROP))
	{
		if (nullptr == m_pTransform)
			return E_FAIL;

		//����
		m_bUsed = true;
		m_bDrop = true;
	}
	else if (0 == lstrcmp(_pAction, AC_THROW))
	{
		//����
		m_bUsed = true;
		m_bDrop = true;
		//���ο��� �����޶�� ��.
		_pHero->ThrowItem(this);

	}
	return S_OK;
}


void CItem::Drop(Vector3 _vDropPos)
{
	//�������� �ʻ� ���̰�
	m_bActive = true;
	//������ ������
	m_pTransform->Set_Position(_vDropPos);
	//���� �������
	m_pTransform->Set_Size(Get_OriginalSize());
	//��� �ʱ�ȭ
	m_bUsed = false;
}

void CItem::Throw(POINT & _pt)
{
	//���콺 ��ǥ ��ȯ
	Vector4 dst = Vector4(_pt.x, _pt.y, 0.f, 1.f);
	D3DXVec4Transform(&dst, &dst, &m_pPipline->Get_CameraMatrix_inverse());

	//��������.
	m_bThrown = true;
	m_vDest = dst;
	//��� �ʱ�ȭ
	m_bUsed = false;
}

void CItem::OnThrow()
{
	//�����.

}

void CItem::Free()
{
	Safe_Release(m_pTransform);
	Safe_Release(m_pTexture);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pShader);
	CGameObject::Free();
}

HRESULT CItem::Render()
{
	if (!m_bActive)
		return 0;

	if (nullptr == m_pTexture ||
		nullptr == m_pVIBuffer ||
		nullptr == m_pTransform ||
		nullptr == m_pPipline)
		return E_FAIL;

	_matrix matrix;

	if (m_bDrop)
		matrix = m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix();
	//���Կ� ���������� ī�޶� ��Ʈ���� ����ȹ��� 
	else
	{
		matrix = m_pTransform->Get_Matrix();
	}

	ALPHABLEND;

	if (FAILED(m_pVIBuffer->Set_Transform(matrix)))
		return E_FAIL;

	//�ؽ���ID�� 1���� ����
	if (FAILED(m_pTexture->Set_Texture(m_iTextureID - 1)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;


	ALPHABLEND_END;

#ifdef MYDEBUG

	m_pTransform->Render_Collider();
#endif // MYDEBUG


	return S_OK;
}



_int CItem::Interact(CGameObject * _pOther)
{
	if (!m_bActive)
		return 0;

	//�κ��丮�� ���������� ���ͷ�Ʈ ����
	if (!m_bDrop)
		return 0;

	//����Ŭ�������� �����ϴ� ��Ÿ ���ǵ�
	if (!IsInteractable())
		return 0;

	CHero* pHero = dynamic_cast<CHero*>(_pOther);
	//����ΰ� �������� �����Ѵ�.
	if (nullptr != pHero)
	{
		//�Ÿ��� ����� ������
		CTransform* pHeroTransform = (CTransform*)pHero->Get_Module(L"Transform");
		if (nullptr == pHeroTransform) return -1;
		if (nullptr == m_pTransform) return -1;
		_float dist = (pHeroTransform->Get_Position() - m_pTransform->Get_Position()).magnitude();
		if (dist > 30)
			return -1;
		
		CInventoryUIMgr* pInventoryUIMgr = CInventoryUIMgr::Get_Instance();
		if (nullptr == pInventoryUIMgr) return -1;
		CInventory* pInven = pInventoryUIMgr->GetInventory();
		if (nullptr == pInven) return -1;
		//��ӵ��� ����
		m_bDrop = false;
		pInven->Put_Item(this);
		//����Ŭ�������� �����Ҷ� ���� �ϱ�.
		OnPickUp(pHero, pInven);
		

		CDialogMgr::Get_Instance()->Log_Main(MSG_PICK(m_pItemName), 0xffff7f00);

	}
	return 0;
}

void CItem::OnPickUp(CHero * _pHero, CInventory* _pInventory)
{
}
