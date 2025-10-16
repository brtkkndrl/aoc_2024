#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

int part_one(){
	std::vector<std::vector<char>> matrix;

	std::string line;

	int total_count = 0;

	while(std::getline(std::cin, line)){
		if(line.empty()){
			break;
		}

		std::vector<char> row (line.begin(), line.end());
		matrix.push_back(row);
	}

	int width = matrix[0].size();
	int height = matrix.size();

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
	return 0;
}
