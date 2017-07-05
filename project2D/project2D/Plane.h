#pragma once
#include "Vector2.h"

class Circle;
class AABB_Cube;

class Plane
{

public:
	Plane();
	Plane(float NormalVec_X, float NormalVec_Y, float _Offset);
	Plane(Vector2 NormalVec, float Offset);

	~Plane();

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	//Set m_normalVec from X & Y float parameters.
	void SetNormalVec(float NormalVec_X, float NormalVec_Y);
	//Set m_normalVec from Vector2 parameter.
	void SetNormalVec(Vector2 NormalVec);
	//Set m_offset from float parameter.
	void SetOffset(float Offset);

	//Set all Plane variables from float parameters.
	void SetPlane(float NormalVec_X, float NormalVec_Y, float Offset);
	//Set all Plane variables from a Vector2 parameter for m_normalVec and a float parameter for m_offset.
	void SetPlane(Vector2 NormalVec, float Offset);


	//Returns Vector2 m_normalVec.
	Vector2 GetNormalVec();
	//Returns float m_offset.
	float   GetOffset();


	//Parameters take a Vector2 Point, Circle or AABB_Cube. Returns true if object is in front of Plane, else returns false. Returns false if object is on Plane.
	bool CheckIf_FrontOrBack(Vector2 Point);
	//Parameters take a Vector2 Point, Circle or AABB_Cube. Returns true if object is in front of Plane, else returns false. Returns false if object is on Plane.
	bool CheckIf_FrontOrBack(Circle _Circle);
	//Parameters take a Vector2 Point, Circle or AABB_Cube. Returns true if object is in front of Plane, else returns false. Returns false if object is on Plane.
	bool CheckIf_FrontOrBack(AABB_Cube AABB);

	//Parameters take a Vector2 Point, Circle or AABB_Cube. Returns true if object is on the Plane.
	bool CheckPlaneOverlap(Vector2 Point);
	//Parameters take a Vector2 Point, Circle or AABB_Cube. Returns true if object is on the Plane.
	bool CheckPlaneOverlap(Circle _Circle);
	//Parameters take a Vector2 Point, Circle or AABB_Cube. Returns true if object is on the Plane.
	bool CheckPlaneOverlap(AABB_Cube AABB);

	//Parameters take a Vector2 Point, Circle or AABB_Cube. Returns 1 if object is in front of Plane, -1 if behind Plane, and 0 if on Plane.
	int CheckCombinedTest(Vector2 Point);
	//Parameters take a Vector2 Point, Circle or AABB_Cube. Returns 1 if object is in front of Plane, -1 if behind Plane, and 0 if on Plane.
	int CheckCombinedTest(Circle _Circle);
	//Parameters take a Vector2 Point, Circle or AABB_Cube. Returns 1 if object is in front of Plane, -1 if behind Plane, and 0 if on Plane.
	int CheckCombinedTest(AABB_Cube AABB);


private:
	//Normalized Vector that determines where the Plane faces (a range from [-1x, -1y] to [1x, 1y]).
	Vector2 m_normalVec;
	//How far forward or backwards (determined by where the plane is facing) the Plane should be moved.
	float   m_offset;
};