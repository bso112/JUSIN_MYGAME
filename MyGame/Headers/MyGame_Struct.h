#pragma once


typedef struct tagVector4 : public D3DXVECTOR4
{
	tagVector4() 
	{
		ZeroMemory(this, sizeof(tagVector4));
	}

	tagVector4(D3DXVECTOR4& _DXVECTOR4) 
	{ 
		x = _DXVECTOR4.x;
		y = _DXVECTOR4.y;
		z = _DXVECTOR4.z;
		w = _DXVECTOR4.w;
	
	}


	tagVector4(float _fX, float _fY, float _fZ = 0, float _fW = 0)
	{
		x = _fX;
		y = _fY;
		z = _fZ;
		w = _fW;
	}


	tagVector4 operator+(tagVector4 _vec)
	{
		return tagVector4((D3DXVECTOR4)*this + (D3DXVECTOR4)_vec);
	}

	tagVector4 operator-(tagVector4 _vec)
	{
		return tagVector4((D3DXVECTOR4)*this - (D3DXVECTOR4)_vec);
	}
	tagVector4& operator+=(tagVector4 _vec)
	{
		*this = (D3DXVECTOR4)*this += (D3DXVECTOR4)_vec;
		return *this;
	}

	tagVector4& operator-=(tagVector4 _vec)
	{
		*this = (D3DXVECTOR4)*this -= (D3DXVECTOR4)_vec;
		return *this;
	}

	tagVector4& operator+=(float _scalar)
	{
		x += _scalar;
		y += _scalar;
		return *this;
	}

	tagVector4& operator-=(float _scalar)
	{
		x -= _scalar;
		y -= _scalar;
		return *this;
	}

	tagVector4 operator*(float _scalar)
	{
		return tagVector4((D3DXVECTOR4)*this * _scalar);
	}
	tagVector4 operator+(float _scalar)
	{

		return tagVector4(x + _scalar, y + _scalar);
	}

	tagVector4 operator-(float _scalar)
	{
		return tagVector4(x - _scalar, y - _scalar);

	}

	tagVector4& nomalize()
	{
		//float mag = magnitude();
		//// 0으로는 나눌 수 없다.
		//if (mag > 0)
		//{
		//	x = x / mag;
		//	y = y / mag;
		//	return *this;
		//}

		D3DXVec4Normalize(this, this);

		return *this;
	}

	//임시객체를 리턴만 할뿐, 자기자신의 값을 변경하지는 않음
	tagVector4 Nomalize()
	{
		//tagVector4 vec = {};
		//float mag = magnitude();
		//// 0으로는 나눌 수 없다.
		//if (mag > 0)
		//{
		//	vec.x = x / mag;
		//	vec.y = y / mag;
		//	return vec;
		//}
		////벡터의 길이가 0 이면 빈 벡터를 출력 
		//return vec;

		tagVector4 vec = {};

		D3DXVec4Normalize(&vec, this);

		return vec;
	}

	float magnitude()
	{
		//return sqrtf(x * x + y * y);
		return D3DXVec4Length(this);
	}

}Vector4, Vector3, Vector2;



typedef struct tagBaseDesc
{
	Vector3 vPos;
	Vector3 vSize;
	tagBaseDesc() {};
	tagBaseDesc(Vector3 _vPos, Vector3 _vSize)
	{
		vPos = _vPos;
		vSize = _vSize;
	}

}BASEDESC;

typedef	struct tagVertex_Texture
{
	D3DXVECTOR4 vPosition;
	D3DXVECTOR2 vTexUV;
	D3DXVECTOR4	vWinPos;
}VTXTEX;




typedef struct tagTerrain
{
	//타일이 참조해야할 텍스처이름
	wchar_t*	m_pFilePath = nullptr;
	
	bool		m_bMovable = false;
	bool		m_bWater = false;
	int			m_iMoveCost = 0;

	tagTerrain() { ZeroMemory(this, sizeof(tagTerrain)); }
	tagTerrain(bool _bMovable, bool _bWater = false, int _iMoveCost = 0)
	{
		m_bMovable = _bMovable;
		m_bWater = _bWater;
		m_iMoveCost = _iMoveCost;
	}



}TERRAIN;

