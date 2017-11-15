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
struct position
{
	int x_pos;
	int y_pos;
};

void generate_board();
void Draw_board();
void Generate_traps();
void game_play();
void generate_monsters( int monsters_number, position monster[]);
int move_monsters(int monsters_number, position monster[], int win);
int ifWin(int x, int y);

int main(int argc, char **argv)
{
	srand (time(NULL));
	initscr();
	keypad(stdscr, TRUE);
	clear();
	noecho();
	cbreak();	
	if(has_colors() == false)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	start_color();
	init_pair(1, COLOR_GREEN, COLOR_BLACK); //Grass field/
	init_pair(2, COLOR_RED, COLOR_BLACK); //Trap
	init_pair(3, COLOR_BLUE, COLOR_BLACK); //Player
	init_pair(4, COLOR_BLACK, COLOR_WHITE); //Monsters
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
	printw("Simple dungeon crawl game\n");
	printw("You move with arrows avoiding (T)raps\n");
	for( int i=0; i<8; i++)
	{
		printw("\n");
		printw( "|");
		for( int j=0; j<8; j++ )
		{
			attron(COLOR_PAIR(1));
			printw("_");
			if(board[i][j] == 'G')
			{	
				attron(COLOR_PAIR(3));
				printw("%c", board[i][j]);
			}
			else if(board[i][j] == 'T')
			{
				attron(COLOR_PAIR(2));
				printw("%c", board[i][j]);
			}
			else if(board[i][j] == 'M')
			{
				attron(COLOR_PAIR(4));
				printw("%c", board[i][j]);
			}
			else
			printw("%c", board[i][j]);
			attron(COLOR_PAIR(1));
			printw( "_");
			attroff(COLOR_PAIR(1));
			printw( "|");
		}
	}
	printw("\n\n");
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
	int monsters_number = 5;
	position monster[monsters_number];
	position Player;
	Player.x_pos = 0;
	Player.y_pos = 0;
	int x_move = 0;
	int y_move = 0;
	int move;
	bool isMoveValid = false;
	int win = -1;
	
	generate_board();
	board[Player.x_pos][Player.y_pos] = 'G';
	Generate_traps();
	generate_monsters( monsters_number, monster);
	Draw_board();
	
	while(win == -1)
	{
		while( isMoveValid == false )
		{
		move = getch();
		switch(move)
		{
			case KEY_UP:
				if(x_move - 1 < 0)
				{
					printw("Invalid move\n");
					break;
				}
				else
				{
					x_move--;
					isMoveValid = true;
					break;
				}
			case KEY_DOWN:
				if(x_move + 1 > 7)
				{
					printw("Invalid move\n");
					break;
				}
				else
				{
					x_move++;
					isMoveValid = true;
					break;
				}
			case KEY_LEFT:
				if(y_move - 1 < 0)
				{
					printw("Invalid move\n");
					break;
				}
				else
				{
					y_move--;
					isMoveValid = true;
					break;
				}
			case KEY_RIGHT:
				if(y_move + 1 > 7)
				{
					printw("Invalid move\n");
					break;
				}
				else
				{
					y_move++;
					isMoveValid = true;
					break;
				}
			default:
				{
					printw("Wrong key!\n");
					break;
				}
		}
		
		}
	isMoveValid = false;
	win = ifWin(x_move, y_move);
		if(win == -1)
		{
			board[Player.x_pos][Player.y_pos] = '_';
			board[x_move][y_move] = 'G';
			Player.x_pos = x_move;
			Player.y_pos = y_move;
			clear();	
			win = move_monsters(monsters_number, monster, win);
			clear();
			Draw_board();
			clrtoeol();
			refresh();
		}
		else if(win == 1)
		{
			clear();
			Draw_board();
			printw("You loose!");
		}
		else
		{
			board[Player.x_pos][Player.y_pos] = '_';
			board[x_move][y_move] = 'G';
			Player.x_pos = x_move;
			Player.y_pos = y_move;
			clear();
			Draw_board();
			printw("\nYou win!");
			clrtoeol();
			refresh();
		}
	}
}
/************************If win or lose********************************/
int ifWin( int x, int y)
{
		if(board[x][y] == 'X')
			return 0;
		else if(board[x][y] == 'T' || board[x][y] == 'M')
			return 1;
		else
			return -1;

}
/*********************Monsters*****************************************/
void generate_monsters( int monsters_number, position monster[])
{
	
	bool is_monster_set = false;
	int x_coordinate = 0;
	int y_coordinate = 0;	
	for( int i=0; i<monsters_number; i++)
	{
		while( is_monster_set == false )
		{
			x_coordinate = rand()%8;
			y_coordinate = rand()%8;
			if(board[x_coordinate][y_coordinate] == '_' && !((x_coordinate ==0 || x_coordinate == 1) && (y_coordinate ==0 || y_coordinate==1)))
			{
				board[x_coordinate][y_coordinate] = 'M';
				monster[i].x_pos = x_coordinate;
				monster[i].y_pos = y_coordinate;
				is_monster_set = true;
			}
		}
		is_monster_set = false;
	}
}
int move_monsters(int monsters_number, position monster[], int win)
{
	int xmove = 0;
	int ymove = 0;
	bool monster_moved = false;
	for(int i=0; i<monsters_number; i++)
	{
		while(monster_moved == false)
		{
			if(rand()%2)
			{
			xmove = (rand()%2?-1:1);
			}
			else
			{
			ymove = (rand()%2?-1:1);
			}
			if((monster[i].x_pos + xmove >= 0 && monster[i].x_pos + xmove <=7) && (monster[i].y_pos + ymove >= 0 && monster[i].y_pos + ymove <=7) && 
			(board[monster[i].x_pos+xmove][monster[i].y_pos+ymove] == '_' || board[monster[i].x_pos+xmove][monster[i].y_pos+ymove]=='G'))
			{
				if(board[monster[i].x_pos+xmove][monster[i].y_pos+ymove]=='G')
				{
					board[monster[i].x_pos][monster[i].y_pos] = '_';
					monster[i].x_pos += xmove;
					monster[i].y_pos += ymove;
					board[monster[i].x_pos][monster[i].y_pos] = 'M';
					xmove = 0;
					ymove = 0;
					monster_moved = true;
					win = 1;
				}
			board[monster[i].x_pos][monster[i].y_pos] = '_';
			monster[i].x_pos += xmove;
			monster[i].y_pos += ymove;
			board[monster[i].x_pos][monster[i].y_pos] = 'M';
			xmove = 0;
			ymove = 0;
			monster_moved = true;
			}
			else
			{
			xmove = 0;
			ymove = 0;
			}
		}
		monster_moved = false;
	}
	return win;
}
