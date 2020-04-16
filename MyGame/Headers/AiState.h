#pragma once
class CAiState
{
public:
	CAiState();
	virtual ~CAiState();

public:
	virtual  _bool act(_bool enemyInFOV, _bool justAlerted) = 0;
};

class Sleeping : public CAiState
{
	// AiState을(를) 통해 상속됨
	virtual _bool act(_bool enemyInFOV, _bool justAlerted) override;
};

class Hunting : public CAiState
{
	// AiState을(를) 통해 상속됨
	virtual _bool act(_bool enemyInFOV, _bool justAlerted) override;
};

class Wandering : public CAiState
{
	// AiState을(를) 통해 상속됨
	virtual _bool act(_bool enemyInFOV, _bool justAlerted) override;
};
