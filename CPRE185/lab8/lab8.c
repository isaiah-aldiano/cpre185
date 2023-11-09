// WII-MAZE Skeleton code written by Jason Erbskorn 2007
// Edited for ncurses 2008 Tom Daniels
// Updated for Esplora 2013 TeamRursch185
// Updated for DualShock 4 2016 Rursch

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ncurses/ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

// Mathematical constants
#define PI 3.14159

// Screen geometry
// Use ROWS and COLS for the screen height and width (set by system)
// MAXIMUMS
#define NUMCOLS 100
#define NUMROWS 72

// Character definitions taken from the ASCII table
#define AVATAR 'A'
#define WALL '*'
#define EMPTY_SPACE ' '

// 2D character array which the maze is mapped into
char MAZE[NUMROWS][NUMCOLS];

// POST: Generates a random maze structure into MAZE[][]
// You will want to use the rand() function and maybe use the output %100.
// You will have to use the argument to the command line to determine how
// difficult the maze is (how many maze characters are on the screen).
void generate_maze(int difficulty);

void generate_maze(int difficulty)
{
	int some_rand = rand();
	srand(time(0));

	for (int j = 0; j < NUMROWS; j++)
	{
		for (int i = 0; i < NUMCOLS; i++)
		{
			some_rand = rand() % 100;

			if ((j == 0 && i == 49))
			{
				MAZE[j][i] = AVATAR;
			}
			else if (some_rand < difficulty)
			{
				// printf("%c", WALL);
				MAZE[j][i] = WALL;
			}
			else
			{
				// printf("O");
				// printf("%c", EMPTY_SPACE);
				MAZE[j][i] = EMPTY_SPACE;
			}
		}
	}
}

// PRE: MAZE[][] has been initialized by generate_maze()
// POST: Draws the maze to the screen
void draw_maze();

void draw_maze()
{
	for (int j = 0; j < NUMROWS; j++)
	{
		for (int i = 0; i < NUMCOLS; i++)
		{
			// fscanf(stdout,"%c", MAZE[j][i]);
			mvaddch(j, i, MAZE[j][i]);
		}
	}
}

// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
void draw_character(int x, int y, char use);

// PRE: -1.0 < x_mag < 1.0
// POST: Returns tilt magnitude scaled to -1.0 -> 1.0
// You may want to reuse the roll function written in previous labs.
float calc_roll(float x_mag);

float calc_roll(float x_mag)
{
	// LEFT
	if (x_mag > .6)
	{
		return -1;
	}
	// RIGHT
	else if (x_mag < -.6)
	{
		return 1;
	}

	return 0;
}

bool check_collison(int x, int y);

bool check_collison(int x, int y)
{
	if (MAZE[y][x] == WALL)
	{
		return 1;
	}

	return 0;
}

// Main - Run with './ds4rd.exe -t -g -b' piped into STDIN
int main(int argc, char *argv[])
{
	double gx, gy, gz;
	int t_since_drop = 0, prev_t = 0, t = 0, curr_x = 49, temp_x, curr_y = 0;
	bool on_ur, can_fall, cannot_fall;

	if (argc < 2)
	{
		printf("You forgot the difficulty\n");
		return 1;
	}
	int difficulty = atoi(argv[1]); // get difficulty from first command line arg

	generate_maze(difficulty);

	// setup screen
	initscr();
	refresh();

	// Generate and draw the maze, with initial avatar
	draw_maze();
	refresh();
	fflush(stdout);
	// MAZE WON'T PRINT???

	// Read gyroscope data to get ready for using moving averages.
	// Event loop
	do
	{
		// Read data, update average
		// scanf("%d, %lf, %lf, %lf", &t, &gx, &gy, &gz);
		fscanf(stdin, "%d, %lf, %lf, %lf", &t, &gx, &gy, &gz);

		// Is it time to move?  if so, then move avatar
		if (prev_t + 750 < t)
		{
			// draw_maze();
			prev_t = t;
			temp_x = calc_roll(gx);
			// curr_x += temp_x;
			// if (curr_x < 0)
			// {
			// 	temp_x = 0;
			// 	curr_x = 0;
			// }
			// else if (curr_x > 99)
			// {
			// 	temp_x = 0;
			// 	curr_x = 99;
			// }

			can_fall = !check_collison(curr_x, curr_y + 1);
			cannot_fall = check_collison(curr_x, curr_y + 1);
			on_ur = check_collison(curr_x + temp_x, curr_y);

			draw_character(curr_x, curr_y, EMPTY_SPACE);

			if (can_fall)
			{
				curr_y++;
				draw_character(curr_x, curr_y, AVATAR);
				t_since_drop = t;
			}
			else if (cannot_fall && (temp_x == 1 || temp_x == -1) && on_ur == 0)
			{
				curr_x += temp_x;
				draw_character(curr_x, curr_y, AVATAR);
			}
			// else if (cannot_fall && temp_x == -1 && on_ur == 0)
			// {
			// 	curr_x += temp_x;
			// 	draw_character(curr_x, curr_y, AVATAR);
			// }
			// else if (t_since_drop + 7000 < t)
			// {
			// 	break;
			// }
			else if (cannot_fall && check_collison(curr_x + 1, curr_y) == 1 && check_collison(curr_x - 1, curr_y) == 1)
			{
				curr_y == 73;
			}
			else if (cannot_fall)
			{
				draw_character(curr_x, curr_y, AVATAR);
			}

			// else if (cannot_fall && on_ur_left == 0)
			// {
			// 	draw_character(curr_x + temp_x, curr_y, AVATAR);
			// }

			/*
				Need to check:
				Left/right collision
				Down collision
				Diagonal left/right collision



			*/
			// TILTING to right

			// can_fall = !check_collison(curr_x, curr_y + 1);
			// cannot_fall = check_collison(curr_x, curr_y + 1);
			// on_ur_left = check_collison(curr_x, curr_y);
			// on_ur_right = check_collison(curr_x, curr_y);

			// if (cannot_fall && on_ur_right)
			// {
			// 	// draw_character(curr_x - 1, curr_y, EMPTY_SPACE);

			// 	draw_character(curr_x - 1, curr_y, AVATAR);
			// }
			// else if (cannot_fall && on_ur_left)
			// {
			// 	// draw_character(curr_x + 1, curr_y, EMPTY_SPACE);

			// 	draw_character(curr_x + 1, curr_y, AVATAR);
			// }
			// // else if (cannot_fall)
			// // {
			// // 	draw_character(curr_x - temp_x, curr_y, EMPTY_SPACE);
			// // 	draw_character(curr_x, curr_y, AVATAR);
			// // }
			// else if (can_fall)
			// {
			// 	draw_character(curr_x - temp_x, curr_y, EMPTY_SPACE);

			// 	curr_y++;
			// 	draw_character(curr_x, curr_y, AVATAR);
			// }

			// else if (check_collison(curr_x, curr_y + 1) && (check_collison(curr_x - 1, curr_y) || check_collison(curr_x + 1, curr_y)))
			// {
			// 	draw_character(curr_x, curr_y, AVATAR);
			// }
			// else if (!check_collison(curr_x, curr_y + 1) && (check_collison(curr_x - 1, curr_y) || check_collison(curr_x + 1, curr_y)))
			// {
			// 	curr_y++;
			// 	draw_character(curr_x, curr_y, AVATAR);
			// }
			// else
			// {
			// 	curr_y++;
			// 	draw_character(curr_x, curr_y, AVATAR);
			// }

			fflush(stdout);
		}
	} while (curr_y < 72); // Change this to end game at right time

	// Print the win message
	endwin();
	if (curr_y == 72)
	{
		printf("YOU WIN!\n");
	}
	else if (curr_y == 73)
	{
		printf("YOU LOOSE!\n");
	}
	return 0;
}

// PRE: 0 < x < COLS, 0 < y < ROWS, 0 < use < 255
// POST: Draws character use to the screen and position x,y
// THIS CODE FUNCTIONS FOR PLACING THE AVATAR AS PROVIDED.
//
//    >>>>DO NOT CHANGE THIS FUNCTION.<<<<
void draw_character(int x, int y, char use)
{
	mvaddch(y, x, use);
	refresh();
}
