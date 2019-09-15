int Evaluation_func(vector< vector<int> > state, int soldier1, int soldier2, int tower1, int tower2, vector<int> weights){
	m = game_state.size();
	n = game_state[0].size();

	s1 = soldier1;
	s2 = soldier2;
	t1 = tower1;
	t2 = tower2;

	game_state = state;

	W_s1 = we
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
