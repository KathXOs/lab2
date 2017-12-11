#pragma once
#include <mutex> 
#include <utility> 
#include <iostream> 
using namespace std;

class Semafor {
	int clock; // Количество выполненных операций 
	int count; // Число свободных мест для потоков 
	mutex mutex; // Мьютекс для защиты count от одновременного доступа 

public:
	Semafor(int x) { // Создание семафора 
		clock = 0; // Обнуление счетчика операций 
		count = x; // Задание максимального числа потоков 
	};

	pair<int, int> Enter() { // Метод входа в семафор 
		while (true) { // Цикл ожидания свободного места 

					   // Создать критическую секцию 
			lock_guard<std::mutex> lock(mutex);

			if (count != 0) { // Если есть свободное место 
							  // Занять место, посчитать операцию 
							  // Вернуть состояние в виде пары 
				return make_pair(clock++, --count);
			}
		}
	}

	pair<int, int> Leave() { // Метод выхода из семафора 

							 // Создать критическую секцию 
		lock_guard<std::mutex> lock(mutex);

		// Освободить место, посчитать операцию 
		// Вернуть состояние в виде пары 
		return std::make_pair(clock++, ++count);
	}
};