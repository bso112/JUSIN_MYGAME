#pragma once
#include "GameObject.h"
BEGIN(MyGame)
class CTransform;
class CTexture;
class CVIBuffer;
class CTerrain : public CGameObject
{

public:
	enum STATE { STATE_NORMAL = 0, STATE_UNLOCKED = 0, STATE_LOCKED = 1, STATE_USED = 1, STATE_END };

public:
	typedef struct tagNode
	{
		_int Gcost = INT_MAX; // distance from staring node
		_int Hcost = INT_MAX; // distance from end node
		_int Fcost = INT_MAX;	// Gcost + Hcost

		//�ε���
		_int X = 0;
		_int Y = 0;

		//�θ�
		CTerrain* pParent = nullptr;

		tagNode() {}
		tagNode(_int _Gcost, _int _Hcost, _int _Fcost, _int _X, _int _Y, CTerrain* _pParent)
		{
			Gcost = _Gcost;
			Hcost = _Hcost;
			Fcost = _Fcost;
			X = _X;
			Y = _Y;
			pParent = _pParent;
		}

		void Clear()
		{
			Gcost = INT_MAX;	// distance from staring node
			Hcost = INT_MAX;	// distance from end node
			Fcost = INT_MAX;	// Gcost + Hcost

			X = 0;
			Y = 0;
			pParent = nullptr;
		}
	}NODE;
public:
	typedef struct tag_SaveData
	{
		_tchar		m_PrototypeTag[MAX_PATH];
		Vector3		m_vPosition;
		Vector3		m_vSize;
		Vector3		m_vRotation;
		_int		m_iCurFrame;
		STATE		m_eState;


	}SAVE_DATA;
protected:
	explicit CTerrain() {};
	explicit CTerrain(PDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CTerrain(CTerrain& _rhs);
	virtual ~CTerrain() = default;

protected:
	CTransform*		m_pTransform = nullptr;
	CTexture*		m_pTexture = nullptr;
	CVIBuffer*		m_pVIBuffer = nullptr;

protected:
	STATE			m_eState = STATE_NORMAL;
	bool			m_bHidden = false;
	NODE			m_tNode = {};
	//Ÿ�� ���� �ִ� �͵�
protected:
	CTransform*		m_pCharacterTranform = nullptr;

protected:
	TERRAIN			m_tInfo = {};
	_tchar			m_PrototypeTag[MAX_PATH];
	// _uint�� �ϸ� ������ �Ǵ¼��� 4500��¼�� �ϴ� ū���� ���� �ִ� �ؽ��� ������ -1 �̵�.
	_int			m_iCurFrame = 0;

	//����׿�
private:
	bool			m_bMarked = false;


public:
	virtual HRESULT	Initialize_Prototype(TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, const _tchar* _pPrototypeTag, _tchar* _pFilePath = nullptr);
	virtual	HRESULT	Initialize();
	virtual _int	LateUpate(_double _timeDelta) override;
	virtual HRESULT	Render();

public:
	SAVE_DATA	Get_SaveData();
	HRESULT		Load_Data(SAVE_DATA& _eSaveData);
	void		Hide() { m_bHidden = true; }
	void		Reveal() { m_bHidden = false; }
	bool		IsHidden() { return m_bHidden; }
	//�������� movable�̰�, _pTransform �̿��� ������ ������ ������ �� �� �ִ�.
	bool		IsMovable(CTransform* _pTransform);
	void		Set_Texture(_int index) { m_iCurFrame = index; }


public:
	HRESULT		Forward_Frame();
	HRESULT		Backward_Frame();
	void		Set_Node(NODE _tNode) { m_tNode = _tNode; }
	const NODE&	Get_Node() { return m_tNode; }
	void		Clear_Node() { m_tNode.Clear(); }
	void		Set_Mark(bool _bMarked) { m_bMarked = _bMarked; }

public:
	virtual void OnCollisionEnter(CGameObject* _pOther);
	virtual void OnCollisionStay(CGameObject* _pOther);
	virtual void OnCollisionExit(CGameObject* _pOther);

protected:
	virtual void OnCollisionEnterTerrain(CGameObject* _pOther);
	virtual void OnCollisionStayTerrain(CGameObject* _pOther);
	virtual void OnCollisionExitTerrain(CGameObject* _pOther);


protected:
	//�����;����� Frame�� ���Ҷ� ����Ŭ������ �´� �����ͷ� ������.
	virtual	HRESULT	OnMoveFrame();
	//Terrain�� �ε��Ҷ� ����Ŭ������ �´� �����ͷ� ������.
	virtual HRESULT	OnLoadData();
public:
	static CTerrain*	Create(PDIRECT3DDEVICE9 _pGraphic_Device, TERRAIN _tData, const _tchar* _pTextureTag, SCENEID _eTextureScene, _tchar* _pFilePath = nullptr);
	virtual CGameObject* Clone(void * _param = nullptr);
	virtual void Free() override;




};
END