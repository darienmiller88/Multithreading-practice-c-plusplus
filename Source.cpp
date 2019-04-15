#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

void findMax(const vector<int> &nums, int &max) {
	max = nums[0];
	for (const auto &elem : nums)
		if (elem > max)
			max = elem;
}

void findMin(const vector<int> &nums, int &min) {
	min = nums[0];
	for (const auto &elem : nums)
		if (elem < min)
			min = elem;
}

int random(int min, long int max) {
	random_device seed;
	default_random_engine rnGen(seed());
	uniform_int_distribution<int> dist(min, max);

	return dist(rnGen);
}

void hello() {
	cout << "hello" << endl;
}

int main() {
	const long long int SIZE = 9000000L;
	vector<int> nums(SIZE * 2);
	int max = 0, min = 0;
	
	srand(time(0));
	for (size_t i = 0; i < SIZE * 2; i++){
		nums[i] = rand() % SIZE;
	}

	thread t1(findMin, ref(nums), ref(min));
	thread t2(findMax, ref(nums), ref(max));
	
	auto start = chrono::system_clock::now();
	
	t1.join();
	t2.join();
	
	auto end = chrono::system_clock::now();


	//min max time
	auto s1 = chrono::system_clock::now();

	auto result = minmax_element(nums.begin(), nums.end());

	auto e2 = chrono::system_clock::now();

	//single thread time
	auto s2 = chrono::system_clock::now();
	
	findMax(nums, max);
	findMin(nums, min);

	auto e3 = chrono::system_clock::now();
	
	
	chrono::duration<double> time = (end - start);
	chrono::duration<double> time2 = (e2 - s1);
	chrono::duration<double> time3 = (e3 - s2);

	//cout << "biggest number in nums: " << max << " and smallest: " << min << endl;
	cout << "time taken for threads: " << time.count() << " seconds" << endl;
	cout << "time taken for minmax: " << time2.count() << " seconds" << endl;
	cout << "time taken for single thread: " << time3.count() << " seconds" << endl;
}
