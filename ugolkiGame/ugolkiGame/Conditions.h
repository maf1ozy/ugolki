#pragma once
#include <iostream>
using namespace std;

class Conditions
{
public:
	bool isOutOfBorders;
	int tempX, tempY, currentImaginaryCell;
	int tempColor;
	int clickOnFigure(int x, int y, int cell[8][8], int cell_imaginary[8][8]) {
		tempColor = cell[x][y];
		tempX = x;
		tempY = y;
		currentImaginaryCell = cell_imaginary[x][y];
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (cell[i][j] == 3) cell[i][j] = 2;
			}
		}
		if ((cell[x + 1][y] == 2) && (cell[x][y + 1] == 2) && (cell[x - 1][y] == 2) && (cell[x][y - 1] == 2)) {
			cell[x + 1][y] = 3;
			cell[x - 1][y] = 3;
			isOutOfBorders = outOfBottomBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y + 1] = 3;
			isOutOfBorders = outOfTopBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y - 1] = 3;
		}
		if ((cell[x + 1][y] == 2) && (cell[x][y + 1] == 2) && (cell[x - 1][y] == 2)) {
			cell[x + 1][y] = 3;
			cell[x - 1][y] = 3;
			isOutOfBorders = outOfBottomBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y + 1] = 3;
		}
		if ((cell[x + 1][y] == 2) && (cell[x][y + 1] == 2) && (cell[x][y - 1] == 2)) {
			cell[x + 1][y] = 3;
			isOutOfBorders = outOfBottomBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y + 1] = 3;
			isOutOfBorders = outOfTopBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y - 1] = 3;
		}
		if ((cell[x + 1][y] == 2) && (cell[x - 1][y] == 2) && (cell[x][y - 1] == 2)) {
			cell[x + 1][y] = 3;
			cell[x - 1][y] = 3;
			isOutOfBorders = outOfTopBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y - 1] = 3;
		}
		if ((cell[x][y + 1] == 2) && (cell[x - 1][y] == 2) && (cell[x][y - 1] == 2)) {
			cell[x - 1][y] = 3;
			isOutOfBorders = outOfBottomBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y + 1] = 3;
			isOutOfBorders = outOfTopBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y - 1] = 3;
		}
		if ((cell[x - 1][y] == 2) && (cell[x][y - 1] == 2)) {
			cell[x - 1][y] = 3;
			isOutOfBorders = outOfTopBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y - 1] = 3;
		}
		if ((cell[x - 1][y] == 2) && (cell[x + 1][y] == 2)) {
			cell[x - 1][y] = 3;
			cell[x + 1][y] = 3;
		}
		if ((cell[x - 1][y] == 2) && (cell[x][y + 1] == 2)) {
			cell[x - 1][y] = 3;
			isOutOfBorders = outOfBottomBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y + 1] = 3;
		}
		if ((cell[x][y - 1] == 2) && (cell[x + 1][y] == 2)) {
			isOutOfBorders = outOfTopBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y - 1] = 3;
			cell[x + 1][y] = 3;
		}
		if ((cell[x][y - 1] == 2) && (cell[x][y + 1] == 2)) {
			isOutOfBorders = outOfTopBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y - 1] = 3;
			isOutOfBorders = outOfBottomBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y + 1] = 3;
		}
		if ((cell[x + 1][y] == 2) && (cell[x][y + 1] == 2)) {
			cell[x + 1][y] = 3;
			isOutOfBorders = outOfBottomBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y + 1] = 3;
		}
		if (cell[x - 1][y] == 2) cell[x - 1][y] = 3;

		if (cell[x][y - 1] == 2) {
			isOutOfBorders = outOfTopBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y - 1] = 3;
		}
		if (cell[x + 1][y] == 2) cell[x + 1][y] = 3;
		if (cell[x][y + 1] == 2) {
			isOutOfBorders = outOfBottomBorders(currentImaginaryCell);
			if (isOutOfBorders == false) cell[x][y + 1] = 3;
		}
		return cell[x][y];
	}
	int clickOnSpot(int cell[8][8], int x, int y) {
		cell[x][y] = tempColor;
		cell[tempX][tempY] = 2;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (cell[i][j] == 3) cell[i][j] = 2;
			}
		}
		return cell[x][y];
	}
	int cancelSpots(int x, int y, int cell[8][8]) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (cell[i][j] == 3) cell[i][j] = 2;
			}
		}
		return cell[x][y];
	}
	int outOfTopBorders(int cic) {
		if ((cic == 0) || (cic == 8) || (cic == 16) || (cic == 24) || (cic == 32) || (cic == 40) || (cic == 48) || (cic == 56)) return true;
		else return false;
	}
	int outOfBottomBorders(int cic) {
		if ((cic == 7) || (cic == 15) || (cic == 23) || (cic == 31) || (cic == 39) || (cic == 47) || (cic == 55) || (cic == 63)) return true;
		else return false;
	}
	int whitesWin(int cell[8][8]) {
		if ((cell[0][0] == 0) && (cell[0][1] == 0) && (cell[0][2] == 0) && (cell[1][0] == 0) && (cell[1][1] == 0) && (cell[1][2] == 0) && (cell[2][0] == 0) && (cell[2][1] == 0) && (cell[2][2] == 0)) {
			return true;
		}
	}
	int blacksWin(int cell[8][8]) {
		if ((cell[5][5] == 1) && (cell[5][6] == 1) && (cell[5][7] == 1) && (cell[6][5] == 1) && (cell[6][6] == 1) && (cell[6][7] == 1) && (cell[7][5] == 1) && (cell[7][6] == 1) && (cell[7][7] == 1)) {
			return true;
		}
	}
};