#include <iostream>
#include <tuple>
#include <future>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include "semafor.h"
using namespace::std;

int main()
{
	int limit = 100;
	int threads = 4000;

	vector<string> logs(2 * threads);
	vector<future<void>> handles(threads);

	auto func = [limit, &logs]() {
		static Semafor semafor(limit);
		int clock, count;

		tie(clock, count) = semafor.Enter();
		stringstream buffer;
		buffer << (limit - count) << '/' << limit << " Ч†¬ход в семафор\n";
		logs[clock] = buffer.str();

		tie(clock, count) = semafor.Leave();
		buffer.str("");
		buffer << (limit - count) << '/' << limit << " Ч†¬ыход из семафора\n";
		logs[clock] = buffer.str();
	};

	for (int i = 0; i < threads; ++i)
		handles[i] = async(launch::async, func);

	for (int i = 0; i < threads; ++i)
		handles[i].wait();

	for (int i = 0; i < 2 * threads; ++i)
		clog << logs[i];
}
