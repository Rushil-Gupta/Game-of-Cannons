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
			opp_soldiers = 3 *()
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
				if(board[sq_x-1][sq_y-1] == val)''
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
	bool is_attack_on_retreat_possible(int x, int y, int player, int val){
		if(x < board.size() && y < board[0].size()){
			if(board[x][y] == val){
				return (is_opponent_adjacent(x,y,(-1*val),player))
			}
			else
				return false;
		}
		else
			return false;
	}
	bool canSquarebeAttacked(int sq_x, int sq_y, int val, int player){
		if(player == 1){
			if(is_opponent_adjacent(sq_x, sq_y,(-1*val),1))
				return true;
			if(is_attack_on_retreat_possible(sq_x-2,sq_y-2,1, (-1*val)) || is_attack_on_retreat_possible(sq_x, sq_y-2,1, (-1*val)) || is_attack_on_retreat_possible(sq_x+2, sq_y-2,1, (-1*val)))
				return true;
		}
		else{
			if(is_opponent_adjacent(sq_x, sq_y, (-1*val),2))
				return true;
			if(is_attack_on_retreat_possible(sq_x-2,sq_y+2,2, (-1*val)) || is_attack_on_retreat_possible(sq_x, sq_y+2,2, (-1*val)) || is_attack_on_retreat_possible(sq_x+2, sq_y+2,2, (-1*val)))
				return true;
		}
		if(check_cannon(sq_x-2,sq_y+2, (-1*val), "LBD") && board[sq_x-1][sq_y+1] == 0)
				return true;
		if(check_cannon(sq_x-3,sq_y+3, (-1*val), "LBD") && board[sq_x-2][sq_y+2] == 0)
			return true;
		if(check_cannon(sq_x+2,sq_y+2, (-1*val), "RBD") && board[sq_x+1][sq_y+1] == 0)
			return true;
		if(check_cannon(sq_x+3,sq_y+3, (-1*val), "RBD") && board[sq_x+2][sq_y+2] == 0)
			return true;
		if(check_cannon(sq_x-2,sq_y-2, (-1*val), "LUD") && board[sq_x-1][sq_y-1] == 0)
			return true;
		if(check_cannon(sq_x-3,sq_y-3, (-1*val), "LUD") && board[sq_x-2][sq_y-2] == 0)
			return true;
		if(check_cannon(sq_x+2,sq_y-2, (-1*val), "RUD") && board[sq_x+1][sq_y-1] == 0)
			return true;
		if(check_cannon(sq_x+3,sq_y-3, (-1*val), "RUD") && board[sq_x+2][sq_y-2] == 0)
			return true;
		if(check_cannon(sq_x-2,sq_y, (-1*val), "LH") && board[sq_x-1][sq_y] == 0)
			return true;
		if(check_cannon(sq_x-3,sq_y, (-1*val), "LH") && board[sq_x-2][sq_y] == 0)
			return true;
		if(check_cannon(sq_x+2,sq_y, (-1*val), "RH") && board[sq_x+1][sq_y] == 0)
			return true;
		if(check_cannon(sq_x+3,sq_y, (-1*val), "RH") && board[sq_x+2][sq_y] == 0)
			return true;
		if(check_cannon(sq_x,sq_y+2, (-1*val), "BV") && board[sq_x][sq_y+1] == 0)
			return true;
		if(check_cannon(sq_x,sq_y+3, (-1*val), "BV") && board[sq_x][sq_y+2] == 0)
			return true;
		if(check_cannon(sq_x,sq_y-2, (-1*val), "UV") && board[sq_x][sq_y-1] == 0)
			return true;
		if(check_cannon(sq_x,sq_y-3, (-1*val), "UV") && board[sq_x][sq_y-2] == 0)
			return true;
		return false;
	}

	int waysToAttackSquare(int sq_x, int sq_y, int val, int player){
		int count = 0;
		if(player == 1){
			if(is_opponent_adjacent(sq_x, sq_y,(-1*val),1))
				count++;
			if(is_attack_on_retreat_possible(sq_x-2,sq_y-2,1, (-1*val)) || is_attack_on_retreat_possible(sq_x, sq_y-2,1, (-1*val)) || is_attack_on_retreat_possible(sq_x+2, sq_y-2,1, (-1*val)))
				count++;
		}
		else{
			if(is_opponent_adjacent(sq_x, sq_y, (-1*val),2))
				count++;
			if(is_attack_on_retreat_possible(sq_x-2,sq_y+2,2, (-1*val)) || is_attack_on_retreat_possible(sq_x, sq_y+2,2, (-1*val)) || is_attack_on_retreat_possible(sq_x+2, sq_y+2,2, (-1*val)))
				count++;
		}
		if(check_cannon(sq_x-2,sq_y+2, (-1*val), "LBD") && board[sq_x-1][sq_y+1] == 0)
			count++;
		if(check_cannon(sq_x-3,sq_y+3, (-1*val), "LBD") && board[sq_x-2][sq_y+2] == 0)
			count++;
		if(check_cannon(sq_x+2,sq_y+2, (-1*val), "RBD") && board[sq_x+1][sq_y+1] == 0)
			count++;
		if(check_cannon(sq_x+3,sq_y+3, (-1*val), "RBD") && board[sq_x+2][sq_y+2] == 0)
			count++;
		if(check_cannon(sq_x-2,sq_y-2, (-1*val), "LUD") && board[sq_x-1][sq_y-1] == 0)
			count++;
		if(check_cannon(sq_x-3,sq_y-3, (-1*val), "LUD") && board[sq_x-2][sq_y-2] == 0)
			count++;
		if(check_cannon(sq_x+2,sq_y-2, (-1*val), "RUD") && board[sq_x+1][sq_y-1] == 0)
			count++;
		if(check_cannon(sq_x+3,sq_y-3, (-1*val), "RUD") && board[sq_x+2][sq_y-2] == 0)
			count++;
		if(check_cannon(sq_x-2,sq_y, (-1*val), "LH") && board[sq_x-1][sq_y] == 0)
			count++;
		if(check_cannon(sq_x-3,sq_y, (-1*val), "LH") && board[sq_x-2][sq_y] == 0)
			count++;
		if(check_cannon(sq_x+2,sq_y, (-1*val), "RH") && board[sq_x+1][sq_y] == 0)
			count++;
		if(check_cannon(sq_x+3,sq_y, (-1*val), "RH") && board[sq_x+2][sq_y] == 0)
			count++;
		if(check_cannon(sq_x,sq_y+2, (-1*val), "BV") && board[sq_x][sq_y+1] == 0)
			count++;
		if(check_cannon(sq_x,sq_y+3, (-1*val), "BV") && board[sq_x][sq_y+2] == 0)
			count++
		if(check_cannon(sq_x,sq_y-2, (-1*val), "UV") && board[sq_x][sq_y-1] == 0)
			count++
		if(check_cannon(sq_x,sq_y-3, (-1*val), "UV") && board[sq_x][sq_y-2] == 0)
			count++
		return count;
	}

	void printState(){
		for(int i=0;i<board.size();i++){
			for(int j=0;j<board[0].size();j++){
				cout<< board[i][j] <<" ";
			}
			cout<<endl;
		}
	}

	vector<string> getValidMovesForSoldier(vector<vector<int> > board, int x, int y, int player,int val, vector<string> moves){
		if(player == 2){
			//Capture Moves
			if(x > 0){
				if(board[x-1][y] == (-1*val))
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x-1) + " " + to_string(y));
			}
			if( x < board.size()-1){
				if(board[x+1][y] == (-1*val))
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x+1) + " " + to_string(y));
			}

			//Valid Moves which may be capture or non-capture
			if(x > 0 && y >0){
				if(board[x-1][y-1] != val)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-1) + " " + to_string(y-1));
			}

			if(y >0){
				if(board[x][y-1] != val)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y-1));
			}

			if(x < board.size()-1 && y > 0){
				if(board[x+1][y-1] != val)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+1) + " " + to_string(y-1));
			}

			//Retreat Check 
			if(is_opponent_adjacent(x,y,(-1*val),2)){
				if(y <= board[0].size()-3){
					if(board[x][y+2] != val)
						moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y+2));
					if(x >= 2){
						if(board[x-2][y+2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-2) + " " + to_string(y+2));
					}
					if(x <= board.size()-3){
						if(board[x+2][y+2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+2) + " " + to_string(y+2));
					}
				}
			}			
		}
		else{
			//Capture Moves
			if(x > 0){
				if(board[x-1][y] == (-1*val))
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x-1) + " " + to_string(y));
			}
			if(x < board.size()-1){
				if(board[x+1][y] == (-1*val))
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x+1) + " " + to_string(y));
			}

			//Valid Moves which may be capture or non-capture
			if(x > 0 && y < board[0].size()-1){
				if(board[x-1][y+1] != val)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-1) + " " + to_string(y+1));
			}

			if(y < board[0].size()-1){
				if(board[x][y+1] != val)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y+1));
			}

			if(x < board.size()-1 && y +1<board[0].size()){
				if(board[x+1][y+1] != val)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+1) + " " + to_string(y+1));
			}

			//Retreat Check 
			if(is_opponent_adjacent(x,y,(-1*val),1)){
				if(y >= 2){
					if(board[x][y-2] != val)
						moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y-2));
					if(x >= 2){
						if(board[x-2][y-2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-2) + " " + to_string(y-2));
					}
					if(x <= board.size()-3){
						if(board[x+2][y-2] != val)
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
						if(board[x+2][y-2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+2) + " " + to_string(y-2));			
					}
					if(x+3 < board.size() && y-3 >= 0){
						if(board[x+3][y-3] != val)
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
						if(board[x][y-2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x) + " " + to_string(y-2));			
					}
					if(y-3 >= 0){
						if(board[x][y-3] != val)
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
						if(board[x-2][y-2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-2) + " " + to_string(y-2));			
					}
					if(x-3 >= 0 && y-3 >= 0){
						if(board[x-3][y-3] != val)
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
						if(board[x-2][y] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-2) + " " + to_string(y));			
					}
					if(x-3 >= 0){
						if(board[x-3][y] != val)
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
						if(board[x-2][y+2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-2) + " " + to_string(y+2));			
					}
					if(x-3 >= 0 && y+3 <= board[0].size()){
						if(board[x-3][y+3] != val)
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
						if(board[x][y+2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x) + " " + to_string(y+2));			
					}
					if(y+3 <= board[0].size()){
						if(board[x][y+3] != val)
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
						if(board[x+2][y+2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+2) + " " + to_string(y+2));			
					}
					if(x+3 <= board.size() && y+3 <= board[0].size()){
						if(board[x+3][y+3] != val)
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
						if(board[x+2][y] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+2) + " " + to_string(y));			
					}
					if(x+3 <= board.size()){
						if(board[x+3][y] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+3) + " " + to_string(y));			
					}
				}		
			}
		}	
		return moves;
	}

	vector<string> getAllValidMoves(vector<vector<int> > state, int player, int val){
		vector<string> moves;
		for(int i=0; i<state.size();i++){
		 	for(int j =0; j<state[0].size();j++){
		 		if(state[i][j] == val)
		 			moves = getValidMovesForSoldier(state,i,j,player,val, moves);
		 	}
		}
		return moves;
	}

	int opp_soldiers_under_attack(vector<vector<int> > state, int val, int player){
		int count = 0;
		for(int i=0; i<state.size();i++){
			for(int j=0; j<state[0].size();j++){
				if(state[i][j] == (-1*val))
					count += canSquarebeAttacked(i,j,(-1* val), player);
			}
		}
		return count;
	}

	vector<int> opp_tower_attacks_possible(vector<vector<int> > state, int val, int player){
		int n = state[0].size()-1;
		int m = state.size();
		vector<int> answer;
		if(player == 2){
			for(int i=0 ;i<m; i+= 2){
				int count = 0;
				if(val < 0)
					count = waysToAttackSquare(i,0,(-1*val),player);
				answer.push_back(count);
			}
		}
		else{
			for(int i=1 ;i<m; i+= 2){
				int count = waysToAttackSquare(i,n,(-1*val), player);
				answer.push_back(count);
			}	
		}
		return answer;
	}

	vector<vector<int> > update_state(vector<vector<int> > state, string move, int* piece_count){
		int coor[4];
		trav = 0;
		char type = '';
		for(int i=1; i<move.length(), trav < 4;i++){
			if(move[i] == ' ' && (move[i+1] != 'M' || move[i+1] != 'B')){
				int j = i+1;
				int num = 0;
				while(move[j] != ' '){
					num = num*10 + atoi(move[j]);
					j++;
				}
				coor[trav] = num;
				i = j-1;
				trav++;
			}
			else{
				type = move[i+1]
				i++;
			}
		}
		if(type == 'B'){
			if(board[coor[0]][coor[1]] == 1){
				if(board[coor[2]][coor[3]] == -1)
					piece_count[2]--;
				else if(board[coor[2]][coor[3]] == -2)
					piece_count[3]--;
				state[coor[2]][coor[3]] = 0;
			}
			else{
				if(board[coor[2]][coor[3]] == 1)
					piece_count[0]--;
				else if(board[coor[2]][coor[3]] == 2)
					piece_count[1]--;
				state[coor[2]][coor[3]] = 0;	
			}
		}
		else{
			if(board[coor[0]][coor[1]] == 1){
				if(board[coor[2]][coor[3]] == -1)
					piece_count[2]--;
				else if(board[coor[2]][coor[3]] == -2)
					piece_count[3]--;
				state[coor[2]][coor[3]] = 1;
				state[coor[0]][coor[1]] = 0;
			}
			else{
				if(board[coor[2]][coor[3]] == 1)
					piece_count[0]--;
				else if(board[coor[2]][coor[3]] == 2)
					piece_count[1]--;
				state[coor[2]][coor[3]] = -1;
				state[coor[0]][coor[1]] = 0;
			}	
		}
		return state;
	}

	int Evaluation_func(vector< vector<int> > state, int piece_count[], vector<int> weights){
	m = state.size();
	n = state[0].size();

	s1 = piece_count[0];
	s2 = piece_count[2];
	t1 = piece_count[1];
	t2 = piece_count[3];
	int target_soldier_us = 0;
	int target_tower_us = 0;
	int target_soldier_opp = 0;
	int target_tower_opp = 0;
	vector<int> target_tower_opp;
	if(player == 1){
		target_soldier_opp = opp_soldiers_under_attack(state,1,2);
		target_tower_opp = opp_tower_attacks_possible(state,1,2);
		target_soldier_us = opp_soldiers_under_attack(state,-1,1);
		target_tower_us = opp_tower_attacks_possible(state,-1,1);

	}
	else{
		target_soldier_opp = opp_soldiers_under_attack(state,1,1);
		target_tower_opp = opp_tower_attacks_possible(state,1,1);	
		target_soldier_us = opp_soldiers_under_attack(state,-1,2);
		target_tower_us = opp_tower_attacks_possible(state,-1,2);
	}
	
	int value = (s1*10) + (t1*100) - (s2*10) - (t2*100) + (target_soldier_opp*5) + (target_tower_opp*50) - (target_soldier_us*5) - (target_tower_us*50);
	return value;
}


int main(){
	Board* newGame = new Board();
	newGame->printState();
	return 0;
}
