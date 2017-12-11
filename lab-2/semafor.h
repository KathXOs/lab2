#pragma once
#include <mutex> 
#include <utility> 
#include <iostream> 
using namespace std;

class Semafor {
	int clock; // ���������� ����������� �������� 
	int count; // ����� ��������� ���� ��� ������� 
	mutex mutex; // ������� ��� ������ count �� �������������� ������� 

public:
	Semafor(int x) { // �������� �������� 
		clock = 0; // ��������� �������� �������� 
		count = x; // ������� ������������� ����� ������� 
	};

	pair<int, int> Enter() { // ����� ����� � ������� 
		while (true) { // ���� �������� ���������� ����� 

					   // ������� ����������� ������ 
			lock_guard<std::mutex> lock(mutex);

			if (count != 0) { // ���� ���� ��������� ����� 
							  // ������ �����, ��������� �������� 
							  // ������� ��������� � ���� ���� 
				return make_pair(clock++, --count);
			}
		}
	}

	pair<int, int> Leave() { // ����� ������ �� �������� 

							 // ������� ����������� ������ 
		lock_guard<std::mutex> lock(mutex);

		// ���������� �����, ��������� �������� 
		// ������� ��������� � ���� ���� 
		return std::make_pair(clock++, ++count);
	}
};