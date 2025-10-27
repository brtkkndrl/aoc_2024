#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <list>

int part_one(){
	std::list<long> stones;

	long x;
	while(std::cin >> x){
		stones.push_back(x);
	}

	for(int blink = 0; blink < 25; blink++){

		for(auto it = stones.begin(); it != stones.end(); it++){
			if(*it == 0){
				*it = 1;
				continue;
			}

			auto const stone_str = std::to_string(*it);
			auto const len = stone_str.size();

			if(len % 2 == 0){
				*it = std::stoi(stone_str.substr(0, len/2));
				it++;//insert behind
				it = stones.insert(it, std::stoi(stone_str.substr(len/2, len/2)));
				continue;
			}

			*it = (*it) * 2024;
		}

	}

	return stones.size();
}

int part_two(){
	std::list<long> stones;

	long x;
	while(std::cin >> x){
		stones.push_back(x);
	}

	for(int blink = 0; blink < 40; blink++){

		for(auto it = stones.begin(); it != stones.end(); it++){
			if(*it == 0){
				*it = 1;
				continue;
			}

			auto const stone_str = std::to_string(*it);
			auto const len = stone_str.size();

			if(len % 2 == 0){
				*it = std::stoi(stone_str.substr(0, len/2));
				it = stones.insert(std::next(it), std::stoi(stone_str.substr(len/2, len/2)));
				continue;
			}

			*it = (*it) * 2024;
		}

		std::cout<<blink<<" "<<stones.size()<<"\n";
	}

	return stones.size();
}
