#include <bits/stdc++.h>
using namespace std;

int s1,s2,t1,t2;
vector< vector<int> > game_state;
int m,n;

vector<int> Targets(int i, int j, bool you, string str){
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
			if(i-2>=0){
				if(game_state[i-2][j] == soldier)
					target_soldier+=1;
				else if(game_state[i-2][j] == tower)
					target_tower+=1;
			}
			if(i-1>=0){
				if(game_state[i-1][j] == soldier)
					target_soldier+=1;
				else if(game_state[i-1][j] == tower)
					target_tower+=1;
			}
			if(i+2>=0){
				if(game_state[i+2][j] == soldier)
					target_soldier+=1;
				else if(game_state[i+2][j] == tower)
					target_tower+=1;
			}			
			if(i+1>=0){
				if(game_state[i+1][j] == soldier)
					target_soldier+=1;
				else if(game_state[i+1][j] == tower)
					target_tower+=1;
			}
		}

		if(str.compare("horz")==0){
			if(j-2>=0){
				if(game_state[i][j-2] == soldier)
					target_soldier+=1;
				else if(game_state[i][j-2] == tower)
					target_tower+=1;
			}
			if(j-1>=0){
				if(game_state[i][j-1] == soldier)
					target_soldier+=1;
				else if(game_state[i][j-1] == tower)
					target_tower+=1;
			}
			if(j+2>=0){
				if(game_state[i][j+2] == soldier)
					target_soldier+=1;
				else if(game_state[i][j+2] == tower)
					target_tower+=1;
			}			
			if(j+1>=0){
				if(game_state[i][j+1] == soldier)
					target_soldier+=1;
				else if(game_state[i][j+1] == tower)
					target_tower+=1;
			}
		}

		if(str.compare("rdiag")==0){
			if(j-2>=0 and i+2<=m-1){
				if(game_state[i+2][j-2] == soldier)
					target_soldier+=1;
				else if(game_state[i+2][j-2] == tower)
					target_tower+=1;
			}
			if(j-1>=0 and i+1<=m-1){
				if(game_state[i+1][j-1] == soldier)
					target_soldier+=1;
				else if(game_state[i+1][j-1] == tower)
					target_tower+=1;
			}
			if(j+2<=n-1 and i-2>=0){
				if(game_state[i-2][j+2] == soldier)
					target_soldier+=1;
				else if(game_state[i-2][j+2] == tower)
					target_tower+=1;
			}			
			if(j+1<=n-1 and i-1>=0){
				if(game_state[i-1][j+1] == soldier)
					target_soldier+=1;
				else if(game_state[i-1][j+1] == tower)
					target_tower+=1;
			}
		}

		if(str.compare("ldiag")==0){
			if(j-2>=0 and i-2>=0){
				if(game_state[i-2][j-2] == soldier)
					target_soldier+=1;
				else if(game_state[i-2][j-2] == tower)
					target_tower+=1;
			}
			if(j-1>=0 and i-1>=0){
				if(game_state[i-1][j-1] == soldier)
					target_soldier+=1;
				else if(game_state[i-1][j-1] == tower)
					target_tower+=1;
			}
			if(j+2<=n-1 and i+2<=m-1){
				if(game_state[i+2][j+2] == soldier)
					target_soldier+=1;
				else if(game_state[i+2][j+2] == tower)
					target_tower+=1;
			}			
			if(j+1<=n-1 and i+1<=m-1){
				if(game_state[i+1][j+1] == soldier)
					target_soldier+=1;
				else if(game_state[i+1][j+1] == tower)
					target_tower+=1;
			}
		}

		ans[0] = target_soldier;
		ans[1] = target_tower;
		return ans;
	}

	vector<int> cannon_effect(int player){
		int cannon_count = 0;
		int targer_soldier = 0;
		int target_tower = 0;
		vector<int> counts(2);
		vector<int> ans(3);
		for(int i=1; i<m-1; i++){
			for(int j=1; j<n-1; j++){
				if(game_state[i][j]==player){
					if(game_state[i-1][j] == player  && game_state[i+1][j] == player){
						(cannon_count)+=1;
						counts = Targets(i, j, player>0, "horz");
					}
					else if(game_state[i][j-1] == player  and game_state[i][j+1] == player){
						(cannon_count)+=1;
						counts = Targets(i, j, player>0, "vert");
					}
					else if(game_state[i-1][j+1] == player  and game_state[i+1][j-1] == player){
						(cannon_count)+=1;
						counts = Targets(i, j, player>0, "rdiag");
					}
					else if(game_state[i-1][j-1] == player  and game_state[i+1][j+1] == player){
						(cannon_count)+=1;
						counts = Targets(i, j, player>0, "ldiag");
					}
				}
			}
		}
		ans[0] = cannon_count;
		ans[1] = counts[0];
		ans[2] = counts[1];

		return ans;
	}

//Assuming we have a struct of game_state with varibales for the count of soldiers and towers as well
int Evaluation_func(vector< vector<int> > state, int soldier1, int soldier2, int tower1, int tower2){
	m = game_state.size();
	n = game_state[0].size();

	s1 = soldier1;
	s2 = soldier2;
	t1 = tower1;
	t2 = tower2;

	game_state = state;

	int cannon_count_us=0;
	int target_soldier_us = 0;
	int target_tower_us = 0;

	int cannon_count_opp=0;
	int target_soldier_opp = 0;
	int target_tower_opp = 0;

	vector<int> ans(3);
	ans = cannon_effect(1);
	cannon_count_us = ans[0];
	target_soldier_opp = ans[1];
	target_tower_opp = ans[2];
	
	ans = cannon_effect( -1);
	cannon_count_opp = ans[0];
	target_soldier_us = ans[1];
	target_tower_us = ans[2];

	int value = (s1*10) + (t1*100) - (s2*10) - (t2*100) + (target_soldier_opp*5) + (target_tower_opp*50) - (target_soldier_us*5) - (target_tower_us*50);
	return value;
}
