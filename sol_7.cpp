#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

int part_one(){
	std::string line;

    long long total_sum = 0;

	while(std::getline(std::cin, line)){
		if(line.empty()){
			break;
		}
        
		std::istringstream ss(line);

        long long target_result;
        ss >> target_result;

        ss.get();//:

        std::vector<int> numbers;
        int n;
        while(ss >> n){
            numbers.push_back(n);
        }

        std::vector<char> operators(numbers.size()-1, '+');

        while(true){
            long long temp_result = numbers[0];
            for(int i = 0; i < operators.size(); i++){
                if(operators[i] == '+')
                    temp_result += (long long)numbers[i+1];
                else if(operators[i] == '*')
                    temp_result *= (long long)numbers[i+1];
            }
            if(temp_result == target_result){
                total_sum += target_result;
                break;
            }

            int index = 0;
            while(index < operators.size() && operators[index] == '*'){
                operators[index] = '+';
                index++;
            }
            
            if(index == operators.size())//final combination
                break;

            operators[index] = '*';
        }
	}

    std::cout<<"\nHad to use long long, this is the result: "<<total_sum<<"\n";

	return 0;
}

int part_two(){
	std::string line;

    long long total_sum = 0;

	while(std::getline(std::cin, line)){
		if(line.empty()){
			break;
		}
        
		std::istringstream ss(line);

        long long target_result;
        ss >> target_result;

        ss.get();//:

        std::vector<int> numbers;
        int n;
        while(ss >> n){
            numbers.push_back(n);
        }

        constexpr int OP_ADD = 0;
        constexpr int OP_MUL = 1;
        constexpr int OP_CONCAT = 2;

        std::vector<int> operators(numbers.size()-1, OP_ADD);

        while(true){
            long long temp_result = numbers[0];
            for(int i = 0; i < operators.size(); i++){
                if(operators[i] == OP_ADD)
                    temp_result += (long long)numbers[i+1];
                else if(operators[i] == OP_MUL)
                    temp_result *= (long long)numbers[i+1];
                else{
                    std::stringstream temp_ss;
                    temp_ss<<temp_result<<numbers[i+1];
                    temp_ss>>temp_result;
                }
            }
            if(temp_result == target_result){
                total_sum += target_result;
                break;
            }

            int index = 0;
            while(index < operators.size() && operators[index] == OP_CONCAT){
                operators[index] = OP_ADD;
                index++;
            }
            
            if(index == operators.size())//final combination
                break;

            operators[index]++;
        }
	}

    std::cout<<"\nHad to use long long, this is the result: "<<total_sum<<"\n";

	return 0;
}
