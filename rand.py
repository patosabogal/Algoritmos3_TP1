import random
import os
import numpy as np


def genTests(agentes,votos):

	for i in range(votos):
		ag = random.randint(0,agentes+1)
		voto = random.randint(0,agentes+1) 
		if(random.randint(-1,2)):
			print()
