#pragma once
#include <iostream>
using namespace std;
class Bot {
public:
	int  x, y, bestWayX,bestWayY,imaginaryCell[8][8],blocked=0,targetX=7,targetY=7;
	void move(int cell[8][8]) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (cell[i][j] == 1) {
					imaginaryCell[i][j] = 0;
				}
			}
		}
		nearestBlack(cell);
		bestWay(cell);
		change(cell);
		
	}
 	void nearestBlack(int cell[8][8]) {
		int deltaX, deltaY, delta, deltaMin = 99999;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((cell[i][j] == 1)&&(imaginaryCell[i][j] == 1)) blocked++;
				if ((cell[i][j] == 1)&&(imaginaryCell[i][j] == 0)) {
					if ((i == 7) && (j == 7)) {
						if (cell[i][j] == 1)continue;
					}
					deltaX = targetX - i;
					deltaY = targetY - j;
					delta = deltaX + deltaY;
					if (deltaMin > delta) {
						deltaMin = delta;
						x = i;
						y = j;
					}
				}
			}
	
		}
	}
	int bestWay(int cell[8][8]) {
		if (blocked == 9) {
			allBlocked(cell);
			bestWayX = x;
			bestWayY = y - 1;
			blocked = 0;
			return 0;
		}
		blocked = 0;
		if (blocked != 9) {
			if (((cell[x + 1][y] < 2) && (cell[x][y + 1] < 2)) || ((y == 7) && (cell[x + 1][y] < 2))||((x==7)&&(cell[x][y+1]<2))) {
				imaginaryCell[x][y] = 1;
				nearestBlack(cell);
				if (bestWay(cell) == 0) return 0;
			}
			conditions(cell);
		}
		return 0;
	}
	void change(int cell[8][8]) {
		cell[x][y] = 2;
		cell[bestWayX][bestWayY] = 1;
		bestWayX = 0;
		bestWayY = 0;
	}
	void allBlocked(int cell[8][8]) {
		int deltaX, deltaY, delta, deltaMin = 99999,counter=0;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((cell[i][j] == 1)&&(cell[i][j-1] > 1)) {
					deltaX = targetX - i;
					deltaY = targetY - j;
					delta = deltaX + deltaY;
					if (deltaMin > delta) {
						deltaMin = delta;
						x = i;
						y = j;
					}
					counter++;
				}
			}

		}
	}
	void conditions(int cell[8][8]) {
		int  right, rightX, rightY, down, downX, downY;
		rightX = targetX - (x + 1);
		rightY = targetY - y;
		right = rightX + rightY;
		downX = targetX - x;
		downY = targetY - (y + 1);
		down = downX + downY;
		if ((right <= down) && (cell[x + 1][y] > 1)) {
			bestWayX = x + 1;
			bestWayY = y;
		}
		if ((right >= down) && (y != 7) && (cell[x][y + 1] < 2)) {
			bestWayX = x + 1;
			bestWayY = y;
		}
		if ((right <= down) && (cell[x + 1][y] < 2) && (y != 7)) {
			bestWayX = x;
			bestWayY = y + 1;
		}
		if ((right >= down) && (y != 7) && (cell[x][y + 1] > 1)) {
			bestWayX = x;
			bestWayY = y + 1;
		}
		
	}
};