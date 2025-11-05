#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <list>
#include <thread>

void blink_stones_pt1(std::list<long> &stones)
{
	for (auto it = stones.begin(); it != stones.end(); it++)
	{
		if (*it == 0)
		{
			*it = 1;
			continue;
		}

		auto const stone_str = std::to_string(*it);
		auto const len = stone_str.size();

		if (len % 2 == 0)
		{
			*it = std::stoi(stone_str.substr(0, len / 2));
			it = stones.insert(std::next(it), std::stoi(stone_str.substr(len / 2, len / 2)));
			continue;
		}

		*it = (*it) * 2024;
	}
}

void blink_stones_pt2(std::list<long> &stones)
{
	for (auto it = stones.begin(); it != stones.end(); it++)
	{
		if (*it == 0)
		{
			*it = 1;
			continue;
		}

		auto const stone_str = std::to_string(*it);
		auto const len = stone_str.size();

		if (len % 2 == 0)
		{
			*it = std::stoi(stone_str.substr(0, len / 2));
			it = stones.insert(std::next(it), std::stoi(stone_str.substr(len / 2, len / 2)));
			continue;
		}

		*it = (*it) * 2024;
	}
}

void split_stones(const std::list<long> &stones, std::vector<std::list<long>> &thread_stones, int num_threads)
{
	int thread_size = stones.size() / num_threads;
	int remaininig = stones.size() % num_threads;

	auto stone_it = stones.begin();

	for (int i = 0; i < num_threads; i++)
	{
		for (int j = 0; j < thread_size; j++)
		{
			thread_stones[i].push_back(*(stone_it++));
		}
		if (i >= num_threads - remaininig)
		{ // start adding remaining at some point for semi uniform distribution
			thread_stones[i].push_back(*(stone_it++));
		}
	}
}

int part_one()
{
	std::list<long> stones;

	long x;
	while (std::cin >> x)
	{
		stones.push_back(x);
	}

	for (int blink = 0; blink < 25; blink++)
	{
		blink_stones_pt1(stones);
	}

	return stones.size();
}

/// @brief
/*
	There exists a function how_many(stone_value: int, blinks: int) -> int
	That determines into how many stones will a stone multiply into given it base value
	For value 0
	blink	|	stones
	0		|	0
	1		|	1
	2		|	2024
	3		|	20 24
	4		|	2 0 2 4			// here 0 will follow pattern recursively
	5		|	4048 1 4048 9096
	6		|	40 48 40 48 90 96	+	zero_rec x 1
	7		|	4 4 8 4 4 8 9 9 6	+ 	zero_rec x 4

	how_many(0, B) = if B >= 4: how_many(2, B-4)*2 + how_many(4, B-4) + how_many(0, B-4)

	1,2,3,4 all follow:

	2024 | 4048 | 6072 | 9096
	...
	rec(4) + rec(0) + rec(2) x 2| rec(4) * 2 + 8 + rec(0) | 6 7 rec(2) + rec(0) | 9 9 6 + rec(0)
	*/
/// @return
int part_two()
{
	std::list<long> stones;

	long x;
	while (std::cin >> x)
	{
		stones.push_back(x);
	}

	int num_threads = std::thread::hardware_concurrency();
	num_threads = num_threads > 0 ? num_threads : 4;

	int blinks = 0;

	constexpr int BLINKS_TARGET = 25;

	for (; blinks < BLINKS_TARGET; blinks++)
	{
		if (stones.size() >= num_threads * 2)
		{ // split into threads when at least 2 stones per thread
			break;
		}

		blink_stones_pt2(stones);
	}

	if (blinks >= BLINKS_TARGET)
	{
		return stones.size();
	}

	std::vector<std::list<long>> thread_stones(num_threads);

	split_stones(stones, thread_stones, num_threads);

	std::vector<std::thread> threads;
	for (int t_id = 0; t_id < num_threads; t_id++)
	{
		threads.emplace_back([&, blinks, t_id]()
							 {
			for(int b = blinks; b < BLINKS_TARGET; b++){
				blink_stones_pt2(thread_stones[t_id]);
				//std::cout<<b<<" ";
			} });
	}

	for (auto &t : threads)
		t.join();

	long long size_sum = 0;

	for (const auto &t_stones : thread_stones)
	{
		size_sum += t_stones.size();
	}

	std::cout << "The result in case it overflows: " << size_sum << "\n";

	return size_sum;
}
