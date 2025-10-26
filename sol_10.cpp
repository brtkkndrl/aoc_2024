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

	auto is_pos_valid = [width, height](int x, int y)
	{
		return x >= 0 && x < width && y >= 0 && y < height;
	};

	const int DIRS[][2] = {{0,-1}, {1,0}, {0,1}, {-1,0}};

	int score_sum = 0;

	for(const auto &trailhead : trailheads){
		std::stack<std::pair<int,int>> frontier;
		frontier.push(trailhead);

		std::set<std::pair<int, int>> peaks;

		while(!frontier.empty()){
			const auto curr_node = frontier.top();
			frontier.pop();

			for(const auto &dir : DIRS){
				int next_x = curr_node.first + dir[0];
				int next_y = curr_node.second + dir[1];
				
				if(!is_pos_valid(next_x, next_y))
					continue;

				if(matrix[next_y][next_x] != matrix[curr_node.second][curr_node.first] + 1)
					continue;
				
				if(matrix[next_y][next_x] == 9){
					peaks.insert({next_x, next_y});
					continue;
				}

				frontier.push({next_x, next_y});
			}
		}

		score_sum += peaks.size();
	}

	return score_sum;
}

int part_two(){
		std::vector<std::vector<char>> matrix;
	std::vector<std::pair<int,int>> trailheads;

	read_input(matrix, trailheads);

	int width = matrix[0].size();
	int height = matrix.size();

	auto is_pos_valid = [width, height](int x, int y)
	{
		return x >= 0 && x < width && y >= 0 && y < height;
	};

	const int DIRS[][2] = {{0,-1}, {1,0}, {0,1}, {-1,0}};

	int score_sum = 0;

	for(const auto &trailhead : trailheads){
		std::stack<std::pair<int,int>> frontier;
		frontier.push(trailhead);

		while(!frontier.empty()){
			const auto curr_node = frontier.top();
			frontier.pop();

			for(const auto &dir : DIRS){
				int next_x = curr_node.first + dir[0];
				int next_y = curr_node.second + dir[1];
				
				if(!is_pos_valid(next_x, next_y))
					continue;

				if(matrix[next_y][next_x] != matrix[curr_node.second][curr_node.first] + 1)
					continue;
				
				if(matrix[next_y][next_x] == 9){
					score_sum++;
					continue;
				}

				frontier.push({next_x, next_y});
			}
		}

	}

	return score_sum;
}
