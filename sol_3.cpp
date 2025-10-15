#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <cctype>
#include <algorithm>

int part_one(){
	char c;
	std::vector<char> word_mul;//tries to keep "mul("
	std::vector<char> word_args; // "num,num)"

	bool reading_mul = true;

	int sum = 0;

	while(std::cin >> c){
		if(reading_mul){
			word_mul.push_back(c);

			if(word_mul.size() > 4){
				word_mul.erase(word_mul.begin());
			}

			std::string word_mul_str(word_mul.begin(), word_mul.end());
			if(word_mul_str == "mul("){
				reading_mul = false;
				word_args.clear();
			}
		}else{
			word_args.push_back(c);
			if (word_args.size() >= 4){
				std::string ending(word_args.end() - 4, word_args.end());
				if(ending == "mul("){
					word_args.clear();
					continue;
				}
			}

			if(c == ')'){
				word_mul.clear();
				reading_mul = true;
				
				std::string args_str(word_args.begin(), word_args.end()-1);
					
				auto comma_pos = args_str.find(',');

				if(comma_pos == std::string::npos)
					continue;

				std::string arg_left(word_args.begin(), word_args.begin() + comma_pos);
				std::string arg_right(word_args.begin() + comma_pos + 1, word_args.end()-1);

				if(arg_left.empty() || arg_right.empty())
					continue;

				if(!std::all_of(arg_left.begin(), arg_left.end(), ::isdigit))
					continue;

				if(!std::all_of(arg_right.begin(), arg_right.end(), ::isdigit))
					continue;
				
				sum += std::stoi(arg_left) * std::stoi(arg_right);

			}
		}

	}
	return sum;
}

int part_two(){
	char c;
	std::vector<char> word_mul;//tries to keep "mul("
	std::vector<char> word_args; // "num,num)"

	std::vector<char> word_cond; //"do()" or "don't()"

	bool conditional = true;

	bool reading_mul = true;

	int sum = 0;

	while(std::cin >> c){
		word_cond.push_back(c);
		if(word_cond.size() > 7){
			word_cond.erase(word_cond.begin());
		}
		std::string dont_str(word_cond.begin(), word_cond.end());
		std::string do_str(word_cond.end()-4, word_cond.end());

		if(do_str == "do()")
			conditional = true;
		else if(dont_str == "don't()")
			conditional = false;
		

		if(reading_mul){
			word_mul.push_back(c);

			if(word_mul.size() > 4){
				word_mul.erase(word_mul.begin());
			}

			std::string word_mul_str(word_mul.begin(), word_mul.end());
			if(word_mul_str == "mul("){
				reading_mul = false;
				word_args.clear();
			}
		}else{
			word_args.push_back(c);
			if (word_args.size() >= 4){
				std::string ending(word_args.end() - 4, word_args.end());
				if(ending == "mul("){
					word_args.clear();
					continue;
				}
			}

			if(c == ')'){
				word_mul.clear();
				reading_mul = true;
				
				if(!conditional)
					continue;

				std::string args_str(word_args.begin(), word_args.end()-1);
					
				auto comma_pos = args_str.find(',');

				if(comma_pos == std::string::npos)
					continue;

				std::string arg_left(word_args.begin(), word_args.begin() + comma_pos);
				std::string arg_right(word_args.begin() + comma_pos + 1, word_args.end()-1);

				if(arg_left.empty() || arg_right.empty())
					continue;

				if(!std::all_of(arg_left.begin(), arg_left.end(), ::isdigit))
					continue;

				if(!std::all_of(arg_right.begin(), arg_right.end(), ::isdigit))
					continue;
				
				sum += std::stoi(arg_left) * std::stoi(arg_right);

			}
		}

	}
	return sum;
}
