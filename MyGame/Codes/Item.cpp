#include "stdafx.h"
#include "..\Headers\Item.h"
#include "Hero.h"
#include "TimerMgr.h"
#include "InventoryUIMgr.h"


USING(MyGame)
//�����Ҷ� �Ѱ��� ���� �� ����
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
	if (nullptr == m_pTransform)
		return -1;

	if (m_bThrown)
	{
		//�� �����ϸ�
		if (NO_ERROR == m_pTransform->MoveToDst(m_vDest, _timeDelta, 2.f))
		{
			//���������� �� �ൿ�� �Ѵ�.
			OnThrow();
			m_bThrown = false;
		}
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
		Drop(pHeroTransform->Get_Position());
	}
	else if (0 == lstrcmp(_pAction, AC_THROW))
	{
		//����
		m_bUsed = true;
		Drop(pHeroTransform->Get_Position());
		//���ο��� �����޶�� ��.
		_pHero->ThrowItem(this);

	}
	return S_OK;
}


void CItem::Drop(Vector3 _vDropPos)
{
	//��ӵ�
	m_bDrop = true;
	//������ ������
	m_pTransform->Set_Position(_vDropPos);
}

void CItem::Throw(POINT & _pt)
{
	//��������.
	m_bThrown = true;
	m_vDest = Vector3(_pt.x, _pt.y);
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
	CGameObject::Free();
}

HRESULT CItem::Render()
{
	if (nullptr == m_pTexture ||
		nullptr == m_pVIBuffer ||
		nullptr == m_pTransform	||
		nullptr == m_pPipline)
		return E_FAIL;

	_matrix matrix;

	if (m_bDrop)
		matrix = m_pTransform->Get_Matrix() * m_pPipline->Get_ViewMatrix();
	//���Կ� ���������� ī�޶� ��Ʈ���� ����ȹ��� 
	else
		matrix = m_pTransform->Get_Matrix();

	ALPHABLEND;

	if (FAILED(m_pVIBuffer->Set_Transform(matrix)))
		return E_FAIL;

	//�ؽ���ID�� 1���� ����
	if (FAILED(m_pTexture->Set_Texture(m_iTextureID - 1)))
		return E_FAIL;

	if (FAILED(m_pVIBuffer->Render()))
		return E_FAIL;

	ALPHABLEND_END;

	return S_OK;
}


void CItem::OnCollisionEnter(CGameObject * _pOther)
{
	if (!m_bActive)
		return;

	//����ΰ� �������� �����Ѵ�.
	if (nullptr != dynamic_cast<CHero*>(_pOther))
	{
		CInventoryUIMgr* pInventoryUIMgr = CInventoryUIMgr::Get_Instance();
		RETURN_IF_NULL(pInventoryUIMgr);
		CInventory* pInven = pInventoryUIMgr->GetInventory();
		RETURN_IF_NULL(pInven);
		//��ӵ��� ����
		m_bDrop = false;
		pInven->Put_Item(this);
	}
}