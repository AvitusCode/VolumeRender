#pragma once
#include <chrono>
#include <iostream>
#include <string>

/*
 * 
 * Простой профайлер для замера времени работы программы в целом и отдельных блоков в частности
 * 
 * Использование:
 * Обернуть нужный блок программы в фигурные скобочки, в самом начале вызвать процедуру LOG_DURATION(<ВАШЕ НАЗВАНИЕ ТЕСТА>)
 * 
 * {
 *     LOG_DURATION(<ВАШЕ НАЗВАНИЕ ТЕСТА>)
 *     ...
 * }
 * 
 * */

class Profiler
{
public:
	explicit Profiler(const std::string& msg = "") : 
		message(msg + ": "),
		time(std::chrono::steady_clock::now()) {};

	~Profiler()
	{
		auto finish = std::chrono::steady_clock::now();
		auto duration = finish - time;
		std::cerr << message
			<< std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
			<< " ms" << std::endl;
	}

private:
	std::string message;
	std::chrono::steady_clock::time_point time;
};

#define UNIQ_ID_IMPL(lineo) _a_local_var_##lineo
#define UNIQ_ID(lineo) UNIQ_ID_IMPL(lineo)

#define LOG_DURATION(message) \
    Profiler UNIQ_ID(__LINE__){message};
