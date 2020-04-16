#include "stdafx.h"
#include "..\Headers\AiState.h"


CAiState::CAiState()
{
}


CAiState::~CAiState()
{
}

_bool Sleeping::act(_bool enemyInFOV, _bool justAlerted)
{
	return _bool();
}

_bool Hunting::act(_bool enemyInFOV, _bool justAlerted)
{
	return _bool();
}

_bool Wandering::act(_bool enemyInFOV, _bool justAlerted)
{
	return _bool();
}
