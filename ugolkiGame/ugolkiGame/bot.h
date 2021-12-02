#pragma once
#include <iostream>
using namespace std;
class Bot {
public:
	int x, y, shortestX, shortestY, targetX, targetY,lastTargetX,lastTargetY,blockedCell[8][8];
	void move(int cell[8][8]) {
		nullifyBlockedCells();
		isTargetReached(cell);
		nearest(cell);
		bestWay(cell);
		change(cell);
	}
	void nullifyBlockedCells() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				blockedCell[i][j] = 0;
			}
		}
	}
	void bestWay(int cell[8][8]) {
		bool noWay, allblocked = false;
		int blocked=0;
		for (int i = 0; i < 9; i++) {
			noWay = false;
			if ((cell[x][y + 1] < 2) && (cell[x + 1][y] < 2)||((x==7)&&((cell[x][y + 1] < 2)))||((y == 7) && ((cell[x + 1][y] < 2)))||((x==lastTargetX)&&(y==lastTargetY))){
				blocked++;
				blockedCell[x][y] = 1;
				nearest(cell);
				noWay = true;
			}
			if (noWay == false) break;
		}
		if (blocked == 9) {
			allblocked = true;
		}
		bestCell(cell, allblocked);
	}
	void nearest(int cell[8][8]) {
		int delta, deltaX, deltaY, deltaMin = 100;
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if ((cell[i][j] == 1)&&(blockedCell[i][j]!=1)) {
					deltaX = targetX - i;
					deltaY = targetY - j;
					delta = deltaX + deltaY;
					if (delta < deltaMin) {
						deltaMin = delta;
						x = i;
						y = j;
					}
				}
			}
		}
	}
	void change(int cell[8][8]) {
		cell[x][y] = 2;
		cell[shortestX][shortestY] = 1;
	}
	void bestCell(int cell[8][8],bool allBlocked) {
		bool found = false;
		if (allBlocked == true) {
			nullifyBlockedCells();
			for (int i = 0; i < 9; i++) {
				nearest(cell);
				if (cell[x][y - 1] > 1) {
					shortestX = x;
					shortestY = y - 1;
					found = true;
				}
				if ((cell[x - 1][y] > 1)&&(found!=true)) {
					shortestX = x - 1;
					shortestY = y;
					found = true;
				}
				blockedCell[x][y] = 1;
				if (found == true) break;
			}
		}
		if(allBlocked == false) {
			int right, down, rightX, rightY, downX, downY;
			rightX = targetX - (x + 1);
			if (rightX < 0)rightX = 0;
			rightY = targetY - y;
			if (rightY < 0)rightY = 0;
			right = rightX + rightY;
			downX = targetX - x;
			if (downX < 0)downX = 0;
			downY = targetY - (y + 1);
			if (downY < 0)downY = 0;
			down = downX + downY;
			if ((down <= right) && (x != 7) && (cell[x][y + 1] < 2)) {
				shortestX = x + 1;
				shortestY = y;
			}
			if ((down >= right) && (x != 7) && (cell[x + 1][y] > 1)) {
				shortestX = x + 1;
				shortestY = y;
			}
			if ((down >= right) && (y != 7) && (cell[x + 1][y] < 2)) {
				shortestX = x;
				shortestY = y + 1;
			}
			if ((down <= right) && (y != 7) && (cell[x][y + 1] > 1)) {
				shortestX = x;
				shortestY = y + 1;
			}
		}
	}
	void isTargetReached(int cell[8][8]) {
		int targets[9] = { 77,67,57,76,66,56,75,65,55 };
		int n = 0;
		int currentTargetX, currentTargetY;
		for (int i = 7; i > 4; i--) {
			for (int j = 7; j > 4; j--) {
				currentTargetX = targets[n] % 10;
				currentTargetY = targets[n] / 10;
				if (((i == currentTargetX) && (j == currentTargetY))&&(cell[i][j]==1)) n++;
			}
		}
		targetX = targets[n] % 10;
		targetY = targets[n] / 10;
		if (n > 0) {
			lastTargetX = targets[n - 1] % 10;
			lastTargetY = targets[n - 1] / 10;
		}
		
	}

};