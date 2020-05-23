#pragma once
#include "Base.h"

BEGIN(MyGame)

//BaseValue와 버프를 받아 수정된 value를 구분하기 위한 래퍼클래스.
class CStat final : public CBase
{
private:
	explicit CStat() {};
	virtual ~CStat() = default;

private:
	//기본 값
	float m_fBaseValue;
	//추가 값
	list<float> m_listModifier;
	//랜덤값인가
	_bool m_bRandom = false;
	//랜덤 최소 값
	float m_fMinValue;

public:
	void AddModifier(float _fModifier) { if (_fModifier > 0) m_listModifier.push_back(_fModifier); }
	void RemoveModifire(float _fModifier) { if (_fModifier > 0) m_listModifier.remove(_fModifier); }
	float GetValue()
	{
		//추가 값들을 더한다.
		float finalValue = m_fBaseValue;
		//랜덤 최소값도 함께 처리하자.
		float finalMinValue = m_fMinValue;
		for (auto& val : m_listModifier)
		{
			finalValue += val;
			finalMinValue += val;
		}

		//음수가 되는 것은 원하는 바가 아니다.
		if (finalValue < 0)
			finalValue = 0;
		if (finalMinValue < 0)
			finalMinValue = 0;

		//랜덤 값이면
		if (m_bRandom)
		{
			//0으로 나누지 못한다.
			if (finalValue - finalMinValue <= 0)
				return finalValue;

			//범위내 랜덤값을 구한다.
			finalValue = float(rand() % (int)(finalValue - finalMinValue));
			finalValue += finalMinValue;
		}

		return finalValue;
	};

public:
	static CStat* Create(float _baseValue)
	{
		CStat* stat = new CStat;
		stat->m_fBaseValue = _baseValue;
		return stat;
	}
	static CStat* Create(float _fMinValue, float _fMaxValue)
	{
		CStat* stat = new CStat;
		stat->m_fMinValue = _fMinValue;
		stat->m_fBaseValue = _fMaxValue;
		stat->m_bRandom = true;
		return stat;
	}


public:
	// CBase을(를) 통해 상속됨
	virtual void Free() override;

};

END