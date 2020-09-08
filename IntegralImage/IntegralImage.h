#pragma once
#include <vector>
using namespace std;
/*
{
{0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,0,1,1,0,0,0,0,0},
{0,0,0,0,0,1,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,1,0,0,1,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0}}

{
{0,0,0,0,0,1,1,1,1,1,1,1,1,1},
{0,0,0,0,0,1,1,1,1,1,1,1,1,1},
{0,0,0,1,1,2,2,3,4,4,4,4,4,4},
{0,0,0,1,1,3,3,4,5,5,5,5,5,5},
{0,0,0,1,1,3,3,4,5,5,5,5,5,5},
{0,0,0,2,2,4,5,6,7,7,7,7,7,7},
{0,0,0,2,2,4,5,6,7,7,7,7,7,7},
{0,0,0,2,2,4,5,6,7,7,7,7,7,7}}

Summe in Bereich =
letztes Feld in Bereich -
letztes Feld über Bereich -
letztes Feld links von Bereich +
letztes Feld diagonal vor Bereich
(wurde zweimal abgezogen)
*/
class IntegralImage {
public:
	struct Point { int row, col; };
	void create(vector<vector<int>> arr) {
		image = arr;
		int rows = image.size(), columns = image[0].size();
		for (int row = 0; row < rows; ++row)
			for (int column = 0; column < columns; ++column) {
				if (row) image[row][column] += image[row - 1][column];
				if (column) image[row][column] += image[row][column - 1];
				if (row && column) image[row][column] -= image[row - 1][column - 1];
			}
	}
	int get_sum(Point top_left, Point bottom_right) {
		int sum = image[bottom_right.row][bottom_right.col];
		if (top_left.row) sum -= image[top_left.row - 1][bottom_right.col];
		if (top_left.col) sum -= image[bottom_right.row][top_left.col - 1];
		if (top_left.row && top_left.col) sum += image[top_left.row - 1][top_left.col - 1];
		return sum;
	}
private:
	vector<vector<int>> image;
};