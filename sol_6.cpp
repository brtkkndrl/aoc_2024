#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>

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
	// Guard is in a loop if he returns to the path he was on
	// Every time you cross a path he was on, check if on obstacle can be placed to return to that path
	// The path taken should be extended to the closest obstacles in both ways
	/*
		#		#
		|		UP
		^	->	UP
		.		UP
		#		#
	*/
	
	std::vector<std::vector<char>> matrix;

	constexpr char DIR_FLAGS[] = {0b00000001, 0b00000010, 0b00000100, 0b00001000};

	static_assert((('#' & 0b11110000) != 0) && (('.' & 0b11110000) != 0),
	"Flag combinations collide with other markings!");

	auto guard_pos = read_input(matrix);
	int gx, gy;
	gx = guard_pos.first;
	gy = guard_pos.second;

	const int dirs[][2] = {{0,-1}, {1,0}, {0,1}, {-1,0}};//UP RIGHT DOWN LEFT
	int dir_index = 0;

	int width = matrix[0].size();
	int height = matrix.size();

	int possible_obstacles = 0;

	std::vector<std::pair<int,int>> new_obs;

	bool searching = true;
	while(searching){
		int next_dir = (dir_index+1)%4;
		int opposite_dir = (dir_index+2)%4;

		

		int next_x = gx + dirs[dir_index][0];
		int next_y = gy + dirs[dir_index][1];

		bool is_next_pos_valid = (next_x >= 0 && next_x < width && next_y >= 0 && next_y < height);

		if(matrix[gy][gx] == '.' || matrix[gy][gx] == '^'){// mark path for the first time
			matrix[gy][gx] = DIR_FLAGS[dir_index];
		}else if(matrix[gy][gx] & DIR_FLAGS[next_dir]){ // can loop
			//crossing path, check for possible loop
			if(is_next_pos_valid && matrix[next_y][next_x] == '.'){
				possible_obstacles++;

				//std::cout<<"\n"<<((matrix[gy][gx] & DIR_FLAGS[0]) > 0)<<" "<<
								//((matrix[gy][gx] & DIR_FLAGS[1]) > 0)<<" "<<
								//((matrix[gy][gx] & DIR_FLAGS[2]) > 0)<<" "<<
								//((matrix[gy][gx] & DIR_FLAGS[3]) > 0)<<" ";

				//std::cout<<"\nobstacle #"<<new_obs.size()<<" val: "<<(int)matrix[gy][gx]<<" , dirs: "<<dir_index<<" "<<next_dir;

				new_obs.push_back({next_x, next_y});
			}
		}
		matrix[gy][gx] |= DIR_FLAGS[dir_index];

		if(!is_next_pos_valid){
			searching = false;
			break;
		}

		if(matrix[next_y][next_x] == '#'){//obstacle change dir

			//fully mark entire availible space in the row/column
			int ox = gx;
			int oy = gy;
			while(true){
				ox += dirs[opposite_dir][0];
				oy += dirs[opposite_dir][1];
				
				if(ox < 0 || ox >= width || oy < 0 || oy >= height)
					break;

				if(matrix[oy][ox] == '#')
					break;

				if(matrix[oy][ox] == '.')//first marking, reset
					matrix[oy][ox] = 0;

				matrix[oy][ox] |= DIR_FLAGS[dir_index];//mark direction
			}

			dir_index = next_dir;//change dir
		}else{
			gx = next_x;
			gy = next_y;
		}
	}


	for(auto &row : matrix){
		for(auto &c : row){
			if(c != '.' && c != '#'){
				c = '.';
			}
		}
	}

	//for(auto pos : new_obs){
		//matrix[pos.second][pos.first] = 'O';
	//}

//	for(const auto& pos : new_obs){
		//std::cout<<'\n';
		//matrix[pos.second][pos.first] = 'O';
		//for(const auto &row : matrix){
			//std::string str(row.begin(), row.end());
			//std::cout<<str<<'\n';
		//}
		//matrix[pos.second][pos.first] = '.';
		//std::cout<<'\n';
	//}

	return possible_obstacles;
}
