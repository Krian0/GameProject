#pragma once
#include "Vector2.h"

class Circle;

class AABB_Cube
{

public:
	AABB_Cube();
	//bool UsingMinMax does nothing, it is only for the purpose of differing these constructors with MidPos/HalfSize constructors.
	AABB_Cube(Vector2 Min, Vector2 Max, bool UsingMinMax);
	AABB_Cube(Vector2 _MidPos, Vector2 _HalfSize);
	AABB_Cube(const Vector2 *PointArray, int NumOfPoints);

	~AABB_Cube();
	
	//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//


	//Set m_min and m_max from Vector2 parameters.
	void SetMinMax_Direct(Vector2 Min, Vector2 Max);
	//Set m_halfSize from Vector2 parameter.
	void SetHalfSize_Direct(Vector2 HalfSize);
	//Set m_midPos from Vector2 parameter.
	void SetMidPos_Direct(Vector2 MidPos);
								
	//Set m_min and m_max from Vector2 MidPos and HalfSize parameters.
	void SetMinMax_From(Vector2 MidPos, Vector2 HalfSize);
	//Set m_halfSize from Vector2 Min and Max parameters.
	void SetHalfSize_From(Vector2 Min, Vector2 Max);
	//Set m_midPos from Vector2 Min and Max parameters.
	void SetMidPos_From(Vector2 Min, Vector2 Max);
															                
	//Set all AABB variables from Vector2 Min and Max parameters.														                
	void SetCube_MinMax(Vector2 Min, Vector2 Max);
	//Set all AABB variables from Vector2 MidPos and HalfSize parameters.
	void SetCube_MidPos(Vector2 MidPos, Vector2 HalfSize);
	//Set AABB to encompass an array of points. Parameters take a pointer to a Vector2 array and an int for the number of points.
	void SetCube_FromPoints(const Vector2 *PointArray, int NumOfPoints);

	//Returns Vector2 m_min.
	Vector2 GetMin();
	//Returns Vector2 m_max.
	Vector2 GetMax();
	
	//Returns Vector2 m_halfSize.
	Vector2 GetHalfSize();
	//Returns Vector2 m_midPos.
	Vector2 GetMidPos();


	//Parameters take a Vector2, AABB_Cube or Circle. Checks if AABB overlaps with shape of the parameters class. Returns true or false.
	bool CheckCubeOverlap(Vector2 Point);
	//Parameters take a Vector2, AABB_Cube or Circle. Checks if AABB overlaps with shape of the parameters class. Returns true or false.
	bool CheckCubeOverlap(AABB_Cube AABB);
	//Parameters take a Vector2, AABB_Cube or Circle. Checks if AABB overlaps with shape of the parameters class. Returns true or false.
	bool CheckCubeOverlap(Circle _Circle);


private:
	Vector2 m_min;
	Vector2 m_max;

	//Alternate setup for AABB
	Vector2 m_midPos;
	Vector2 m_halfSize;
};