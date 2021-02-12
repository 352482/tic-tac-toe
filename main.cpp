//+++++++++++
//Tic tac toe - A game of tic tac toe
//Andrew Hett
//2-10-2021
//------

#include <iostream>
#include <cstring>
#include <regex>

using namespace std;

void draw_board(char board[][3]){
	cout << "  1 2 3" << endl;
	for (int i=0;i<3;i++){
		cout << (char)(97+i);
		for (int o=0;o<3;o++){
			cout << " " << board[o][i];
		}
		cout << endl;
	}
}

int check_board_condition(char board[][3]){
	int return_value = 0;
	//check for a stalemate
	int filled_spaces=0;
	for (int i=0;i<3;i++){
		for (int o=0;o<3;o++){
			if (board[i][o] != ' '){
				filled_spaces++;
			}
		}
	}
	if (filled_spaces == 9){
		return_value=-1;
	}
	//check for winning rows/columns
	for (int i=0;i<3;i++){
		if (board[i][0] != ' '){
			if (board[i][0]==board[i][1]
					&& board[i][1]==board[i][2]){
				return_value=1;
				break;
			}
		}
		if (board[0][i] != ' '){
			if (board[0][i]==board[1][i]
					&& board[1][i]==board[2][i]){
				return_value=1;
				break;
			}
		}
	}
	//check for winning diagonals
	if (board[1][1] != ' '){
		if (board[0][0]==board[1][1]
				&& board[1][1]==board[2][2]){
			return_value=1;
		}
		if (board[0][2]==board[1][1]
				&& board[1][1]==board[2][0]){
			return_value=1;
		}
	}
	return return_value;
}

void clear_board(char board[][3]){
	//fill all indicies of the board with spaces
	for (int i=0;i<3;i++){
		for (int o=0;o<3;o++){
			board[i][o]=' ';
		}
	}
}

int main(){
	char board_array[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
	char current_player = 'X';
	int player_x_wins = 0, player_o_wins = 0;
	char move_buffer[100];
	//define a regular expression which matches valid coordinates
	regex coordinate_regex("[1-3][a-cA-C]");
	while (true){
		//draw the board
		draw_board(board_array);
		cout << "Player " << current_player << "'s turn. Enter move coordinates in the format (1a): ";
		bool valid_coordinates = false;
		while (!valid_coordinates){
			//reset the string in the move_buffer array
			move_buffer[0]='\0';
			cin >> move_buffer;
			//check if the selected coordinates match the specified
			//regular expression and that there are no extraneous characters
			if (regex_match(move_buffer, coordinate_regex) && strlen(move_buffer) == 2){
				//make sure the selected coordinates are not occupied
				if (board_array[((int)move_buffer[0])-48][((int)move_buffer[1])-100] == ' '){
					board_array[((int)move_buffer[0])-48][((int)move_buffer[1])-100] = current_player;
					valid_coordinates=true;
					break;
				}else{
					cout << "Invalid coordinates. Space already occupied." << endl;
					cout << "Enter move coordinates: ";
				}
			}else{
				cout << "Invalid coordinates. Enter coordinates in the format (1a): ";
			}
		}
		switch (current_player){
			case 'X':
				current_player='O';
				break;
			case 'O':
				current_player='X';
				break;
		}
		switch (check_board_condition(board_array)){
			case -1:
				//stalemate
				cout << "Stalemate." << endl;
				clear_board(board_array);
				current_player = 'X';
				cout << "Player X Wins: " << player_x_wins << endl;
				cout << "Player O Wins: " << player_o_wins << endl;
				break;
			case 1:
				//a player has won
				switch (current_player){
					case 'X':
						cout << "Player O Wins!" << endl;
						player_o_wins++;
						break;
					case 'O':
						cout << "Player X Wins!" << endl;
						player_x_wins++;
						break;
				}
				cout << "Player X Wins: " << player_x_wins << endl;
				cout << "Player O Wins: " << player_o_wins << endl;
				clear_board(board_array);
				current_player = 'X';
				break;
		}
	}
	return 0;
}
