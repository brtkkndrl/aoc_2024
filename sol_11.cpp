#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <list>
#include <unordered_map>

void blink_stones_2(std::list<long> &stones)
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


void blink_stones(std::list<long> &stones)
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
		blink_stones(stones);
	}

	return stones.size();
}


// TODO use dynamic programming
/// @brief
/*
	blink	|	stones
	0		|	0
	1		|	1
	2		|	2024
	3		|	20 24
	4		|	2 0 2 4			// here 0 will follow pattern recursively, aslo 2 is present twice, no need to expand both
	
	// remove 0 and 2 from the stones, save them as add them later
	0 todo (N_STEPS-4), 2 todo (N_STEPS-4)
	
	5		|	4048 9096
	6		|	40 48 90 96
	7		|	4 0 4 8 9 0 9 6 

	// save duplicates (N_STEPS-7)

	0, 4, 0, 9

	8		|	4 8 9 6



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

	for (int blink = 0; blink < 7; blink++)
	{
		blink_stones_2(stones);
	}

	return stones.size();
}
