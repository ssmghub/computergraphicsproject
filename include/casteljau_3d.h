#include <list>
#include <vector>
#include <algorithm>

#include "point.h"

//The function returns a dummy point so that it will compile
point evaluate(float t, std::list<point> P)
{
	std::list<point> Q = P;
	while (Q.size() > 1)
	{
		std::list<point> R; //initialised empty list R

		std::list<point>::iterator p1;
		std::list<point>::iterator p2;

		for (p1 = Q.begin(), p2 = Q.begin(), ++p2; p2 != Q.end(); ++p1, ++p2)
		{
			point point1 = *p1;
			point point2 = *p2;
			point p = ((1 - t) * (point1)) + (t * (point2));
			R.push_back(p);
		}
		Q.clear();
		Q = R;
	}
	return Q.front();
}

std::vector<point> EvaluateBezierCurve(std::vector<point>ctrl_points, int num_evaluations)
{
	float offset = 1.0 / num_evaluations; //how many evalution?

	std::list<point> ps(ctrl_points.begin(), ctrl_points.end()); //copies the vector of control points argument to a list
	std::vector<point> curve; //initialised empty curve

	curve.push_back(ctrl_points.front()); //add the first point on the curve


	for (int evalu = 0; evalu < num_evaluations; evalu++)
	{

		point p = evaluate(offset * (evalu + 1), ps); //call function to get the point

		curve.push_back(p);
	}

	return curve; //return the points on the curve
}

//The function returns NULL so that it will compile
float* MakeFloatsFromVector(std::vector<point> curve, int& num_verts, int& num_floats, float r, float g, float b, float rl, float tb, float fb)
{
	num_verts = curve.size();
	if (num_verts == 0)
	{
		return NULL;
	}

	// 9 float for each vertex (position, colour, normal)
	num_floats = num_verts * 9;

	float* vertices = (float*)malloc(sizeof(float) * num_floats); //allocate memory for the vertex attributes

	for (int p = 0; p < num_verts; p++)
	{
		//specify vertex position using p
		vertices[0 + 9 * p] = curve[p].x;
		vertices[1 + 9 * p] = curve[p].y;
		vertices[2 + 9 * p] = curve[p].z;
		//specify vertex colour using r, g, b
		vertices[3 + 9 * p] = r;
		vertices[4 + 9 * p] = g;
		vertices[5 + 9 * p] = b;
		//specify vertex normal using  rl,  tb,  fb
		vertices[6 + 9 * p] = rl;
		vertices[7 + 9 * p] = tb;
		vertices[8 + 9 * p] = fb;
	}

	return vertices;
}
