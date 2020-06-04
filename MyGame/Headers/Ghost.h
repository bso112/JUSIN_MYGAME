#pragma once
#include "Monster.h"

BEGIN(MyGame)
class CTexture;
class CAIStateCon;
class CItem;
class CGhost final : public CMonster
{
private:
	explicit CGhost(PDIRECT3DDEVICE9 _pGraphic_Device) :CMonster(_pGraphic_Device) {};
	explicit CGhost(CGhost& _rhs);
	virtual ~CGhost() = default;

public:
	virtual HRESULT	Initialize_Prototype(_tchar* _pFilePath = nullptr);
	virtual HRESULT Initialize(void * _param = nullptr);

private:
	vector<CItem*>	m_vecReward;
	const _tchar* m_pDialogueForStart;
	const _tchar* m_pDialogueForEnd;

public:
	virtual	_int	Interact(CGameObject* _pOther);

public:
	static CGhost* Create(PDIRECT3DDEVICE9 _pGraphic_Device);
	// CMonster��(��) ���� ��ӵ�
	virtual CGameObject * Clone(void * _param = nullptr) override;

public:
	// CBase��(��) ���� ��ӵ�
	virtual void Free() override;

};


END
