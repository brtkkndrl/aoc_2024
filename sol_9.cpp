#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <list>

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

	return 0;
}

int part_two()
{
	std::list<std::pair<int, int>> disk_layout; // file_id, (-1 is free space), number of blocks

	char c;
	int file_id = 0;

	auto print_disk = [&disk_layout]()
	{
		for (const auto p : disk_layout)
		{
			if (p.first >= 0)
			{
				for (int i = 0; i < p.second; i++)
					std::cout << p.first;
			}
			else
			{
				for (int i = 0; i < p.second; i++)
					std::cout << '.';
			}
		}
		std::cout << std::endl;
	};

	while (std::cin >> c)
	{
		int occupied_blocks = c - '0';

		disk_layout.push_back({file_id, occupied_blocks});

		std::cin >> c;

		if (std::cin.eof()) // last line
		{
			break;
		}

		int free_blocks = c - '0';

		disk_layout.push_back({-1, free_blocks});

		file_id++;
	}

	auto file_iter = std::prev(disk_layout.end());

	while (file_iter != disk_layout.begin())
	{
		if ((*file_iter).first < 0)
		{
			file_iter--;
			continue;
		}

		auto free_iter = disk_layout.begin();

		while (free_iter != file_iter)
		{
			if ((*free_iter).first == -1 && (*free_iter).second >= (*file_iter).second)
			{
				int diff = (*free_iter).second - (*file_iter).second;
				*free_iter = (*file_iter); // move file

				if (diff > 0) // some space left
				{
					disk_layout.insert(std::next(free_iter), {-1, diff}); // innsert remaining space
				}
				(*file_iter).first = -1; // remove old file

				break;
			}
			free_iter++;
		}

		file_iter--;
	}

	long long checksum = 0;
	int index = 0;

	for (const auto &blocks : disk_layout)
	{
		if (blocks.first < 0)
		{
			index += blocks.second;
			continue;
		}

		for (int i = 0; i < blocks.second; i++)
		{
			checksum += blocks.first * index;
			index++;
		}
	}

	std::cout << "\nHad to use long long, the aswer is: " << checksum << "\n";

	return 0;
}
