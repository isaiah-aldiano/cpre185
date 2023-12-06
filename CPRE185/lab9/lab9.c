// Lab 9 DS4Talker Skeleton Code

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ncurses.h>
#define MAXWORDS 100
#define MAXSEN 80
#define WORDLEN 11
#define DEBUG 0 // set to 0 to disable debug output
#define SEL '*'
#define UNSEL ' '
#define DELTA_Y 5
#define DELTA_X 1
#define CLEAR '\0'

// reads words from the file
// into wl and trims the whitespace off of the end of each word
// DO NOT MODIFY THIS Prototype
int readWords(char *wl[MAXWORDS], char *filename);

// modifies s to trim white space off the right side
//  DO NOT MODIFY THIS Prototype
void trimws(char *s);

// Sets joystick movement to -1 <= 0 <= 1
int js_tolerance(int val);

// Draw character from last lab
void draw_character(int x, int y, char use);

int main(int argc, char *argv[])
{
	char *wordlist[MAXWORDS];
	char sentence[MAXSEN];
	int backspace[MAXSEN] = {0};
	int wordCount = 0, selected = 0;
	int offset = 10;
	int t = 0, prev_t = 0;											  // Time
	int tri, circ, x, sqr;											  // Button input
	int lx, ly, rx, ry, lz, rz, s1, s2, s3, s4, s5, s6;				  // Joystick input
	int X, Y, Xmult = 1, Ymult = 0;									  // Word selector character
	int sel_word_len = 0, last_word, del_word = 0, cur_del_word = -1; // Tracking words to delete
	int pressed = 0;												  // Button press limiter

	wordCount = readWords(wordlist, argv[1]);

	if (DEBUG)
	{
		// add code to print the words to the screen here for part 1

		initscr();
		refresh();

		int j = 0;
		int col = 0;
		while (j < wordCount)
		{
			mvprintw(j / 5, (j % 5) * 11, "%11s", wordlist[j]);
			j++;
		}
		fflush(stdout);
		refresh();

		X = (WORDLEN * Xmult) - strlen(wordlist[selected]) - 1;
		Y = 0;

		draw_character(X, Y, SEL);
	}

	// most of your code for part 2 goes here. Don't forget to include the ncurses library

	initscr();
	refresh();

	int j = 0;
	int col = 0;
	while (j < wordCount) // Printing word list
	{
		mvprintw(j / 5, (j % 5) * 11, "%11s", wordlist[j]);
		j++;
	}

	fflush(stdout);
	refresh();

	X = (WORDLEN * Xmult) - strlen(wordlist[selected]) - 1;
	Y = 0;

	draw_character(X, Y, SEL);

	// Clearing everything
	sentence[0] = CLEAR;
	backspace[0] = CLEAR;
	move(18, 0);
	clrtoeol();
	move(19, 0);
	clrtoeol();
	sel_word_len = 0;
	cur_del_word = -1;

	do
	{
		scanf("%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d", &t, &tri, &circ, &x, &sqr, &rz, &lz, &s1, &s2, &s3, &s4, &s5, &s6, &lx, &ly, &rx, &ry); // Controller input

		if (tri == 1 && selected < wordCount && pressed == 0 && sel_word_len + strlen(wordlist[selected]) + 1 <= MAXWORDS)
		{ // Checking if Triangle is pressed, selected character is on list, button press limiter, and if the selected word won't go over character limit of 100
			pressed = 1;
			if (strlen(wordlist[selected]) > 0)
			{
				last_word = strlen(wordlist[selected]) + 1;
				strcat(sentence, " ");
			}
		}
		else if (sqr == 1 && selected < wordCount && pressed == 0 && sel_word_len + strlen(wordlist[selected]) <= MAXWORDS)
		{ // Checking if Square is pressed, selected character is on list, button press limiter, and if the selected word won't go over character limit of 100
			pressed = 1;
			if (strlen(wordlist[selected]) > 0)
			{
				last_word = strlen(wordlist[selected]);
			}
		}
		else if (x == 1 && cur_del_word >= 0 && pressed == 0)
		{ // Checks if X is pressed, the word to delete won't go outside of memory, and press limiter
			pressed = 2;
		}
		else if (rz == 1)
		{ // Right joystick press clears everything
			sentence[0] = CLEAR;
			backspace[0] = CLEAR;
			move(18, 0);
			clrtoeol();
			move(19, 0);
			clrtoeol();
			sel_word_len = 0;
			cur_del_word = -1;
		}

		if (prev_t + 140 < t && (tri + circ + x + sqr) == 0)
		{ // Moving word select character
			draw_character(X, Y, UNSEL);
			refresh();

			if (js_tolerance(lx) == -1 && Xmult > 1)
			{ // LEFT
				Xmult -= 1;
				selected -= 1;
			}
			else if (js_tolerance(lx) == 1 && Xmult < 5)
			{ // RIGHT
				Xmult += 1;
				selected += 1;
			}
			else if (js_tolerance(ly) == 1 && Y < 15)
			{
				Y += 1;
				selected += 5;
			}
			else if (js_tolerance(ly) == -1 && Y > 0)
			{
				Y -= 1;
				selected -= 5;
			}

			X = (WORDLEN * Xmult) - strlen(wordlist[selected]) - 1;

			draw_character(X, Y, SEL);
			refresh();

			prev_t = t;
		}

		if (pressed == 2 && (tri + circ + x + sqr) == 0)
		{ // pressed = 2 -> X was pressed -> use parallel to delete specific amount of characters
			pressed = 0;
			sel_word_len -= backspace[cur_del_word];

			sentence[sel_word_len] = '\0';

			backspace[cur_del_word] = CLEAR;

			cur_del_word -= 1;
		}
		else if (pressed == 1 && (tri + circ + x + sqr) == 0)
		{ // pressed = 2 -> Sqr||Tri was pressed -> increase sentence length varaiable, increase parallel array index
			pressed = 0;
			sel_word_len += last_word;
			cur_del_word++;
			backspace[cur_del_word] = last_word;
			last_word = 0;
			strcat(sentence, wordlist[selected]);
		}

		move(18, 0);
		clrtoeol();

		for (int m = 0; m < sel_word_len; m++)
		{ // Print out sentence
			mvprintw(18, WORDLEN + m, "%c", sentence[m]);
			refresh();
		}

		fflush(stdout);

	} while (s5 != 1);

	endwin();

	return 0;
}

void trimws(char *s)
{
	for (int i = 0; i < strlen(s); i++)
	{
		if (isspace(s[i]))
		{
			s[i] = '\0';
			return;
		}
	}
}

int readWords(char *wl[MAXWORDS], char *filename)
{

	FILE *fp;
	char buf[WORDLEN];
	int i = 0;
	int wordcount = 0;

	fp = fopen(filename, "r");

	while (!feof(fp))
	{
		fgets(buf, WORDLEN, fp);
		trimws(buf);

		wl[i] = (char *)malloc(sizeof(char) * strlen(buf));

		strcpy(wl[i], buf);

		i++;
		wordcount++;
	}

	fclose(fp);
	return wordcount;
}

void draw_character(int x, int y, char use)
{
	mvaddch(y, x, use);
	refresh();
}

int js_tolerance(int val)
{
	// L = -128, R = +128, U = -128, D = +128
	// LEFT or RIGHT stick

	if (val >= 100)
	{ // RIGHT OR DOWN
		return 1;
	}
	else if (val <= -100) // LEFT OR UP
	{
		return -1;
	}

	return 0;
}