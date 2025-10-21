#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <map>
#include <set>

/// @brief
/// @param matrix_out
/// @return map of antena type -> vector of positions
std::map<char, std::vector<std::pair<int, int>>> read_input(std::vector<std::vector<char>> &matrix_out)
{
	std::map<char, std::vector<std::pair<int, int>>> antenas;

	matrix_out.clear();
	std::string line;

	int y = 0;

	while (std::getline(std::cin, line))
	{
		if (line.empty())
		{
			break;
		}

		std::vector<char> row(line.begin(), line.end());
		matrix_out.push_back(row);

		for (int x = 0; x < (int)row.size(); x++)
		{
			if (row[x] == '.')
				continue;

			antenas[row[x]].push_back({x, y});
		}

		y++;
	}

	return antenas;
}

void print_matrix(const std::vector<std::vector<char>> &matrix)
{
	std::cout << "\n";
	for (auto row : matrix)
	{
		std::string row_str(row.begin(), row.end());
		std::cout << row_str << "\n";
	}
	std::cout << "\n";
}

/// @brief
///	for each antenta type a vector of their positions
///	compare every pair of antenas of the same type, calculate vector between them, check if it is valid pos in
///	positive and negative direction, if yes, save the position
/// return unique positions count
/// @return
int part_one()
{
	std::vector<std::vector<char>> matrix;
	auto antenas = read_input(matrix);
	std::set<int> antinodes_positions;

	int width = matrix[0].size();
	int height = matrix.size();

	auto pos_to_index = [width](int x, int y)
	{
		return x + y * width;
	};

	auto is_pos_valid = [width, height](int x, int y)
	{
		return x >= 0 && x < width && y >= 0 && y < height;
	};

	for (auto const &[antena_type, pos] : antenas)
	{
		if (pos.size() < 2)
			continue;

		for (int i = 0; i < pos.size(); i++)
		{
			for (int j = i + 1; j < pos.size(); j++)
			{
				int dx = pos[j].first - pos[i].first;
				int dy = pos[j].second - pos[i].second;

				// possible antinodes positions
				int ax = pos[i].first - dx;
				int ay = pos[i].second - dy;

				int bx = pos[i].first + dx * 2;
				int by = pos[i].second + dy * 2;

				if (is_pos_valid(ax, ay))
				{
					antinodes_positions.insert(pos_to_index(ax, ay));
				}
				if (is_pos_valid(bx, by))
				{
					antinodes_positions.insert(pos_to_index(bx, by));
				}
			}
		}
	}

	return antinodes_positions.size();
}

int part_two()
{
	std::vector<std::vector<char>> matrix;
	auto antenas = read_input(matrix);
	std::set<int> antinodes_positions;

	int width = matrix[0].size();
	int height = matrix.size();

	auto pos_to_index = [width](int x, int y)
	{
		return x + y * width;
	};

	auto is_pos_valid = [width, height](int x, int y)
	{
		return x >= 0 && x < width && y >= 0 && y < height;
	};

	for (auto const &[antena_type, pos] : antenas)
	{
		if (pos.size() < 2)
			continue;

		for (int i = 0; i < pos.size(); i++)
		{
			for (int j = i + 1; j < pos.size(); j++)
			{
				int dx = pos[j].first - pos[i].first;
				int dy = pos[j].second - pos[i].second;

				// possible antinodes positions
				int ax = pos[i].first;
				int ay = pos[i].second;

				int bx = pos[j].first;
				int by = pos[j].second;

				while (is_pos_valid(ax, ay))
				{
					antinodes_positions.insert(pos_to_index(ax, ay));
					ax -= dx;
					ay -= dy;
				}
				while (is_pos_valid(bx, by))
				{
					antinodes_positions.insert(pos_to_index(bx, by));
					bx += dx;
					by += dy;
				}
			}
		}
	}

	return antinodes_positions.size();
}
