/*
 * bez nazwy.cpp
 * 
 * Copyright 2017 tabaka <tabaka@linux-i125>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <iostream>
#include <unistd.h>
#include <term.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
using namespace std;

char board[8][8];

void generate_board();
void Draw_board();
void Generate_traps();
void game_play();
bool ifWin();




int main(int argc, char **argv)
{
	srand (time(NULL));
	initscr();
	if(has_colors() == false)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	init_pair(1, COLOR_RED, -1);
	generate_board();
	Generate_traps();
	game_play();
	
	getch();
	endwin();
	return 0;
}

/***********************Generate board*********************************/
void generate_board()
{
	for( int i=0; i<8; i++)
	{
		for( int j=0; j<8; j++)
		{
			board[i][j] = '_';
		}
	}
}
/***********************Draw board*************************************/
void Draw_board()
{
	printw("Dungeon Crawl");
	printw("\n\n");
	for( int i=0; i<8; i++)
	{
		printw("\n");
		printw( "|");
		for( int j=0; j<8; j++ )
		{
			printw("_");
			if(board[i][j] == '_')
			{	
				attron(COLOR_PAIR(1));
				printw("%c", board[i][j]);
				attroff(COLOR_PAIR(1));
			}
			else
				printw("%c", board[i][j]);
			printw( "_|");
		}
	}
}
/*********************Generate traps***********************************/
void Generate_traps()
{
	int number_of_traps = 5;
	bool is_trap_set = false;
	int x_coordinate = 0;
	int y_coordinate = 0;
	board[7][7] = 'X';	
	for( int i=0; i<number_of_traps; i++)
	{
		while( is_trap_set == false )
		{
			x_coordinate = rand()%8;
			y_coordinate = rand()%8;
			if( board[x_coordinate][y_coordinate] == '_' && !((x_coordinate ==0 || x_coordinate == 1) && (y_coordinate ==0 || y_coordinate==1)))
			{
				board[x_coordinate][y_coordinate] = 'T';
				is_trap_set = true;
			}
		}
		is_trap_set = false;
	}
	
}
/*************************GamePlay***************************************/
void game_play()
{
	int x_pos = 0;
	int y_pos = 0;
	board[x_pos][y_pos] = 'G';
	Draw_board();
}
/************************If win or lose********************************/
bool ifWin( )
{
	
		return true;

}
