#pragma once
#include "Vector2.h"

class AABB_Cube;

class Circle
{

public:
	Circle();
	Circle(Vector2 MidPos, float Radius);
	Circle(const Vector2 *PointArray, int NumOfPoints);
	
	~Circle();

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	//Parameters take Vector2 MidPos, Min and Max. Returns Vector2 of the closest point to Circle MidPos inbetween Min and Max of AABB. Used in checking Circle/AABB_Cube overlap.
	Vector2 Clamp(Vector2 Circle_MidPos, Vector2 Min, Vector2 Max);


	//Set m_midPos from Vector parameter.
	void SetMidPos(Vector2 MidPos);
	//Set m_radius from float parameter.
	void SetRadius(float Radius);

	//Set all Circle variables from Vector2 parameter for MidPos, and a float parameter for Radius.
	void SetCircle(Vector2 MidPos, float Radius);
	//Set Circle to encompass an array of points. Parameters take a pointer to a Vector2 array and an int for the number of points.
	void SetCircle_FromPoints(const Vector2 *PointArray, int NumOfPoints);


	//Returns Vector2 m_midPos.
	Vector2 GetMidPos();
	//Returns float m_radius.
	float   GetRadius();


	//Parameters take a Vector2, AABB_Cube or Circle. Checks if Circle overlaps with shape of the parameters class. Returns true or false.
	bool CheckCircleOverlap(Vector2 Point);
	//Parameters take a Vector2, AABB_Cube or Circle. Checks if Circle overlaps with shape of the parameters class. Returns true or false.
	bool CheckCircleOverlap(AABB_Cube AABB);
	//Parameters take a Vector2, AABB_Cube or Circle. Checks if Circle overlaps with shape of the parameters class. Returns true or false.
	bool CheckCircleOverlap(Circle _Circle);


private:
	Vector2 m_midPos;
	float m_radius;
};