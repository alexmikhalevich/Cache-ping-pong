#include <thread>
#include <chrono>
#include <vector>
#include <assert.h>
#include <cstring>

class CTest {
	private:
		static const int m_iterations = 1000000;
		static void Task(unsigned short pos, std::vector<unsigned int>& data) {
			assert(pos < data.size());
			for(int i = 0; i < m_iterations; ++i) data[pos]++;
		}
		static double GetTaskTime(unsigned short dst) {
			std::chrono::time_point<std::chrono::system_clock> start, end;
			start = std::chrono::system_clock::now();

			const size_t threads_num = std::thread::hardware_concurrency();
			std::vector<std::thread> threads;
			std::vector<unsigned int> data(dst * threads_num, 0);
			for(unsigned short i = 0; i < threads_num; ++i) 
				threads.emplace_back(Task, i * dst, std::ref(data));
			for(std::thread& t : threads) t.join();

			end = std::chrono::system_clock::now();
			std::chrono::duration<double> elapsed_seconds = end - start;
			return elapsed_seconds.count();
		}
	public:
		static double get_avg_time(unsigned short dst) {
			const short num_of_probes = 20;
			double time_sum = 0;
			for(int i = 0; i < num_of_probes; ++i)
				time_sum += CTest::GetTaskTime(dst);
			return time_sum / num_of_probes;
		}
};
