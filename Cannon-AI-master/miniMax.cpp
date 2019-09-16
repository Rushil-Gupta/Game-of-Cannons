#include <bits/stdc++.h>
#include <ctime>
using namespace std;

int move_count = 0;
int pieces_count[4];
int weights[8];
int my_player=0;
int opp_player=0;
int player = 0; 

struct Node{
	vector<vector<int> > state;
	int pieces_count[4];
	float eval=0;
	int alpha;
	int beta;
};

struct Node_prune{
	vector<vector<int> > state;
	int pieces_count[4];
	float eval;
};


// class Board{
// public:
	vector<vector<int> > board;
	// white originally
	void Board(int n, int m){
		vector<int> tempVector1;
		vector<int> tempVector2;
		bool flag = false;
		pieces_count[0] = (3*m)/2;
		pieces_count[1] = m/2;
		pieces_count[2] = (3*m)/2;
		pieces_count[3] = m/2;
		// opp_soldiers = 3 *()
		if(player == 1){
			cerr << "Yo!" << endl;
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
		if(direction.compare("LBD")==0){
			if(x >=2 && y <= board[0].size()-3){
				if(board[x][y] == val && board[x-1][y+1] == val && board[x-2][y+2] == val)
					return true;
			}
			return false;
		}
		if(direction.compare("RBD")==0){
			if(y <= board[0].size()-3 && x <= board.size()-3){
				if(board[x][y] == val && board[x+1][y+1] == val && board[x+2][y+2] == val)
					return true;
			}
			return false;
		}
		if(direction.compare("LUD")==0){
			if(x >= 2 && y >= 2){
				if(board[x][y] == val && board[x-1][y-1] == val && board[x-2][y-2] == val)
					return true;
			}
			return false;
		}
		if(direction.compare("RUD")==0){
			if(x <= board.size()-3 && y >= 2){
				if(board[x][y] == val && board[x+1][y-1] == val && board[x+2][y-2] == val)
					return true;
			}
			return false;
		}
		if(direction.compare("BV")==0){
			if(y <= board[0].size()-3){
				if(board[x][y] == val && board[x][y+1] == val && board[x][y+2] == val)
					return true;
			}
			return false;
		}
		if(direction.compare("UV")==0){
			if(y >= 2){
				if(board[x][y] == val && board[x][y-1] == val && board[x][y-2] == val)
					return true;
			}
			return false;
		}
		if(direction.compare("LH")==0){
			if(x >= 2){
				if(board[x][y] == val && board[x-1][y] == val && board[x-2][y] == val)
					return true;
			}
			return false;
		}
		if(direction.compare("RH")==0){
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

	bool is_attack_on_retreat_possible(int x, int y, int player, int val){
		if(x < board.size() && y < board[0].size()){
			if(board[x][y] == val){
				return (is_opponent_adjacent(x,y,(-1*val),player));
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
			count++;
		if(check_cannon(sq_x,sq_y-2, (-1*val), "UV") && board[sq_x][sq_y-1] == 0)
			count++;
		if(check_cannon(sq_x,sq_y-3, (-1*val), "UV") && board[sq_x][sq_y-2] == 0)
			count++;
		return count;
	}

	void printState(vector<vector<int> > board){
		for(int i=0;i<board[0].size();i++){
			for(int j=0;j<board.size();j++){
				cerr<< board[j][i] <<" ";
			}
			cerr<<endl;
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
		int trav = 0;
		char type;
		//cerr<<move.length()<<endl;
		for(int i=1; i<move.length();i++){
			if(move[i] == ' ' && (move[i+1] != 'M' && move[i+1] != 'B')){
				int j = i+1;
				int num = 0;
				while(j < move.length()){
					//cerr << move[j] << endl;
					if(move[j] == ' ')
						break;
					num = num*10 + (int)(move[j]-'0');
					j++;
				}
				coor[trav] = num;
				//cerr << j << endl;
				if(j == move.length())
					break;
				i = j-1;
				trav++;
				if(trav == 4)
					break;
			}
			else{
				type = move[i+1];
				i++;
			}
		}
		//cerr << type << endl;
		if(type == 'B'){
			if(state[coor[0]][coor[1]] == 1){
				if(state[coor[2]][coor[3]] == -1)
					piece_count[2]--;
				else if(state[coor[2]][coor[3]] == -2)
					piece_count[3]--;
				state[coor[2]][coor[3]] = 0;
			}
			else{
				if(state[coor[2]][coor[3]] == 1)
					piece_count[0]--;
				else if(state[coor[2]][coor[3]] == 2)
					piece_count[1]--;
				state[coor[2]][coor[3]] = 0;	
			}
		}
		else{
			if(state[coor[0]][coor[1]] == 1){
				if(state[coor[2]][coor[3]] == -1)
					piece_count[2]--;
				else if(state[coor[2]][coor[3]] == -2)
					piece_count[3]--;
				state[coor[2]][coor[3]] = 1;
				//cerr << " lag ja gale" << endl;
				state[coor[0]][coor[1]] = 0;
			}
			else{
				if(state[coor[2]][coor[3]] == 1)
					piece_count[0]--;
				else if(state[coor[2]][coor[3]] == 2)
					piece_count[1]--;
				state[coor[2]][coor[3]] = -1;
				state[coor[0]][coor[1]] = 0;
			}	
		}
		//cerr << "Chal ja be" << endl;
		return state;
	}

	int Evaluation_func(vector< vector<int> > state, int piece_count[], int* weights){
		// int m = state.size();
		// int n = state[0].size();

		int s1 = piece_count[0];
		int s2 = piece_count[2];
		int t1 = piece_count[1];
		int t2 = piece_count[3];
		int target_soldier_us = 0;
		int target_soldier_opp = 0;
		vector<int> target_tower_opp;
		vector<int> target_tower_us;
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
		
		int value = (s1*10) + (t1*100) - (s2*10) - (t2*100) + (target_soldier_opp*5) + (target_tower_opp[0]*50) - (target_soldier_us*5) - (target_tower_us[0]*50);
		return value;
	}

	string minValue(Node* node, int numb_ply, string s);

	string maxValue(Node* node, int numb_ply, string s){
		if(numb_ply==0){
			(*node).eval = Evaluation_func((*node).state,(*node).pieces_count,weights);
			// cerr << numb_ply << " max ply left" << endl;
			return s;
		}

		Node temp_node = *node;
		vector<string> moves = getAllValidMoves((*node).state, my_player,1);
		float max = INT_MIN;
		vector<vector<int> > next_state;
		vector<vector<int> > best_state;
		int action_index=0;
		string temp_string;
		string action_string;

		for(int i=0; i<moves.size(); i++){
			temp_node = *node;
			next_state = update_state(temp_node.state, moves[i], (temp_node.pieces_count));
			temp_node.state = next_state;
			// cerr << numb_ply << " max ply left and value = "<<i<< endl;
			temp_string = minValue(&temp_node, numb_ply-1, moves[i]);
			temp_node.alpha = max((*node).alpha, temp_node.alpha);
			temp_node.eval = temp_node.alpha;
			if(temp_node.alpha >= temp_node.beta)
				return moves[i];
			if(max < temp_node.eval){
				max = temp_node.eval;
				best_state = next_state;
				action_string = temp_string;
				action_index = i;
			}
		}
						
		
		// (*node).eval = max;
		// (*node).state = next_state;
		return moves[action_index];
	}

	string minValue(Node* node, int numb_ply, string s){
		if(numb_ply==0){
			// cerr << "Woah bhai!" << endl;
			(*node).eval = Evaluation_func((*node).state,(*node).pieces_count,weights);
			// cerr << numb_ply << " min ply left" << endl;
			return s;
		}

		Node temp_node = *node;
		vector<string> moves = getAllValidMoves((*node).state, opp_player, -1);
		float min = INT_MAX;
		vector<vector<int> > next_state;
		vector<vector<int> > best_state;
		int action_index=0;
		string temp_string;
		string action_string;

		for(int i=0; i<moves.size(); i++){
			temp_node = *node;
			next_state = update_state(temp_node.state, moves[i], (temp_node.pieces_count));
			temp_node.state = next_state;
			// cerr << numb_ply << "min ply left and value = "<<i<< endl;
			temp_string = maxValue(&temp_node, numb_ply-1, moves[i]);
			temp_node.beta = min(((*node).beta), temp_node.beta);
			temp_node.eval = temp_node.beta;
			if(temp_node.alpha >= temp_node.beta)
				return moves[i];
			if(min > temp_node.eval){
				min = temp_node.eval;
				action_string = temp_string;
			}
		}

		//(*node).eval = min;

		return action_string;
	}

	string miniMax(Node* node, int numb_ply){
		string action = maxValue(node, numb_ply,"");
		// value already updated in node
		cerr<<"action "<<action<<endl;
		return action;
	}

	string greedyBestStep(vector<string> valid_moves, Node* node, int weights[8]){   //state and pieces_count updated
		float temp_max = INT_MIN;
		int temp_pieces_count[4];
		copy(begin((*node).pieces_count), end((*node).pieces_count), begin(temp_pieces_count));
		int final_pieces_count[4];
		copy(begin((*node).pieces_count), end((*node).pieces_count), begin(final_pieces_count));

		vector<vector<int> > branch_state;
		vector<vector<int> > best_state;
		float temp_eval=0;	
		int index_best=-1;

		for(int i=0; i<valid_moves.size(); i++){
			// temp_pieces_count = (*node).pieces_count;
			temp_pieces_count[0] = (*node).pieces_count[0]; temp_pieces_count[1] = (*node).pieces_count[1]; temp_pieces_count[2] = (*node).pieces_count[2]; temp_pieces_count[3] = (*node).pieces_count[3];
			branch_state = update_state((*node).state, valid_moves[i],temp_pieces_count);  //doesn't change state but only the pieces_count
			// cerr<<"move "<<valid_moves[i]<<endl;
			// printState(branch_state);
			temp_eval = Evaluation_func(branch_state, temp_pieces_count, weights);
			// cerr<<"temp_eval "<<temp_eval<<endl;
			if(temp_max <= temp_eval){
				temp_max = temp_eval;
				best_state = branch_state;
				index_best = i;
				// final_pieces_count = temp_pieces_count;
				copy(begin(temp_pieces_count), end(temp_pieces_count), begin(final_pieces_count)); 
			}

			// if(max_eval < temp_eval){
			// 	max_eval = temp_eval;
			// 	index_best = i;
			// 	// best_state = branch_state;
			// 	// final_pieces_count = temp_pieces_count; 
			// 	break;
			// }

		}
		cerr<<"best index"<<index_best<<endl;
		cerr<<valid_moves[index_best]<<endl;
		// if(index_best<valid_moves.size()){
			// (*node).state = best_state;
			// copy(begin(final_pieces_count), end(final_pieces_count), begin((*node).pieces_count)); 
			// (*node).pieces_count = final_pieces_count;
			(*node).eval = temp_max;
			return valid_moves[index_best];
		// }

	}

	string myNextMove(Node* curr_node){
		string next = "";
	 	if(move_count<6){			//move greedily
	 		cerr<<"greedy "<<move_count<<endl;
		 	vector<string> valid_moves = getAllValidMoves((*curr_node).state,my_player,1);
		 	cerr<<valid_moves[0]<<endl;
		 	next = greedyBestStep(valid_moves, curr_node, weights);
		 	// cerr<<next<<endl;
		}
		else{
			printState((*curr_node).state);
			if(move_count>=6 && move_count<=60){	//ply of 4
				cerr<<"2 ply"<<endl;
				next = miniMax(curr_node, 2);
			} 
			else if(move_count>40 && move_count<=100){ //ply of 6
				next = miniMax(curr_node, 4);
			}
		}
		move_count+=2;
		return next;
	}


	int main(){
		int ID;
		int N;
		int M; 
		int t;
		cerr<< "hi" <<endl;
		cin >> ID >> N >> M >> t;
		cerr<< ID <<", "<<N<<endl;
		// Board* newGame = new Board(N,M);
		// Board* newGame;
		if(ID == 1)
			player = 2;
		else
			player = 1;
		Board(N,M);
		// cout<<"Hello guys"<<endl;
		if(ID == 1){
			player = 2;
			my_player = 2;
			opp_player = 1;
			cerr<< "hi 1" <<endl;
			// cout<<"pls come 1"<<endl;
			// newGame->printState();

			Node start;
			start.state = board;
			start.alpha = INT_MIN;
			start.beta = INT_MAX;
			start.eval = start.alpha;
			copy(begin(pieces_count), end(pieces_count), begin(start.pieces_count));
			while(1){
				string action_to_perform = myNextMove(&start);
				board = update_state(board,action_to_perform,start.pieces_count);
				// cout<"give action"<<endl;
				cout << action_to_perform << endl;
				string opp_move = "";
				string read = "";
				cin >> read;
				opp_move += read;
				for(int i=0; i<5;i++){
					cin >> read;
					opp_move += " " + read;
				}
				board = update_state(board,opp_move,start.pieces_count);
				start.state = board;
				start.alpha = INT_MIN;
				start.beta = INT_MAX;
				start.eval = start.alpha;
			}
		}
		else{
			cerr<< "hi 2" <<endl;
			player = 1;
			my_player = 1;
			opp_player = 2;
			// newGame->printState();
			// cout<<"pls come 2"<<endl;
			
			Node start;
			start.state = board;
			start.eval = 0;
			start.alpha = INT_MIN;
			start.beta = INT_MAX;
			copy(begin(pieces_count), end(pieces_count), begin(start.pieces_count));
			while(1){
				string opp_move = "";
				string read = "";
				cin >> read;
				opp_move += read;
				for(int i=0; i<5;i++){
					cin >> read;
					opp_move += " " + read;
				}
				//cerr<<opp_move<<endl;
				board = update_state(board,opp_move,start.pieces_count);
				//cerr<<"updated"<<endl;
				// printState(board);
				start.state = board;
				start.alpha = INT_MIN;
				start.beta = INT_MAX;
				start.eval = start.alpha;
				string action_to_perform = myNextMove(&start);
				// cerr << action_to_perform << endl;
				board = update_state(board,action_to_perform,start.pieces_count);
				// cout<"give action"<<endl;
				cout << action_to_perform << endl;
			}	
		}
		return 0;
	}
// };
