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
#include "SoundMgr.h"

USING(MyGame)



CCharacter::CCharacter(PDIRECT3DDEVICE9 _pGraphic_Device)
	:CGameObject(_pGraphic_Device)
{
};


CCharacter::CCharacter(CCharacter & _character)
	:CGameObject(_character),
	m_tStat(_character.m_tStat),
	m_listImmune(_character.m_listImmune)
{
	m_pDeadClock = CClock_Delay::Create();

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

	OnAct();

	//마비면 버프만 start하고 행동은 못함
	if (m_bParalyze)
		return 0;


	return m_pStateCon->Start(IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange));;

}

_int CCharacter::UpdateAct()
{
	if (m_bDying || m_bDead || m_bParalyze)
		return -1;

	if (!m_bActive)
		return 0;
	return m_pStateCon->Update(IsTargetInRange(m_pFocus, m_iAttackRange), IsTargetInRange(m_pFocus, m_iRecogRange));
}


HRESULT CCharacter::ShowText(const _tchar * _pText, D3DXCOLOR _Color, ID3DXFont* _pFont)
{
	if (nullptr == m_pTransform)
		return E_FAIL;

	CImage::STATEDESC desc;
	desc.m_eTextureSceneID = SCENE_STATIC;
	desc.m_pTextureTag = L"empty";
	desc.m_fSpeed = 50.f;
	desc.m_tBaseDesc = BASEDESC(Vector3(m_pTransform->Get_Position().x, m_pTransform->Get_Position().y - 10.f), Vector2(100.f, 30.f));
	desc.m_dLifeTime = 1.f;
	CImage* pDamageText = (CImage*)CObjMgr::Get_Instance()->Add_GO_To_Layer(L"UI", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &desc));
	pDamageText->Set_Depth(-1);
	if (nullptr != pDamageText)
	{
		//카메라 영향받도록 지정
		pDamageText->Set_UI(false);
		//폰트지정
		MYFONT font;
		font.m_pFont = _pFont;
		font.m_Color = _Color;
		memcpy(font.m_pTextArr, _pText, sizeof(_tchar) * MAX_PATH);
		pDamageText->Set_Font(font);
		//위로 올리기
		CTransform* pTransform = (CTransform*)pDamageText->Get_Module(L"Transform");
		if (nullptr != pTransform)
			pTransform->MoveToDirAuto(Vector2(0.f, -1.f));
	}
	return S_OK;
}

//레이어에 추가한다음에 인자로 넘겨야함.
HRESULT CCharacter::ShowBuffImg(CImage * _pImage)
{
	CImage* pImage = _pImage;
	if (nullptr == pImage)
		return E_FAIL;
	pImage->Set_UI(false);
	pImage->Set_Depth(-1);
	CTransform* pImgTransform = (CTransform*)pImage->Get_Module(L"Transform");
	pImgTransform->MoveToDirAuto(Vector3(0.f, -1.f));
	return S_OK;
}

HRESULT CCharacter::ShowBuffImg(SCENEID _eTextureSceneID, const _tchar* _pTextureTag, _uint _iTextureID, BASEDESC _tBaseDesc)
{
	CImage::STATEDESC desc;
	desc.m_dLifeTime = 0.5f;
	desc.m_eTextureSceneID = _eTextureSceneID;
	desc.m_fSpeed = 70.f;
	desc.m_pTextureTag = _pTextureTag;
	desc.m_tBaseDesc = _tBaseDesc;
	desc.m_iTextureID = _iTextureID;

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	CImage* pImage = (CImage*)pObjMgr->Add_GO_To_Layer(L"Particle", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &desc));
	if (nullptr == pImage)
		return E_FAIL;
	pImage->Set_UI(false);
	pImage->Set_Depth(-1);
	CTransform* pImgTransform = (CTransform*)pImage->Get_Module(L"Transform");
	pImgTransform->MoveToDirAuto(Vector3(0.f, -1.f));


	return S_OK;
}

HRESULT CCharacter::ShowStateIcon(SCENEID _eTextureSceneID, const _tchar* _pTextureTag, _uint _iTextureID, BASEDESC _tBaseDesc)
{
	CImage::STATEDESC desc;
	desc.m_iLifeTimeInTurn = 1;
	desc.m_eTextureSceneID = _eTextureSceneID;
	desc.m_pTextureTag = _pTextureTag;
	desc.m_tBaseDesc = _tBaseDesc;
	desc.m_iTextureID = _iTextureID;

	CObjMgr* pObjMgr = CObjMgr::Get_Instance();
	CImage* pImage = (CImage*)pObjMgr->Add_GO_To_Layer(L"Particle", SCENE_STAGE, CImage::Create(m_pGraphic_Device, &desc));
	if (nullptr == pImage) return E_FAIL;
	pImage->Set_UI(false);
	pImage->Set_Depth(-1);
	if (nullptr == m_pTransform) return E_FAIL;
	CTransform* pTransform = (CTransform*)pImage->Get_Module(L"Transform");
	if (nullptr == pTransform) return E_FAIL;
	pTransform->Set_Parent(m_pTransform);


	return S_OK;
}


_bool CCharacter::TakeDamage(float _fDamage, _bool _bDodgable)
{
	if (m_bDying || m_bDead)
		return false;

	if (_bDodgable)
	{
		_float chance = rand() / (float)RAND_MAX * 100.0f;
		if (chance < m_tStat.m_fAvoidability)
		{
			CSoundMgr::Get_Instance()->PlaySound_Overwrite(L"snd_miss.mp3", CSoundMgr::EFFECT);
			ShowText(L"회피");
			return false;
		}

	}


	_float fDamage = _fDamage - m_tStat.m_fArmor->GetValue();

	if (fDamage < 0)
		fDamage = 0;
	m_tStat.m_fHP -= fDamage;
	if (m_tStat.m_fHP < 0.f)
		m_tStat.m_fHP = 0.f;


	if (m_tStat.m_fHP <= 0 && !m_bInvincible)
	{
		OnDead();
		m_tStat.m_fHP = 0.f;
		
		m_bDying = true;
	}

	OnTakeDamage(_fDamage);
	return true;

}

HRESULT CCharacter::Attack(CCharacter * pCharacter)
{

	if (nullptr != pCharacter && !pCharacter->Is_NPC())
	{
		if (pCharacter->Get_Dying() || pCharacter->Get_Dead())
			return 0;

		CTransform* pOtherTransform = (CTransform*)pCharacter->Get_Module(L"Transform");
		if (nullptr == pOtherTransform)return -1;

		if (IsTargetInRange(pCharacter, m_iAttackRange))
		{
			CSoundMgr::Get_Instance()->PlaySound_Overwrite(L"snd_hit.mp3", CSoundMgr::CHANNELID::PLAYER);
			_float Damage = m_tStat.m_fAtt->GetValue();
			pCharacter->TakeDamage(Damage);
			OnAttack(pCharacter);




#pragma region 파티클 생성


			//피 파티클 생성
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

			//피가 튀긴다.
			pParticleSystem->Spread(vDir, CTimerMgr::Get_Instance()->Get_TimeDelta(), 5);

#pragma endregion
		}
	}
	return S_OK;
}


void CCharacter::Heal(_float _healAmount)
{
	m_tStat.m_fHP += _healAmount;
	if (m_tStat.m_fHP >= m_tStat.m_fMaxHp->GetValue())
		m_tStat.m_fHP = m_tStat.m_fMaxHp->GetValue();

	//회복 파티클 생성
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

void CCharacter::Set_Paralyze(bool _bParalyze)
{
	for (auto& immune : m_listImmune)
	{
		if (immune == CBuff::TYPE_PARALIZE)
			return;
	}
	m_bParalyze = _bParalyze;
	OnParalyzed();
}


bool CCharacter::IsAlive()
{
	return m_tStat.m_fHP > 0;
}

_bool CCharacter::IsImmune(CBuff::TYPE _eType)
{
	for (auto& buff : m_listImmune)
	{
		if (buff == _eType)
			return true;
	}
	return false;
}



void CCharacter::Add_Buff(CBuff * pBuff)
{
	if (nullptr == pBuff)
		return;

	const _tchar* pBuffText = L"";
	for (auto& immune : m_listImmune)
	{
		if (immune == pBuff->Get_Type())
		{
			pBuffText = L"면역";
			ShowText(pBuffText);
			return;
		}
	}

	pBuff->Act(this);
	m_pBuffCon->Add_Buff(pBuff);

	switch (pBuff->Get_Type())
	{
	case CBuff::TYPE_BURN:
		pBuffText = L"화상";
		break;
	case CBuff::TYPE_FREEZE:
		pBuffText = L"동상";
		break;
	case CBuff::TYPE_PARALIZE:
		pBuffText = L"마비됨";
		break;
	case CBuff::TYPE_POISION:
		pBuffText = L"중독됨";
		break;
	default:
		break;
	}

	ShowText(pBuffText);


}

HRESULT CCharacter::Add_Immune(CBuff::TYPE _eType)
{
	//중복 불허용
	auto& iter = m_listImmune.begin();
	while (iter != m_listImmune.end())
	{
		if (*iter == _eType)
			return E_FAIL;
	}

	m_listImmune.push_back(_eType);

	return S_OK;
}

_int CCharacter::Interact(CGameObject * _pOther)
{
	if (nullptr == m_pTransform ||
		nullptr == _pOther)
		return -1;

	//상대방이 캐릭터면 상대방에게 데미지를 줌
	CCharacter* pCharacter = dynamic_cast<CCharacter*>(_pOther);
	if (nullptr != pCharacter && !pCharacter->Get_Dying() && !pCharacter->Get_Dead())
		Attack(pCharacter);


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

	//타깃이 범위안에 들어오면
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





void CCharacter::OnTakeDamage(float _fDamage)
{


	//반짝거림
	m_iPass = 3;

	if (nullptr == m_pTransform)
		return;

	//데미지 폰트, 로그
	_tchar szBuff[MAX_PATH] = L"";
	wsprintf(szBuff, L"%d", (_int)_fDamage);
	ShowText(szBuff, COLOR_ORANGE);
	CDialogMgr::Get_Instance()->Log_Main(MSG_DAMAGE(m_pName, szBuff));


}

void CCharacter::OnParalyzed()
{
}

void CCharacter::OnAttack(CGameObject * _pOther)
{
}

void CCharacter::OnAct()
{
}

void CCharacter::Free()
{
	Safe_Release(m_pDeadClock);
	Safe_Release(m_pTransform);
	Safe_Release(m_pVIBuffer);
	Safe_Release(m_pStateCon);
	Safe_Release(m_pShader);
	m_tStat.Free();
	Safe_Release(m_pBuffCon);

	CGameObject::Free();
}
