#include "stdafx.h"
#include "..\Headers\State.h"

USING(MyGame)

CState * Sleeping::Update(_double _timeDelta)
{
	return nullptr;
}

HRESULT Sleeping::Initialize(_bool enemyInFOV, _bool justAlerted)
{
	return S_OK;
}



Sleeping * Sleeping::Create(CCharacter * _pActor, _bool enemyInFOV, _bool justAlerted)
{
	Sleeping* pInstance = new Sleeping(_pActor);
	if (FAILED(pInstance->Initialize(enemyInFOV, justAlerted)))
	{
		MSG_BOX("Fail to create Sleeping");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void Sleeping::Free()
{
}

CState * Hunting::Update(_double _timeDelta)
{
	return nullptr;
}

HRESULT Hunting::Initialize(_bool enemyInFOV, _bool justAlerted)
{
	return S_OK;
}


Hunting * Hunting::Create(CCharacter * _pActor, _bool enemyInFOV, _bool justAlerted)
{
	Hunting* pInstance = new Hunting(_pActor);
	if (FAILED(pInstance->Initialize(enemyInFOV, justAlerted)))
	{
		MSG_BOX("Fail to create Hunting");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void Hunting::Free()
{
}

CState * Wandering::Update(_double _timeDelta)
{
	return nullptr;
}

HRESULT Wandering::Initialize(_bool enemyInFOV, _bool justAlerted)
{
	return S_OK;
}



Wandering * Wandering::Create(CCharacter * _pActor, _bool enemyInFOV, _bool justAlerted)
{
	Wandering* pInstance = new Wandering(_pActor);
	if (FAILED(pInstance->Initialize(enemyInFOV, justAlerted)))
	{
		MSG_BOX("Fail to create Wandering");
		Safe_Release(pInstance);

	}
	return pInstance;
}

void Wandering::Free()
{
}

