#include "BoundingShapes.h"

#pragma region AABB & Circle
//Parameters take Vector2 MidPos, Min and Max. Returns Vector2 of the closest point to Circle MidPos inbetween Min and Max of AABB. Used in checking Circle/AABB_Cube overlap.
Vector2 Circle::Clamp(Vector2 Circle_MidPos, Vector2 Min, Vector2 Max)
{
	Vector2 Temp;

	if (Circle_MidPos.x > Min.x && Circle_MidPos.x < Max.x)
		Temp.x = Circle_MidPos.x;

	if (Circle_MidPos.x < Min.x)
		Temp.x = Min.x;
	if (Circle_MidPos.x > Max.x)
		Temp.x = Max.x;


	if (Circle_MidPos.y > Min.y && Circle_MidPos.y < Max.y)
		Temp.y = Circle_MidPos.y;

	if (Circle_MidPos.y < Min.y)
		Temp.y = Min.y;
	if (Circle_MidPos.y > Max.y)
		Temp.y = Max.y;

	return Temp;
}

//Check for a Circle-AABB_Cube overlap.
//Parameters take a Vector2, AABB_Cube or Circle. Checks if Circle overlaps with shape of the parameters class. Returns true or false.
bool Circle::CheckCircleOverlap(AABB_Cube AABB)
{
	return CheckCircleOverlap(Clamp(m_midPos, AABB.GetMin(), AABB.GetMax()));
}

//Check for a AABB_Cube-Circle overlap: Reverse of above
//Parameters take a Vector2, AABB_Cube or Circle. Checks if AABB overlaps with shape of the parameters class. Returns true or false.
bool AABB_Cube::CheckCubeOverlap(Circle _Circle)
{
	return _Circle.CheckCircleOverlap(_Circle.Clamp(_Circle.GetMidPos(), GetMin(), GetMax()));
}
#pragma endregion


#pragma region Plane & Circle
//Parameters take a Vector2 Point, AABB_Cube or Circle. Returns true if object is in front of Plane, else returns false. Returns false if object is on Plane.
bool Plane::CheckIf_FrontOrBack(Circle _Circle)
{
	bool FrontOrBack = false;
	if ((m_normalVec.dot(_Circle.GetMidPos()) + m_offset) > _Circle.GetRadius())
		FrontOrBack = true;

	return FrontOrBack;
}

//Parameters take a Vector2 Point, AABB_Cube or Circle. Returns true if object is on the Plane.
bool Plane::CheckPlaneOverlap(Circle _Circle)
{
	bool IsThereAnOverlap = true;
	Vector2 Off(m_offset, m_offset);
	Vector2 Pos = _Circle.GetMidPos() + Off;
	
	float Result = m_normalVec.dot(Pos);
	float Radius = _Circle.GetRadius();
	if (Result > Radius || Result < -Radius)
		IsThereAnOverlap = false;

	return IsThereAnOverlap;
}

//Parameters take a Vector2 Point, AABB_Cube or Circle. Returns 1 if object is in front of Plane, -1 if behind Plane, and 0 if on Plane.
int Plane::CheckCombinedTest(Circle _Circle)
{
	int Result = 1;

	if (CheckIf_FrontOrBack(_Circle) == false)
		Result = -1;

	if (CheckPlaneOverlap(_Circle) == true)
		Result = 0;

	return Result;
}
#pragma endregion


#pragma region Plane & AABB
//Parameters take a Vector2 Point, AABB_Cube or Circle. Returns true if object is in front of Plane, else returns false. Returns false if object is on Plane.
bool Plane::CheckIf_FrontOrBack(AABB_Cube AABB)
{
	bool FrontOrBack = false;
	float DistanceFromPlane = (m_normalVec.dot(AABB.GetMidPos()) + m_offset);

	float Dot = AABB.GetHalfSize().dot(m_normalVec);

	if (DistanceFromPlane > Dot)
		FrontOrBack = true;

	return FrontOrBack;
}

//Parameters take a Vector2 Point, AABB_Cube or Circle. Returns true if object is on the Plane.
bool Plane::CheckPlaneOverlap(AABB_Cube AABB)
{
	bool IsThereAnOverlap = true;
	float DistanceFromPlane = (m_normalVec.dot(AABB.GetMidPos()) + m_offset);

	float Dot = AABB.GetHalfSize().dot(m_normalVec);

	if (DistanceFromPlane > Dot || DistanceFromPlane < -Dot)
		IsThereAnOverlap = false;

	return IsThereAnOverlap;
}

//Parameters take a Vector2 Point, AABB_Cube or Circle. Returns 1 if object is in front of Plane, -1 if behind Plane, and 0 if on Plane.
int Plane::CheckCombinedTest(AABB_Cube AABB)
{
	int Result = 1;

	if (CheckIf_FrontOrBack(AABB) == false)
		Result = -1;

	if (CheckPlaneOverlap(AABB) == true)
		Result = 0;

	return Result;
}
#pragma endregion