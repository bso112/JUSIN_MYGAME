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
	// AiState��(��) ���� ��ӵ�
	virtual _bool act(_bool enemyInFOV, _bool justAlerted) override;
};

class Hunting : public CAiState
{
	// AiState��(��) ���� ��ӵ�
	virtual _bool act(_bool enemyInFOV, _bool justAlerted) override;
};

class Wandering : public CAiState
{
	// AiState��(��) ���� ��ӵ�
	virtual _bool act(_bool enemyInFOV, _bool justAlerted) override;
};
