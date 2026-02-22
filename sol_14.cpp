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


void print_grid(const std::vector<std::vector<char>>& grid, const int width, const int height){
    std::cout<<"\n";
    for(int y = 0; y < height; y++){
        std::string row_string(grid[y].begin(), grid[y].end());
        std::cout<<row_string<<"\n";
    }
}

void update_grid(std::vector<std::vector<char>>& grid, const bool clear, const std::vector<robot_t>& robots, const int width, const int height){
    if(clear){
        for(const auto& robot : robots){
            grid[robot.py][robot.px] = '.';
        }
        return;
    }


    for(const auto& robot : robots){
        const char curr = grid[robot.py][robot.px];
        if(curr == '.'){
            grid[robot.py][robot.px] = '1';
        }else if(curr == '9'){
            grid[robot.py][robot.px] = 'A';
        }else if(curr >= '1' && curr <= '9'){
            char c = curr + 1;
            grid[robot.py][robot.px] = c;
        }
    }
}

int grid_score(const std::vector<std::vector<char>>& grid, const int width, const int height){
    bool in_row = false;
    int row_size = 0;

    std::vector<bool> has_row(height);

    for(int y = 0; y < height; y++){
        has_row[y] = false;
        for(int x =0; x < width; x++){
            if(grid[y][x] == '.'){
                if(in_row){
                    in_row = false;
                    if(row_size >= 3){
                        has_row[y] = true;
                    }
                    row_size = 0;
                }
            }else{
                in_row = true;
                row_size++;
            }
        }
    }

    bool in_col = false;
    int col_size = 0;
    int max_col = 0;
    for(int y = 0; y < height; y++){
        if(has_row[y]){
            in_col = true;
            col_size++;
        }else{
            if(in_col){
                in_col = false;
                if(col_size > max_col){
                    max_col = col_size;
                }
                col_size = 0;
            }
        }
    }

    return max_col;
}

int part_two()
{
    constexpr int MAX_STEPS = 10000;
    constexpr int WIDTH = 101;
    constexpr int HEIGHT = 103;
    std::vector<robot_t> robots;
    std::pair<int, int> readPos, readVel;

    while(read_line(readPos, readVel)){
        robots.push_back({px: readPos.first, py: readPos.second, vx: readVel.first, vy: readVel.second});
    }

    std::vector<std::vector<char>> grid(HEIGHT, std::vector<char>(WIDTH, '.'));

    for(int second = 0; second < MAX_STEPS; second++){
        update_grid(grid, true, robots, WIDTH, HEIGHT);
        for(auto& robot : robots){
            robot.px = (robot.px + robot.vx)%WIDTH;
            robot.py = (robot.py + robot.vy)%HEIGHT;

            if(robot.px < 0)
                robot.px += WIDTH;
            if(robot.py < 0)
                robot.py += HEIGHT;
        }
        update_grid(grid, false, robots, WIDTH, HEIGHT);
        
        const auto score = grid_score(grid, WIDTH, HEIGHT);
        if(score > 7){
            print_grid(grid, WIDTH, HEIGHT);
            std::cout<<"step: "<< second+1<<" score: "<< score <<"\n";
            return second+1;
        }
    }
    
    return 0;
}
