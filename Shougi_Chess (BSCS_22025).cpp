

#include <iostream>
#include <fstream>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
using namespace std;
enum Turn { white, black };
#define in_Box_dimension 10
#define board_dimension 9
#define screen_rows 100
#define screen_cols 175
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}

struct	position {
	int posx = 0, posy = 0;
};
struct p_count
{
	int Pawn_c=0;
	int Bishop_c=0;
	int Rook_c = 0;
	int Nite_c = 0;
	int Lance_c = 0;
	int Silv_c = 0;
	int Gold_c = 0;
};
struct brd_decoy
{       // turn 
	int turn_t;
	   // main board
	char** B;
	int** nB = 0;
	   // promotion arrays
	bool* prom_white=new bool[34]{false};
	bool* prom_black= new bool[34] {false};
	
	   // white placer board
	char* White_placer = new char[20] {'\0'}; // Jab white, black ka koi piece capture kara ga to wo is pa aa jai ga! 
	int* nWhite_placer = new int [20]; 
	
	// black placer board
	char* Black_placer = new char[20] {'\0'}; // Jab black, white ka koi piece capture kara ga to wo is pa aa jai ga!
	int* nBlack_placer = new int [20];
};


void SelectPosi(position& Ps, int brow, int cols, int &pre_ch,int &pre_d)
{
	int ch; int d;
	do {
		getRowColbyLeftClick(ch, d);
		Ps.posy = ch / cols;  // cols = box dimension = 10
		Ps.posx = d / brow;   // b_rows = box dimension = 10 
	} while (pre_ch==ch && pre_d==d);
	pre_ch = ch ;
	pre_d = d ;
}
//_____________________ Shapes of pieces _____________________

    
void base_of_pieces(int row, int col, char x)
{
	gotoRowCol(row, col); cout << x;
	gotoRowCol(row + 1, col + 1); cout << x;
	gotoRowCol(row + 1, col); cout << x;
	gotoRowCol(row + 1, col - 1); cout << x;
	//_________________________________________
	gotoRowCol(row + 2, col - 2); cout << x;
	gotoRowCol(row + 2, col - 1); cout << x;
	gotoRowCol(row + 2, col); cout << x;
	gotoRowCol(row + 2, col + 1); cout << x;
	gotoRowCol(row + 2, col + 2); cout << x;

}
void King_shape(int row,int col,int clr,char x)
{
	SetClr(clr);
	gotoRowCol(row - 2, col+1); cout << x;
	gotoRowCol(row - 3, col); cout << x;
	gotoRowCol(row - 2, col); cout <<x;
	gotoRowCol(row-2, col-1); cout << x;
	gotoRowCol(row-1, col); cout << x;
	//_________________________________
	base_of_pieces(row, col, x);
}
void Gold_general_shape(int row, int col, int clr, char x)
{
	SetClr(clr);
	gotoRowCol(row - 3, col + 2); cout << x;
	gotoRowCol(row - 3, col); cout << x;
	gotoRowCol(row - 3, col-2); cout << x;
	//___________________________________
	
	gotoRowCol(row - 2, col+2); cout << x;
	gotoRowCol(row - 2, col + 1); cout << x;
	gotoRowCol(row - 2, col); cout << x;
	gotoRowCol(row - 2, col - 1); cout << x;
	gotoRowCol(row - 2, col - 2); cout << x;
	
	//___________________________________
	gotoRowCol(row - 1, col + 1); cout << x;
	gotoRowCol(row - 1, col); cout << x;
	gotoRowCol(row - 1, col - 1); cout << x;
	//___________________________________
	base_of_pieces(row, col, x);
}
void Silver_general_shape(int row, int col, int clr, char x)
{
	SetClr(clr);
	gotoRowCol(row - 3, col + 1); cout << x;
	gotoRowCol(row - 3, col - 1); cout << x;
	//___________________________________
	gotoRowCol(row - 2, col + 1); cout << x;
	gotoRowCol(row - 2, col); cout << x;
	gotoRowCol(row - 2, col - 1); cout << x;
	//___________________________________
	gotoRowCol(row - 1, col); cout << x;
	//___________________________________
	base_of_pieces(row, col, x);
}
void Night_shape(int row, int col, int clr, char x) // Ghora
{
	SetClr(clr);
	gotoRowCol(row - 3, col); cout << x;
	//_________________________________
	//gotoRowCol(row - 2, col + 2); cout << x;
	gotoRowCol(row - 2, col + 1); cout << x;
	gotoRowCol(row - 2, col); cout << x;
	gotoRowCol(row - 2, col - 1); cout << x;
	//_________________________________
	//gotoRowCol(row - 1, col + 3); cout << x;
	gotoRowCol(row - 1, col + 2); cout << x;
	gotoRowCol(row - 1, col); cout << x;
	gotoRowCol(row - 1, col - 1); cout << x;
	gotoRowCol(row - 1, col - 2); cout << x;
	//_____________________________________
	gotoRowCol(row, col); cout << x;
	
	gotoRowCol(row , col); cout << x;
	gotoRowCol(row, col - 1); cout << x;
	//_________________________________________
	gotoRowCol(row+1, col); cout << x;
	
	gotoRowCol(row + 2, col - 2); cout << x;
	gotoRowCol(row + 2, col - 1); cout << x;
	gotoRowCol(row + 2, col); cout << x;
	gotoRowCol(row + 2, col + 1); cout << x;
	gotoRowCol(row + 2, col + 2); cout << x;
}
void Lance_shape(int row, int col, int clr, char x)  // Tope
{
	SetClr(clr);
	
	gotoRowCol(row - 2, col); cout << char(-129);
	
	//_____________________
	gotoRowCol(row - 1, col); cout <<x;
	//_____________________
	gotoRowCol(row, col); cout << x;
	//______________________________
	base_of_pieces(row,col,x);
}
void Bishop_shape(int row, int col, int clr, char x)
{
	SetClr(clr);
	gotoRowCol(row - 3, col + 1); cout << char(-129);
	gotoRowCol(row - 3, col); cout << char(-129);
	gotoRowCol(row - 3, col-1); cout << char(-129);
	//_____________________
	gotoRowCol(row - 2, col+1); cout << x;
	gotoRowCol(row - 2, col); cout << x;
	gotoRowCol(row - 2, col-1); cout << x;
	//_____________________
	
	gotoRowCol(row - 1, col); cout << x;
	
	//______________________
	gotoRowCol(row, col); cout << x;
	//______________________________
	base_of_pieces(row, col, x);
}
void Rook_shape(int row, int col, int clr, char x)
{
	SetClr(clr);
	
	gotoRowCol(row - 3, col); cout << char(-129);
	gotoRowCol(row - 2, col); cout << x;
	//_____________________
	
	//_____________________
	gotoRowCol(row - 1, col + 1); cout << x;
	gotoRowCol(row - 1, col); cout << x;
	gotoRowCol(row - 1, col - 1); cout << x;
	//______________________
	gotoRowCol(row, col); cout << x;
	//______________________________
	base_of_pieces(row, col, x);
}
void Pawn_shape(int row, int col, int clr, char x)
{
	SetClr(clr);
	gotoRowCol(row-1, col); cout << char(-129);
	gotoRowCol(row, col); cout << x;
	gotoRowCol(row + 1, col + 1); cout << x;
	gotoRowCol(row + 1, col); cout << x;
	gotoRowCol(row + 1, col - 1); cout << x;
	//_________________________________________
	gotoRowCol(row + 2, col - 2); cout << x;
	gotoRowCol(row + 2, col - 1); cout << x;
	gotoRowCol(row + 2, col); cout << x;
	gotoRowCol(row + 2, col + 1); cout << x;
	gotoRowCol(row + 2, col + 2); cout << x;

}

//______________________________________________
void turn_change(int & turn_t)
{
	turn_t = (turn_t + 1) % 2;
}
/*
                0 1 2 -1 -2 -3 3 4 5 
				  6              7           (For Black)
               8 9 10 11 12 13 14 15 16   


			   16 15 14 13 12 11 10 9 8
			      7               6          (For White)
			    5 4 3 -3 -2 -1 2 1 0


*/
void init(string mode,char**& B,int**& nB, int& turn_t, int& dimension, string Player_names[], int& NOP,bool*&prom_white, bool* &prom_black,char * &White_placer,int* &nWhite_placer,char*&Black_placer,int* &nBlack_placer)
{
	//mode, B, nB, turn_t,
	dimension = 9;
	B = new char* [dimension];
	nB = new int* [dimension];
	for (int i = 0; i < dimension; i++)
	{
		B[i] = new char[dimension];
		nB[i] = new int[dimension];
	}
	string file;
	if (mode == "N" || mode == "n")
	{
		file = "chess Board.txt";
	}
	if (mode == "Y" || mode == "y")
	{
		file = "save file.txt";
	}
	fstream rdr(file);
	NOP = 2;
	gotoRowCol((100 / 2) + 4, 175 / 3);
	
	if (mode == "N"|| mode == "n")
	{
		cout << "1st player is with white pieces and 2nd with black" << endl << endl;
		for (int i = 0; i < NOP; i++)
		{
			gotoRowCol((100 / 2) + 5 + i, 175 / 3);
			cout << "What is the name of your Player " << i + 1 << ": ";
			cin >> Player_names[i];
		}
		// Loading alphabets
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				rdr >> B[i][j];
			}
		}
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				rdr >> nB[i][j];
			}
		}
	}
	else
	{    
		rdr >> turn_t;
		// Loading names from saved files
		for (int i = 0; i < NOP; i++)
		{
			rdr >> Player_names[i];
		}
		  // Loading alphabets  from saved file
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				rdr >> B[i][j];
			}
		}
		  // Loading their corresponding numbers from saved file
		for (int i = 0; i < dimension; i++)
		{
			for (int j = 0; j < dimension; j++)
			{
				rdr >> nB[i][j];
			}
		}
		  // Transferring promotion arrays from saved file
		for (int i = 0; i < 34; i++)
		{
			rdr >>prom_white[i];
			
		}
		for (int i = 0; i < 34; i++)
		{
			rdr >> prom_black[i];

		}
		  // Transferring Placer arrays from saved file
			for (int i = 0; i < 19; i++)
		{
			rdr >> White_placer[i];
		}
		for (int i = 0; i < 19; i++)
		{
			rdr >> nWhite_placer[i];
		}
		for (int i = 0; i < 19; i++)
		{
			rdr >> Black_placer[i];
		}
		for (int i = 0; i < 19; i++)
		{
			rdr >> nBlack_placer[i];
		}
	}
	
		
		
}
bool pick_white(char**B,int x,int y)
{
	if (B[y][x]>='A' && B[y][x] <= 'Z')
	{
		return true;
	}
	return false;
}
bool pick_black(char** B, int x, int y) 
{
	if (B[y][x] >= 'a' && B[y][x] <= 'z') 
	{
		return true;
	}
	return false;
}
bool is_piecePick_valid(char**B,int x,int y,int turn_t)
{
	if (turn_t == white)
		return pick_white(B,x,y);
	return pick_black(B,x,y);
}
bool pick_is_valid(char** B, int x, int y, int dimension,int turn_t)
{
	if (x < 0 || y < 0 || x >= dimension || y >= dimension) 
	{
		return false;
	}
	return is_piecePick_valid(B,x,y,turn_t);
}
bool drop_is_valid(char** B, int x, int y, int dimension, int turn_t)
{
	if (x < 0 || y < 0 || x >= dimension || y >= dimension) 
	{
		return false;
	}
	return !is_piecePick_valid(B,x,y,turn_t);

}
void move_placer(char**arr,int x_pic,int y_pic,int x_drop,int y_drop) 
{
	arr[y_drop][x_drop] = arr[y_pic][x_pic];
	arr[y_pic][x_pic] = '_';
}
void move_placer_int(int** arr, int x_pic, int y_pic, int x_drop, int y_drop)
{
	arr[y_drop][x_drop] = arr[y_pic][x_pic];
	arr[y_pic][x_pic] = -5;
}
void msg(string Player_name) 
{
	cout << "It is " << Player_name << "'s turn\r" << endl;
}
void print_pieces_shape(char**B,int index_ri,int index_ci,int row, int col, int clr, char x)
{
	
	if(B[index_ri][index_ci] == 'k' || B[index_ri][index_ci] == 'K')
	{
		King_shape(row, col, clr, x);
	}
	else if (B[index_ri][index_ci] == 'G' || B[index_ri][index_ci] == 'g')
	{
		Gold_general_shape(row, col, clr, x);
	}
	else if (B[index_ri][index_ci] == 'S' || B[index_ri][index_ci] == 's')
	{
		Silver_general_shape(row, col, clr, x);
	}
	else if (B[index_ri][index_ci] == 'N' || B[index_ri][index_ci] == 'n')
	{
		Night_shape(row, col, clr, x);
	}
	else if (B[index_ri][index_ci] == 'l' || B[index_ri][index_ci] == 'L')
	{
		Lance_shape(row, col, clr, x);
	}
	else if (B[index_ri][index_ci] == 'b' || B[index_ri][index_ci] == 'B')
	{
		Bishop_shape(row, col, clr, x);
	}
	else if (B[index_ri][index_ci] == 'R' || B[index_ri][index_ci] == 'r')
	{
		Rook_shape(row, col, clr, x);
	}
	else if (B[index_ri][index_ci] == 'P' || B[index_ri][index_ci] == 'p')
	{
		Pawn_shape(row, col, clr, x);
	}
	else
	{
		SetClr(clr);
		gotoRowCol(row, col); cout << " ";
	}
}
void circle(int c_x, int c_y, int& r, char x) {
	float p_row = 0, p_col = 0;

	for (int th = 0; th < 360; th++)
	{
		float rad = th * (3.14 / 180);
		p_row = ceil(r * sin(rad)) + c_y;
		p_col = ceil(r * cos(rad)) + c_x;
		SetClr(10);
		gotoRowCol(p_row, p_col);
		cout << x;
	}
}

void print_Box_1(char** B, bool** hl_array, int row, int col, int start_row, int start_col, int end_row, int end_col, int clr,bool hl_turn)
{
	char x = -37;
	int r=4 ;
	for (int i = 0; i < end_row; i++)
	{
		for (int j = 0; j < end_col; j++)
		{
			SetClr(clr);
			gotoRowCol(start_row + i,start_col + j);
			cout << x;
		}
	}
	int c = 0;
	if (clr == 8)
	{
		
		if (B[row][col] >= 'A' && B[row][col] <= 'Z')
		{
			c = 142;
		}
		else
		{
			c = 128;
		}
		print_pieces_shape(B, row, col, start_row + (end_row / 2),start_col + (end_col / 2), c, -37);
		if (hl_turn == true && hl_array[row][col] == true )
		{
			circle((start_col + (end_col / 2) - 1), (start_row + (end_row / 2)) - 1, r, x);
		}
		
	}
	else
	{
		if (B[row][col] >= 'A' && B[row][col] <= 'Z')
		{
			c = 126;
		}
		else
		{
			c = 112;
		}
		//SetClr(112);
		print_pieces_shape(B, row,col,start_row + (end_row / 2), start_col + (end_col / 2),c, -37);
		if (hl_turn == true && hl_array[row][col] == true )
		{
			circle((start_col + (end_col / 2)) - 1, (start_row + (end_row / 2)) - 1, r, x);
		}
	}
}
void print_Box_small(int start_row, int start_col, int end_row, int end_col, int clr,int print_piece_turn,p_count white,p_count black)
{
	char x = -37;
	int c = 0;
	int p_row = 0, p_col = 0;
	
	for (int k = 0; k < 2; k++)
	{
		for (int i = 0; i < end_row; i++)
		{
			for (int j = 0; j < end_col; j++)
			{
				int ri, ci;
				if (k == 0)
				{
					ri = start_row + i;
					ci = start_col + j;
				}
				if (k == 1)
				{
					ri = start_row + i;
					ci = (start_col + j)+30;
				}
				SetClr(clr);
				gotoRowCol(ri,ci);
				cout << x;
			}
		}
		if (clr == 8)
		{
			if (k == 0)
			{
				c = 142;
				p_row = start_row + (end_row / 2);
				p_col = start_col + (end_col / 2);
			}
			if (k == 1)
			{
				c = 128;
				p_row = start_row + (end_row / 2);
				p_col = (start_col + (end_col / 2)) + 30;
			}
			if (print_piece_turn == 1)
			{
				Pawn_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout <<"--> " << white.Pawn_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Pawn_c;
				}
			}
			else if (print_piece_turn == 2)
			{
				Bishop_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Bishop_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Bishop_c;
				}
			}
			else if (print_piece_turn == 3)
			{
				Lance_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Lance_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Lance_c;
				}
			}
			else if (print_piece_turn == 4)
			{
				Rook_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Rook_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Rook_c;
				}
			}
			else if (print_piece_turn == 5)
			{
				Silver_general_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Silv_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Silv_c;
				}
			}
			else if (print_piece_turn == 6)
			{
				Gold_general_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Gold_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Gold_c;
				}
			}
			else if (print_piece_turn == 7)
			{
				Night_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Nite_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Nite_c;
				}
			}
		}
		else
		{
		//print_pieces_shape(B, row, col, start_row + (end_row / 2), start_col + (end_col / 2), c, -37);
			
			
			if (k == 0)
			{
				c = 126;
				p_row = start_row + (end_row / 2);
				p_col = start_col + (end_col / 2);
			}
			if (k == 1)
			{
				c = 112;
				p_row = start_row + (end_row / 2);
				p_col = (start_col + (end_col / 2)) + 30;
			}
			if (print_piece_turn == 1)
			{
				Pawn_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Pawn_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Pawn_c;
				}
			}
			else if (print_piece_turn == 2)
			{
				Bishop_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Bishop_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Bishop_c;
				}
			}
			else if (print_piece_turn == 3)
			{
				Lance_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Lance_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Lance_c;
				}
			}
			else if (print_piece_turn == 4)
			{
				Rook_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Rook_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Rook_c;
				}
			}
			else if (print_piece_turn == 5)
			{
				Silver_general_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Silv_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Silv_c;
				}
			}
			else if (print_piece_turn == 6)
			{
				Gold_general_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Gold_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Gold_c;
				}
			}
			else if (print_piece_turn == 7)
			{
				Night_shape(p_row, p_col, c, -37);
				if (k == 0)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << white.Nite_c;
				}
				if (k == 1)
				{
					gotoRowCol(p_row, p_col + 9);
					SetClr(10);
					cout << "--> " << black.Nite_c;
				}
			}
			

		}
	}
		
}
void replay_button(int start_row, int start_col, int end_row, int end_col, int clr,char x=-37)
{
	for (int i = 0; i < end_row; i++)
	{
		for (int j = 0; j < end_col; j++)
		{
			int ri, ci;
			SetClr(clr);
			gotoRowCol(start_row+i, start_col+j); 
			cout << x;
		}
	}
	gotoRowCol((start_row + 9 / 2), (start_col + 9 / 2)-2);
	SetClr(4);
	cout << "Replay";
}
void print_Board_1(char** B, bool** hl_array, int dimension, int B_row, int B_col,bool hl_turn, char *White_placer,char* Black_placer,p_count white,p_count black)
{
	
	int count = 0,clr=7;
	for (int ri = 0; ri < dimension; ri++) 
	{
		for (int ci = 0; ci < dimension; ci++) 
		{
			print_Box_1(B,hl_array,ri,ci,ri*B_row,ci*B_col,B_row,B_col,clr,hl_turn);
			count = (count + 1) % 2;
			if (count == 1) 
			{
				clr = 8;
			}
			else
			{
				clr = 7;
			}
		}
	}
	SetClr(15);
	gotoRowCol(5,(3*175/4)-30);
	cout << "White PLacer Board";
	gotoRowCol(5, (3 * 175 / 4));
	cout << "Black PLacer Board";
	for (int i = 0; i < 7; i++)
	{
		if (i % 2 == 0)
		{
			clr = 8;
		}
		else
		{
			clr = 7;
		}
		print_Box_small((i * 7) + 7, (3 * 175 / 4) - 25, 7, 7, clr, i + 1,white,black);
	}
	
	replay_button((3 * screen_rows / 4) + 17, (3 * screen_cols / 4) + 30,9,9,10);
	SetClr(15);

}
bool Horizontal_move_determiner(int pick_posy, int drop_posy) 
{
	if (pick_posy == drop_posy) 
	{
		return true;
	}
	return false;

}
bool Verticle_move_determiner(int pick_posx, int drop_posx)
{
	if (pick_posx == drop_posx)
	{
		return true;
	}
	return false;

}
int abso(int& x) 
{
	if (x < 0)
	{
		x = (x * -1);
	}
	else
	{
		x = x;
	}
	return x;
}
bool  Diagnol_move_determiner(int pick_y, int pick_x, int drop_y, int drop_x)
{
	int y = pick_y - drop_y;
	int delta_row = abso(y);
	int x = pick_x - drop_x;
	int delta_col = abso(x);
	if (delta_row == delta_col)
	{
		return true;
	}
	return false;
}
//____________________Outhenticators________________________
bool verticle_move_otheticator(char**B,position pick,position drop)
{
	int start_point = 0, end_point = 0; 
	if (pick.posy < drop.posy)
	{
		start_point = pick.posy;
		end_point = drop.posy;
	}
	else
	{
		start_point = drop.posy;
		end_point = pick.posy;
	}
	for (int check = start_point + 1; check < end_point; check++)
	{
		if (B[check][pick.posx] != '_')
		{
			return false;
		}
	}
	return true;

}
bool Horizontal_move_otheticator(char** B, position pick, position drop)
{
	int start_point = 0, end_point = 0; 
	if (pick.posx < drop.posx)
	{
		start_point = pick.posx;
		end_point = drop.posx;
	}
	else
	{
		start_point = drop.posx;
		end_point = pick.posx;
	}
	for (int check = start_point+1; check < end_point; check++)
	{
		if (B[pick.posy][check] != '_')
		{
			return false;
		}
	}
	return true;
}
bool Diagnal_move_checker_1(char **B,position pick,position drop) // from top left to bottom right and vice versa
{
	int strt_row = 0, strt_col = 0,end_row=0,end_col=0;
	int difference = 0;
	if (pick.posy < drop.posy)
	{
		difference = (drop.posy - pick.posy)-1;
		strt_row = pick.posy+1;
		strt_col = pick.posx + 1;
	}
	else
	{
		difference = (pick.posy - drop.posy)-1;
		strt_row = drop.posy + 1;
		strt_col = drop.posx + 1;
	}
	for (int i = 0; i < difference; i++)
	{
		if (B[strt_row + i][strt_col + i] != '_')
		{
			return false;
		}
	}
	return true;
}
bool Diagnal_move_checker_2(char** B, position pick, position drop) // from top right to bottom left and vice versa
{
	int strt_row = 0, strt_col = 0, end_row = 0, end_col = 0;
	int difference = 0;
	if (pick.posy < drop.posy)
	{
		difference = (drop.posy - pick.posy) - 1;
		strt_row = pick.posy + 1;
		strt_col = pick.posx - 1;
	}
	else
	{
		difference = (pick.posy - drop.posy) - 1;
		strt_row = drop.posy + 1;
		strt_col = drop.posx - 1;
	}
	for (int i = 0; i < difference; i++)
	{
		if (B[strt_row + i][strt_col - i] != '_')
		{
			return false;
		}
	}
	return true;
}
//------------------------- Movelegalities of all pieces----------------
bool Rook_legality(char **B,position pick,position drop) 
{
	if (Verticle_move_determiner(pick.posx, drop.posx))
	{
		return verticle_move_otheticator(B, pick, drop);
	}
	if (Horizontal_move_determiner(pick.posy, drop.posy))
	{
		return Horizontal_move_otheticator(B, pick, drop);
	}
	else
	{
		return false;
	}
}
bool Bishop_legality(char**B,position pick,position drop) 
{
	if (Diagnol_move_determiner(pick.posy, pick.posx, drop.posy, drop.posx)) 
	{
		if ((pick.posx < drop.posx && pick.posy < drop.posy) || (pick.posx > drop.posx && pick.posy > drop.posy))
		{
			return Diagnal_move_checker_1(B, pick, drop);
		}
		if ((pick.posx < drop.posx && pick.posy > drop.posy) || (pick.posx > drop.posx && pick.posy < drop.posy))
		{
			return Diagnal_move_checker_2(B, pick, drop);
		}
	}
	else 
	{
		return false;
	}
}
bool King_legality(char** B, position pick, position drop)
{
	if (Diagnol_move_determiner(pick.posy, pick.posx, drop.posy, drop.posx) && (pick.posx == (drop.posx - 1) || drop.posx == (pick.posx - 1))) 
	{
		if ((pick.posx < drop.posx && pick.posy < drop.posy) || (pick.posx > drop.posx && pick.posy > drop.posy))
		{
			return Diagnal_move_checker_1(B, pick, drop);
		}
		if ((pick.posx < drop.posx && pick.posy > drop.posy) || (pick.posx > drop.posx && pick.posy < drop.posy))
		{
			return Diagnal_move_checker_2(B, pick, drop);
		}
	}
	else if(Verticle_move_determiner(pick.posx, drop.posx)&&(pick.posy==(drop.posy-1)|| drop.posy == (pick.posy - 1)))
	{
		return verticle_move_otheticator(B, pick, drop);
	}
	else if(Horizontal_move_determiner(pick.posy, drop.posy)&&(pick.posx== (drop.posx - 1)|| drop.posx == (pick.posx - 1)))
	{
		return Horizontal_move_otheticator(B, pick, drop);
	}
	else
	{
		return false;
	}
}
bool Golden_general_white(char** B, position pick, position drop)
{
	if (Diagnol_move_determiner(pick.posy, pick.posx, drop.posy, drop.posx) && (pick.posx == (drop.posx - 1) || drop.posx == (pick.posx - 1))) 
	{
		if ((pick.posx > drop.posx && pick.posy > drop.posy))
		{
			return Diagnal_move_checker_1(B, pick, drop);
		}
		if ((pick.posx < drop.posx && pick.posy > drop.posy))
		{
			return Diagnal_move_checker_2(B, pick, drop);
		}
	}
	else if(Verticle_move_determiner(pick.posx, drop.posx)&&(pick.posy==(drop.posy-1)|| drop.posy == (pick.posy - 1)))
	{
		return verticle_move_otheticator(B, pick, drop);
	}
	else if(Horizontal_move_determiner(pick.posy, drop.posy)&&(pick.posx== (drop.posx - 1)|| drop.posx == (pick.posx - 1)))
	{
		return Horizontal_move_otheticator(B, pick, drop);
	}
	return false;
	

}
bool Golden_general_black(char** B, position pick, position drop)
{
	if (Diagnol_move_determiner(pick.posy, pick.posx, drop.posy, drop.posx) && (pick.posx == (drop.posx - 1) || drop.posx == (pick.posx - 1)))
	{
		if ((pick.posx < drop.posx && pick.posy < drop.posy))
		{
			return Diagnal_move_checker_1(B, pick, drop);
		}
		if ((pick.posx > drop.posx && pick.posy < drop.posy))
		{
			return Diagnal_move_checker_2(B, pick, drop);
		}
	}
	else if (Verticle_move_determiner(pick.posx, drop.posx) && (pick.posy == (drop.posy - 1) || drop.posy == (pick.posy - 1)))
	{
		return verticle_move_otheticator(B, pick, drop);
	}
	else if (Horizontal_move_determiner(pick.posy, drop.posy) && (pick.posx == (drop.posx - 1) || drop.posx == (pick.posx - 1)))
	{
		return Horizontal_move_otheticator(B, pick, drop);
	}
	return false;


}
bool Silver_general_white(char** B, position pick, position drop)
{
	if (Diagnol_move_determiner(pick.posy, pick.posx, drop.posy, drop.posx) && (pick.posx == (drop.posx - 1) || drop.posx == (pick.posx - 1)))
	{
		if ((pick.posx < drop.posx && pick.posy < drop.posy) || (pick.posx > drop.posx && pick.posy > drop.posy))
		{
			return Diagnal_move_checker_1(B, pick, drop);
		}
		if ((pick.posx < drop.posx && pick.posy > drop.posy) || (pick.posx > drop.posx && pick.posy < drop.posy))
		{
			return Diagnal_move_checker_2(B, pick, drop);
		}
	}
	else if (Verticle_move_determiner(pick.posx, drop.posx) && (pick.posy == (drop.posy - 1) || drop.posy == (pick.posy - 1)))
	{
		if (pick.posy > drop.posy) {
			return verticle_move_otheticator(B, pick, drop);
		}
	}
	return false;
}
bool Silver_general_black(char** B, position pick, position drop)
{
	if (Diagnol_move_determiner(pick.posy, pick.posx, drop.posy, drop.posx) && (pick.posx == (drop.posx - 1) || drop.posx == (pick.posx - 1)))
	{
		if ((pick.posx < drop.posx && pick.posy < drop.posy) || (pick.posx > drop.posx && pick.posy > drop.posy))
		{
			return Diagnal_move_checker_1(B, pick, drop);
		}
		if ((pick.posx < drop.posx && pick.posy > drop.posy) || (pick.posx > drop.posx && pick.posy < drop.posy))
		{
			return Diagnal_move_checker_2(B, pick, drop);
		}
	}
	else if (Verticle_move_determiner(pick.posx, drop.posx) && (pick.posy == (drop.posy - 1) || drop.posy == (pick.posy - 1)))
	{
		if (pick.posy < drop.posy) {
			return verticle_move_otheticator(B, pick, drop);
		}
	}
	return false;
}
bool Lance_white(char** B, position pick, position drop)
{
	if (Verticle_move_determiner(pick.posx, drop.posx)&&(pick.posy>drop.posy))
	{
		return verticle_move_otheticator(B, pick, drop);
	}
	return false;
}
bool Lance_black(char** B, position pick, position drop)
{
	if (Verticle_move_determiner(pick.posx, drop.posx) && (pick.posy < drop.posy))
	{
		return verticle_move_otheticator(B, pick, drop);
	}
	return false;
}
bool Pown_white(char** B, position pick, position drop)
{
	if (Verticle_move_determiner(pick.posx, drop.posx) && (pick.posy==(drop.posy+1)))
	{
		return verticle_move_otheticator(B, pick, drop);
	}
	return false;
}
bool Pown_Black(char** B, position pick, position drop)
{
	if (Verticle_move_determiner(pick.posx, drop.posx) && (pick.posy == (drop.posy - 1)))
	{
		return verticle_move_otheticator(B, pick, drop);
	}
	return false;
}

bool White_Knight(char** B, position pick, position drop)
{
	if ((pick.posy-2) == drop.posy && (pick.posx == (drop.posx - 1) || pick.posx == (drop.posx + 1))) {

		return true;
	}
	return false;
}
bool black_Knight(char** B, position pick, position drop)
{
	if (((pick.posy+2) == (drop.posy)) && (pick.posx == (drop.posx - 1) || pick.posx == (drop.posx + 1))) {

		return true;
	}
	return false;
}
//_________________________________________________

bool Move_Legality(char** B, position pick, position drop) // For all pieces.
{
	if (B[pick.posy][pick.posx] == 'R' || B[pick.posy][pick.posx] == 'r')
	{
		return Rook_legality(B, pick, drop); 
	}
	if (B[pick.posy][pick.posx] == 'B' || B[pick.posy][pick.posx] == 'b') 
	{
		return Bishop_legality(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 'K' || B[pick.posy][pick.posx] == 'k') 
	{
		return King_legality(B,pick,drop);
	}
	if (B[pick.posy][pick.posx] == 'G')
	{
		return Golden_general_white(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 'g')
	{
		return Golden_general_black(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 'S')
	{
		return Silver_general_white(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 's')
	{
		return Silver_general_black(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 'L')
	{
		return Lance_white(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 'l')
	{
		return Lance_black(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 'p')
	{
		return Pown_Black(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 'P')
	{
		return Pown_white(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 'N')
	{
		return White_Knight(B, pick, drop);
	}
	if (B[pick.posy][pick.posx] == 'n')
	{
		return black_Knight(B, pick, drop);
	}

}

// if a piece is promoted it will give the moves of his promoted state other wise it will only run move legality function
bool promotion(char** B, position pick, position drop, bool promotion)
{
	// created a decoy array....

	
	if (promotion == true && (B[pick.posy][pick.posx] == 'N' || B[pick.posy][pick.posx] == 'S' || B[pick.posy][pick.posx] == 'L' || B[pick.posy][pick.posx] == 'P'))
	{
		return Golden_general_white(B, pick, drop);
	}
	else if (promotion == true && (B[pick.posy][pick.posx] == 'n' || B[pick.posy][pick.posx] == 's' || B[pick.posy][pick.posx] == 'l' || B[pick.posy][pick.posx] == 'p'))
	{
		return Golden_general_black(B, pick, drop);
	}
	else if (promotion == true && (B[pick.posy][pick.posx] == 'R' || B[pick.posy][pick.posx] == 'r'))
	{
		return(King_legality(B, pick, drop) || Rook_legality(B, pick, drop));
	}
	else if(promotion == true && (B[pick.posy][pick.posx] == 'B' || B[pick.posy][pick.posx] == 'b'))
	{
		return(King_legality(B, pick, drop) || Bishop_legality(B, pick, drop));
	}
	else
	{
		return Move_Legality(B, pick, drop);

	}

}
bool piece_promotion_identifier(char** B,int **nB, bool* prom_white, bool* prom_black, position pick)
{          // for white pieces
	if (B[pick.posy][pick.posx] == 'B' && nB[pick.posy][pick.posx] == 7)
	{
		return prom_white[7];
	}
	if (B[pick.posy][pick.posx] == 'N' && nB[pick.posy][pick.posx] == 4)
	{
		return prom_white[4];
	}
	if (B[pick.posy][pick.posx] == 'N' && nB[pick.posy][pick.posx] == 1)
	{
		return prom_white[1];
	}
	if (B[pick.posy][pick.posx] == 'L' && nB[pick.posy][pick.posx] == 5)
	{
		return prom_white[5];
	}
	if (B[pick.posy][pick.posx] == 'L' && nB[pick.posy][pick.posx] == 0)
	{
		return prom_white[0];
	}
	if (B[pick.posy][pick.posx] == 'R' && nB[pick.posy][pick.posx] == 6)
	{
		return prom_white[6];
	}
	if (B[pick.posy][pick.posx] == 'S' && nB[pick.posy][pick.posx] == 3)
	{
		return prom_white[3];
	}
	if (B[pick.posy][pick.posx] == 'S' && nB[pick.posy][pick.posx] == 2)
	{
		return prom_white[2];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 8)
	{
		return prom_white[8];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 9)
	{
		return prom_white[9];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 10)
	{
		return prom_white[10];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 11)
	{
		return prom_white[11];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 12)
	{
		return prom_white[12];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 13)
	{
		return prom_white[13];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 14)
	{
		return prom_white[14];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 15)
	{
		return prom_white[15];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 16)
	{
		return prom_white[16];
	}
	  // ________
	if (B[pick.posy][pick.posx] == 'B' && nB[pick.posy][pick.posx]==24)
	{
		return prom_white[24];
	}
	if (B[pick.posy][pick.posx] == 'N' && nB[pick.posy][pick.posx] == 21)
	{
		return prom_white[21];
	}
	if (B[pick.posy][pick.posx] == 'N' && nB[pick.posy][pick.posx] == 18)
	{
		return prom_white[18];
	}
	if (B[pick.posy][pick.posx] == 'L' && nB[pick.posy][pick.posx] == 22)
	{
		return prom_white[22];
	}
	if (B[pick.posy][pick.posx] == 'L' && nB[pick.posy][pick.posx] == 17)
	{
		return prom_white[17];
	}
	if (B[pick.posy][pick.posx] == 'R' && nB[pick.posy][pick.posx] == 23)
	{
		return prom_white[23];
	}
	if (B[pick.posy][pick.posx] == 'S' && nB[pick.posy][pick.posx] ==20)
	{
		return prom_white[20];
	}
	if (B[pick.posy][pick.posx] == 'S' && nB[pick.posy][pick.posx] == 19)
	{
		return prom_white[19];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 25)
	{
		return prom_white[25];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 26)
	{
		return prom_white[26];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 27)
	{
		return prom_white[27];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 28)
	{
		return prom_white[28];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 29)
	{
		return prom_white[29];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 30)
	{
		return prom_white[30];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 31)
	{
		return prom_white[31];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 32)
	{
		return prom_white[32];
	}
	if (B[pick.posy][pick.posx] == 'P' && nB[pick.posy][pick.posx] == 33)
	{
		return prom_white[33];
	}
	            // for black pieces
	if (B[pick.posy][pick.posx] == 'b' && nB[pick.posy][pick.posx] == 7)
	{
		return prom_black[7];
	}
	if (B[pick.posy][pick.posx] == 'n' && nB[pick.posy][pick.posx] == 4)
	{
		return prom_black[4];
	}
	if (B[pick.posy][pick.posx] == 'n' && nB[pick.posy][pick.posx] == 1)
	{
		return prom_black[1];
	}
	if (B[pick.posy][pick.posx] == 'l' && nB[pick.posy][pick.posx] == 5)
	{
		return prom_black[5];
	}
	if (B[pick.posy][pick.posx] == 'l' && nB[pick.posy][pick.posx] == 0)
	{
		return prom_black[0];
	}
	if (B[pick.posy][pick.posx] == 'r' && nB[pick.posy][pick.posx] == 6)
	{
		return prom_black[6];
	}
	if (B[pick.posy][pick.posx] == 's' && nB[pick.posy][pick.posx] == 3)
	{
		return prom_black[3];
	}
	if (B[pick.posy][pick.posx] == 's' && nB[pick.posy][pick.posx] == 2)
	{
		return prom_black[2];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 8)
	{
		return prom_black[8];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 9)
	{
		return prom_black[9];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 10)
	{
		return prom_black[10];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 11)
	{
		return prom_black[11];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 12)
	{
		return prom_black[12];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 13)
	{
		return prom_black[13];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 14)
	{
		return prom_black[14];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 15)
	{
		return prom_black[15];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 16)
	{
		return prom_black[16];
	}
	  //_____________
	if (B[pick.posy][pick.posx] == 'b' && nB[pick.posy][pick.posx] == 24)
	{
		return prom_black[24];
	}
	if (B[pick.posy][pick.posx] == 'n' && nB[pick.posy][pick.posx] == 21)
	{
		return prom_black[21];
	}
	if (B[pick.posy][pick.posx] == 'n' && nB[pick.posy][pick.posx] == 18)
	{
		return prom_black[18];
	}
	if (B[pick.posy][pick.posx] == 'l' && nB[pick.posy][pick.posx] == 22)
	{
		return prom_black[22];
	}
	if (B[pick.posy][pick.posx] == 'l' && nB[pick.posy][pick.posx] == 17)
	{
		return prom_black[17];
	}
	if (B[pick.posy][pick.posx] == 'r' && nB[pick.posy][pick.posx] == 23)
	{
		return prom_black[23];
	}
	if (B[pick.posy][pick.posx] == 's' && nB[pick.posy][pick.posx] == 20)
	{
		return prom_black[20];
	}
	if (B[pick.posy][pick.posx] == 's' && nB[pick.posy][pick.posx] == 19)
	{
		return prom_black[19];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 25)
	{
		return prom_black[25];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 26)
	{
		return prom_black[26];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 27)
	{
		return prom_black[27];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 28)
	{
		return prom_black[28];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 29)
	{
		return prom_black[29];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 30)
	{
		return prom_black[30];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 31)
	{
		return prom_black[31];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 32)
	{
		return prom_black[32];
	}
	if (B[pick.posy][pick.posx] == 'p' && nB[pick.posy][pick.posx] == 33)
	{
		return prom_black[33];
	}
	
}
position King_finder(char** B, int Dimension, int turn_t)
{
	position King_coordinate;
	char Kng;
	if (turn_t == white)
	{
		Kng = 'K';

	}
	else
	{
		Kng = 'k';
	}
	for (int i = 0; i < Dimension; i++)
	{
		for (int j = 0; j < Dimension; j++)
		{
			if (Kng==B[i][j])
			{
				King_coordinate.posx = j;
				King_coordinate.posy = i;
				return King_coordinate;
			}

		}
	}
}
bool self_check_algorithm(char** &B, int**nB,position &KingInCheck_coordinates,int dimension, int turn_t, bool promotion_ID,bool*prom_white,bool*prom_black)
{
	position King_coordinates;
	

	King_coordinates = King_finder(B, dimension, turn_t);
	KingInCheck_coordinates.posx = King_coordinates.posx;
	KingInCheck_coordinates.posy = King_coordinates.posy;

	turn_change(turn_t);

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			position pick;
			pick.posx = j, pick.posy = i;
			if (pick_is_valid(B, pick.posx, pick.posy, dimension, turn_t)  )
			{
				promotion_ID=piece_promotion_identifier(B,nB,prom_white,prom_black,pick);
				if (promotion(B, pick, King_coordinates, promotion_ID)) {
					bool x = true;
					//  Deleting the created decoy_array after the purpose is fulfilled
						// To avoid memory leaks
					for (int i = 0; i < dimension; i++)
					{
						delete[]B[i];
					}
					delete[]B;
					return x;
				}
			}

		}
	}
	turn_change(turn_t);
	for (int i = 0; i < dimension; i++)
	{
		delete[]B[i];
	}
	delete[]B;
	return false;
}
// This will turn the dezired move in a duplicate array and it will judge weather that move causes the check on the players king or not 
bool checker(char**B,int**nB,position &KingInCheck_coordinates,int dimension,position pick, position drop,int turn_t,bool promotion_ID,int check_turn,bool*prom_white,bool*prom_black)
{
	char** decoy_b;
	int** ndecoy_b;
	decoy_b = new char* [dimension];
	ndecoy_b = new int* [dimension];
	for (int i = 0; i < dimension; i++)
	{
		decoy_b[i] = new char[dimension];
		ndecoy_b[i] = new int[dimension];
	}
	//____
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			decoy_b[i][j] = B[i][j];
			ndecoy_b[i][j] = nB[i][j];
		}
	}               // Making the move on the decoy array and checking safety of King
	move_placer(decoy_b, pick.posx, pick.posy, drop.posx, drop.posy);
	move_placer_int(ndecoy_b, pick.posx, pick.posy, drop.posx, drop.posy);
	return self_check_algorithm(decoy_b,ndecoy_b,KingInCheck_coordinates,dimension,turn_t,promotion_ID,prom_white,prom_black);
}
   
// Makes record of promotion in bool array.
void promotion_giver(char**B,int**nB,int y,int x,bool*&prom_white, bool*& prom_black)
{
	       //______ for white pieces__________
	if (B[y][x] == 'B' && nB[y][x] == 7 && y <= 2) // B:24
	{
		prom_white[7] = true; // 7-->27
	}
	else if (B[y][x] == 'N' && nB[y][x] == 4 && y <= 2) // N:21
	{
		prom_white[4] = true; //4,24 
	}
	else if (B[y][x] == 'N' && nB[y][x] == 1 && y >= 6) // N :18
	{
		prom_white[1] = true; // 21, 1
	}
	else if (B[y][x] == 'L' && nB[y][x] == 5 && y <= 2)// L:22
	{
		prom_white[5] = true;//25,5
	}
	else if (B[y][x] == 'L' && nB[y][x] == 0 && y <= 2) // L:17
	{
		prom_white[0] = true;
	}
	else if (B[y][x] == 'S' && nB[y][x] == 3 && y <= 2) // S:3
	{
		prom_white[3] = true;
	}
	else if (B[y][x] == 'S' && nB[y][x] == 2 && y <= 2)// S:2
	{
		prom_white[2] = true;
	}
	else if (B[y][x] == 'R' && nB[y][x] == 6 && y <= 2)// S:2
	{
		prom_white[6] = true;
	}
	
	else if (B[y][x] == 'P' && nB[y][x] == 8 && y <= 2)
	{
		prom_white[8] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 9 && y <= 2)
	{
		prom_black[9] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 10 && y <= 2)
	{
		prom_white[10] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 11 && y <= 2)
	{
		prom_white[11] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 12 && y <= 2)
	{
		prom_white[12] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 13 && y <= 2)
	{
		prom_white[13] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 14 && y <= 2)
	{
		prom_white[14] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 15 && y <= 2)
	{
		prom_white[15] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 16 && y <= 2)
	{
		prom_white[16] = true;
	}
	          //__________
	if (B[y][x] == 'B'&& nB[y][x]==24 && y <= 2) // B:7
	{
		prom_white[24] = true;
	}
	else if (B[y][x] == 'N'&& nB[y][x] == 21 && y <= 2) // N:4
	{
		prom_white[21] = true;
	}
	else if (B[y][x] == 'N' && nB[y][x] == 18 && y <= 2) // N :1
	{
		prom_white[18] = true;
	}
	else if (B[y][x] == 'L' && nB[y][x] == 22 && y <= 2)// L:5
	{
		prom_white[22] = true;
	}
	else if (B[y][x] == 'L' && nB[y][x] == 17 && y <= 2) // L:0
	{
		prom_white[17] = true;
	}
	else if (B[y][x] == 'S' && nB[y][x] == 20 && y <= 2) // S:3
	{
		prom_white[20] = true;
	}
	else if (B[y][x] == 'S' && nB[y][x] == 19 && y <= 2) // S:3
	{
		prom_white[19] = true;
	}
	else if (B[y][x] == 'R' && nB[y][x] == 23 && y <= 2)// S:2
	{
		prom_white[23] = true;
	}                     // 9 Pawns of white 
	else if (B[y][x] == 'P' && nB[y][x] == 25 && y <= 2) 
	{
		prom_white[25] = true;
	}       
	else if (B[y][x] == 'P' && nB[y][x] == 26 && y <= 2)
	{
		prom_white[26] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 27 && y <= 2)
	{
		prom_white[27] = true;
	}
	else if (B[y][x] == 'P' && nB[y][x] == 28 && y <= 2)
	{
		prom_white[28] = true;
	}
	 else if (B[y][x] == 'P' && nB[y][x] == 29 && y <= 2)
	{
		prom_white[29] = true;
	} 
	 else if (B[y][x] == 'P' && nB[y][x] == 30 && y <= 2)
	{
		prom_white[30] = true;
	}
	 else if (B[y][x] == 'P' && nB[y][x] == 31 && y <= 2)
	{
		prom_white[31] = true;
	}
	 else if (B[y][x] == 'P' && nB[y][x] == 32 && y <= 2)
	{
		prom_white[32] = true;
	}
	 else if (B[y][x] == 'P' && nB[y][x] == 33 && y <= 2)
	{
		prom_white[33] = true;
	}
	
	     //______ for black pieces__________
	if (B[y][x] == 'b' && nB[y][x] == 7 && y >= 6) // B:24
	{
		prom_black[7] = true; // 7-->27
	}
	else if (B[y][x] == 'n' && nB[y][x] == 4 && y >= 6) // N:21
	{
		prom_black[4] = true; //4,24 
	}
	else if (B[y][x] == 'n' && nB[y][x] == 1 && y >= 6) // N :18
	{
		prom_black[1] = true; // 21, 1
	}
	else if (B[y][x] == 'l' && nB[y][x] == 5 && y >= 6)// L:22
	{
		prom_black[5] = true;//25,5
	}
	else if (B[y][x] == 'l' && nB[y][x] == 0 && y >= 6) // L:17
	{
		prom_black[0] = true;
	}
	else if (B[y][x] == 's' && nB[y][x] == 3 && y >= 6) // S:3
	{
		prom_black[3] = true;
	}
	else if (B[y][x] == 's' && nB[y][x] == 2 && y >= 6)// S:2
	{
		prom_black[2] = true;
	}
	else if (B[y][x] == 'r' && nB[y][x] == 6 && y >= 6)// S:2
	{
		prom_black[6] = true;
	}
	             // 9 Pawns of black          (Values and index in black are by diiference of 20)
	else if (B[y][x] == 'p' && nB[y][x] == 8 && y >= 6)
	{
		prom_black[8] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 9 && y >= 6)
	{
		prom_black[9] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 10 && y >= 6)
	{
		prom_black[10] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 11 && y >= 6)
	{
		prom_black[11] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 12 && y >= 6)
	{
		prom_black[12] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 13 && y >= 6)
	{
		prom_black[13] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 14 && y >= 6)
	{
		prom_black[14] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 15 && y >= 6)
	{
		prom_black[15] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 16 && y >= 6)
	{
		prom_black[16] = true;
	}
	      //_______________________________________-
	if (B[y][x] == 'b' && nB[y][x] == 24 && y >= 6) // B:7
	{
		prom_black[24] = true;
	}
	else if (B[y][x] == 'n' && nB[y][x] == 21 && y >= 6) // N:4
	{
		prom_black[21] = true;
	}
	else if (B[y][x] == 'n' && nB[y][x] == 18 && y >= 6) // N :1
	{
		prom_black[18] = true;
	}
	else if (B[y][x] == 'l' && nB[y][x] == 22 && y >= 6)// L:5
	{
		prom_black[22] = true;
	}
	else if (B[y][x] == 'l' && nB[y][x] == 17 && y >= 6) // L:0
	{
		prom_black[17] = true;
	}
	else if (B[y][x] == 's' && nB[y][x] == 20 && y >= 6) // S:3
	{
		prom_black[20] = true;
	}
	else if (B[y][x] == 's' && nB[y][x] == 19 && y >= 6) // S:3
	{
		prom_black[19] = true;
	}
	else if (B[y][x] == 'r' && nB[y][x] == 23 && y >= 6)// S:2
	{
		prom_black[23] = true;
	}                     
	else if (B[y][x] == 'p' && nB[y][x] == 25 && y >= 6)
	{
		prom_black[25] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 26 && y >= 6)
	{
		prom_black[26] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 27 && y >= 6)
	{
		prom_black[27] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 28 && y >= 6)
	{
		prom_black[28] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 29 && y >= 6)
	{
		prom_black[29] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 30 && y >= 6)
	{
		prom_black[30] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 31 && y >= 6)
	{
		prom_black[31] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 32 && y >= 6)
	{
		prom_black[32] = true;
	}
	else if (B[y][x] == 'p' && nB[y][x] == 33 && y >= 6)
	{
		prom_black[33] = true;
	}
}

//_________________________________________________
//_____________________________________


void highlighted_board(char** B, position pick, char x, int turn_t, int count, bool promotion_ID,bool hl_turn, char*White_placer, char*Black_placer, p_count white,p_count black)
{   // making a 2D bool array....
	
	bool** hl_array;
	hl_array = new bool* [9];
	for (int i = 0; i < 9; i++)
	{
		hl_array[i] = new bool[9];
	}
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			position drop;
			drop.posx = j;
			drop.posy = i;
			if (promotion(B,pick,drop,promotion_ID) && drop_is_valid(B, drop.posx, drop.posy, in_Box_dimension, turn_t))
			{
				hl_array[i][j] = true; // highlight array
			}
			else
			{
				hl_array[i][j] = false;
			}
		}
	}
	print_Board_1(B, hl_array, 9, in_Box_dimension, in_Box_dimension,hl_turn, White_placer, Black_placer,white, black); //char** B, bool** hl_array, int dimension, int B_row, int B_col,bool hl_turn
	
}
char small_To_Capital(char x)
{
	char y = char(x - 32);
	return y;
}
char Capital_To_small(char x)
{
	char y = char(x+32);
	return y;
}
            // For placing piece from board to captured pieces array.
void capturedPiece_placer(char* &White_placer,bool* &prom_white, bool* &prom_black,char* &Black_placer,int *&nWhite_placer, int*& nBlack_placer,char piece,int npiece)
{
	int index = 0;
	if (piece >= 'a' && piece <= 'z')
	{
		prom_black[npiece] = false;
		piece = small_To_Capital(piece);
		for (index = 0; White_placer[index]!='_'; index++)
		{
			if (index == 18)
			{
				index = 0;
			}
		}
		White_placer[index] = piece;
		nWhite_placer[index] = npiece;
		return;
	}
	else if (piece >= 'A' && piece <= 'Z')
	{
		prom_white[npiece] = false;
		piece = Capital_To_small(piece);
		for (index = 0; index < 19 && Black_placer[index] != '_'; index++)
		{
			if (index == 18)
			{
				index = 0;
			}
		}
		Black_placer[index] = piece;
		nBlack_placer[index] = npiece;
		return;
	}
}
  // Not only places move on the board put also picks the capture piece and hands it over to placer board
void move_placer_pro(char** arr,int **nB,bool*prom_white,bool*prom_black ,int x_pic, int y_pic, int x_drop, int y_drop, char* &White_placer, char* &Black_placer, int*& nWhite_placer,int*& nBlack_placer)
{                                  // not using & here (awain nhi kar rha bas marzi meri)
	char piece = arr[y_drop][x_drop];
	arr[y_drop][x_drop] = arr[y_pic][x_pic];
	arr[y_pic][x_pic] = '_';
	int npiece = nB[y_drop][x_drop];
	nB[y_drop][x_drop] = nB[y_pic][x_pic];
	nB[y_pic][x_pic] = -5;
	if (piece!='_') {

		capturedPiece_placer(White_placer,prom_white,prom_black ,Black_placer,nWhite_placer,nBlack_placer, piece,npiece);
	}
}
bool Drop_piece_signal(position pick)
{
	if ((pick.posx >= (board_dimension) || pick.posy >= (board_dimension))&& (pick.posx<16 && pick.posy<9))
	{
		return true;
	}
	return false;
}
bool Replay_signal(position pick)
{
	if (pick.posx >= 16 && pick.posy >= 9)
	{
		return true;
	}
	return false;
}
bool is_capturedPick_valid(char p_piece,int turn_t, char* White_placer,char *Black_placer)
{
	int count = 0;
	if (turn_t == 0 && (p_piece >= 'A' && p_piece <= 'Z') && p_piece != 'K')
	{
		for (int i = 0; i < 19; i++)
		{
			if (p_piece == White_placer[i])
			{
				return  true;
			}
		}
		return false;
	
	}

	// Black player black piece (represented by small letters) chose kara ga
	else if (turn_t == 1 && (p_piece >= 'a' && p_piece <= 'z') && p_piece != 'k')
	{
		for (int i = 0; i < 19; i++)
		{
			if (p_piece == Black_placer[i])
			{
				return  true;
			}
		}
		return false;
	}
	else
	{
		return false;
	}
}
bool drop_is_validPro(char** B, int x, int y, int dimension, int turn_t,bool drop_signal,char pieceTo_drop)
{
	if (drop_signal == false)
	{
		if (!drop_is_valid(B, x, y, dimension, turn_t))
		{
			return false;
		}
		else
		{
			return true;
		}
	}
	if (drop_signal == true)
	{
		if (drop_is_valid(B, x, y, dimension, turn_t) && B[y][x] == '_') 
		{
			if ((pieceTo_drop == 'L') && (y == 0)) // Ya piece wo piece ha jo hum ma pick kia ha or drop karna lga han.
			{
				return false;
			}
			else if ((pieceTo_drop == 'l') && (y == 8)) // Ya piece wo piece ha jo hum ma pick kia ha or drop karna lga han.
			{
				return false;
			}
			else if ((pieceTo_drop == 'N') && (y <= 1)) // Ya piece wo piece ha jo hum ma pick kia ha or drop karna lga han.
			{
				return false;
			}
			else if ((pieceTo_drop == 'n') && (y >= 7)) // Ya piece wo piece ha jo hum ma pick kia ha or drop karna lga han.
			{
				return false;
			}
			else if ((pieceTo_drop == 'P' && (y <= 7)) && (pieceTo_drop == 'P'&&B[y - 1][x] == 'k'))
			{
				return false;
			}                    // There is a mistake here
			else if ((pieceTo_drop == 'p' && (y >= 7)) && (pieceTo_drop == 'p' && B[y + 1][x] == 'K'))
			{
				return false;
			}
			else
			{
				return true;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}
void CapturedPiece_to_boardPlacer(char** &B,int**& nB,char* &White_placer,char* &Black_placer,int*&nWhite_placer,int*& nBlack_placer,char piece,position drop)
{
	int index = 0;
	if (piece >= 'a' && piece <= 'z')
	{
		while (Black_placer[index] != piece)
		{
			index++;
		}
		Black_placer[index] = '_';
		B[drop.posy][drop.posx] = piece;
		nB[drop.posy][drop.posx] = nBlack_placer[index];
		nBlack_placer[index] = -5;

	}
	else
	{
		while (White_placer[index] != piece)
		{
			index++;
		}
		White_placer[index] = '_';
		B[drop.posy][drop.posx] = piece;
		nB[drop.posy][drop.posx] = nWhite_placer[index];
		nWhite_placer[index] = -5;
	}

}
bool Check_mate_extension(char**decoy_arr,int**ndecoy_arr,bool*prom_white,bool*prom_black ,position KingInCheck_coordiantes,int dimension,position &drop,position pick,bool promotion_ID,int turn_t,int check_turn)
{
	//bool ck;

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j< dimension; j++)
		{
			drop.posx = j; drop.posy=i;                   // decoy array ki number array bhi nhajni ha    
			promotion_ID = piece_promotion_identifier(decoy_arr, ndecoy_arr, prom_white, prom_black, pick);
			if (promotion(decoy_arr, pick, drop, promotion_ID) && drop_is_valid(decoy_arr,drop.posx,drop.posy,dimension,turn_t))
			{
				
				if (!checker(decoy_arr, ndecoy_arr, KingInCheck_coordiantes, dimension, pick, drop, turn_t, promotion_ID, check_turn, prom_white, prom_black))
				{
					return false;
				}
				
			}
		}
	}
	return true;
}
bool Check_mate(char** B, int** nB,position KingInCheck_coordiantes,int dimension, int turn_t, bool promotion_ID, int check_turn, bool* prom_white, bool* prom_black)
{
	char piece;
	position pick, drop;
	char** decoy_arr;
	int** ndecoy_arr;
	bool x;
	decoy_arr = new char* [dimension];
	ndecoy_arr = new int* [dimension];
	for (int i = 0; i < dimension; i++)
	{
		decoy_arr[i] = new char[dimension];
		ndecoy_arr[i] = new int[dimension];
	}
	//____
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			decoy_arr[i][j] = B[i][j];
			ndecoy_arr[i][j] = nB[i][j];
		}
	}               // Making the move on the decoy array and checking safety of King
	for (int ri = 0; ri < dimension; ri++)
	{
		for (int ci = 0; ci < dimension; ci++)
		{
			//piece = B[ri][ci];
			pick.posx = ci; pick.posy = ri;
			if (is_piecePick_valid(B,ci,ri,turn_t))
			{
				x = Check_mate_extension(decoy_arr, ndecoy_arr, prom_white, prom_black, KingInCheck_coordiantes, dimension, drop, pick, promotion_ID, turn_t, check_turn);
				     // Agr check khatam ho gia is ka matlab check mate abhi nhi lga.
				if (x == false)
				{
					return x;
				}
			}
		}
	}
	return true;
}
void piece_occurance_checker(char * white_placer,char*black_placer,p_count& white,p_count&black)
{                // for white pieces
	white.Pawn_c=0, white.Bishop_c = 0,white.Silv_c = 0, white.Gold_c = 0,white.Lance_c=0,white.Nite_c=0,white.Rook_c=0;
	             // for black pieces 
	black.Pawn_c = 0, black.Bishop_c= 0, black.Silv_c= 0, black.Gold_c = 0, black.Nite_c = 0,black.Lance_c = 0, black.Rook_c = 0;
	for (int i = 0; i < 19; i++)
	{
		// For white pieces
		if (white_placer[i] == 'P')
		{
			white.Pawn_c++;
		}
		if (white_placer[i] == 'B')
		{
			white.Bishop_c++;
		}
		if (white_placer[i] == 'S')
		{
			white.Silv_c++;
		}
		if (white_placer[i] == 'G')
		{
			white.Gold_c++;
		}
		if (white_placer[i] == 'L')
		{
			white.Lance_c++;
		}
		if (white_placer[i] == 'R')
		{
			white.Rook_c++;
		}
		if (white_placer[i] == 'N')
		{
			white.Nite_c++;
		}
		// For black pieces
		if (black_placer[i] == 'p')
		{
			black.Pawn_c++;
		}
		if (black_placer[i] == 'b')
		{
			black.Bishop_c++;
		}
		if (black_placer[i] == 's')
		{
			black.Silv_c++;
		}
		if (black_placer[i] == 'g')
		{
			black.Gold_c++;
		}
		if (black_placer[i] == 'l')
		{
			black.Lance_c++;
		}
		if (black_placer[i] == 'r')
		{
			black.Rook_c++;
		}
		if (black_placer[i] == 'n')
		{
			black.Nite_c++;
		}
	}
}
void replay_array_loader(brd_decoy*& arr, int& read_arr_index, int turn_t, char** B, int** nB, bool* prom_white, bool* prom_black, char* White_placer, int* nWhite_placer, char* Black_placer, int* nBlack_placer)
{
	arr[read_arr_index].turn_t = turn_t;
	// cretaing 2d arrays(decoys) for B and nB
	arr[read_arr_index].B = new char* [board_dimension];
	arr[read_arr_index].nB = new int* [board_dimension];
	for (int i = 0; i < board_dimension; i++)
	{
		arr[read_arr_index].B[i] = new char[board_dimension];
		arr[read_arr_index].nB[i] = new int[board_dimension];

	}
	// Initializing decoy B and nB with values
	for (int i = 0; i < board_dimension; i++)
	{
		for (int j = 0; j < board_dimension; j++)
		{
			arr[read_arr_index].B[i][j] = B[i][j];
			arr[read_arr_index].nB[i][j] = nB[i][j];
		}
	}
	// intializing decoy promtion record arrays
	for (int i = 0; i < 34; i++)
	{
		arr[read_arr_index].prom_white[i] = prom_white[i];
		arr[read_arr_index].prom_black[i] = prom_black[i];
	}
	// Initializing decoy placer boards
	for (int i = 0; i < 19; i++)
	{
		arr[read_arr_index].White_placer[i] = White_placer[i];
		arr[read_arr_index].nWhite_placer[i] = nWhite_placer[i];
		arr[read_arr_index].Black_placer[i] = Black_placer[i];
		arr[read_arr_index].nBlack_placer[i] = nBlack_placer[i];
	}
	read_arr_index++;
}
void replayer(brd_decoy*& arr, int& read_arr_index, int &turn_t, char** &B, int** &nB, bool* &prom_white, bool* &prom_black, char* &White_placer, int* &nWhite_placer, char* &Black_placer, int* &nBlack_placer)
{
	read_arr_index--;
	turn_t=arr[read_arr_index].turn_t ;
	for (int i = 0; i < board_dimension; i++)
	{
		for (int j = 0; j < board_dimension; j++)
		{
			B[i][j] =arr[read_arr_index].B[i][j] ;
			nB[i][j] =arr[read_arr_index].nB[i][j];
		}
	}
	    // Since it is created every time in replay_array_loader we have to destroy every time
	for (int i = 0; i < board_dimension; i++)
	{
		delete[]arr[read_arr_index].B[i];
		delete[]arr[read_arr_index].nB[i];

	}
	delete[]arr[read_arr_index].B;
	delete[]arr[read_arr_index].nB;
	    // Transferring promotion arrays back
	for (int i = 0; i < 34; i++)
	{
		prom_white[i] = arr[read_arr_index].prom_white[i];
		prom_black[i]=arr[read_arr_index].prom_black[i] ;
	}
	   // Transferring placer boards back 
	for (int i = 0; i < 19; i++)
	{
		White_placer[i]=arr[read_arr_index].White_placer[i];
		nWhite_placer[i]=arr[read_arr_index].nWhite_placer[i];
		Black_placer[i]=arr[read_arr_index].Black_placer[i];
		nBlack_placer[i]=arr[read_arr_index].nBlack_placer[i];
	}
	
}


void save_load(int turn_t,string* Player_names,char ** B,int ** nB, bool*prom_white, bool* prom_black,char*White_placer,int *nWhite_placer,char*Black_placer,int *nBlack_placer)
{
	ofstream rite("save file.txt");
	rite << turn_t;
	rite << endl;
	rite << Player_names[0];
	rite << endl;
	rite << Player_names[1];
	rite << endl;
	for (int i = 0; i < board_dimension; i++)
	{
		for (int j = 0; j < board_dimension; j++)
		{
			rite << B[i][j];
		}
		rite << endl;
	}
	for (int i = 0; i < board_dimension; i++)
	{
		for (int j = 0; j < board_dimension; j++)
		{
			rite << nB[i][j] << " ";
		}
		rite << endl;
	}
	// Transferring promotion arrays towards saved file
	for (int i = 0; i < 34; i++)
	{
		rite << prom_white[i] << " ";

	}
	rite << endl;
	for (int i = 0; i < 34; i++)
	{
		rite << prom_black[i] << " ";

	}
	rite << endl;
	// Transferring Placer arrays to saved file
	for (int i = 0; i < 19; i++)
	{
		rite << White_placer[i] << " ";
	}
	rite << endl;
	for (int i = 0; i < 19; i++)
	{
		rite << nWhite_placer[i] << " ";
	}
	rite << endl;
	for (int i = 0; i < 19; i++)
	{
		rite << Black_placer[i] << " ";
	}
	rite << endl;
	for (int i = 0; i < 19; i++)
	{
		rite << nBlack_placer[i] << " ";
	}
}

int main()
{
	gotoRowCol((100 / 2)-5, (175 / 3) - 5);
	cout << "Welcome to Shougi made By 'MUHAMMAD AHMAD'";
	gotoRowCol(100/2,(175/3)-15);
	cout<<">>_ My dimensions are 'Width= 175 and Height= 100' and 'Raster font (8x8)' "<<endl<<endl;
	char** B = 0;
	int** nB = 0;
	// prom_white contains prmotion bools of [B,N,L,P,R,S] respectively.... (if the piece is promoted it's respective index will have value true otherwise false)
	   // same goes for prom_black
	bool* prom_white; 
	bool* prom_black;
	prom_white = new bool[34]{false};
	prom_black = new bool[34]{false};
	int NOP = 0, dimension = 0, turn_t = 0, count = 0, check_turn = 0;
	bool promotion_id = 0,y;
	position pick, drop, White_king_c, black_king_c;
	position KingInCheck_coordinates;
	string Player_names[2];
	bool** hl_array=new bool*[1], hl_turn;
	hl_array[0] = new bool(false);
	string mode;
	gotoRowCol((100 / 2)+2, (175 / 3)-15);
	cout << ">>_ Do you want to load the saved game or just want to run a new one ('Y' for Saved 'N' for New) ";
	cin >> mode;
	p_count white;
	p_count black;
	int x = 1,pre_ch,pre_h;
	//______ 19spots pieces ka lia or 20th spot \0 ka lia (according to indexes)
	    //  King cannot be captured (king ka baghar 19 pieces han)
	char* White_placer = new char[20]{'\0'}; // Jab white, black ka koi piece capture kara ga to wo is pa aa jai ga! 
	  int* nWhite_placer = new int[20] ;
	  nWhite_placer[19] = -5;
	char* Black_placer = new char[20] {'\0'}; // Jab black, white ka koi piece capture kara ga to wo is pa aa jai ga!
	  int* nBlack_placer = new int[20] ;
	  nBlack_placer[19] = -5;
	for (int i = 0; i < 19; i++)
	{
		White_placer[i] = '_';
		Black_placer[i] = '_';
		nWhite_placer[i] = -5;
		nBlack_placer[i] = -5;
	}
	bool drop_signal, z, replay_signal;
	char p_piece='_';
	string *str_turn=new string[2]{ "White", "Black" };
	brd_decoy* arr = new brd_decoy[600]{0};
	int read_arr_index = 0;
	init(mode, B, nB, turn_t,dimension, Player_names, NOP, prom_white, prom_black,White_placer,nWhite_placer,Black_placer,nBlack_placer);
	//______
	system("cls");
	hl_turn = false;
	piece_occurance_checker(White_placer, Black_placer, white, black);
	print_Board_1(B,hl_array,dimension, in_Box_dimension, in_Box_dimension,hl_turn, White_placer, Black_placer, white, black); 
	
	
	while (true)
	{
		gotoRowCol((3 * 100 / 4) + 18, (175 / 3) - 10);
		msg(Player_names[turn_t]);
		do{
			do
			{
				do
				{
					do
					{
						replay_signal = false;
						
						SelectPosi(pick, in_Box_dimension, in_Box_dimension,pre_ch,pre_h);///
						drop_signal=Drop_piece_signal(pick);
						if (drop_signal == false)
						{
							replay_signal = Replay_signal(pick);
							if (replay_signal == true)
							{
								if(read_arr_index!=0)
								{
								
									replayer(arr, read_arr_index, turn_t, B, nB, prom_white, prom_black, White_placer, nWhite_placer, Black_placer, nBlack_placer);
									piece_occurance_checker(White_placer, Black_placer, white, black);
									print_Board_1(B, hl_array, dimension, in_Box_dimension, in_Box_dimension, hl_turn, White_placer, Black_placer, white, black);
									save_load(turn_t, Player_names, B, nB, prom_white, prom_black, White_placer, nWhite_placer, Black_placer, nBlack_placer);
									gotoRowCol((3 * 100 / 4) + 20, (175 / 3) - 10);
									cout << "                                      ";
									continue;
								}
								else
								{
									gotoRowCol((3 * 100 / 4) + 20,(175 / 3) - 10);
									cout << "You have reached your replay limit!!!";
								}
								
							}
						}
						if (drop_signal == true)
						{
							
							bool check;
							do {
								gotoRowCol((3 * 100 / 4) + 17, (175 / 3) - 10);
								cout << "Which Piece You want to pick from " << str_turn[turn_t] << "'s capture board (x is termination symbol): ";
								cin >> p_piece;                      // White player white piece (represented by capital letters) chose kara ga
								gotoRowCol((3 * 100 / 4) + 17, (175 / 3) - 10);
								cout << "                                                                                                    ";// usnig spacer as an eraser
								if (p_piece == 'x')
								{
									drop_signal = false;
									break;
								}
								check = is_capturedPick_valid(p_piece,turn_t,White_placer,Black_placer);
								if (!check)
								{
									gotoRowCol((3 * 100 / 4) + 17, (175 / 3) - 10);
									cout << "    >>You picked invalid piece";
								}
							}while (!check);
							gotoRowCol((3 * 100 / 4) + 17, (175 / 3) - 10);
							cout << "                                    ";
							if(drop_signal==true)
							{
								break;
							}
							
						}

					} while (!pick_is_valid(B, pick.posx, pick.posy, dimension, turn_t));
					
					count = 1;
					if (drop_signal == false)
					{
						promotion_id = piece_promotion_identifier(B, nB,prom_white, prom_black, pick);  //char** B,int **nB, bool* prom_white, bool* prom_black, position pick
					}
					else
					{
						promotion_id = false;
					}
					hl_turn = true;
					if (drop_signal == false)///
					{
						highlighted_board(B, pick, '*', turn_t, count, promotion_id, hl_turn, White_placer, Black_placer, white, black);
					}
					//if (drop_signal == true);
					SelectPosi(drop, in_Box_dimension, in_Box_dimension, pre_ch, pre_h);///
				} while (!drop_is_validPro(B, drop.posx, drop.posy, dimension, turn_t,drop_signal,p_piece) );
				
				if (drop_signal == false)
				{
					z = promotion(B, pick, drop, promotion_id);
				}
				else
					z = true;
			} while (!z);
			check_turn = 0;
			if (drop_signal == false)
			{
				y = checker(B, nB,KingInCheck_coordinates,dimension, pick, drop, turn_t, promotion_id, check_turn, prom_white, prom_black);///
				if (y == true)
				{
					if (Check_mate(B, nB, KingInCheck_coordinates, dimension, turn_t, promotion_id, check_turn, prom_white, prom_black))
					{
						system("cls");
						gotoRowCol((100 / 2), (175 / 2) - 18);
						SetClr(4);
						cout << "'" << Player_names[turn_t] << "' lost because he is in check_mate";
						SetClr(15);
						_getch();
						return 0;
					}
					else
					{
						gotoRowCol((3 * 100 / 4) - 5, (3 * 175 / 4) - 25);
						SetClr(4);
						cout << Player_names[turn_t] << " is in check!!!!!!!!!!!!!!!!!" ;
						SetClr(15);
					}
					
				}
			}
			else
			{
				y = false;
			}
		}while(y);
		gotoRowCol((3 * 100 / 4) - 5, (3 * 175 / 4) - 25);
		cout <<"                                     ";
		if (read_arr_index >= 0 || pick_is_valid(B, pick.posx, pick.posy, dimension, turn_t))
		{
			replay_array_loader(arr, read_arr_index, turn_t, B, nB, prom_white, prom_black, White_placer, nWhite_placer, Black_placer, nBlack_placer);
		}
		if (drop_signal==false ) 
		{
			move_placer_pro(B, nB,prom_white,prom_black ,pick.posx, pick.posy, drop.posx, drop.posy, White_placer, Black_placer,nWhite_placer,nBlack_placer);
		}
		else
		{
			CapturedPiece_to_boardPlacer(B,nB,White_placer,Black_placer,nWhite_placer,nBlack_placer,p_piece,drop);// char** &B,int**& nB,char* &White_placer,char* &Black_placer,int*&nWhite_placer,int*& nBlack_placer,char piece,position drop
		}
		if (drop_signal == false)
		{
			promotion_giver(B, nB,drop.posy, drop.posx, prom_white, prom_black); //char**B,int**nB,int y,int x,bool*&prom_white, bool*& prom_black
		}
		drop_signal = false;
		hl_turn = false;
		if (replay_signal == false)
		{
			piece_occurance_checker(White_placer, Black_placer, white, black);
			
			print_Board_1(B, hl_array, dimension, in_Box_dimension, in_Box_dimension, hl_turn, White_placer, Black_placer, white, black);
	        turn_change(turn_t);
			save_load(turn_t,Player_names,B,nB,prom_white,prom_black,White_placer,nWhite_placer,Black_placer,nBlack_placer);
		}
		
	
	}
	    
	return 0;
}
