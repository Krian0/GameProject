#include "Plane.h"

#pragma region Plane Constructors + Destructor
Plane::Plane()
{
}

Plane::Plane(float NormalVec_X, float NormalVec_Y, float Offset)
{
	SetPlane(NormalVec_X, NormalVec_Y, Offset);
}

Plane::Plane(Vector2 _NormalVec, float Offset)
{
	SetPlane(_NormalVec, Offset);
}

Plane::~Plane()
{
}
#pragma endregion


#pragma region Plane Set Functions
void Plane::SetNormalVec(float NormalVec_X, float NormalVec_Y)
{
	m_normalVec.x = NormalVec_X;
	m_normalVec.y = NormalVec_Y;

	m_normalVec.normaliseDirect();
}

void Plane::SetNormalVec(Vector2 NormalVec)
{
	m_normalVec = NormalVec;

	m_normalVec.normaliseDirect();
}

void Plane::SetOffset(float Offset)
{
	m_offset = Offset;
}


void Plane::SetPlane(float NormalVec_X, float NormalVec_Y, float Offset)
{
	m_normalVec.x = NormalVec_X;
	m_normalVec.y = NormalVec_Y;
	m_normalVec.normaliseDirect();

	m_offset = Offset;
}
void Plane::SetPlane(Vector2 NormalVec, float Offset)
{
	m_normalVec = NormalVec;
	m_normalVec.normaliseDirect();

	m_offset = Offset;
}
#pragma endregion


#pragma region Plane Get Functions
Vector2 Plane::GetNormalVec()
{
	return m_normalVec;
}

float Plane::GetOffset()
{
	return m_offset;
}
#pragma endregion


#pragma region Plane Check Functions
bool Plane::CheckIf_FrontOrBack(Vector2 Point)
{
	bool FrontOrBack = false;
	if ((m_normalVec.dot(Point) + m_offset) > 0)
		FrontOrBack = true;

	return FrontOrBack;
}

bool Plane::CheckPlaneOverlap(Vector2 Point)
{
	bool IsThereAnOverlap = false;
	if ((m_normalVec.dot(Point) + m_offset) == 0)
		IsThereAnOverlap = true;

	return IsThereAnOverlap;
}

int Plane::CheckCombinedTest(Vector2 Point)
{
	int Result = 1;

	if (CheckIf_FrontOrBack(Point) == false)
		Result = -1;

	if (CheckPlaneOverlap(Point) == true)
		Result = 0;

	return Result;
}
#pragma endregion