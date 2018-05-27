#include <array>
#include <iostream>
#include <string>
#include <algorithm>



constexpr std::string_view INPUT_MAP = (
	#include "State.txt"
);

constexpr int NumberOfRows(const std::string_view& map, size_t index = 0)
{
	return map.find('\n', index) == map.npos ? 0 : 1 + NumberOfRows(map, map.find('\n', index) + 1);
}

constexpr int NumberOfRows()
{
	return NumberOfRows(INPUT_MAP) - 2;
}

constexpr int NumberOfCols()
{
	return static_cast<int>(INPUT_MAP.find('\n', 1) - 1);
}

constexpr int NumberOfElems()
{
	return NumberOfRows() * NumberOfCols();
}

constexpr auto Parse_Input()
{
	std::array<int, NumberOfElems()> output = {};

	auto input = &INPUT_MAP[0];
	auto oRef = &output[0];

	while (*input != 'E')
	{
		if ((input[0]) != '\n') {
			*oRef = *input == '+' ? 1 : 0;
			oRef += 1;
		}
		input += 1;
	}

	return output;
}


constexpr auto GameOfLife(std::array<int, NumberOfElems()> input)
{
	std::array<int, NumberOfElems()> output = {};
	constexpr auto rows = NumberOfRows();
	constexpr auto cols = NumberOfCols();

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			int count = 0;
			int currPos = i * cols + j;
			if (i == 0)
			{
				if (j == 0)
				{
					count = input[currPos + 1] + input[currPos + cols] + input[currPos + cols + 1];
				}
				else if (j == cols - 1)
				{
					count = input[currPos - 1] + input[currPos + cols - 1] + input[currPos + cols];
				}
				else
				{
					count = input[currPos - 1] + input[currPos + 1] + input[currPos + cols - 1] + input[currPos + cols] + input[currPos + cols + 1];
				}
			}
			else if (i == rows - 1)
			{
				if (j == 0)
				{
					count = input[currPos - cols] + input[currPos - cols + 1] + input[currPos + 1];
				}
				else if (j == cols - 1)
				{
					count = input[currPos - cols - 1] + input[currPos - cols] + input[currPos - 1];
				}
				else
				{
					count = input[currPos - cols - 1] + input[currPos - cols] + input[currPos - cols + 1] + input[currPos - 1] + input[currPos + 1];
				}
			}
			else
			{
				if (j == 0)
				{
					count = input[currPos - cols] + input[currPos - cols + 1] + input[currPos + 1] + input[currPos + cols] + input[currPos + cols + 1];
				}
				else if (j == cols - 1)
				{
					count = input[currPos - cols - 1] + input[currPos - cols] + input[currPos - 1] + input[currPos + cols - 1] + input[currPos + cols];
				}
				else
				{
					count = input[currPos - cols - 1] + input[currPos - cols] + input[currPos - cols + 1] + input[currPos - 1] + input[currPos + 1] + input[currPos + cols - 1] + input[currPos + cols] + input[currPos + cols + 1];
				}
			}

			output[i*cols + j] = input[i*cols + j];
			if (input[i*cols + j] == 1) {
				if (count < 2 || count > 3) {
					output[currPos] = 0;
				}
			}
			else {
				if (count == 3) {
					output[currPos] = 1;
				}
			}
		}
	}

	return output;
}


constexpr auto Serialize(std::array<int, NumberOfElems()> input)
{
	constexpr auto siz = NumberOfElems() + NumberOfRows() - 1;
	constexpr auto cols = NumberOfCols();
	std::array<char, siz> output = {};

	int col = 0;
	int j = 0;
	for (int i = 0; i < siz; ++i)
	{
		if (col == cols) {
			output[i] = '\n';
			col = 0;
		}
		else {
			output[i] = input[j] == 1 ? '+' : ' ';
			j += 1;
			col += 1;
		}
	}

	return output;
}


constexpr auto Play()
{
	constexpr auto output = Parse_Input();
	constexpr auto output2 = GameOfLife(output);
	constexpr auto output3 = Serialize(output2);

	return output3;
}


int main()
{
	for (auto& elem : Play()) {
		std::cout << elem;
	}
	std::cout << "\n";
	return 0;
}