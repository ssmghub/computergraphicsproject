#include <list>
#include <vector>
#include <algorithm>

#include "point.h"

//The function returns a dummy point so that it will compile
point evaluate1(float t, std::list<point> P)
{

	std::list<point> Q = P;

	//while (Q has more than 1 element)
	while (Q.size() > 1)
	{
		//Initialise empty list R
		std::list<point> R;
		std::list<point>::iterator p1;// = Q.begin();
		std::list<point>::iterator p2;// = std::next(p1);
		for (p1 = Q.begin(), p2 = std::next(p1); p2 != Q.end(); ++p1, ++p2)
		{
			point p;
			p = ((1 - t) * (*p1)) + (t * (*p2));

			R.push_back(p);
		}

		Q.clear();
		Q = R;
	}


	//return Q.begin();
	return Q.front();
}

std::vector<point> EvaluateBezierCurve1(std::vector<point>ctrl_points, int num_evaluations)
{
	float offset = 1.0f / num_evaluations; 

	//initialise empty curve
	std::list<point> ps(ctrl_points.begin(), ctrl_points.end());
	std::vector<point> curve;

	curve.push_back(ctrl_points.front());
	//curve.push_back(ctrl_points[0]); /////////// ???

	for(int e=0; e<num_evaluations; e++)
	{
		point p = evaluate1(offset * (e + 1), ps);
		curve.push_back(p);
	}
	return curve;
}

float* MakeFloatsFromVector1(std::vector<point> curve, int &num_verts, int &num_floats, float r, float g, float b)
{
	num_verts = curve.size();
	if(num_verts==0)
	{
		return NULL;
	}

	num_floats = num_verts * 6;

	//allocate memory for the vertex attributes
	float* vertices = (float*)malloc(sizeof(float)* num_floats);
	
	for (int p=0; p < num_verts; p++)
	{
		//specify vertex position using p
		vertices[0 + 6 * p] = curve[p].x;
		vertices[1 + 6 * p] = curve[p].y;
		vertices[2 + 6 * p] = curve[p].z;
		//specify vertex colour using r, g, b
		vertices[3 + 6 * p] = r;
		vertices[4 + 6 * p] = g;
		vertices[5 + 6 * p] = b;
	}

	return vertices;
}

