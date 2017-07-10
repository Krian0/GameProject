#include "AABB_Cube.h"

#pragma region AABB Constructors + Destructor
//Don't use the default
AABB_Cube::AABB_Cube()
{
}

AABB_Cube::AABB_Cube(Vector2 Min, Vector2 Max, bool UsingMinMax)
{
	SetMinMax_Direct(Min, Max);
	SetHalfSize_From(Min, Max);
	SetMidPos_From(Min, Max);
}

AABB_Cube::AABB_Cube(Vector2 MidPos, Vector2 HalfSize)
{
	SetMinMax_From(MidPos, HalfSize);
	SetHalfSize_Direct(HalfSize);
	SetMidPos_Direct(MidPos);
}

AABB_Cube::AABB_Cube(const Vector2 *PointArray, int NumOfPoints)
{
	SetCube_FromPoints(PointArray, NumOfPoints);
}

AABB_Cube::~AABB_Cube()
{
}
#pragma endregion


#pragma region AABB Set Functions
void AABB_Cube::SetMinMax_Direct(Vector2 Min, Vector2 Max)
{
	m_min = Min;
	m_max = Max;
}

void AABB_Cube::SetHalfSize_Direct(Vector2 HalfSize)
{
	m_halfSize = HalfSize;
}

void AABB_Cube::SetMidPos_Direct(Vector2 MidPos)
{
	m_midPos = MidPos;
}


void AABB_Cube::SetMinMax_From(Vector2 MidPos, Vector2 HalfSize)
{
	m_min = (MidPos - HalfSize);
	m_max = (MidPos + HalfSize);
}

void AABB_Cube::SetHalfSize_From(Vector2 Min, Vector2 Max)
{
	m_halfSize = ((Max - Min) / 2);
}

void AABB_Cube::SetMidPos_From(Vector2 Min, Vector2 Max)
{
	m_midPos = (Min + ((Max - Min) / 2));
}


void AABB_Cube::SetCube_MinMax(Vector2 Min, Vector2 Max)
{
	SetMinMax_Direct(Min, Max);
	SetHalfSize_From(Min, Max);
	SetMidPos_From(Min, Max);
}

void AABB_Cube::SetCube_MidPos(Vector2 MidPos, Vector2 HalfSize)
{
	SetMinMax_From(MidPos, HalfSize);
	SetHalfSize_Direct(HalfSize);
	SetMidPos_Direct(MidPos);
}

void AABB_Cube::SetCube_FromPoints(const Vector2 *PointArray, int NumOfPoints)
{
	//Iterates through each point in PointArray to find the Min and Max X & Y values.
	if (NumOfPoints > 1)
	{
		Vector2 Min(INFINITY, INFINITY);
		Vector2 Max(-INFINITY, -INFINITY);

		for (int i = 0; i < NumOfPoints; i++)
		{
			if (PointArray[i].x < Min.x)
				Min.x = PointArray[i].x;

			if (PointArray[i].y < Min.y)
				Min.y = PointArray[i].y;

			if (PointArray[i].x > Max.x)
				Max.x = PointArray[i].x;

			if (PointArray[i].y > Max.y)
				Max.y = PointArray[i].y;
		}

		m_min = Min;
		m_max = Max;

		//Set other values in AABB from Min and Max X & Y values.
		SetHalfSize_From(m_min, m_max);
		SetMidPos_From(m_min, m_max);
	}
}
#pragma endregion


#pragma region AABB Get Functions
Vector2 AABB_Cube::GetMin()
{
	return m_min;
}

Vector2 AABB_Cube::GetMax()
{
	return m_max;
}

Vector2 AABB_Cube::GetHalfSize()
{
	return m_halfSize;
}

Vector2 AABB_Cube::GetMidPos()
{
	return m_midPos;
}
#pragma endregion


#pragma region AABB CheckOverlap Functions
bool AABB_Cube::CheckCubeOverlap(Vector2 Point)
{
	bool IsThereAnOverlap = false;
	if (m_min.x < Point.x && m_min.y < Point.y && m_max.x > Point.x && m_max.y > Point.y)
		IsThereAnOverlap = true;

	return IsThereAnOverlap;
}

bool AABB_Cube::CheckCubeOverlap(AABB_Cube AABB)
{
	bool IsThereAnOverlap = false;
	if (m_max.x < AABB.m_min.x && AABB.m_max.x < m_min.x && m_max.y < AABB.m_min.y && AABB.m_max.y < m_min.y)
		IsThereAnOverlap = true;

	return IsThereAnOverlap;
}

bool AABB_Cube::CheckCubeOverlap(AABB_Cube* AABB)
{
	bool IsThereAnOverlap = false;
	if (m_max.x < AABB->m_min.x && AABB->m_max.x < m_min.x && m_max.y < AABB->m_min.y && AABB->m_max.y < m_min.y)
		IsThereAnOverlap = true;

	return IsThereAnOverlap;
}
#pragma endregion