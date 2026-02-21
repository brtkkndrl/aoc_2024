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
#include <map>


bool read_line(std::pair<int, int>& outPos, std::pair<int,int>& outVel){
    if(std::cin.eof()){
        return false;
    }
    
    std::string word;
    char c;
    int n1 = 0;
    int n2 = 0;

    std::cin >> c >> c >> n1 >> c >> n2; //p=X,Y
    outPos = std::make_pair(n1, n2);
    
    std::cin >> c >> c >> n1 >> c >> n2; //v=X,Y
    outVel = std::make_pair(n1, n2);

    return std::cin.good();
}

struct robot_t{
    int px, py, vx, vy;
};

void print_grid(const std::vector<robot_t>& robots, const int widht, const int height){
    std::cout<<"\n";
    for(int y = 0; y < height; y++){
        for(int x = 0; x < widht; x++){
            int n = 0;
            for(const auto& robot : robots){
                if(robot.px == x && robot.py == y)
                    n++;
            }
            if(n > 0 && n < 10){
                char c = '0' + n;
                std::cout<<c;
            }else if(n >= 10){
                std::cout<<'A';
            }
            else{
                std::cout<<".";
            }
        }
        std::cout<<"\n";
    }
}

int part_one()
{
    constexpr int WIDTH = 101;
    constexpr int HEIGHT = 103;
    std::vector<robot_t> robots;
    std::pair<int, int> readPos, readVel;

    while(read_line(readPos, readVel)){
        robots.push_back({px: readPos.first, py: readPos.second, vx: readVel.first, vy: readVel.second});
    }

    for(int second = 0; second < 100; second++){
        for(auto& robot : robots){
            robot.px = (robot.px + robot.vx)%WIDTH;
            robot.py = (robot.py + robot.vy)%HEIGHT;

            if(robot.px < 0)
                robot.px += WIDTH;
            if(robot.py < 0)
                robot.py += HEIGHT;
        }
    }
    
    int q1, q2, q3, q4;
    q1 = q2 = q3 = q4 = 0;

    for(const auto& robot : robots){
        if(robot.px < WIDTH/2 && robot.py < HEIGHT/2)
            q1++;
        else if(robot.px > WIDTH/2 && robot.py < HEIGHT/2)
            q2++;
        else if(robot.px > WIDTH/2 && robot.py > HEIGHT/2)
            q3++;
        else if(robot.px < WIDTH/2 && robot.py > HEIGHT/2)
            q4++;
    }

    return q1*q2*q3*q4;
}

int part_two()
{
    constexpr int WIDTH = 101;
    constexpr int HEIGHT = 103;
    std::vector<robot_t> robots;
    std::pair<int, int> readPos, readVel;

    while(read_line(readPos, readVel)){
        robots.push_back({px: readPos.first, py: readPos.second, vx: readVel.first, vy: readVel.second});
    }

    for(int second = 0; second < 100; second++){
        for(auto& robot : robots){
            robot.px = (robot.px + robot.vx)%WIDTH;
            robot.py = (robot.py + robot.vy)%HEIGHT;

            if(robot.px < 0)
                robot.px += WIDTH;
            if(robot.py < 0)
                robot.py += HEIGHT;
        }
    }
    
    //TODO check christmass tree
    //    11
    //   1111 
    //  111111  
    // 11111111

    int q1, q2, q3, q4;
    q1 = q2 = q3 = q4 = 0;

    for(const auto& robot : robots){
        if(robot.px < WIDTH/2 && robot.py < HEIGHT/2)
            q1++;
        else if(robot.px > WIDTH/2 && robot.py < HEIGHT/2)
            q2++;
        else if(robot.px > WIDTH/2 && robot.py > HEIGHT/2)
            q3++;
        else if(robot.px < WIDTH/2 && robot.py > HEIGHT/2)
            q4++;
    }

    return q1*q2*q3*q4;
}




