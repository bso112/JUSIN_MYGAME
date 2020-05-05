#pragma once

#include "Base.h"
BEGIN(MyGame)

class CCharacter;

class CState abstract : public CBase
{
protected:
	explicit CState(CCharacter* _pActor) :m_pActor(_pActor) {};
protected:
	CCharacter*	m_pActor = nullptr;
	CState*		m_pNextState = nullptr;

public:
	virtual CState*	Update(_double _timeDelta) = 0;
	virtual  HRESULT Initialize(_bool enemyInFOV, _bool justAlerted) = 0;

public:
	void	SetActor(CCharacter* _pActor) { m_pActor = _pActor; }
	void	SetNextState(CState* _pNext) { m_pNextState = _pNext; }




};


class CAIState abstract : public CState
{
protected:
	explicit CAIState(CCharacter* _pActor) :CState(_pActor) {};
};

class Sleeping : public CAIState
{
protected:
	explicit Sleeping(CCharacter* _pActor) :CAIState(_pActor) {};
public:
	virtual CState*	Update(_double _timeDelta) override;
	// AiState을(를) 통해 상속됨
	virtual HRESULT Initialize(_bool enemyInFOV, _bool justAlerted) override;


public:
	static Sleeping* Create(CCharacter* _pActor, _bool enemyInFOV = false, _bool justAlerted = false);
	virtual void Free() override;
};

class Hunting : public CAIState
{
protected:
	explicit Hunting(CCharacter* _pActor) :CAIState(_pActor) {};
public:
	virtual CState*	Update(_double _timeDelta) override;
	virtual HRESULT Initialize(_bool enemyInFOV, _bool justAlerted) override;


public:
	static Hunting* Create(CCharacter* _pActor, _bool enemyInFOV = false, _bool justAlerted = false);
	virtual void Free() override;
};

class Wandering : public CAIState
{
protected:
	explicit Wandering(CCharacter* _pActor) :CAIState(_pActor) {};

public:
	virtual CState*	Update(_double _timeDelta) override;
	// AiState을(를) 통해 상속됨
	virtual HRESULT Initialize(_bool enemyInFOV, _bool justAlerted) override;

public:
	static Wandering* Create(CCharacter* _pActor, _bool enemyInFOV = false, _bool justAlerted = false);
	virtual void Free() override;
};
END