#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>

void read_input(std::vector<std::vector<char>>& matrix_out, std::vector<std::pair<int,int>> &trailheads_out){
	matrix_out.clear();
	trailheads_out.clear();
	std::string line;

	int y = 0;

	while(std::getline(std::cin, line)){
		if(line.empty()){
			break;
		}

		std::vector<char> row (line.begin(), line.end());
		
		std::for_each(row.begin(), row.end(), [](auto &x){ x = x - '0'; });//convert to actual numbers

		for(int x = 0; x < row.size(); x++){
			if(row[x] == 0)
				trailheads_out.push_back({x,y});
		}

		matrix_out.push_back(row);

		y++;
	}
}

int part_one(){
	std::vector<std::vector<char>> matrix;
	std::vector<std::pair<int,int>> trailheads;

	read_input(matrix, trailheads);

	int width = matrix[0].size();
	int height = matrix.size();

	auto neighbours = [](std::pair<int,int> pos) {
        return std::vector<std::pair<int, int>>{
			std::make_pair(pos.first+1, pos.second),
			std::make_pair(pos.first-1, pos.second),
			std::make_pair(pos.first, pos.second+1),
			std::make_pair(pos.first, pos.second-1)};
    };

	auto is_pos_valid = [width, height](int x, int y)
	{
		return x >= 0 && x < width && y >= 0 && y < height;
	};

	int pointer = 0;
	int total_cost = 0;

    while(pointer < width*height){
        while(pointer < width*height && matrix[pointer / width][pointer % width] < 0){
            pointer += 1;
        }
        if(pointer >= width*height){
            break;
        }

		std::stack<std::pair<int,int>> stack;

        stack.push(std::make_pair(pointer % width, pointer/width));
        auto curr_plant = matrix[pointer / width][pointer % width];
        auto area = 0;
        auto perimeter = 0;

        while(!stack.empty()){
			auto curr_pos = stack.top();
			stack.pop();

            if(matrix[curr_pos.second][curr_pos.first] < 0){
                continue;
            }

            area += 1;
            matrix[curr_pos.second][curr_pos.first] = -curr_plant;

            for(const auto &n : neighbours(curr_pos)){
                if(!is_pos_valid(n.first, n.second)){
                    perimeter+=1;
                    continue;
                }
            
                if(matrix[n.second][n.first] != curr_plant && matrix[n.second][n.first] != -curr_plant){
                    perimeter+=1;
                    continue;
                }

                stack.push(n);
            }
        }

        total_cost += area*perimeter;
    }

	return total_cost;
}

int part_two(){
	return -1;
}
