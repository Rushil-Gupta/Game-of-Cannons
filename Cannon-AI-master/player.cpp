#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<bits/stdc++.h>
using namespace std;
class Board{
public:
	vector<vector<int> > board;
	int player = 1; // white originally
	Board(int n, int m){
			vector<int> tempVector1;
			vector<int> tempVector2;
			bool flag = false;
		if(player == 1){
			tempVector1.push_back(1);
			tempVector1.push_back(1);
			tempVector1.push_back(1);
			tempVector2.push_back(2);
			for(int i=0; i<n-4;i++){
				tempVector1.push_back(0);
				tempVector2.push_back(0);
			}
			tempVector1.push_back(-2);
			tempVector2.push_back(-1);
			tempVector2.push_back(-1);
			tempVector2.push_back(-1);
			for(int i=0; i<m; i++){
				if(!flag)
					board.push_back(tempVector2);
				else
					board.push_back(tempVector1);
				flag = !flag;
			}			
		}
		else{
			tempVector1.push_back(-1);
			tempVector1.push_back(-1);
			tempVector1.push_back(-1);
			tempVector2.push_back(-2);
			for(int i=0; i<n-4;i++){
				tempVector1.push_back(0);
				tempVector2.push_back(0);
			}
			tempVector1.push_back(2);
			tempVector2.push_back(1);
			tempVector2.push_back(1);
			tempVector2.push_back(1);
			for(int i=0; i<m; i++){
				if(!flag)
					board.push_back(tempVector2);
				else
					board.push_back(tempVector1);
				flag = !flag;
			}
		}
	}

/* Direcion dictionary:
	1) LBD - Left Diagonal below current square
	2) RBD - Right diagonal below current square
	3) LUD - Left diagonal above the square
	4) RUD - Right diagonal above the square
	5) BV - Vertical direction below the current square
	6) UV - Vertical direction above the current square
	7) RH - Horizontal direction right of current square
	8) LH - Horizontal direction left of current square
*/
	bool check_cannon(int x, int y, int val,string direction){
		if(direction.equals("LBD")){
			if(x >=2 && y <= board[0].size()-3){
				if(board[x][y] == val && board[x-1][y+1] == val && board[x-2][y+2] == val)
					return true;
			}
			return false;
		}
		if(direction.equals("RBD")){
			if(y <= board[0].size()-3 && x <= board.size()-3){
				if(board[x][y] == val && board[x+1][y+1] == val && board[x+2][y+2] == val)
					return true;
			}
			return false;
		}
		if(direction.equals("LUD")){
			if(x >= 2 && y >= 2){
				if(board[x][y] == val && board[x-1][y-1] == val && board[x-2][y-2] == val)
					return true;
			}
			return false;
		}
		if(direction.equals("RUD")){
			if(x <= board.size()-3 && y >= 2){
				if(board[x][y] == val && board[x+1][y-1] == val && board[x+2][y-2] == val)
					return true;
			}
			return false;
		}
		if(direction.equals("BV")){
			if(y <= board[0].size()-3){
				if(board[x][y] == val && board[x][y+1] == val && board[x][y+2] == val)
					return true;
			}
			return false;
		}
		if(direction.equals("UV")){
			if(y >= 2){
				if(board[x][y] == val && board[x][y-1] == val && board[x][y-2] == val)
					return true;
			}
			return false;
		}
		if(direction.equals("LH")){
			if(x >= 2){
				if(board[x][y] == val && board[x-1][y] == val && board[x-2][y] == val)
					return true;
			}
			return false;
		}
		if(direction.equals("RH")){
			if(x <= board.size()-3){
				if(board[x][y] == val && board[x+1][y] == val && board[x+2][y] == val)
					return true;
			}
			return false;
		}
		return false;
	}

	bool is_opponent_adjacent(int sq_x, int sq_y, int val, int player){
		if(sq_x > 0){
			if(board[sq_x-1][sq_y] == val)
				return true;
		}
		if(sq_x < board.size()-1){
			if(board[sq_x+1][sq_y] == val)
				return true;
		}
		if(player == 1){
			if(sq_x > 0 && sq_y < board[0].size()-1){
				if(board[sq_x-1][sq_y+1] == val)
					return true;
			}
			if(sq_y < board[0].size()-1){
				if(board[sq_x][sq_y+1] == val)
					return true;
			}
			if(sq_x < board.size()-1 && sq_y < board[0].size()-1){
				if(board[sq_x+1][sq_y+1] == val)
					return true;
			}
		}
		else{
			if(sq_x > 0 && sq_y >0){
				if(board[sq_x-1][sq_y-1] == val)
					return true;
			}
			if(sq_y >0){
				if(board[sq_x][sq_y-1] == val)
					return true;
			}
			if(sq_x < board.size()-1 && sq_y > 0){
				if(board[sq_x+1][sq_y-1] == val)
					return true;
			}	
		}
		return false;
	}
	bool is_attack_on_retreat_possible(int x, int y, int player){
		if(x < board.size() && y < board[0].size()){
			if(board[x][y] == -1){
				return (is_opponent_adjacent(x,y,1,player))
			}
			else
				return false;
		}
		else
			return false;
	}
	bool canSquarebeAttacked(int sq_x, int sq_y){
		if(player == 1){
			if(is_opponent_adjacent(sq_x, sq_y,-1,1))
				return true;
			if(check_cannon(sq_x-2,sq_y+2,-1, "LBD") && board[sq_x-1][sq_y+1] == 0)
				return true;
			if(check_cannon(sq_x-3,sq_y+3,-1, "LBD") && board[sq_x-2][sq_y+2] == 0)
				return true;
			if(check_cannon(sq_x+2,sq_y+2,-1, "RBD") && board[sq_x+1][sq_y+1] == 0)
				return true;
			if(check_cannon(sq_x+3,sq_y+3,-1, "RBD") && board[sq_x+2][sq_y+2] == 0)
				return true;
			if(check_cannon(sq_x-2,sq_y-2,-1, "LUD") && board[sq_x-1][sq_y-1] == 0)
				return true;
			if(check_cannon(sq_x-3,sq_y-3,-1, "LUD") && board[sq_x-2][sq_y-2] == 0)
				return true;
			if(check_cannon(sq_x+2,sq_y-2,-1, "RUD") && board[sq_x+1][sq_y-1] == 0)
				return true;
			if(check_cannon(sq_x+3,sq_y-3,-1, "RUD") && board[sq_x+2][sq_y-2] == 0)
				return true;
			if(check_cannon(sq_x-2,sq_y,-1, "LH") && board[sq_x-1][sq_y] == 0)
				return true;
			if(check_cannon(sq_x-3,sq_y,-1, "LH") && board[sq_x-2][sq_y] == 0)
				return true;
			if(check_cannon(sq_x+2,sq_y,-1, "RH") && board[sq_x+1][sq_y] == 0)
				return true;
			if(check_cannon(sq_x+3,sq_y,-1, "RH") && board[sq_x+2][sq_y] == 0)
				return true;
			if(check_cannon(sq_x,sq_y+2,-1, "BV") && board[sq_x][sq_y+1] == 0)
				return true;
			if(check_cannon(sq_x,sq_y+3,-1, "BV") && board[sq_x][sq_y+2] == 0)
				return true;
			if(check_cannon(sq_x,sq_y-2,-1, "UV") && board[sq_x][sq_y-1] == 0)
				return true;
			if(check_cannon(sq_x,sq_y-3,-1, "UV") && board[sq_x][sq_y-2] == 0)
				return true;
			if(is_attack_on_retreat_possible(sq_x-2,sq_y-2,1) || is_attack_on_retreat_possible(sq_x, sq_y-2,1) || is_attack_on_retreat_possible(sq_x+2, sq_y-2,1))
				return true;
		}
		else{
			if(is_opponent_adjacent(sq_x, sq_y,-1,2))
				return true;
			if(check_cannon(sq_x-2,sq_y+2,-1, "LBD") && board[sq_x-1][sq_y+1] == 0)
				return true;
			if(check_cannon(sq_x-3,sq_y+3,-1, "LBD") && board[sq_x-2][sq_y+2] == 0)
				return true;
			if(check_cannon(sq_x+2,sq_y+2,-1, "RBD") && board[sq_x+1][sq_y+1] == 0)
				return true;
			if(check_cannon(sq_x+3,sq_y+3,-1, "RBD") && board[sq_x+2][sq_y+2] == 0)
				return true;
			if(check_cannon(sq_x-2,sq_y-2,-1, "LUD") && board[sq_x-1][sq_y-1] == 0)
				return true;
			if(check_cannon(sq_x-3,sq_y-3,-1, "LUD") && board[sq_x-2][sq_y-2] == 0)
				return true;
			if(check_cannon(sq_x+2,sq_y-2,-1, "RUD") && board[sq_x+1][sq_y-1] == 0)
				return true;
			if(check_cannon(sq_x+3,sq_y-3,-1, "RUD") && board[sq_x+2][sq_y-2] == 0)
				return true;
			if(check_cannon(sq_x-2,sq_y,-1, "LH") && board[sq_x-1][sq_y] == 0)
				return true;
			if(check_cannon(sq_x-3,sq_y,-1, "LH") && board[sq_x-2][sq_y] == 0)
				return true;
			if(check_cannon(sq_x+2,sq_y,-1, "RH") && board[sq_x+1][sq_y] == 0)
				return true;
			if(check_cannon(sq_x+3,sq_y,-1, "RH") && board[sq_x+2][sq_y] == 0)
				return true;
			if(check_cannon(sq_x,sq_y+2,-1, "BV") && board[sq_x][sq_y+1] == 0)
				return true;
			if(check_cannon(sq_x,sq_y+3,-1, "BV") && board[sq_x][sq_y+2] == 0)
				return true;
			if(check_cannon(sq_x,sq_y-2,-1, "UV") && board[sq_x][sq_y-1] == 0)
				return true;
			if(check_cannon(sq_x,sq_y-3,-1, "UV") && board[sq_x][sq_y-2] == 0)
				return true;
			if(is_attack_on_retreat_possible(sq_x-2,sq_y+2,2) || is_attack_on_retreat_possible(sq_x, sq_y+2,2) || is_attack_on_retreat_possible(sq_x+2, sq_y+2,2))
				return true;
		}
		return false;
	}

	void printState(){
		for(int i=0;i<board.size();i++){
			for(int j=0;j<board[0].size();j++){
				cout<< board[i][j] <<" ";
			}
			cout<<endl;
		}
	}

	vector<string> getValidMovesForSoldier(int x, int y, int player, vector<string> moves){
		if(player == 2){
			//Capture Moves
			if(x > 0){
				if(board[x-1][y] == -1)
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x-1) + " " + to_string(y));
			}
			if( x < board.size()-1){
				if(board[x+1][y] == -1)
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x+1) + " " + to_string(y));
			}

			//Valid Moves which may be capture or non-capture
			if(x > 0 && y >0){
				if(board[x-1][y-1] != 1)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-1) + " " + to_string(y-1));
			}

			if(y >0){
				if(board[x][y-1] != 1)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y-1));
			}

			if(x < board.size()-1 && y > 0){
				if(board[x+1][y-1] != 1)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+1) + " " + to_string(y-1));
			}

			//Retreat Check 
			if(is_opponent_adjacent(x,y,-1,2)){
				if(y <= board[0].size()-3){
					if(board[x][y+2] != 1)
						moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y+2));
					if(x >= 2){
						if(board[x-2][y+2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-2) + " " + to_string(y+2));
					}
					if(x <= board.size()-3){
						if(board[x+2][y+2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+2) + " " + to_string(y+2));
					}
				}
			}			
		}
		else{
			//Capture Moves
			if(x > 0){
				if(board[x-1][y] == -1)
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x-1) + " " + to_string(y));
			}
			if(x < board.size()-1){
				if(board[x+1][y] == -1)
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x+1) + " " + to_string(y));
			}

			//Valid Moves which may be capture or non-capture
			if(x > 0 && y < board[0].size()-1){
				if(board[x-1][y+1] != 1)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-1) + " " + to_string(y+1));
			}

			if(y < board[0].size()-1){
				if(board[x][y+1] != 1)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y+1));
			}

			if(x < board.size()-1 && y +1<board[0].size()){
				if(board[x+1][y+1] != 1)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+1) + " " + to_string(y+1));
			}

			//Retreat Check 
			if(is_opponent_adjacent(x,y,-1,1)){
				if(y >= 2){
					if(board[x][y-2] != 1)
						moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y-2));
					if(x >= 2){
						if(board[x-2][y-2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-2) + " " + to_string(y-2));
					}
					if(x <= board.size()-3){
						if(board[x+2][y-2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+2) + " " + to_string(y-2));
					}
				}
			}
		}

			//cannon movement and bombing covered for possible cannons in all 8 directions
		if(check_cannon(x,y,1,"LBD")){
			if(x-3 >= 0 &&  y+3 < board[0].size()){
				if(board[x-3][y+3] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-3) + " " + to_string(y+3));
			}
			if(x+1 < board.size() && y-1 >= 0){
				if(board[x+1][y-1] == 0){
					if(x+2 < board.size() && y-2 >= 0){
						if(board[x+2][y-2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+2) + " " + to_string(y-2));			
					}
					if(x+3 < board.size() && y-3 >= 0){
						if(board[x+3][y-3] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+3) + " " + to_string(y-3));			
					}
				}		
			}
		}

		if(check_cannon(x,y,1,"BV")){
			if(y+3 < board[0].size()){
				if(board[x][y+3] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y+3));
			}
			if(y-1 >= 0){
				if(board[x][y-1] == 0){
					if(y-2 >= 0){
						if(board[x][y-2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x) + " " + to_string(y-2));			
					}
					if(y-3 >= 0){
						if(board[x][y-3] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x) + " " + to_string(y-3));			
					}
				}		
			}
		}

		if(check_cannon(x,y,1,"RBD")){
			if(x+3 <= board.size() &&  y+3 < board[0].size()){
				if(board[x+3][y+3] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+3) + " " + to_string(y+3));
			}
			if(x-1 >= 0 && y-1 >= 0){
				if(board[x-1][y-1] == 0){
					if(x-2 >= 0 && y-2 >= 0){
						if(board[x-2][y-2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-2) + " " + to_string(y-2));			
					}
					if(x-3 >= 0 && y-3 >= 0){
						if(board[x-3][y-3] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-3) + " " + to_string(y-3));			
					}
				}		
			}
		}

		if(check_cannon(x,y,1,"RH")){
			if(x+3 < board.size()){
				if(board[x+3][y] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+3) + " " + to_string(y));
			}
			if(x-1 >= 0){
				if(board[x-1][y] == 0){
					if(x-2 >= 0){
						if(board[x-2][y] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-2) + " " + to_string(y));			
					}
					if(x-3 >= 0){
						if(board[x-3][y] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-3) + " " + to_string(y));			
					}
				}		
			}
		}
		
		if(check_cannon(x,y,1,"RUD")){
			if(x+3 <= board.size() &&  y-3 >=0){
				if(board[x+3][y-3] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+3) + " " + to_string(y-3));
			}
			if(x-1 >= 0 && y+1 <= board[0].size()){
				if(board[x-1][y+1] == 0){
					if(x-2 >= 0 && y+2 <= board[0].size()){
						if(board[x-2][y+2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-2) + " " + to_string(y+2));			
					}
					if(x-3 >= 0 && y+3 <= board[0].size()){
						if(board[x-3][y+3] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-3) + " " + to_string(y+3));			
					}
				}		
			}
		}

		if(check_cannon(x,y,1,"UV")){
			if(y-3 >=0){
				if(board[x][y-3] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y-3));
			}
			if(y+1 <= board[0].size()){
				if(board[x][y+1] == 0){
					if(y+2 <= board[0].size()){
						if(board[x][y+2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x) + " " + to_string(y+2));			
					}
					if(y+3 <= board[0].size()){
						if(board[x][y+3] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x) + " " + to_string(y+3));			
					}
				}		
			}
		}

		if(check_cannon(x,y,1,"LUD")){
			if(x-3 >=0 &&  y-3 >=0){
				if(board[x-3][y-3] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-3) + " " + to_string(y-3));
			}
			if(x+1 <= board.size() && y+1 <= board[0].size()){
				if(board[x+1][y+1] == 0){
					if(x+2 <= board.size() && y+2 <= board[0].size()){
						if(board[x+2][y+2] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+2) + " " + to_string(y+2));			
					}
					if(x+3 <= board.size() && y+3 <= board[0].size()){
						if(board[x+3][y+3] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+3) + " " + to_string(y+3));			
					}
				}		
			}
		}

		if(check_cannon(x,y,1,"LH")){
			if(x-3 >=0){
				if(board[x-3][y] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-3) + " " + to_string(y));
			}
			if(x+1 <= board.size()){
				if(board[x+1][y] == 0){
					if(x+2 <= board.size()){
						if(board[x+2][y] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+2) + " " + to_string(y));			
					}
					if(x+3 <= board.size()){
						if(board[x+3][y] != 1)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+3) + " " + to_string(y));			
					}
				}		
			}
		}	
		return moves;
	}

	vector<string> getAllValidMoves(int player){
		vector<string> moves;
		for(int i=0; i<board.size();i++){
		 	for(int j =0; j<board[0].size();j++){
		 		if(board[i][j] == 1)
		 			moves = getValidMovesForSoldier(i,j,player, moves);
		 	}
		}
		return moves;
	}

int main(){
	Board* newGame = new Board();
	newGame->printState();
	return 0;
}

/*
1) If a given square can be attacked?
2) 