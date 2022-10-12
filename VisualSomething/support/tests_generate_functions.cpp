#include "tests_generate_functions.h"
#include <iostream>
#include <math.h>

float alpha(float p, float delta) {
	return 1.0f - expf(-p * delta);
}

// distribution length function: exp(x / a) * (sin(x) + b)
float distribution(float x, int a, int b){
	return expf(x / a) * (sinf(x) + 1.0f) / b;
}

std::vector<jd::vec4> generateData_DIAG(jd::Mat3D<jd::Voxel>& data, float len)
{
	if (data.GetNumDepth() != 2){
		std::cerr << "ERROR: dimension error in: " << __LINE__ << ", at file: " << __FILE__ << std::endl;
		return {};
	}
	
	using namespace jd;

	const int xdim = data.GetNumRows();
	const int ydim = data.GetNumColumns();
	const int zdim = data.GetNumDepth();

	std::vector<vec4> colors(2);
	colors[0] = vec4{ 0.0f, 1.0f, 0.0f, 0.2f }; // Green color
	colors[1] = vec4{ 1.0f, 0.0f, 0.0f, 0.2f }; // Red color

	const float step = len / static_cast<float>(xdim);
	float firstSlice = 0.0f;
	float secondSlice = len;
	for (int i = 0; i < xdim; i++)
	{
		for (int j = 0; j < ydim; j++)
		{
			for (int k = 0; k < zdim; k++)
			{
				data.At(k, i, j).sDepth = k == 0 ? firstSlice : secondSlice;
				data.At(k, i, j).iLayer = k;
			}
		}
		
		firstSlice += step;
		secondSlice -= step;
	}

	return colors;
}

std::vector<jd::vec4> generateData_PARAL(jd::Mat3D<jd::Voxel>& data, float len)
{
	if (data.GetNumDepth() > 5){
		std::cerr << "ERROR: dimension error in: " << __LINE__ << ", at file: " << __FILE__ << std::endl;
		return {};
	}
	
	using namespace jd;

	const int xdim = data.GetNumRows();
	const int ydim = data.GetNumColumns();
	const int zdim = data.GetNumDepth();

	std::vector<vec4> colors(5);
	colors[0] = vec4 { 0.0f, 1.0f, 0.0f, 1.0f / static_cast<float>(zdim) }; // Green color
	colors[1] = vec4 { 1.0f, 0.0f, 0.0f, 1.0f / static_cast<float>(zdim) }; // Red color
	colors[2] = vec4 { 1.0f, 0.657f, 0.0f, 1.0f / static_cast<float>(zdim) }; // orange color
	colors[3] = vec4 { 0.09f, 0.639f, 0.992f, 1.0f / static_cast<float>(zdim) }; // blue color
	colors[4] = vec4 { 0.815f, 0.301f, 0.855f, 1.0f / static_cast<float>(zdim) }; // dark pink color

	for (int k = 0; k < zdim; k++)
	{
		for (int j = 0; j < ydim; j++)
		{
			for (int i = 0; i < xdim; i++)
			{
				data.At(k,  i,  j).iLayer = k;
				data.At(k,  i,  j).sDepth = len / static_cast<float>(zdim);
			}
		}
	}

	return colors;
}
