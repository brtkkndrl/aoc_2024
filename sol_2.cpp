#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

int part_one(){
	std::string line;

	int safe_count = 0;

	while(std::getline(std::cin, line)){
		if(line.empty()){
			break;
		}

		std::istringstream ss(line);

		int prev, current;
		bool first_read = true;	
		int order = 0; // 1 increasing, -1 decreasing, 0 undefined
		int safe = true;

		while(ss >> current){
			if(!first_read){
				int diff = std::abs(current - prev);
				if(diff < 1 || diff > 3){
					safe = false;
					break;
				}

				int new_order = current > prev ? 1 : -1;
				if(order == 0){
					order = new_order;
				}else if(order != new_order){
					safe = false;
					break;
				}
			}

			prev = current;	
			first_read = false;
		}

		if(safe){
			safe_count++;
		}
	}

	return safe_count;
}

int part_two(){
	std::string line;

	int safe_count = 0;


	while(std::getline(std::cin, line)){
		if(line.empty()){
			break;
		}

		std::istringstream ss(line);

		std::vector<int> readings;
		int x;
		while(ss >> x){
			readings.push_back(x);
		}

		auto find_bad_reading = [](std::vector<int> readings, int erase_index = -1){//returns problematic index if found, else -1
			if(erase_index >= 0 && erase_index < (int)readings.size())
				readings.erase(readings.begin() + erase_index);
			
			if(readings.size() < 2)
				return -1;
			

			int first_diff = readings[1] - readings[0];

			for(size_t i = 0; i < readings.size() - 1; i++){
				size_t j = i + 1;
				
				int diff = readings[j] - readings[i];
				int diff_abs = std::abs(diff);

				if(diff_abs < 1 || diff_abs > 3)
					return (int)j;
				if((diff > 0) != (first_diff > 0))
					return (int)j;	
			}

			return -1;
		};

		bool safe = false;

		for(int i = -1; i < (int)readings.size(); i++){
			int bad_index = find_bad_reading(readings, i);
			if(bad_index < 0){
				safe = true;
				break;
			}
		}
		
		if(safe)
			safe_count++;
	}	

	return safe_count;
}
