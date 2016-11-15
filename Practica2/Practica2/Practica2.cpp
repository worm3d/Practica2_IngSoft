#include "stdafx.h"
#define WORLDSIZE 80
#define GAMEWAIT 39.998

bool gameOver = false;

int characterPos = 40;
int lives = 3;

int bulletPos = 40;
bool bullet = false;	//Indicates if the bullet is moving
int bulletDir = -1;	//Indicates the direction of the bullet, -1 is left, and 1 is right

int enemyPos = 0;
bool enemy = false;
int enemyOrigin = -1; //Indicates the origin of the enemy, 0 is no enemy, 1 is left, 2 is right


void readInput()
{
	if (_kbhit()) {
		char c = _getch();

		if (c == 'a' && characterPos > 0)				characterPos--;
		else if (c == 'd' && characterPos < WORLDSIZE)	characterPos++;
		else if (c == 'q' && !bullet) {
			bulletPos--;
			bulletDir = -1;
			bullet = true;
		}
		else if (c == 'e' && !bullet) {
			bulletPos++;
			bulletDir = 1;
			bullet = true;
		}
	}
}

//This function updates the state of the bullet and its position
void updateBullet()
{
	if (!bullet) bulletPos = characterPos; //If a bullet is not moving, its position must be equal to the character position
	else if (bullet) {
		if (bulletDir == -1)	bulletPos--;
		else bulletPos++;
	}

	if (bulletPos <= 0 || bulletPos >= WORLDSIZE) { //If the bullet is on the limits of the world it dissapears and the position goes back to the player
		bullet = false;
		bulletPos = characterPos;
	}
}

void updateEnemy()
{
	if (!enemy) {
		enemyOrigin = rand() % 3; //Creates a random to determine the initial position of the enemy.
		if (enemyOrigin == 1) {
			enemyPos = 0; 
			enemy = true;
		}
		else if (enemyOrigin == 2) {
			enemyPos = WORLDSIZE;
			enemy = true;
		}
	}
	else {
		if (enemyOrigin == 1) enemyPos++;
		else if (enemyOrigin == 2) enemyPos--;
	}

	if (enemyOrigin == 1 && enemyPos >= bulletPos) {
		enemy = false;
		bullet = false;
	}
	else if (enemyOrigin == 2 && enemyPos <= bulletPos) {
		enemy = false;
		bullet = false;
	}
	if (enemyOrigin == 1 && enemyPos >= characterPos) {
		enemy = false;
		lives--;
	}
	if (enemyOrigin == 2 && enemyPos <= characterPos) {
		enemy = false;
		lives--;
	}
}

void printWorld()
{
	for (int i = 0; i <= WORLDSIZE; i++)
	{
		if (i == characterPos)				printf("^.^");	//Prints the character
		else if (i == bulletPos && bullet)	printf("-");	//Prints the bullet
		else if (i == enemyPos && enemy)	printf("@");	//Prints the enemy
		else								printf("_");	//Prints the world's floor
	}
	printf("         Lives: %d", lives);
}

int main()
{
	printf("\n\n\n\n\n\n\n"); //Move the cursor a bit down from initial position

	while (!gameOver)
	{
		updateBullet();
		updateEnemy();

		printWorld();
		printf("\r"); //Returns the cursor to the beginning of the line

		readInput();

		if (lives == 0) gameOver = true;

		Sleep(GAMEWAIT);
	}

	printf("\r");
	printf("\t\t\t\t\t\t\tGAME OVER\t\t\t\t\t\t\t");
	Sleep(2000);

	return 0;
}