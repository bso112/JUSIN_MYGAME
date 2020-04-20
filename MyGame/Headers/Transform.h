#pragma once
#include "Module.h"

BEGIN(MyGame)
class CTransform final : public CModule
{
private:
	explicit CTransform(LPDIRECT3DDEVICE9 _pGraphic_Device);
	explicit CTransform(CTransform& _module);
	virtual ~CTransform() = default;


private:
	_matrix		m_StateMatrix;
	_matrix		m_BaseMatrix;
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* _pArg);

public:
	HRESULT	Set_Position(Vector4 _vPosition);
	HRESULT	Set_Size(Vector2 _vSize);
	_matrix	Get_Matrix() { return m_StateMatrix; }
	Vector4	Get_Position() { return Vector4(m_StateMatrix.m[3][0], m_StateMatrix.m[3][1], m_StateMatrix.m[3][2], m_StateMatrix.m[3][3]); }
	_float2	Get_Size();
	RECT	Get_Rect();
		

public:
	static CTransform*	Create(LPDIRECT3DDEVICE9 _pGraphic_Device);
	// CModule을(를) 통해 상속됨
	virtual CModule * Clone(void * _pArg = nullptr) override;
	virtual void Free() override;
};

END
