#include <bits/stdc++.h>
using namespace std;

int s1,s2,t1.t2;
int** game_state;
int m,n;
//Assuming we have a struct of game_state with varibales for the count of soldiers and towers as well
int Evaluation_func(int** game_state, int soldier1, int soldier2, int tower1, int tower2){
	int m = game_state.size();
	int n = game_state[0].size();

	void Targets(int i, int j, bool you, string str, int* target_soldier, int* target_tower){
		int soldiers = 1;
		int tower = 2;
		if(!you){
			soldiers = -1;
			tower = -2;
		}

		if(str.equals("vert")){
			if(i-2>=0){
				if(self.state[i-2][j] == soldier)
					target_soldier+=1;
				else if(self.state[i-2][j] == tower)
					target_tower+=1;
			}
			if(i-1>=0){
				if(self.state[i-1][j] == soldier)
					target_soldier+=1;
				else if(self.state[i-1][j] == tower)
					target_tower+=1;
			}
			if(i+2>=0){
				if(self.state[i+2][j] == soldier)
					target_soldier+=1;
				else if(self.state[i+2][j] == tower)
					target_tower+=1;
			}			
			if(i+1>=0){
				if(self.state[i+1][j] == soldier)
					target_soldier+=1;
				else if(self.state[i+1][j] == tower)
					target_tower+=1;
			}
		}

		if(str.equals("horz")){
			if(j-2>=0){
				if(self.state[i][j-2] == soldier)
					target_soldier+=1;
				else if(self.state[i][j-2] == tower)
					target_tower+=1;
			}
			if(j-1>=0){
				if(self.state[i][j-1] == soldier)
					target_soldier+=1;
				else if(self.state[i][j-1] == tower)
					target_tower+=1;
			}
			if(j+2>=0){
				if(self.state[i][j+2] == soldier)
					target_soldier+=1;
				else if(self.state[i][j+2] == tower)
					target_tower+=1;
			}			
			if(j+1>=0){
				if(self.state[i][j+1] == soldier)
					target_soldier+=1;
				else if(self.state[i][j+!] == tower)
					target_tower+=1;
			}
		}

		if(str.equals("rdiag")){
			if(j-2>=0 and i+2<=m-1){
				if(self.state[i+2][j-2] == soldier)
					target_soldier+=1;
				else if(self.state[i+2][j-2] == tower)
					target_tower+=1;
			}
			if(j-1>=0 and i+1<=m-1){
				if(self.state[i+1][j-1] == soldier)
					target_soldier+=1;
				else if(self.state[i+1][j-1] == tower)
					target_tower+=1;
			}
			if(j+2<=n-1 and i-2>=0){
				if(self.state[-2i][j+2] == soldier)
					target_soldier+=1;
				else if(self.state[i-2][j+2] == tower)
					target_tower+=1;
			}			
			if(j+1<=n-1 and i-1>=0){
				if(self.state[i-1][j+1] == soldier)
					target_soldier+=1;
				else if(self.state[i-1][j+!] == tower)
					target_tower+=1;
			}
		}

		if(str.equals("ldiag")){
			if(j-2>=0 and i-2>=0){
				if(self.state[i-2][j-2] == soldier)
					target_soldier+=1;
				else if(self.state[i-2][j-2] == tower)
					target_tower+=1;
			}
			if(j-1>=0 and i-1>=0){
				if(self.state[i-1][j-1] == soldier)
					target_soldier+=1;
				else if(self.state[i-1][j-1] == tower)
					target_tower+=1;
			}
			if(j+2<=n-1 and i+2<=m-1){
				if(self.state[i+2][j+2] == soldier)
					target_soldier+=1;
				else if(self.state[i+2][j+2] == tower)
					target_tower+=1;
			}			
			if(j+1<=n-1 and i+1<=m-1){
				if(self.state[i+1][j+1] == soldier)
					target_soldier+=1;
				else if(self.state[i+1][j+!] == tower)
					target_tower+=1;
			}
		}
	}

	void cannon_effect(int*  cannon_count, int* target_soldier, int* target_tower, int player){
		cannon_count = 0
		targer_soldier = 0
		target_tower = 0
		for(int i=1; i<m-1; i++){
			for(int j=1; j<n-1; j++){
				if(game_state[i][j]==player){
					if(game_state[i-1][j] == player  && game_state[i+1][j] == player){
						cannon_count+=1
						targets(i, j, player>0, "horz", target_soldier, target_tower);
					}
					else if(game_state[i][j-1] == player  and game_state[i][j+1] == player){
						cannon_count+=1
						targets(i, j, player>0, "vert", target_soldier, target_tower);
					}
					else if(game_state[i-1][j+1] == player  and game_state[i+1][j-1] == player){
						cannon_count+=1
						targets(i, j, player>0, "rdiag", target_soldier, target_tower);
					}
					else if(game_state[i-1][j-1] == player  and game_state[i+1][j+1] == player){
						cannon_count+=1
						targets(i, j, player>0, "ldiag", target_soldier, target_tower);
					}
				}
			}
		}
	}

	int cannon_count_us=0;
	int target_soldier_us = 0;
	int target_tower_us = 0;

	int cannon_count_opp=0;
	int target_soldier_opp = 0;
	int target_tower_opp = 0;

	cannon_effect(cannon_count_us, target_soldier_opp, target_tower_opp, 1);
	cannon_effect(cannon_count_opp, target_soldier_us, target_tower_us, -1);

	int value = (s1*10) + (t1*100) - (s2*10) - (t2*100) + (target_soldier_opp*5) + (target_tower_opp*50) - (targer_soldier_us*5) - (target_tower_us*50);
	return value;

}