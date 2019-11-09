#include <bits/stdc++.h>
#include <ctime>
using namespace std;
		
int move_count = 0;
vector<int> pieces_count{0,0,0,0};
int weights[14] = {1000,6500,-1200,-3200,500,1900,-700, -5000,200, 300,400,-200, -300, -400};
// int weights[14] = {1000,6500,-1200,-3200,61,226,-1000, -7157,25, 37,49,-285, -430, -570};

int my_player=0;
int opp_player=0;
int player = 0; 
string last_move = "";
string sec_last_move = "";
bool print_weight = false;
int prev_score = INT_MAX;
int score = 0;
float learning_rate_inc = 0.3;
float learning_rate_dec = 0.3;

struct Node{
	vector<vector<int> > state;
	vector<int> pieces_count{0,0,0,0};
	float eval=0;
	int alpha;
	int beta;
};

struct Node_prune{
	vector<vector<int> > state;
	vector<int> pieces_count{0,0,0,0};
	float eval;
};

	vector<vector<int> > board;
	void Board(int n, int m){
		vector<int> tempVector1;
		vector<int> tempVector2;
		bool flag = false;
		pieces_count[0] = (3*m)/2;
		pieces_count[1] = m/2;
		pieces_count[2] = (3*m)/2;
		pieces_count[3] = m/2;
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
			if(board[sq_x-1][sq_y] == val){
				return true;
			}
		}
		if(sq_x < board.size()-1){
			if(board[sq_x+1][sq_y] == val){
				return true;
			}
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
				if(board[sq_x-1][sq_y-1] == val){
					return true;
				}
			}
			if(sq_y >0){
				if(board[sq_x][sq_y-1] == val){
					return true;
				}
			}
			if(sq_x < board.size()-1 && sq_y > 0){
				if(board[sq_x+1][sq_y-1] == val){
					return true;
				}
			}	
		}
		return false;
	}

	bool is_attack_on_retreat_possible(int x, int y, int player, int val){
		if(x < board.size() && y < board[0].size() && x >=0 && y >=0){
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
				if(board[x-1][y] == (-1*val) || board[x-1][y] == (-2*val))
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x-1) + " " + to_string(y));
			}
			if( x < board.size()-1){
				if(board[x+1][y] == (-1*val) || board[x+1][y] == (-2*val))
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
					if(board[x][y+2] != val && board[x][y+2] != (2*val))
						moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y+2));
					if(x >= 2){
						if(board[x-2][y+2] != val && board[x-2][y+2] != (2*val))
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-2) + " " + to_string(y+2));
					}
					if(x <= board.size()-3){
						if(board[x+2][y+2] != val && board[x+2][y+2] != (2*val))
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+2) + " " + to_string(y+2));
					}
				}
			}			
		}
		else{
			//Capture Moves
			if(x > 0){
				if(board[x-1][y] == (-1*val) || board[x-1][y] == (-2*val))
					moves.push_back("S " + to_string(x) + " " + to_string(y)+ " M "+ to_string(x-1) + " " + to_string(y));
			}
			if(x < board.size()-1){
				if(board[x+1][y] == (-1*val) || board[x+1][y] == (-2*val))
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
					if(board[x][y-2] != val && board[x][y-2] != (2*val))
						moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y-2));
					if(x >= 2){
						if(board[x-2][y-2] != val && board[x-2][y-2] != (2*val))
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-2) + " " + to_string(y-2));
					}
					if(x <= board.size()-3){
						if(board[x+2][y-2] != val && board[x+2][y-2] != (2*val))
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+2) + " " + to_string(y-2));
					}
				}
			}
		}

			//cannon movement and bombing covered for possible cannons in all 8 directions
		if(check_cannon(x,y,val,"LBD")){
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

		if(check_cannon(x,y,val,"BV")){
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

		if(check_cannon(x,y,val,"RBD")){
			if(x+3 < board.size() &&  y+3 < board[0].size()){
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

		if(check_cannon(x,y,val,"RH")){
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
		
		if(check_cannon(x,y,val,"RUD")){
			if(x+3 < board.size() &&  y-3 >=0){
				if(board[x+3][y-3] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x+3) + " " + to_string(y-3));
			}
			if(x-1 >= 0 && y+1 < board[0].size()){
				if(board[x-1][y+1] == 0){
					if(x-2 >= 0 && y+2 < board[0].size()){
						if(board[x-2][y+2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-2) + " " + to_string(y+2));			
					}
					if(x-3 >= 0 && y+3 < board[0].size()){
						if(board[x-3][y+3] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x-3) + " " + to_string(y+3));			
					}
				}		
			}
		}

		if(check_cannon(x,y,val,"UV")){
			if(y-3 >=0){
				if(board[x][y-3] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x) + " " + to_string(y-3));
			}
			if(y+1 < board[0].size()){
				if(board[x][y+1] == 0){
					if(y+2 < board[0].size()){
						if(board[x][y+2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x) + " " + to_string(y+2));			
					}
					if(y+3 < board[0].size()){
						if(board[x][y+3] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x) + " " + to_string(y+3));			
					}
				}		
			}
		}

		if(check_cannon(x,y,val,"LUD")){
			if(x-3 >=0 &&  y-3 >=0){
				if(board[x-3][y-3] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-3) + " " + to_string(y-3));
			}
			if(x+1 < board.size() && y+1 < board[0].size()){
				if(board[x+1][y+1] == 0){
					if(x+2 < board.size() && y+2 < board[0].size()){
						if(board[x+2][y+2] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+2) + " " + to_string(y+2));			
					}
					if(x+3 < board.size() && y+3 < board[0].size()){
						if(board[x+3][y+3] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+3) + " " + to_string(y+3));			
					}
				}		
			}
		}

		if(check_cannon(x,y,val,"LH")){
			if(x-3 >=0){
				if(board[x-3][y] == 0)
					moves.push_back("S " + to_string(x) + " " + to_string(y) + " M "+ to_string(x-3) + " " + to_string(y));
			}
			if(x+1 < board.size()){
				if(board[x+1][y] == 0){
					if(x+2 < board.size()){
						if(board[x+2][y] != val)
							moves.push_back("S " + to_string(x) + " " + to_string(y) + " B "+ to_string(x+2) + " " + to_string(y));			
					}
					if(x+3 < board.size()){
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
		 		if(state[i][j] == val){
		 			moves = getValidMovesForSoldier(state,i,j,player,val, moves);
		 		}
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

	int waysToAttackSquareTower(int sq_x, int sq_y, int val, int player){
		int count = 0;
		if(player == 1){
			if(is_opponent_adjacent(sq_x, sq_y,(-1*val),1))
				count++;
		if(sq_x > 2){
			if(check_cannon(sq_x-2,sq_y-2, (-1*val), "LUD") && board[sq_x-1][sq_y-1] == 0)
				count++;
			if(check_cannon(sq_x-3,sq_y-3, (-1*val), "LUD") && board[sq_x-2][sq_y-2] == 0)
				count++;
			if(check_cannon(sq_x-2,sq_y, (-1*val), "LH") && board[sq_x-1][sq_y] == 0)
				count++;
			if(check_cannon(sq_x-3,sq_y, (-1*val), "LH") && board[sq_x-2][sq_y] == 0)
				count++;
		}
		if(sq_x < board.size()-3){
			if(check_cannon(sq_x+2,sq_y-2, (-1*val), "RUD") && board[sq_x+1][sq_y-1] == 0)
				count++;
			if(check_cannon(sq_x+3,sq_y-3, (-1*val), "RUD") && board[sq_x+2][sq_y-2] == 0)
				count++;
			if(check_cannon(sq_x+2,sq_y, (-1*val), "RH") && board[sq_x+1][sq_y] == 0)
				count++;
			if(check_cannon(sq_x+3,sq_y, (-1*val), "RH") && board[sq_x+2][sq_y] == 0)
				count++;
		}
		if(check_cannon(sq_x,sq_y-2, (-1*val), "UV") && board[sq_x][sq_y-1] == 0)
			count++;
		if(check_cannon(sq_x,sq_y-3, (-1*val), "UV") && board[sq_x][sq_y-2] == 0)
			count++;
		}
		else{
			if(is_opponent_adjacent(sq_x, sq_y, (-1*val),2))
				count++;
		if(sq_x > 2){
			if(check_cannon(sq_x-2,sq_y+2, (-1*val), "LBD") && board[sq_x-1][sq_y+1] == 0)
				count++;
			if(check_cannon(sq_x-3,sq_y+3, (-1*val), "LBD") && board[sq_x-2][sq_y+2] == 0)
				count++;
			if(check_cannon(sq_x-2,sq_y, (-1*val), "LH") && board[sq_x-1][sq_y] == 0)
				count++;
			if(check_cannon(sq_x-3,sq_y, (-1*val), "LH") && board[sq_x-2][sq_y] == 0)
				count++;
		}
		if(sq_x < board.size()-3){
			if(check_cannon(sq_x+2,sq_y+2, (-1*val), "RBD") && board[sq_x+1][sq_y+1] == 0)
				count++;
			if(check_cannon(sq_x+3,sq_y+3, (-1*val), "RBD") && board[sq_x+2][sq_y+2] == 0)
				count++;
			if(check_cannon(sq_x+2,sq_y, (-1*val), "RH") && board[sq_x+1][sq_y] == 0)
				count++;
			if(check_cannon(sq_x+3,sq_y, (-1*val), "RH") && board[sq_x+2][sq_y] == 0)
				count++;
		}
		if(check_cannon(sq_x,sq_y+2, (-1*val), "BV") && board[sq_x][sq_y+1] == 0)
			count++;
		if(check_cannon(sq_x,sq_y+3, (-1*val), "BV") && board[sq_x][sq_y+2] == 0)
			count++;
		}
		return count;
	}

	vector<int> opp_tower_attacks_possible(vector<vector<int> > state, int val, int player1){
		int m = state[0].size()-1;
		int n = state.size();
		vector<int> answer;
		if(player1 == 2){
			for(int i=0 ;i<n; i+= 2){
				int count = 0;
				if(abs(state[i][0]) == 2)
					count = waysToAttackSquareTower(i,0,(-1*val),player1);
				answer.push_back(count);
			}
		}
		else{
			for(int i=1 ;i<n; i+= 2){
				int count = 0;
				if(abs(state[i][m]) == 2)
					count = waysToAttackSquareTower(i,m,(-1*val), player1);
				answer.push_back(count);
			}	
		}
		return answer;
	}

	vector<vector<int> > update_state(vector<vector<int> > state, string move, vector<int> &piece_count){
		int coor[4];
		int trav = 0;
		char type;
		for(int i=1; i<move.length();i++){
			if(move[i] == ' ' && (move[i+1] != 'M' && move[i+1] != 'B')){
				int j = i+1;
				int num = 0;
				while(j < move.length()){
					if(move[j] == ' ')
						break;
					num = num*10 + (int)(move[j]-'0');
					j++;
				}
				coor[trav] = num;
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
		return state;
	}

	void Targets(vector<vector<int> > game_state, int x, int y, bool you, string str, int* target_tow, int* target_sol){
		int soldier = 1;
		int tower = 2;
		int target_soldier=0;
		int target_tower =0;
		vector<int> ans(2);
		if(!you){
			soldier = -1;
			tower = -2;
		}

		if(str.compare("vert")==0){
			if(y+2 < game_state[0].size()){
				if(game_state[x][y+2] == 0){
					if(y+3 < game_state[0].size()){
						if(game_state[x][y+3] == soldier)
							target_soldier+=1;
						else if(game_state[x][y+3] == tower)
							target_tower+=1;
					}
					if(y+4 < game_state[0].size()){
						if(game_state[x][y+4] == soldier)
							target_soldier+=1;
						else if(game_state[x][y+4] == tower)
							target_tower+=1;
					}
				}
			}
			if(y-2 >= 0){
				if(game_state[x][y-2] == 0){
					if(y-3 >= 0){
						if(game_state[x][y-3] == soldier)
							target_soldier+=1;
						else if(game_state[x][y-3] == tower)
							target_tower+=1;
					}
					if(y-4 >=0){
						if(game_state[x][y-4] == soldier)
							target_soldier+=1;
						else if(game_state[x][y-4] == tower)
							target_tower+=1;
					}
				}
			}
		}

		if(str.compare("horz")==0){
			if(x+2 < game_state.size()){
				if(game_state[x+2][y] == 0){
					if(x+3 < game_state.size()){
						if(game_state[x+3][y] == soldier)
							target_soldier+=1;
						else if(game_state[x+3][y] == tower)
							target_tower+=1;
					}
					if(x+4 < game_state.size()){
						if(game_state[x+4][y] == soldier)
							target_soldier+=1;
						else if(game_state[x+4][y] == tower)
							target_tower+=1;
					}
				}
			}
			if(x-2 >= 0){
				if(game_state[x-2][y] == 0){
					if(x-3 >= 0){
						if(game_state[x-3][y] == soldier)
							target_soldier+=1;
						else if(game_state[x-3][y] == tower)
							target_tower+=1;
					}
					if(x-4 >=0){
						if(game_state[x-4][y] == soldier)
							target_soldier+=1;
						else if(game_state[x-4][y] == tower)
							target_tower+=1;
					}
				}
			}
		}

		if(str.compare("ldiag")==0){
			if(x+2 < game_state.size() && y+2 < game_state[0].size()){
				if(game_state[x+2][y+2] == 0){
					if(x+3 < game_state.size() && y+3 < game_state[0].size()){
						if(game_state[x+3][y+3] == soldier)
							target_soldier+=1;
						else if(game_state[x+3][y+3] == tower)
							target_tower+=1;
					}
					if(x+4 < game_state.size() && y+4 < game_state[0].size()){
						if(game_state[x+4][y+4] == soldier)
							target_soldier+=1;
						else if(game_state[x+4][y+4] == tower)
							target_tower+=1;
					}
				}
			}
			if(x-2 >= 0 && y-2 >= 0){
				if(game_state[x-2][y-2] == 0){
					if(x-3 >= 0 && y-3 >= 0){
						if(game_state[x-3][y-3] == soldier)
							target_soldier+=1;
						else if(game_state[x-3][y-3] == tower)
							target_tower+=1;
					}
					if(x-4 >= 0 && y-4 >= 0){
						if(game_state[x-4][y-4] == soldier)
							target_soldier+=1;
						else if(game_state[x-4][y-4] == tower)
							target_tower+=1;
					}
				}
			}
		}
		
		if(str.compare("rdiag")==0){
			if(x+2 < game_state.size() && y-2 >= 0){
				if(game_state[x+2][y-2] == 0){
					if(x+3 < game_state.size() && y-3 >=0){
						if(game_state[x+3][y-3] == soldier)
							target_soldier+=1;
						else if(game_state[x+3][y-3] == tower)
							target_tower+=1;
					}
					if(x+4 < game_state.size() && y-4 >=0){
						if(game_state[x+4][y-4] == soldier)
							target_soldier+=1;
						else if(game_state[x+4][y-4] == tower)
							target_tower+=1;
					}
				}
			}
			if(x-2 >= 0 && y+2 < game_state[0].size()){
				if(game_state[x-2][y+2] == 0){
					if(x-3 >= 0 && y+3 < game_state[0].size()){
						if(game_state[x-3][y+3] == soldier)
							target_soldier+=1;
						else if(game_state[x-3][y+3] == tower)
							target_tower+=1;
					}
					if(x-4 >= 0 && y+4 < game_state[0].size()){
						if(game_state[x-4][y+4] == soldier)
							target_soldier+=1;
						else if(game_state[x-4][y+4] == tower)
							target_tower+=1;
					}
				}
			}
		}
		(*target_sol) += target_soldier;
		(*target_tow) += target_tower;
		return;
	}

	vector<int> cannon_effect(vector<vector<int> > game_state,int val){
		int cannon_attack_vert = 0;
		int cannon_attack_hori = 0;
		int cannon_attack_diag = 0;
		int cannon_attack_tower = 0;
		int cannon_attack_soldier = 0;
		vector<int> ans;
		for(int i=0; i<game_state.size(); i++){
			for(int j=0; j<game_state[0].size(); j++){
				if(game_state[i][j]==val){
					if(i > 0 && i < game_state.size()-1){
						if(game_state[i-1][j] == val  && game_state[i+1][j] == val){
							Targets(game_state,i, j,val<0 , "horz", &cannon_attack_tower, &cannon_attack_soldier);
							cannon_attack_hori += (cannon_attack_tower + cannon_attack_soldier);
							cannon_attack_tower = 0;
							cannon_attack_soldier = 0;
						}
					}
					if(j > 0 && j < game_state[0].size()-1){
						if(game_state[i][j-1] == val  && game_state[i][j+1] == val){
							Targets(game_state,i, j,val<0 , "vert", &cannon_attack_tower, &cannon_attack_soldier);
							cannon_attack_vert += (cannon_attack_tower + cannon_attack_soldier);
							cannon_attack_tower = 0;
							cannon_attack_soldier = 0;
						}
					}
					if(i > 0 && i < game_state.size()-1 && j > 0 && j < game_state[0].size()-1){
						if(game_state[i-1][j+1] == val  && game_state[i+1][j-1] == val){
							Targets(game_state,i, j,val<0 , "rdiag", &cannon_attack_tower, &cannon_attack_soldier);
							cannon_attack_diag += (cannon_attack_tower + cannon_attack_soldier);
							cannon_attack_tower = 0;
							cannon_attack_soldier = 0;
						}
					}
					if(i > 0 && i < game_state.size()-1 && j > 0 && j < game_state[0].size()-1){
						if(game_state[i-1][j-1] == val  && game_state[i+1][j+1] == val){
							Targets(game_state,i, j,val<0 , "ldiag", &cannon_attack_tower, &cannon_attack_soldier);
							cannon_attack_diag += (cannon_attack_tower + cannon_attack_soldier);
							cannon_attack_tower = 0;
							cannon_attack_soldier = 0;
						}
					}
				}
			}
		}
		ans.push_back(cannon_attack_hori);
		ans.push_back(cannon_attack_vert);
		ans.push_back(cannon_attack_diag);
		return ans;
	}

	int Evaluation_func(vector< vector<int> > state, vector<int> piece_count){
		int s1 = piece_count[0];
		int s2 = piece_count[2];
		int t1 = piece_count[1];
		int t2 = piece_count[3];
		int target_soldier_us = 0;
		int target_soldier_opp = 0;
		vector<int> target_tower_opp;
		vector<int> target_tower_us;
		vector<int> my_cannon_stats;
		vector<int> opp_cannon_stats;
		if(player == 1){
			target_soldier_opp = opp_soldiers_under_attack(state,1,1);
			target_tower_opp = opp_tower_attacks_possible(state,1,1);
			target_soldier_us = opp_soldiers_under_attack(state,-1,2);
			target_tower_us = opp_tower_attacks_possible(state,-1,2);
		}
		else{
			target_soldier_opp = opp_soldiers_under_attack(state,1,2);
			target_tower_opp = opp_tower_attacks_possible(state,1,2);	
			target_soldier_us = opp_soldiers_under_attack(state,-1,1);
			target_tower_us = opp_tower_attacks_possible(state,-1,1);
		}
		my_cannon_stats = cannon_effect(state,1);
		opp_cannon_stats = cannon_effect(state,-1);
		int towers_at_risk_us = 0;
		for(int i=0; i<state.size()/2; i++){
			if(target_tower_us[i]>0)
				towers_at_risk_us++;
		}
		int towers_at_risk_opp = 0;
		for(int i=0; i<state.size()/2; i++){
			if(target_tower_opp[i]>0)
				towers_at_risk_opp++;
		}
		///GOOD VERSION OF WEIGHTS
		// int value = ((s1*800) + (t1*3500) - (s2*800) - (t2*3200));
		// value += ((target_soldier_opp*300) + (towers_at_risk_opp*900) - (target_soldier_us*300) - (towers_at_risk_us*5000));
		// value += ((my_cannon_stats[0] * 100) + (my_cannon_stats[1] * 200) + (my_cannon_stats[2] * 200));
		// value -= ((opp_cannon_stats[0] * 100) + (opp_cannon_stats[1] * 200) + (opp_cannon_stats[2] * 200));

		// //TRIAL WAALE WEIGHTS
		// int value = ((s1*1000) + (t1*6500) - (s2*1200) - (t2*3200));
		// value += ((target_soldier_opp*500) + (towers_at_risk_opp*1900) - (target_soldier_us*700) - (towers_at_risk_us*5000));
		// value += ((my_cannon_stats[0] * 200) + (my_cannon_stats[1] * 300) + (my_cannon_stats[2] * 400));
		// value -= ((opp_cannon_stats[0] * 200) + (opp_cannon_stats[1] * 300) + (opp_cannon_stats[2] * 400));
	
		int value = ((s1*weights[0]) + (t1*weights[1]) + (s2*weights[2]) + (t2*weights[3]));
		value += ((target_soldier_opp*weights[4]) + (towers_at_risk_opp*weights[5]) + (target_soldier_us*weights[6]) + (towers_at_risk_us*weights[7]));
		value += ((my_cannon_stats[0] * weights[8]) + (my_cannon_stats[1] * weights[9]) + (my_cannon_stats[2] * weights[10]));
		value += ((opp_cannon_stats[0] * weights[11]) + (opp_cannon_stats[1] * weights[12]) + (opp_cannon_stats[2] * weights[13]));

		if(print_weight){
			cerr<<"soldier us "<<s1<<endl;
			cerr<<"tower us "<<t1<<endl;
			cerr<<"soldier opp "<<s2<<endl;
			cerr<<"tower opp "<<t2<<endl;
			cerr<<"target_soldier_opp: "<<target_soldier_opp<<endl;
			cerr<<"target_soldier_us: "<<target_soldier_us<<endl;
			cerr<<"towers_at_risk_opp: "<<towers_at_risk_opp<<endl;
			cerr<<"towers_at_risk_us: "<<towers_at_risk_us<<endl;
			cerr<<"my_cannon_stats horiz: "<<my_cannon_stats[0]<<endl;
			cerr<<"my_cannon_stats vert: "<<my_cannon_stats[1]<<endl;
			cerr<<"my_cannon_stats diag: "<<my_cannon_stats[2]<<endl;
			cerr<<"my_cannon_stats tower: "<<my_cannon_stats[3]<<endl;
			cerr<<"my_cannon_stats sold: "<<my_cannon_stats[4]<<endl;
			cerr<<"opp_cannon_stats horiz: "<<opp_cannon_stats[0]<<endl;
			cerr<<"opp_cannon_stats vert: "<<opp_cannon_stats[1]<<endl;
			cerr<<"opp_cannon_stats diag: "<<opp_cannon_stats[2]<<endl;
			cerr<<"opp_cannon_stats tower: "<<opp_cannon_stats[3]<<endl;
			cerr<<"opp_cannon_stats sold: "<<opp_cannon_stats[4]<<endl;
		}
		return value;
	}

	string minValue(Node* node, int numb_ply, string s);

	string maxValue(Node* node, int numb_ply, string s){
		
		Node temp_node = *node;  
		vector<string> moves = getAllValidMoves((*node).state, my_player,1);	
		if(moves.size()==0){
			cout<<"I have no move left \n";
		}		
		if(numb_ply==0 || moves.size() == 0){
			(*node).eval = Evaluation_func((*node).state,(*node).pieces_count);
			(*node).alpha = (*node).eval;
			return s;
		}

		float max1 = INT_MIN;
		vector<vector<int> > best_state;
		int action_index=0;
		string temp_string;
		string action_string;
		int random_ind = rand()%(moves.size());
		for(int i=0; i<moves.size(); i++){
			temp_node = *node;
			temp_node.state = update_state(temp_node.state, moves[(random_ind+i)%(moves.size())], (temp_node.pieces_count));
			temp_string = minValue(&temp_node, numb_ply-1, moves[(random_ind+i)%(moves.size())]);
			(*node).alpha = max((*node).alpha, temp_node.beta);
			if((*node).alpha >= (*node).beta){
				return moves[(random_ind+i)%(moves.size())];
			}
			if(max1 < temp_node.beta){
				max1 = temp_node.beta;
				action_index = (random_ind+i)%(moves.size());
			}
		}						
		return moves[action_index];
	}

	string minValue(Node* node, int numb_ply, string s){
		Node temp_node = (*node);
		vector<string> moves = getAllValidMoves((*node).state, opp_player, -1);
		if(moves.size()==0){
			cerr<<"oppoent has no move left \n";
		}
		if(numb_ply==0 || moves.size() == 0){
			(*node).eval = Evaluation_func((*node).state,(*node).pieces_count);
			(*node).beta = (*node).eval;
			return s;
		}
		
		float min1 = INT_MAX;
		vector<vector<int> > best_state;
		int action_index=0;
		string temp_string;
		string action_string;
		int random_ind = rand()%(moves.size());
		for(int i=0; i<moves.size(); i++){
			temp_node = *node;
			temp_node.state  = update_state(temp_node.state, moves[(random_ind+i)%(moves.size())], (temp_node.pieces_count));
			temp_string = maxValue(&temp_node, numb_ply-1, moves[(random_ind+i)%(moves.size())]);
			(*node).beta = min(((*node).beta), temp_node.alpha);
			if((*node).alpha >= (*node).beta){
				return moves[(random_ind+i)%(moves.size())];
			}
			if(min1 > temp_node.alpha){
				min1 = temp_node.alpha;
				action_index = (random_ind+i)%(moves.size());
			}
		}
		return moves[action_index];
	}

	string miniMax(Node* node, int numb_ply){
		cerr<<"Move count----------------------------------------- "<< move_count <<"-----------------------------------------------"<<endl;
		(*node).alpha = INT_MIN;
		(*node).beta = INT_MAX;
		string action = maxValue(node, numb_ply,"");
		// value already updated in node
		return action;
	}

	string greedyBestStep(Node* node, int weights[8]){   //state and pieces_count updated
		float temp_max = INT_MIN;
		vector<int> temp_pieces_count(4,0);
		copy(begin((*node).pieces_count), end((*node).pieces_count), begin(temp_pieces_count));
		vector<int> final_pieces_count(4,0);

		copy(begin((*node).pieces_count), end((*node).pieces_count), begin(final_pieces_count));
		vector<string> valid_moves = getAllValidMoves((*node).state,my_player, 1);
		vector<vector<int> > branch_state;
		vector<vector<int> > best_state;
		float temp_eval=0;	
		int index_best=-1;
		
		int random_ind = rand()%(valid_moves.size());
		for(int i=0; i<valid_moves.size(); i++){
			temp_pieces_count[0] = (*node).pieces_count[0]; temp_pieces_count[1] = (*node).pieces_count[1]; temp_pieces_count[2] = (*node).pieces_count[2]; temp_pieces_count[3] = (*node).pieces_count[3];
			branch_state = update_state((*node).state, valid_moves[(random_ind+i)%(valid_moves.size())],temp_pieces_count);  //doesn't change state but only the pieces_count
			temp_eval = Evaluation_func(branch_state, temp_pieces_count);
			if(temp_max <= temp_eval){
				temp_max = temp_eval;
				best_state = branch_state;
				index_best = (random_ind+i)%(valid_moves.size());
				copy(begin(temp_pieces_count), end(temp_pieces_count), begin(final_pieces_count)); 
			}
		}
			(*node).eval = temp_max;
			return valid_moves[index_best];
	}

	bool tower_danger(vector<vector<int> > state, int val){
		bool t1;
		if(my_player==1){
			for(int i=0; i<state.size()/2;i+= 2){
				if(state[i][0] == 2){
					t1 = canSquarebeAttacked(i,0,val,1);
				 	if(t1)
				 		return true;
				}
			}
			return false;
		}
		else{
			int last = state[0].size()-1;
			for(int i=1; i<state.size()/2;i+=2){
				if(state[i][last] == 2){
					t1 = canSquarebeAttacked(i,last,val,2);
				 	if(t1)
				 		return true;
				}
			}
			return false;
		}
		return false;
	}

	string myNextMove(Node* curr_node){
		string next = "";
		vector<string> valid_moves = getAllValidMoves((*curr_node).state,my_player, 1);
		 	if(move_count<10){			//move greedily
			 	next = greedyBestStep(curr_node, weights);
			}
			else if(true){
				if(move_count>=10 && move_count<30){	//ply of 4
					cerr<<"2 ply"<<endl;
					next = miniMax(curr_node, 2);
				} 
				else if(move_count>=30){	//ply of 4
					cerr<<"4 ply"<<endl;
					next = miniMax(curr_node, 2);
				} 
				// else if(move_count>=40 && move_count<=100 && valid_moves.size()<10){ //ply of 6
				// 	next = miniMax(curr_node, 3);
				// }
				// else{
				// 	cerr<<"4 ply"<<endl;
				// 	next = miniMax(curr_node, 2);
				// }
			}
		if(next.compare(last_move)==0 || next.compare(sec_last_move)==0){
			vector<string> move = getAllValidMoves((*curr_node).state, my_player,1);
			int ind = rand()%(move.size());
			next = move[ind];
		}
		move_count+=2;
		sec_last_move = last_move;
		last_move = next;
		return next;
	}

	void updateWeights(int new_score, int prev_score){
	cerr << "New Score: " << new_score << " PUrana kya hai bhai: " << prev_score << endl;
	if(new_score < prev_score){
		cerr << "????????????????????????? WOah bhai WAAH!???????????????????????????" << endl;
		for(int i=4 ;i<14; i++){
			if(weights[i] < 0)
				weights[i] += (int)((-1) * weights[i] * learning_rate_inc);
			if(weights[i] > 0)
				weights[i] += (int)((weights[i] * learning_rate_inc));
		}
		learning_rate_inc -= 0.005;
	}
	else{
		for(int i=4 ;i<14; i++){
			if(weights[i] > 0)
				weights[i] += (int)((-1) *(weights[i] * learning_rate_dec));
			if(weights[i] < 0)
				weights[i] += (int)((weights[i] * learning_rate_dec));
		}
		learning_rate_dec -= 0.005;
	}
	printState(board);
	cerr << " Weights begin: -----------------------------------" << endl;
	for(int i=0; i<14;i++){
		cerr << weights[i] << endl;
	}
	cerr << "Weights FInish- ....................................." << endl; 
}


	int main(){
		int ID;
		int N;
		int M; 
		int t;
		cin >> ID >> N >> M >> t;
		vector<vector<int> > old;
		srand ( time(NULL));
		if(ID == 1)
			player = 2;
		else
			player = 1;
		Board(N,M);
		if(ID == 1){
			player = 2;
			my_player = 2;
			opp_player = 1;
			Node start;
			start.state = board;
			start.alpha = INT_MIN;
			start.beta = INT_MAX;
			start.eval = start.alpha;
			copy(begin(pieces_count), end(pieces_count), begin(start.pieces_count));
			while(1){
				string action_to_perform = myNextMove(&start);
				old = board;
				board = update_state(board,action_to_perform,start.pieces_count);
				pieces_count = start.pieces_count;
				cout << action_to_perform << endl;
				string opp_move = "";
				string read = "";
				cin >> read;
				opp_move += read;
				for(int i=0; i<5;i++){
					cin >> read;
					opp_move += " " + read;
				}
				old = board;
				board = update_state(board,opp_move,start.pieces_count);
				score = Evaluation_func(board, pieces_count);
				print_weight = false;
				if(prev_score != INT_MAX && prev_score != score){
					cerr << "OKay sir!" << endl;
					updateWeights(score,prev_score);
				}
				prev_score = score;
				pieces_count = start.pieces_count;
				start.state = board;
				start.alpha = INT_MIN;
				start.beta = INT_MAX;
				start.eval = start.alpha;
			}
		}
		else{
			player = 1;
			my_player = 1;
			opp_player = 2;
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
				old = board;
				board = update_state(board,opp_move,start.pieces_count);
				pieces_count = start.pieces_count;
				start.state = board;
				start.alpha = INT_MIN;
				start.beta = INT_MAX;
				start.eval = start.alpha;
				// printState(board);
				string action_to_perform = myNextMove(&start);
				old = board;
				board = update_state(board,action_to_perform,start.pieces_count);
				score = Evaluation_func(board, pieces_count);
				print_weight = false;
				if(prev_score != INT_MAX && prev_score != score)
					updateWeights(score,prev_score);
				prev_score = score;
				pieces_count = start.pieces_count;
				cout << action_to_perform << endl;
			}	
		}
		return 0;
	}
