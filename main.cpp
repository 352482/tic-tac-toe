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

int main(){
	char board_array[3][3] = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
	char current_player = 'X';
	regex coordinate_regex("[1-3][a-cA-C]");
	while (true){
		draw_board(board_array);
		cout << "Player " << current_player << "'s turn. Enter move coordinates in the format (1a): ";
		bool valid_coordinates = false;
		char move_buffer[100];
		while (!valid_coordinates){
			move_buffer[0]='\0';
			cin >> move_buffer;
			if (regex_match(move_buffer, coordinate_regex) && strlen(move_buffer) == 2){
				valid_coordinates=true;
				break;
			}
			cout << "Invalid coordinates. Enter coordinates in the format (1a): ";
		}
		board_array[((int)move_buffer[0])-48][((int)move_buffer[1])-100] = current_player;
		switch (current_player){
			case 'X':
				current_player='O';
				break;
			case 'O':
				current_player='X';
				break;
		}
	}
	return 0;
}
