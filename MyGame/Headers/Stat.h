#pragma once
#include "Base.h"

BEGIN(MyGame)

//BaseValue�� ������ �޾� ������ value�� �����ϱ� ���� ����Ŭ����.
class CStat final : public CBase
{
private:
	explicit CStat() {};
	virtual ~CStat() = default;

private:
	//�⺻ ��
	float m_fBaseValue;
	//�߰� ��
	list<float> m_listModifier;
	//�������ΰ�
	_bool m_bRandom = false;
	//���� �ּ� ��
	float m_fMinValue;

public:
	void AddModifier(float _fModifier) { if (_fModifier > 0) m_listModifier.push_back(_fModifier); }
	void RemoveModifire(float _fModifier) { if (_fModifier > 0) m_listModifier.remove(_fModifier); }
	float GetValue()
	{
		//�߰� ������ ���Ѵ�.
		float finalValue = m_fBaseValue;
		//���� �ּҰ��� �Բ� ó������.
		float minValue = m_fMinValue;
		for (auto& val : m_listModifier)
		{
			finalValue += val;
			minValue += val;
		}

		//������ �Ǵ� ���� ���ϴ� �ٰ� �ƴϴ�.
		if (finalValue < 0)
			finalValue = 0;
		if (minValue < 0)
			minValue = 0;

		//���� ���̸�
		if (m_bRandom)
		{
			//0���� ������ ���Ѵ�.
			if (finalValue - minValue <= 0)
				return finalValue;

			//������ �������� ���Ѵ�.
			finalValue = float(rand() % (int)(finalValue - minValue));
			finalValue += m_fMinValue;
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
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};

END