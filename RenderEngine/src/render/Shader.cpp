#include "Shader.h"

#include <glad/glad.h> // подключаем glad для активации всех заголовочных файлов OpenGL
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader() : ID(0) {}

Shader::Shader(const char* const& vertexPath, const char* const& fragmentPath){
	makeShader(vertexPath, fragmentPath);
}

bool Shader::makeShader(const char* const& vertexPath, const char* const& fragmentPath)
{
	// Этап №1: Получение исходного кода вершинного/фрагментного шейдера из переменной filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// Убеждаемся, что объекты ifstream могут выбросить исключение
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;

		// Считываем содержимое файловых буферов в потоки 
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Закрываем файлы
		vShaderFile.close();
		fShaderFile.close();

		// Конвертируем данные из потока в строковые переменные
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	} 
	catch (const std::ifstream::failure& e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		return false;
	}

	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();

	// Этап №2: Компилируем шейдеры
	unsigned int vertex, fragment;

	// Вершинный шейдер
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	if (!checkCompileErrors(vertex, "VERTEX")){
		return false;
	}

	// Фрагментный шейдер
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	if (!checkCompileErrors(fragment, "FRAGMENT")){
		return false;
	}

	// Шейдерная программа
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	if (!checkCompileErrors(ID, "PROGRAM")){
		return false;
	}

	// После того, как мы связали шейдеры с нашей программой, удаляем их, так как они нам больше не нужны
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	
	return true;
}
 
void Shader::use(){
	glUseProgram(ID);
}
    
unsigned int Shader::getID() const{
	return ID;
}
 
// TODO: написать обобщенную функцию, возможно, с множеством переменных
void Shader::setBool(const std::string &name, bool value) const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), static_cast<int>(value));
}

void Shader::setInt(const std::string &name, int value) const{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setFloat(const std::string &name, float value) const{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

bool Shader::checkCompileErrors(unsigned int shader, const std::string& type)
{
	int success;
	char infoLog[1024];
	
	if (type == "VERTEX" || type == "FRAGMENT")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: " << type
					<< "\n" << infoLog
					<< "\n -- --------------------------------------------------- -- "
					<< std::endl;
			
			return false;
		}
	} 
	else if (type == "PROGRAM")
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: " << type
					<< "\n" << infoLog
					<< "\n -- --------------------------------------------------- -- "
					<< std::endl;
			
			return false;
		}
	}
	
	return true;
}


