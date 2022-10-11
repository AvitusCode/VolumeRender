#pragma once
#include "../math/vec4.h"
#include "Shader.h"

struct GLFWwindow;

class WinRender
{
public:
	/* Функция инициализации окна
	 * @param[in]: длина окна, ширина окна, заголовок окна, вершинный шейдер, фрагментный шейдер (для простоты на данном этапе только по одной паре шейдеров)
	 * @param[out]: true - Инициализация успешна, false - в противном случае
	 * */
	bool init(unsigned width, unsigned height, const char* const& title, const char* const& vertexPath, const char* const& fragmentPath);
	bool windowShouldClose() const;
	void pollEvents() const;
	void processInput() const;
	/* Отрисовываем пиксель на экране
	 * @param[in]: цвет пикселя, координаты, ширина и высота
	 * */
	void putPixel(const jd::vec4& color, int x, int y, int width = 1, int height = 1) const;
	void useRender();
	void flush(float r, float g, float b, float a);
	void flush(const jd::vec4& color);
	void shutdown();
	GLFWwindow* getWindow();
	
	int getWidth() const;
	int getHeight() const;

private:
	GLFWwindow* window;
	int displayW;
	int displayH;
	
	unsigned VAO, VBO;
	Shader shader;
};
