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
using namespace std;

char board[8][8];

void generate_board();
void Draw_board();
void Generate_traps();




int main(int argc, char **argv)
{
	generate_board();
	Draw_board();
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
	for( int i=0; i<8; i++)
	{
		cout << endl;
		cout << "|";
		for( int j=0; j<8; j++ )
		{
			cout << "_" << board[i][j] << "_|";
		}
	}
}
/*********************Generate traps***********************************/
void Generate_traps()
{
	cout << "Stub" << endl;
}
