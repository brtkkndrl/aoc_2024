#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

int read_input(std::vector<std::vector<char>>& matrix_out){
	matrix_out.clear();
	std::string line;

	while(std::getline(std::cin, line)){
		if(line.empty()){
			break;
		}

		std::vector<char> row (line.begin(), line.end());
		matrix_out.push_back(row);
	}

	int width = matrix_out[0].size();
	return width;
}

int part_one(){
	std::vector<std::vector<char>> matrix;

	int width = read_input(matrix);
	int height = width;

	int total_count = 0;

	constexpr int N = 6;
 	std::vector<char> buffers[N];

	for(int i = 0; i < height; i++){
		for(int b = 0; b < N; b++){
			buffers[b].clear();
		}

		for(int j = 0; j < width; j++){	
			
			buffers[0].push_back(matrix[j][i]);//horizontal
			buffers[1].push_back(matrix[i][j]);//vertical
			if(j + i < width){
				buffers[2].push_back(matrix[j][j+i]);//diagonal
				buffers[3].push_back(matrix[j][width-1-i-j]);//diagonal
				if(i != 0){
					buffers[4].push_back(matrix[j+i][j]);//diagonal
					buffers[5].push_back(matrix[j+i][width-1-j]);//diagonal
				}
			}else{
				buffers[2].clear();
				buffers[3].clear();
				buffers[4].clear();
				buffers[5].clear();
			}


			for(int b = 0; b < N; b++){
				if(buffers[b].size() > 4)//"XMAS"
					buffers[b].erase(buffers[b].begin());
			}
			
			for(int b = 0; b < N; b++){
				std::string buffer_str(buffers[b].begin(), buffers[b].end());
				if(buffer_str == "XMAS" || buffer_str == "SAMX"){
					total_count++;
				}
			}

		}
	}

	return total_count;
}

int part_two(){
	std::vector<std::vector<char>> matrix;
	int width = read_input(matrix);

	int total_count = 0;

	for(int i = 0; i < width-2; i++){
		for(int j = 0; j < width-2; j++){
			int cx = i+1;
			int cy = j+1;

			if(matrix[cy][cx] != 'A')// center A
				continue;

			char left_top = matrix[cy-1][cx-1];
			char right_top = matrix[cy-1][cx+1];
			char left_bottom = matrix[cy+1][cx-1];
			char right_bottom = matrix[cy+1][cx+1];

			//diagonal 1
			if (!((left_top == 'M' && right_bottom == 'S') || (left_top == 'S' && right_bottom == 'M')))
				continue;

			//diagonal 25
			if (!((left_bottom == 'M' && right_top == 'S') || (left_bottom == 'S' && right_top == 'M')))
				continue;

			total_count++;
		}
	}


	return total_count;
}
