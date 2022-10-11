#include <iostream>
#include <cmath>
#include "Voxel.h"
#include "math/vec4.h"
#include "Mat3D.h"
#include "support/tests_generate_functions.h"

#include "render/WinRender.h"

using namespace jd;

/// <summary>
/// Print data in Mat3D Voxels 
/// </summary>
void printData(const Mat3D<Voxel>& data)
{
	const size_t xdim = data.GetNumRows();
	const size_t ydim = data.GetNumColumns();
	const size_t depth = data.GetNumDepth();

	for (size_t k = 0; k < depth; k++)
	{
		std::cout << "Slice "<< k << ": " << std::endl;
		const auto& slice = data.GetSlice(k);

		for (size_t i = 0; i < xdim; i++)
		{
			for (size_t j = 0; j < ydim; j++)
			{
				std::cout << "[" << slice[i][j].iLayer << ", " << slice[i][j].sDepth << "] ";
			}
			
			std::cout << std::endl;
		}
	}
}

void printOneColor(const Mat2D<vec4>& colorMatrix, size_t i, size_t j){
	std::cout << "(" << colorMatrix.At(i, j).x_ << ", " << colorMatrix.At(i, j).y_ << ", " << colorMatrix.At(i, j).z_ << ", " << colorMatrix.At(i, j).w_<<  ")" << std::endl;
}

/// <summary>
/// Test color integer
/// </summary>
Mat2D<vec4> testSum(const Mat3D<Voxel>& data, const std::vector<vec4>& colors)
{
	const size_t xdim = data.GetNumRows();
	const size_t ydim = data.GetNumColumns();
	const size_t depth = data.GetNumDepth();
	
	// Матрица с посчитанными цветами
	Mat2D<vec4> colorRes(xdim, ydim); 
	
	for (size_t i = 0; i < xdim; i++)
	{
		for (size_t j = 0; j < ydim; j++)
		{
			// vec4 color - будет содержать конечный цвет пикселя после суммирования
			vec4 color = vec4 { 0.0f, 0.0f, 0.0f, 1.0f };
			// значение для A_{0} и накопитель произведений
			float Am = 1.0f - colors[data.At(0, i, j).iLayer].w_;
			float accumulator = 1.0f;

			for (size_t m = 0; m < depth; m++)
			{
				// Получаем номер слоя
				const size_t indexOfLayer = data.At(m, i, j).iLayer;
				// Equation (4)
				// Получаем 1-alpha в нужной степени
				const float ONE_MINUS_ALPHA = powf(1.0f - colors[indexOfLayer].w_, data.At(m, i, j).sDepth);

				// Equation (3)
				// Основаня формула суммирования
				// w_ - четвертая компонента вектора, отвечающая параметру альфа 
				color += (colors[indexOfLayer] * Am * ((1.0f - ONE_MINUS_ALPHA) / colors[indexOfLayer].w_));
				// Equation (2)
				// получаем следующий A_{m+1}
				accumulator = ONE_MINUS_ALPHA == 0.0f ? accumulator :  accumulator * ONE_MINUS_ALPHA;
				Am = accumulator * (1.0f - colors[data.At((m + 1) % depth, i, j).iLayer].w_); 
			}

			// Проверяем, что компоненты вектора не больше ед., и добавляем в результат в 2d матрицу пикселей
			colorRes.At(i, j) = color.correct();
		}
	}

	return colorRes;
}

int main(void)
{
	// Константы
	const unsigned int SCR_WIDTH = 1280;
	const unsigned int SCR_HEIGHT = 720;
	const int PIXEL_WIDTH = 3;
	const int PIXEL_HEIGHT = 3;
	const float LEN = 16.0f; // длина всего объема в глубину

	Mat3D<Voxel> mat3d(2, 128, 128);
	std::vector<vec4> colors = generateData_DIAG(mat3d, LEN);
	Mat2D<vec4> colorMatrix = testSum(mat3d, colors);

	// printOneColor(colorMatrix, 1, 0);
	
	WinRender render;
	if (!render.init(SCR_WIDTH, SCR_HEIGHT, "3D volume render", "vertex.vert", "fragment.frag")){
		return -1;
	}
	
	// Смещения
	int XOFFSET = (render.getWidth()  - colorMatrix.GetNumRows() * PIXEL_WIDTH) / 2;
	int YOFFSET = (render.getHeight() - colorMatrix.GetNumColumns() * PIXEL_HEIGHT) / 2;
	
	while (!render.windowShouldClose())
	{
		render.pollEvents();
		render.processInput();
		
		for (size_t i = 0; i < colorMatrix.GetNumRows(); i++)
		{
			for (size_t j = 0; j < colorMatrix.GetNumColumns(); j++){
				render.putPixel(colorMatrix.At(colorMatrix.GetNumRows() - i - 1, colorMatrix.GetNumColumns() - j - 1),
						j +  PIXEL_WIDTH* j + XOFFSET, i + PIXEL_HEIGHT * i + YOFFSET, PIXEL_WIDTH + 1, PIXEL_HEIGHT + 1);
			}
		}
		
		render.flush(1.0f, 1.0f, 1.0f, 1.0f);
		XOFFSET = (render.getWidth()  - colorMatrix.GetNumRows() * PIXEL_WIDTH) / 2;
		YOFFSET = (render.getHeight() - colorMatrix.GetNumColumns() * PIXEL_HEIGHT) / 2;
	}
	
	render.shutdown();
    return 0;
}
