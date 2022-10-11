#pragma once
#include <string>

class Shader
{
public:
    // Конструктор считывает данные и выполняет построение шейдера
	Shader();
    Shader(const char* const& vertexPath, const char* const& fragmentPath);
 
    // Создание шейдера
    bool makeShader(const char* const& vertexPath, const char* const& fragmentPath);
    // Использование/активация шейдера
    void use();
    // Получить ID
    unsigned int getID() const;
 
    // Полезные uniform-функции
    void setBool(const std::string &name, bool value) const;  
    void setInt(const std::string &name, int value) const;   
    void setFloat(const std::string &name, float value) const;
    
private:
    static bool checkCompileErrors(unsigned int shader, const std::string& type);
    // ID - идентификатор программы
    unsigned int ID;
};
  
