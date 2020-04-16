#pragma once


typedef struct tagVector2 : public D3DXVECTOR4
{
	tagVector2() 
	{
		ZeroMemory(this, sizeof(tagVector2));
	}

	tagVector2(D3DXVECTOR4& _DXVECTOR4) 
	{ 
		x = _DXVECTOR4.x;
		y = _DXVECTOR4.y;
		z = _DXVECTOR4.z;
		w = _DXVECTOR4.w;
	
	}

	tagVector2(float _fX, float _fY)
	{
		x = _fX;
		y = _fY;
		z = 0;
		w = 0;
	}

	tagVector2(float _fX, float _fY, float _fW)
	{
		x = _fX;
		y = _fY;
		z = 0;
		w = _fW;
	}

	tagVector2 operator+(tagVector2 _vec)
	{
		return tagVector2((D3DXVECTOR4)*this + (D3DXVECTOR4)_vec);
	}

	tagVector2 operator-(tagVector2 _vec)
	{
		return tagVector2((D3DXVECTOR4)*this - (D3DXVECTOR4)_vec);
	}
	tagVector2& operator+=(tagVector2 _vec)
	{
		(D3DXVECTOR4)*this += (D3DXVECTOR4)_vec;
		return *this;
	}

	tagVector2& operator-=(tagVector2 _vec)
	{
		(D3DXVECTOR4)*this -= (D3DXVECTOR4)_vec;
		return *this;
	}

	tagVector2& operator+=(float _scalar)
	{
		x += _scalar;
		y += _scalar;
		return *this;
	}

	tagVector2& operator-=(float _scalar)
	{
		x -= _scalar;
		y -= _scalar;
		return *this;
	}

	tagVector2 operator*(float _scalar)
	{
		return tagVector2((D3DXVECTOR4)*this * _scalar);
	}
	tagVector2 operator+(float _scalar)
	{

		return tagVector2(x + _scalar, y + _scalar);
	}

	tagVector2 operator-(float _scalar)
	{
		return tagVector2(x - _scalar, y - _scalar);

	}

	tagVector2& nomalize()
	{
		float mag = magnitude();
		// 0으로는 나눌 수 없다.
		if (mag > 0)
		{
			x = x / mag;
			y = y / mag;
			return *this;
		}

		return *this;
	}

	//임시객체를 리턴만 할뿐, 자기자신의 값을 변경하지는 않음
	tagVector2 Nomalize()
	{
		tagVector2 vec = {};
		float mag = magnitude();
		// 0으로는 나눌 수 없다.
		if (mag > 0)
		{
			vec.x = x / mag;
			vec.y = y / mag;
			return vec;
		}
		//벡터의 길이가 0 이면 빈 벡터를 출력 
		return vec;
	}

	float magnitude()
	{
		return sqrtf(x * x + y * y);
	}

}Vector2;



typedef struct tagFrame
{

}FRAME;

typedef	struct tagVertex_Texture
{
	D3DXVECTOR4 vPosition;
	D3DXVECTOR2 vTexUV;
}VTXTEX;




typedef struct tagInfo
{
	Vector2		vPos;
	_uint		iCX;
	_uint		iCY;

	tagInfo() {}
	tagInfo(D3DXVECTOR4 _vPos, _uint _iCX, _uint _iCY)
		:vPos(_vPos), iCX(_iCX), iCY(_iCY)
	{

	}

}INFO;

