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
#include <unordered_set>
#include <map>


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


long stone_count_dp(long stone_val, int blinks){
	static std::map<std::pair<long,long>, long> prev_results; //stone,blinks -> count

	if(prev_results.count({stone_val, blinks})){
		std::cout<<"<cached "<<stone_val<<","<<blinks<<">";
		return prev_results[{stone_val, blinks}];
	}

	std::list<long> stones = {stone_val};
	long rest_sum = 0;
	for (int blink = 0; blink < blinks; blink++)
	{
		blink_stones(stones);
		for(auto it = stones.begin(); it != stones.end();){//TODO also update prev results
			if(prev_results.count({*it, blinks-blink-1})){
				rest_sum += prev_results[{*it, blinks-blink-1}];
				std::cout<<"<cached2 "<<*it<<","<<blinks-blink-1<<">";
				it = stones.erase(it);
			}else{
				++it;
			}
		}
	}

	prev_results[{stone_val, blinks}] = stones.size() + rest_sum;
	return stones.size() + rest_sum;
}

int part_two()
{
	std::list<long> stones;

	long x;
	while (std::cin >> x)
	{
		stones.push_back(x);
	}

	constexpr int N_BLINKS = 75;

	std::unordered_set<long> seen_stones;//likely only 54 are unique at most...
	std::vector<std::pair<int,int>> to_expand;
	for (int blink = 0; blink < N_BLINKS; blink++)
	{
		for(auto it = stones.begin(); it != stones.end();){
			if(seen_stones.count(*it)){
				to_expand.push_back(std::make_pair(*it, N_BLINKS-blink));
				it = stones.erase(it);
			}else{
				seen_stones.insert(*it);
				++it;
			}
		}

		for(const auto &stone : stones){
			seen_stones.insert(stone);
			//std::cout<<stone<<" ";
		}
		//std::cout<<"\n";
		blink_stones(stones);
	}

	std::reverse(to_expand.begin(), to_expand.end());

	std::cout<<"to expand: \n";
	for(const auto& p : to_expand){
		std::cout<<p.first<<"^"<<p.second<<" ";
	}
	std::cout<<"\n";

	long rest_sum = 0;
	//for(const auto& p : to_expand){
		//rest_sum += stone_count_dp(p.first, p.second);
	//}

	return stones.size() + rest_sum; 
}
