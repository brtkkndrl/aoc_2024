#include <iostream>
#include <set>
#include <map>

int part_one(){
	std::multiset<int> sorted_left, sorted_right;

	int left, right;
	while(std::cin >> left >> right){
		sorted_left.insert(left);
		sorted_right.insert(right);	
	}

	auto it_left = sorted_left.begin();
	auto it_right = sorted_right.begin();

	int total_diff = 0;

	while(it_left != sorted_left.end() && it_right != sorted_right.end()){
		int diff_abs = *it_left - *it_right; 
		diff_abs = diff_abs < 0 ? -diff_abs : diff_abs;

		total_diff += diff_abs;	

		it_left++;
		it_right++;
	}
	

	return total_diff;
}

int part_two(){
	std::multiset<int> sorted_left;
	std::map<int, int> right_count;

	int left, right;
	while(std::cin >> left >> right){
		sorted_left.insert(left);
		if (right_count.find(right) == right_count.end()){
			right_count[right] = 1;
		}else{
			right_count[right]++;
		}
	}

	int sim_score = 0;

	for(auto num_left : sorted_left){
		int times = (right_count.find(num_left) == right_count.end()) ? 0 : right_count[num_left];
		sim_score += num_left * times;
	}

	return sim_score;
}
