from game import Game
from RandomPlayer import RandomPlayer
import random
import sys
import time

class Evaluation_func:
	def __init__(self):
		#correct this initial input function
		self.game = Game(self.n, self.m)
		self.state = self.game.current_state()
		self.m = len(self.state)
		self.n = len(self.state[0])
		self.s1 = self.game.numb_soldiers(1)
		self.t1 = self.game.numb_towers(1)
		self.s2 = self.game.numb_soldiers(2)
		self.t2 = self.game.numb_towers(2)
		self.eval()

	def targets(state, target_soldier, target_tower, str, i, j, you):
		if you:
			soldier = 1
			tower = 2
		else:
			soldier = -1
			tower = -2
		if str == "vert":
			if i-2>=0:
				if self.state[i-2][j] == soldier:
					target_soldier+=1
				elif self.state[i-2][j] == tower:
					target_tower+=1
			if i-1>=0:
				if self.state[i-1][j] == soldier:
					target_soldier+=1
				elif self.state[i-1][j] == tower:
					target_tower+=1
			if i+2<=m-1:
				if self.state[i+2][j] == soldier:
					target_soldier+=1
				elif self.state[i+2][j] == tower:
					target_tower+=1
			if i+1<=m-1:
				if self.state[i+1][j] == soldier:
					target_soldier+=1
				elif self.state[i+1][j] == tower:
					target_tower+=1
		elif str == "horz":
			if j-2>=0:
				if self.state[i][j-2] == soldier:
					target_soldier+=1
				elif self.state[i][j-2] == tower:
					target_tower+=1
			if j-1>=0:
				if self.state[i][j-1] == soldier:
					target_soldier+=1
				elif self.state[i][j-1] == tower:
					target_tower+=1
			if j+2<=n-1:
				if self.state[i][j+2] == soldier:
					target_soldier+=1
				elif self.state[i][j+2] == tower:
					target_tower+=1
			if j+1<=n-1:
				if self.state[i][j+1] == soldier:
					target_soldier+=1
				elif self.state[i][j+1] == tower:
					target_tower+=1
		elif str == "rdiag":
			if j-2>=0 and i+2<=m-1:
				if self.state[i+2][j-2] == soldier:
					target_soldier+=1
				elif self.state[i+2][j-2] == tower:
					target_tower+=1
			if j-1>=0 and i+1<=m-1:
				if self.state[i+1][j-1] == soldier:
					target_soldier+=1
				elif self.state[i+1][j-1] == tower:
					target_tower+=1
			if j+2<=n-1 and i-2>=0:
				if self.state[i-2][j+2] == soldier:
					target_soldier+=1
				elif self.state[i-2][j+2] == tower:
					target_tower+=1
			if j+1<=n-1 and i-1>=0:
				if self.state[i-1][j+1] == soldier:
					target_soldier+=1
				elif self.state[i-1][j+1] == tower:
					target_tower+=1
		else:
			if j-2>=0  and i-2>=0:
				if self.state[i-2][j-2] == soldier:
					target_soldier+=1
				elif self.state[i-2][j-2] == tower:
					target_tower+=1
			if j-1>=0 and i-1>=0:
				if self.state[i-1][j-1] == soldier:
					target_soldier+=1
				elif self.state[i-1][j-1] == tower:
					target_tower+=1
			if j+2<=n-1 and i+2<=m-1:
				if self.state[i+2][j+2] == soldier:
					target_soldier+=1
				elif self.state[i+2][j+2] == tower:
					target_tower+=1
			if j+1<=n-1 and i+1<=m-1:
				if self.state[i+1][j+1] == soldier:
					target_soldier+=1
				elif self.state[i+1][j+1] == tower:
					target_tower+=1


	def cannon_effect(self,player):   #player = int 1 or -1
		cannon_count = 0
		targer_soldier = 0
		target_tower = 0
		for i in range(1, m-2) :
			for j in range(1, n-2):
				if self.state[i][j] == player:
					if self.state[i-1][j] == player  and self.state[i+1][j] == player:
						cannon_count+=1
						targets(self.state, target_soldier, target_tower, "horz", i, j, player>0)
					elif self.state[i][j-1] == player  and self.state[i][j+1] == player:
						cannon_count+=1
						targets(self.state, target_soldier, target_tower, "vert", i, j, player>0)
					elif self.state[i-1][j+1] == player  and self.state[i+1][j-1] == player:
						cannon_count+=1
						targets(self.state, target_soldier, target_tower, "rdiag", i, j, player>0)
					elif self.state[i-1][j-1] == player  and self.state[i+1][j+1] == player:
						cannon_count+=1
						targets(self.state, target_soldier, target_tower, "ldiag", i, j, player>0)
		return '{cannon_count} {target_soldier} {target_tower}'.format(cannon_count = int, target_soldier = int, target_tower = int), cannon_count, target_soldier, target_tower

	def evaluate(self):
		cannon_count_opp, targer_soldier_us, target_tower_us = cannon_effect(state, 2)
		cannon_count_us, targer_soldier_opp, target_tower_opp = cannon_effect(state, 1)
		value = (s1*10) + (t1*100) - (s2*10) - (t2*100) + (target_soldier_opp*5) + (target_tower_opp*50) - (targer_soldier_us*5) - (target_tower_us*50)
		return value


# 	def play(self):
# 		if(self.player == 1):
# 			move = sys.stdin.readline().strip()
# 			self.game.execute_move(move)
# 		while(1):
# 			move_sequence = []
# 			while(1):
# 				state = self.game.check_player_state()

# 				if(state == 0):
# 					move, type, x, y = self.selectSoldier()
# 					success = self.game.execute_move(move)
# 					if(success != 0):
# 						move_sequence.append(move)
# 						state = 1

# 				if(state == 1):
# 					while(1):
# 						r = random.randint(0, 10)
# 						if(r < 10):
# 							move, type, x, y = self.moveSoldier()
# 						else:
# 							move, type, x, y = self.throwBomb()
# 						if(move != -1):
# 							break

# 					success = self.game.execute_move(move)
# 					if(success != 0):
# 						move_sequence.append(move)
# 						break

# 			self.play_move_seq(move_sequence)

# 			move = sys.stdin.readline().strip()
# 			self.game.execute_move(move)

# random_player = RandomPlayer()