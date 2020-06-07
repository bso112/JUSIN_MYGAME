#include "stdafx.h"
#include "..\Headers\BuffController.h"
#include "Image.h"
#include "ObjMgr.h"
#include "Transform.h"
USING(MyGame)
CBuffController::CBuffController(PDIRECT3DDEVICE9 _pGraphic_Device)
	:m_pGraphic_Device(_pGraphic_Device)
{
	Safe_AddRef(m_pGraphic_Device);
	ZeroMemory(&m_pBuffIcons, sizeof(m_pBuffIcons));
}

HRESULT CBuffController::Initialize(_bool _isPlayer)
{
	m_isPlayer = _isPlayer;

	if (!_isPlayer)
		return S_OK;

	_float margin = 30.f;
	Vector3 vBasePos = Vector3(110.f, 45.f);
	Vector3 vBaseSize = Vector3(25.f, 25.f, 1.f);
	for (int i = 0; i < MAX_BUFFICON; ++i)
	{
		CImage::STATEDESC desc;
		desc.m_eTextureSceneID = SCENE_STAGE;
		desc.m_pTextureTag = L"buffs";
		desc.m_iTextureID = 1;
		desc.m_tBaseDesc.vPos = Vector2(vBasePos.x + margin * i, vBasePos.y);
		desc.m_tBaseDesc.vSize = vBaseSize;
		m_pBuffIcons[i] = (CImage*)CObjMgr::Get_Instance()->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &desc));
		m_pBuffIcons[i]->Set_UI(true);
		Safe_AddRef(m_pBuffIcons[i]);
	}
	return S_OK;
}
_int CBuffController::Act(CCharacter* _pTarget)
{
	if (m_listBuff.size() <= 0)
		return 0;

	int iIconIndex = 0;
	auto& iter = m_listBuff.begin();
	while (iter != m_listBuff.end())
	{
		//지워진걸 부르네?
		_int iDuration = (*iter)->Act(_pTarget);
		//남은턴이 0턴이면
		if (iDuration == 0)
		{
			if (iIconIndex >= MAX_BUFFICON)
				continue;

			if (m_isPlayer)
			{

				CImage::STATEDESC desc = m_pBuffIcons[iIconIndex]->Get_DESC();
				desc.m_dLifeTime = 0.8f;
				CImage* pImage = (CImage*)CObjMgr::Get_Instance()->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &desc));
				if (nullptr == pImage) continue;
				pImage->Set_UI(true);
				pImage->Set_FadeOut();
				CTransform* pTransform = (CTransform*)pImage->Get_Module(L"Transform");
				if (nullptr == pTransform) continue;
				pTransform->Expand_Auto(Vector2(200.f, 200.f));

			}

			//삭제
			Safe_Release(*iter);
			iter = m_listBuff.erase(iter);
		}
		else
			++iter;
	}
	return 0;
}

HRESULT CBuffController::Update_BuffIcon()
{
	int i = 0;
	for (auto& buff : m_listBuff)
	{
		if (i >= MAX_BUFFICON)
			break;
		switch (buff->Get_Type())
		{
		case CBuff::TYPE_BURN:
			m_pBuffIcons[i]->Set_TextureID(8);
			break;
		case CBuff::TYPE_FREEZE:
			m_pBuffIcons[i]->Set_TextureID(3);
			break;
		case CBuff::TYPE_POISION:
			m_pBuffIcons[i]->Set_TextureID(2);
			break;
		case CBuff::TYPE_PARALIZE:
			m_pBuffIcons[i]->Set_TextureID(4);
			break;
		}
		++i;
	}

	_int iStart = m_listBuff.size();
	if (iStart < 0)
		iStart = 0;
	//클리어
	for (int j = iStart; j < MAX_BUFFICON; ++j)
	{
		m_pBuffIcons[j]->Set_TextureID(1);
	}

	return S_OK;
}

HRESULT CBuffController::Add_Buff(CBuff * _pBuff)
{
	if (nullptr == _pBuff)
		return E_FAIL;
	//중복 버프는 갱신
	auto& iter = find_if(m_listBuff.begin(), m_listBuff.end(), [&](CBuff* _a) { return _a->Get_Type() == _pBuff->Get_Type();});
	if (iter != m_listBuff.end())
	{
		Safe_Release(*iter);
		m_listBuff.erase(iter);
	}

	m_listBuff.push_back(_pBuff);

	return S_OK;
}

CBuffController * CBuffController::Create(PDIRECT3DDEVICE9 _pGraphic_Device, _bool _isPlayer)
{
	CBuffController* pInstance = new CBuffController(_pGraphic_Device);
	if (FAILED(pInstance->Initialize(_isPlayer)))
	{
		MSG_BOX("Fail to create CBuffController");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void CBuffController::Free()
{
	for (auto& buffIcon : m_pBuffIcons)
	{
		Safe_Release(buffIcon);
	}
	for (auto& buff : m_listBuff)
	{
		Safe_Release(buff);
	}

	Safe_Release(m_pGraphic_Device);
}
