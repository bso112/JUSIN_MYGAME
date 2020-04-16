#pragma once
#include "Base.h"

BEGIN(MyGame)

//BaseValue�� ������ �޾� ������ value�� �����ϱ� ���� ����Ŭ����.
class CStat final: public CBase
{
private:
	explicit CStat();
	virtual ~CStat() = default;

private:
	float m_fBaseValue;
	list<float> m_listModifier;

public:
	void AddModifier(float _fModifier) { if (_fModifier > 0) m_listModifier.push_back(_fModifier); }
	void RemoveModifire(float _fModifier) { if (_fModifier > 0) m_listModifier.remove(_fModifier); }
	float GetValue()
	{
		float finalValue = m_fBaseValue;
		for (auto& val : m_listModifier)
		{
			finalValue += val;
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

	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};

END