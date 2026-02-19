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
#include <cstdint>


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

std::pair<int, int> compute_presses(const std::pair<int64_t, int64_t>& btn_a,
 const std::pair<int64_t, int64_t>& btn_b, const std::pair<long, long>& prize){

    int64_t press_a = (prize.second*btn_b.first - prize.first*btn_b.second)/(btn_b.first*btn_a.second - btn_a.first*btn_b.second);
   
    int64_t press_b=(prize.second-press_a*btn_a.second) / btn_b.second;

    const auto actual_res = std::make_pair(press_a*btn_a.first + press_b*btn_b.first,press_a*btn_a.second + press_b*btn_b.second);

    if(actual_res.first != prize.first || actual_res.second != prize.second){//no result
        return std::make_pair(0,0);
    }
    
    return std::make_pair(press_a, press_b);
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

        const auto presses = compute_presses(btn_a, btn_b, prize);

        total_credit += presses.first*3 + presses.second;
    }

    return total_credit;
}

int part_two()
{
	std::string line;

	int safe_count = 0;

    int64_t total_credit = 0;

    while(std::cin.good() && !std::cin.eof()){
        const auto btn_a = read_line(true);
        const auto btn_b = read_line(true);
        const auto prize = read_line(false);        

        const int64_t offset = 10000000000000LL;

        const std::pair<int64_t, int64_t> prize_updated = std::make_pair(prize.first + offset, prize.second + offset);


        if(std::cin.fail()){ // didn't read input
            break;
        }

        const auto presses = compute_presses(btn_a, btn_b, prize_updated);

        std::cout<<presses.first<<" "<<presses.second<<"\n";

        total_credit += presses.first*3 + presses.second;
    }

    std::cout<<"|"<<total_credit<<"|\n";

    return total_credit;
}




