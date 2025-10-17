#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <vector>
#include <utility>
#include <set>

std::set<std::pair<int, int>> read_rules(){
    std::string line;

    std::set<std::pair<int, int>> rules;

    char separator;

	while(std::getline(std::cin, line)){
		if(line.empty()){
			break;
		}

        std::istringstream ss(line);
        int n1, n2;
        ss >> n1;
        ss >> separator;
        ss >> n2;

        rules.insert({n1, n2});
    }

    return rules;
}

int part_one(){
    std::string line;

    auto rules = read_rules();

    int sum = 0;

    while(std::getline(std::cin, line)){
            char separator;
            int n;
            std::istringstream ss(line);

            std::vector<int> updates;

            while(ss >> n){
                updates.push_back(n);
                ss >> separator;
            }
            
            bool valid = true;

            for(int i = 0; i < (int)updates.size(); i++){
                for(int j = i+1; j < (int)updates.size(); j++){
                    if(rules.count({updates[j], updates[i]})){
                        valid = false;
                        break;
                    }
                }
                if(!valid)
                    break;
            }

            if(valid)
                sum += updates[updates.size()/2];
    }

	return sum;
}

int part_two(){
	 std::string line;

    auto rules = read_rules();

    int sum = 0;

    while(std::getline(std::cin, line)){
            char separator;
            int n;
            std::istringstream ss(line);

            std::vector<int> updates;

            while(ss >> n){
                updates.push_back(n);
                ss >> separator;
            }
            
            bool valid = true;

            for(int i = 0; i < (int)updates.size(); i++){
                for(int j = i+1; j < (int)updates.size(); j++){
                    if(rules.count({updates[j], updates[i]})){
                        valid = false;
                        std::swap(updates[j], updates[i]);
                    }
                }
            }

            if(!valid)
                sum += updates[updates.size()/2];
    }

	return sum;
}
