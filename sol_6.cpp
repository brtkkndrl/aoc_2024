#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

std::pair<int, int> read_input(std::vector<std::vector<char>>& matrix_out){
	matrix_out.clear();
	std::string line;

	int guard_x, guard_y;
	guard_x = 0;
	guard_y = 0;

	int row_index = 0;

	while(std::getline(std::cin, line)){
		if(line.empty()){
			break;
		}

		std::vector<char> row (line.begin(), line.end());
		matrix_out.push_back(row);

		auto index = line.find('^');

    	if (index != std::string::npos){
			guard_y = row_index;
			guard_x = (int)index;
		}

		row_index++;
	}

	return {guard_x, guard_y};
}

int part_one(){
	std::vector<std::vector<char>> matrix;

	auto guard_pos = read_input(matrix);
	int gx, gy;
	gx = guard_pos.first;
	gy = guard_pos.second;

	int dirs[][2] = {{0,-1}, {1,0}, {0,1}, {-1,0}};
	int dir_index = 0;

	int width = matrix[0].size();
	int height = matrix.size();

	int unique_steps = 0;

	bool walking = true;
	while(walking){
		if(matrix[gy][gx] != 'X'){
			unique_steps++;
			matrix[gy][gx] = 'X';
		}

		gx += dirs[dir_index][0];
		gy += dirs[dir_index][1];

		if(gx < 0 || gx >= width || gy < 0 || gy >= height){
			walking = false;
			break;
		}

		if(matrix[gy][gx] == '#'){//obstacle change dir
			gx -= dirs[dir_index][0];
			gy -= dirs[dir_index][1];

			dir_index = dir_index == 3 ? 0 : dir_index+1;
		}
	}

	return unique_steps;
}

int part_two(){
	std::vector<std::vector<char>> matrix;

	auto guard_pos = read_input(matrix);
	int gx, gy;
	gx = guard_pos.first;
	gy = guard_pos.second;

	int dirs[][2] = {{0,-1}, {1,0}, {0,1}, {-1,0}};
	int dir_index = 0;

	int width = matrix[0].size();
	int height = matrix.size();

	int possible_obstacles = 0;

	bool searching = true;
	while(searching){
		if(matrix[gy][gx] != 'X'){
			unique_steps++;
			matrix[gy][gx] = 'X';
		}

		gx += dirs[dir_index][0];
		gy += dirs[dir_index][1];

		if(gx < 0 || gx >= width || gy < 0 || gy >= height){
			searching = false;
			break;
		}

		if(matrix[gy][gx] == '#'){//obstacle change dir
			gx -= dirs[dir_index][0];
			gy -= dirs[dir_index][1];

			dir_index = dir_index == 3 ? 0 : dir_index+1;
		}
	}

	return possible_obstacles;
}
