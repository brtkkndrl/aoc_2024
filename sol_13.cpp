#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
#include <set>
#include <list>
#include <unordered_map>
#include <cmath>

std::pair<int, int> read_line(bool button){
    std::string word;
    char c;
    int n1 = 0;
    int n2 = 0;

    std::cin >> word;
    if(button){
        std::cin>>word;
    }
    std::cin >> c >> c;
    std::cin >> n1;
    std::cin >> word;
    std::cin >>c>>c;
    std::cin >> n2;
    
    return std::make_pair(n1, n2);
}


int part_one()
{
	std::string line;

	int safe_count = 0;

    int total_credit = 0;

    while(std::cin.good() && !std::cin.eof()){
        const auto btn_a = read_line(true);
        const auto btn_b = read_line(true);
        const auto prize = read_line(false);

        if(std::cin.fail()){ // didn't read input
            break;
        }

        float press_a = (prize.second*btn_b.first - prize.first*btn_b.second)/
        (float)(btn_b.first*btn_a.second - btn_a.first*btn_b.second);
   
        float press_b=(prize.second-press_a*btn_a.second) / btn_b.second;

        if(press_a != std::floor(press_a) || press_b != std::floor(press_b)){//no result
            continue;
        }

        total_credit += press_a*3 + press_b;
    }

    return total_credit;
}

int part_two()
{
    return 0;
}




