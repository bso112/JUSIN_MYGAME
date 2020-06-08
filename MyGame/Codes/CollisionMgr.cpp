#include "stdafx.h"
#include "..\Headers\CollisionMgr.h"
#include "GameObject.h"
#include "Transform.h"

USING(MyGame)


CCollisionMgr::CCollisionMgr()
{
}

bool CCollisionMgr::Collision_Rect(list<CGameObject*> _Dst, list<CGameObject*> _Src)
{

	RECT rc = {};
	
	for (auto& Dst : _Dst)
	{	
		if (nullptr == Dst ||
			(nullptr != Dst && !Dst->Get_Active()))
			continue;

		CTransform* pDstTransform = (CTransform*)Dst->Get_Module(L"Transform");
		
		if (nullptr == pDstTransform)
			return false;

		for (auto& Src : _Src)
		{	

			if (nullptr == Src ||
				(nullptr != Src && !Src->Get_Active()))
				continue;

			CTransform* pSrcTransform = (CTransform*)Src->Get_Module(L"Transform");
			
			if (nullptr == pSrcTransform)
				return false;


			if (IntersectRect(&rc, &pDstTransform->Get_RECT(), &pSrcTransform->Get_RECT()))
			{
				//상대방이 죽은경우, 충돌처리를 하지 않는다.
				if (Src->Get_Dead())
					Dst->Erase_Collided(Src);
				if (Dst->Get_Dead())
					Src->Erase_Collided(Dst);
				if (Src->Get_Dead() || Dst->Get_Dead())
					continue;


				//만약 서로 충돌한 적이 없으면 서로의 충돌리스트에 서로를 추가한다.
				if (!Dst->Contain_Collided(Src))
				{
					Dst->Add_Collided(Src);
					Dst->Set_isCollided(true);
					Dst->OnCollisionEnter(Src);
				}
				if (!Src->Contain_Collided(Dst))
				{
					Src->Add_Collided(Dst);
					Src->Set_isCollided(true);
					Src->OnCollisionEnter(Dst);
				}


				Dst->OnCollisionStay(Src);
				Src->OnCollisionStay(Dst);

			}
			else
			{
				//만약 상대방이 전에 충돌한 리스트에 있으면 삭제한다.
				Dst->Erase_Collided(Src);
				Src->Erase_Collided(Dst);

				//충돌리스트가 비었고, 전에 충돌한적이 있으면 collisionExit을 실행한다.
				if (Dst->Get_CollidedSize() == 0 && Dst->Get_isCollided())
				{
					Dst->Set_isCollided(false);
					Dst->OnCollisionExit(Src);
				}
				if (Src->Get_CollidedSize() == 0 && Src->Get_isCollided())
				{
					Src->Set_isCollided(false);
					Src->OnCollisionExit(Dst);
				}
			}
		}
	}
	return false;
}

//bool CCollisionMgr::Collision_Rect(list<CGameObject*> _Dst, list<CGameObject*> _Src)
//{
//
//	RECT rc = {};
//
//	for (auto& Dst : _Dst)
//	{
//		if (nullptr == Dst ||
//			(nullptr != Dst && !Dst->Get_Active()))
//			continue;
//
//		CTransform* pDstTransform = (CTransform*)Dst->Get_Module(L"Transform");
//
//		if (nullptr == pDstTransform)
//			return false;
//
//		for (auto& Src : _Src)
//		{
//
//			if (nullptr == Src ||
//				(nullptr != Src && !Src->Get_Active()))
//				continue;
//
//			CTransform* pSrcTransform = (CTransform*)Src->Get_Module(L"Transform");
//
//			if (nullptr == pSrcTransform)
//				return false;
//
//
//			if (IntersectRect(&rc, &pDstTransform->Get_RECT(), &pSrcTransform->Get_RECT()))
//			{
//				Dst->OnCollisionEnter(Src);
//				Src->OnCollisionEnter(Dst);
//
//			}
//		}
//	}
//	return false;
//}


bool CCollisionMgr::GameObjectInTile(list<CGameObject*> _listObj, list<CGameObject*> _listTerrain)
{
	RECT rc = {};

	for (auto& pObj : _listObj)
	{

		if (nullptr == pObj ||
			(nullptr != pObj && !pObj->Get_Active()))
			continue;

		CTransform* pObjTransform = (CTransform*)pObj->Get_Module(L"Transform");

		if (nullptr == pObjTransform)
			return false;

		for (auto& pTile : _listTerrain)
		{


			if (nullptr == pTile ||
				(nullptr != pTile && !pTile->Get_Active()))
				continue;

			CTransform* pTileTransform = (CTransform*)pTile->Get_Module(L"Transform");

			if (nullptr == pTileTransform)
				return false;

			POINT pt;
			pt.x = (LONG)pObjTransform->Get_Position().x;
			pt.y = (LONG)pObjTransform->Get_Position().y;

			if (PtInRect(&pTileTransform->Get_RECT(), pt))
			{
				//상대방이 죽은경우, 충돌처리를 하지 않는다.
				if (pTile->Get_Dead())
					pObj->Erase_Collided(pTile);
				if (pObj->Get_Dead())
					pTile->Erase_Collided(pObj);
				if (pTile->Get_Dead() || pObj->Get_Dead())
					continue;


				//만약 서로 충돌한 적이 없으면 서로의 충돌리스트에 서로를 추가한다.
				if (!pObj->Contain_Collided(pTile))
				{
					pObj->Add_Collided(pTile);
					pObj->Set_isCollided(true);
					pObj->OnCollisionEnter(pTile);
				}
				if (!pTile->Contain_Collided(pObj))
				{
					pTile->Add_Collided(pObj);
					pTile->Set_isCollided(true);
					pTile->OnCollisionEnter(pObj);
				}


				pObj->OnCollisionStay(pTile);
				pTile->OnCollisionStay(pObj);

			}
			else
			{
				//만약 상대방이 전에 충돌한 리스트에 있으면 삭제한다.
				pObj->Erase_Collided(pTile);
				pTile->Erase_Collided(pObj);

				//충돌리스트가 비었고, 전에 충돌한적이 있으면 collisionExit을 실행한다.
				if (pObj->Get_CollidedSize() == 0 && pObj->Get_isCollided())
				{
					pObj->Set_isCollided(false);
					pObj->OnCollisionExit(pTile);
				}
				if (pTile->Get_CollidedSize() == 0 && pTile->Get_isCollided())
				{
					pTile->Set_isCollided(false);
					pTile->OnCollisionExit(pObj);
				}
			}
		}
	}
	return false;
}




bool CCollisionMgr::Collision(list<CGameObject*> _Dst, list<CGameObject*> _Src, bool _bisCollided)
{
	RECT rc = {};

	for (auto& Dst : _Dst)
	{
		if (nullptr == Dst)
			return false;

		for (auto& Src : _Src)
		{
			if (nullptr == Src)
				return false;

			if (_bisCollided)
			{
				//상대방이 죽은경우, 충돌처리를 하지 않는다.
				if (Src->Get_Dead())
					Dst->Erase_Collided(Src);
				if (Dst->Get_Dead())
					Src->Erase_Collided(Dst);
				if (Src->Get_Dead() || Dst->Get_Dead())
					continue;


				//만약 서로 충돌한 적이 없으면 서로의 충돌리스트에 서로를 추가한다.
				if (!Dst->Contain_Collided(Src))
				{
					Dst->Add_Collided(Src);
					Dst->Set_isCollided(true);
					Dst->OnCollisionEnter(Src);
				}
				if (!Src->Contain_Collided(Dst))
				{
					Src->Add_Collided(Dst);
					Src->Set_isCollided(true);
					Src->OnCollisionEnter(Dst);
				}


				Dst->OnCollisionStay(Src);
				Src->OnCollisionStay(Dst);

			}
			else
			{
				//만약 상대방이 전에 충돌한 리스트에 있으면 삭제한다.
				Dst->Erase_Collided(Src);
				Src->Erase_Collided(Dst);

				//충돌리스트가 비었고, 전에 충돌한적이 있으면 collisionExit을 실행한다.
				if (Dst->Get_CollidedSize() == 0 && Dst->Get_isCollided())
				{
					Dst->Set_isCollided(false);
					Dst->OnCollisionExit(Src);
				}
				if (Src->Get_CollidedSize() == 0 && Src->Get_isCollided())
				{
					Src->Set_isCollided(false);
					Src->OnCollisionExit(Dst);
				}
			}
		}
	}
	return false;
}

//bool CCollisionMgr::Intersect_LIne(const LINE _line1, const LINE _line2, Vector2& _result)
//{
//
//	Vector2 p0 = _line1.src;
//	Vector2 p1 = _line1.dst;
//	Vector2 p2 = _line2.src;
//	Vector2 p3 = _line2.dst;
//
//
//	float a1 = p1.fY - p0.fY;
//	float b1 = p0.fX - p1.fX;
//	float c1 = a1 * p0.fX + b1 * p0.fY;
//	float a2 = p3.fY - p2.fY;
//	float b2 = p2.fX - p3.fX;
//	float c2 = a2 * p2.fX + b2 * p2.fY;
//	float denominator = a1 * b2 - a2 * b1;
//
//	float intersectX = (b2 * c1 - b1 * c2) / denominator;
//	float intersectY = (a1 * c2 - a2 * c1) / denominator;
//
//	float distX0 = (intersectX - p0.fX) / (p1.fX - p0.fX);
//	float distY0 = (intersectY - p0.fY) / (p1.fY - p0.fY);
//	float distX1 = (intersectX - p2.fX) / (p3.fX - p2.fX);
//	float distY1 = (intersectY - p2.fY) / (p3.fY - p2.fY);
//
//	if (((distX0 >= 0 && distX0 <= 1) || (distY0 >= 0 && distY0 <= 1))
//		&& ((distX1 >= 0 && distX1 <= 1) || (distY1 >= 0 && distY1 <= 1)))
//	{
//		_result.fX = intersectX;
//		_result.fY = intersectY;
//		return true;
//	}
//
//	return false;
//}



void CCollisionMgr::Free()
{
}
