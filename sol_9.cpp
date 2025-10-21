#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

int part_one()
{
	std::vector<int> disk_layout; // -1 for free space, else file id

	char c, next_c;
	int occupied_blocks, free_blocks;
	int file_id = 0;
	while (std::cin >> c)
	{
		occupied_blocks = c - '0';

		std::cin >> next_c;

		if (std::cin.eof()) // last line
		{
			free_blocks = 0;
		}
		else
		{
			free_blocks = next_c - '0';
		}

		disk_layout.insert(disk_layout.end(), occupied_blocks, file_id);
		disk_layout.insert(disk_layout.end(), free_blocks, -1);

		if (std::cin.eof())
		{
			break;
		}

		file_id++;
	}

	auto put_it = disk_layout.begin();
	auto take_it = disk_layout.end() - 1;

	while (put_it < take_it)
	{
		while (put_it < take_it && *put_it >= 0)
		{
			put_it++;
		}
		while (put_it < take_it && *take_it < 0)
		{
			take_it--;
		}

		std::swap(*put_it, *take_it);
	}

	long long checksum = 0;

	for (int i = 0; i < disk_layout.size(); i++)
	{
		if (disk_layout[i] < 0)
			break;

		checksum += disk_layout[i] * i;
	}

	std::cout << "\nHad to use long long, the aswer is: " << checksum << "\n";

	return checksum;
}

int part_two()
{
	return 0;
}
