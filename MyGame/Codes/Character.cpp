#include "stdafx.h"
#include "..\Headers\Character.h"
#include "Stat.h"
#include "Clock.h"
#include "Shader.h"
#include "StateCon.h"
#include "ParticleSystem.h"
#include "ObjMgr.h"
#include "TimerMgr.h"
#include "Image.h"
#include "DialogMgr.h"
#include "BuffController.h"

USING(MyGame)



CCharacter::CCharacter(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
};


CCharacter::CCharacter(CCharacter & _character)
	:CGameObject(_character),
	m_tStat(_character.m_tStat),
	m_vecImmune(_character.m_vecImmune)
{
	m_pEffect = nullptr;
	m_pDeadClock = CClock_Delay::Create();
	m_pBuffCon = CBuffController::Create(m_pGraphic_Device);
}

_int CCharacter::StartAct()
{
	if (m_bDying || m_bDead)
		return -1;
	if (!m_bActive)
		return 0;

	if (nullptr == m_pStateCon ||
		nullptr == m_pBuffCon)
		return 0;

	m_pBuffCon->Act(this);

	return m_pStateCon->Start(IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange));
}

_int CCharacter::UpdateAct()
{
	if (m_bDying || m_bDead)
		return -1;

	if (!m_bActive)
		return 0;
	return m_pStateCon->Update(IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange));
}

void CCharacter::PlayEffect(CEffect * _pEffect)
{


}

void CCharacter::TakeDamage(float _fDamage)
{

	m_tStat.m_fHP -= _fDamage;

	if (m_tStat.m_fHP < 0)
	{
		OnDead();
		m_tStat.m_fHP = 0.f;
		m_bDying = true;
	}
	else
	{
		if (nullptr == m_pTransform)
			return;

#pragma region ��������Ʈ

		CImage::STATEDESC desc;
		desc.m_eTextureSceneID = SCENE_STATIC;
		desc.m_pTextureTag = L"empty";
		desc.m_fSpeed = 100.f;
		desc.m_tBaseDesc = BASEDESC(m_pTransform->Get_Position(), Vector2(30.f, 30.f));
		desc.m_dLifeTime = 0.3f;
		CImage* pDamageText = (CImage*)CObjMgr::Get_Instance()->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &desc));
		if (nullptr != pDamageText)
		{
			//ī�޶� ����޵��� ����
			pDamageText->Set_UI(false);
			//��Ʈ����
			MYFONT font;
			font.m_pFont = g_pFontX2;
			font.m_Color = 0xFFFF7F00;
			_tchar szBuff[MAX_PATH] = L"";
			wsprintf(szBuff, L"%d", (_int)_fDamage);
			memcpy(font.m_pTextArr, szBuff, sizeof(_tchar) * MAX_PATH);
			pDamageText->Set_Font(font);
			//���� �ø���
			CTransform* pTransform = (CTransform*)pDamageText->Get_Module(L"Transform");
			if (nullptr != pTransform)
				pTransform->MoveToDirAuto(Vector2(0.f, -1.f));
		}
#pragma endregion

		OnTakeDamage();
	}

}

void CCharacter::Heal(_float _healAmount)
{
	m_tStat.m_fHP += _healAmount;
	if (m_tStat.m_fHP >= m_tStat.m_fMaxHp->GetValue())
		m_tStat.m_fHP = m_tStat.m_fMaxHp->GetValue();

	//ȸ�� ��ƼŬ ����
	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	if (nullptr == pObjMgr) return;

	if (nullptr == m_pTransform)
		return;
	Vector3 vPos = m_pTransform->Get_Position();
	CImage::STATEDESC desc;
	desc.m_dLifeTime = 0.5f;
	desc.m_eTextureSceneID = SCENE_STAGE;
	desc.m_fSpeed = 70.f;
	desc.m_pTextureTag = L"specks";
	desc.m_tBaseDesc = BASEDESC(vPos, Vector2(20.f, 20.f));
	desc.m_iTextureID = 1;

	CImage* pImage = (CImage*)pObjMgr->Add_GO_To_Layer(L"Particle", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &desc));
	if (nullptr == pImage)
		return;
	pImage->Set_UI(false);
	CTransform* pImgTransform = (CTransform*)pImage->Get_Module(L"Transform");
	pImgTransform->MoveToDirAuto(Vector3(0.f, -1.f));

}


bool CCharacter::IsAlive()
{
	return m_tStat.m_fHP > 0;
}

bool CCharacter::IsImmune(IMMUNE _eImmune)
{
	for (auto& immune : m_vecImmune)
	{
		if (immune == _eImmune)
			return true;
	}
	return false;
}

void CCharacter::Add_Buff(CBuff * pBuff)
{
	if (nullptr == pBuff)
		return;

	m_pBuffCon->Add_Buff(pBuff);
}

_int CCharacter::Interact(CGameObject * _pOther)
{
	if (nullptr == m_pTransform ||
		nullptr == _pOther)
		return -1;

	//������ ĳ���͸� ���濡�� �������� ��
	CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);
	if (nullptr != pCharacter)
	{
		CTransform* pOtherTransform = (CTransform*)_pOther->Get_Module(L"Transform");
		if (nullptr == pOtherTransform)return -1;

		if (IsTargetInRange(pCharacter, m_iAttackRange))
		{
			_float Damage = m_tStat.m_fAtt->GetValue();
			pCharacter->TakeDamage(Damage);
			OnAttack(_pOther);

			_tchar szBuff[20] = L"";
			wsprintf(szBuff, L"%d", (_int)Damage);
			CDialogMgr::Get_Instance()->Log_Main(MSG_DAMAGE(pCharacter->Get_Name(), m_pName, szBuff));




#pragma region ��ƼŬ ����


			//�� ��ƼŬ ����
			Vector3 vPos = m_pTransform->Get_Position();
			CParticleSystem::STATEDESC desc;
			desc.m_tBaseDesc.vPos = pOtherTransform->Get_Position();
			desc.m_pTextureTag = L"Blood";
			desc.m_eTextureSceneID = SCENE_STAGE;
			desc.m_dDuration = 0.2f;
			desc.m_dLifeTime = 0.2f;
			desc.m_fSpeed = 300.f;
			desc.m_vParticleSize = Vector2(10.f, 10.f);
			CObjMgr* pObjMgr = CObjMgr::Get_Instance();
			CParticleSystem* pParticleSystem = dynamic_cast<CParticleSystem*>(pObjMgr->Add_GO_To_Layer(L"ParticleSystem", SCENE_STATIC, L"ParticleSystem", SCENE_STAGE, &desc));


			Vector2 vDir = pOtherTransform->Get_Position() - m_pTransform->Get_Position();
			m_pTransform->FaceDir(vDir);

			//�ǰ� Ƣ���.
			pParticleSystem->Spread(vDir, CTimerMgr::Get_Instance()->Get_TimeDelta(), 5);

#pragma endregion
		}


	}
	return 0;
}

HRESULT CCharacter::Get_TerrainIndex(pair<_int, _int>& _out)
{
	if (nullptr == m_pTransform)
		return E_FAIL;
	_int x = (_int)m_pTransform->Get_Position().x / TILECX;
	_int y = (_int)m_pTransform->Get_Position().y / TILECY;

	_out.first = x;
	_out.second = y;

	return S_OK;
}

bool CCharacter::IsTargetInRange(CCharacter * pTarget, _int _iRange)
{
	if (nullptr == pTarget)
		return false;

	pair<_int, _int> vTargetTerrainIndex;
	if (FAILED(pTarget->Get_TerrainIndex(vTargetTerrainIndex)))
		return false;

	pair<_int, _int> vMyTerrainIndex;
	if (FAILED(Get_TerrainIndex(vMyTerrainIndex)))
		return false;

	//Ÿ���� �����ȿ� ������
	if (vTargetTerrainIndex.first >= vMyTerrainIndex.first - _iRange && vTargetTerrainIndex.first <= vMyTerrainIndex.first + _iRange)
	{
		if (vTargetTerrainIndex.second >= vMyTerrainIndex.second - _iRange && vTargetTerrainIndex.second <= vMyTerrainIndex.second + _iRange)
		{
			return true;
		}
	}
	return false;
}

void CCharacter::OnCollisionEnter(CGameObject * _pOther)
{
	//if (nullptr != dynamic_cast<CCharacter*>(_pOther))
	//{
	//	m_pTransform->Stop();
	//}
}





void CCharacter::OnTakeDamage()
{

	//��¦�Ÿ�
	m_iPass = 3;


}

void CCharacter::OnAttack(CGameObject * _pOther)
{
}

void CCharacter::Free()
{
	Safe_Release(m_pEffect);
	Safe_Release(m_pDeadClock);
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pStateCon);
	Safe_Release(m_pShader);
	m_tStat.Free();
	Safe_Release(m_pBuffCon);

	CGameObject::Free();
}
