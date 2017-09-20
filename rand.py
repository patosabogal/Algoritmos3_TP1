import random
import sys
import numpy as np


def genVotacion(agentes,votos):
	print "{} {}".format(agentes,votos)
	for i in range(0,votos):
		ag = random.randint(1,agentes)
		voto = random.randint(1,agentes) 
		if random.randint(0,1):
			print "{} {}".format(ag,voto)
		else:
			print"{} {}".format(ag,-voto)


def main(argv):
	
	inicio = int(argv[0])
	total = int(argv[1])
	votosI = int(argv[2])
	votosF = int(argv[3])
	votosStep = int(argv[4])
	cantidad = int(argv[5])
	for i in range(inicio+1,total):
		for j in range(votosI,votosF,votosStep):
			for k in range(cantidad):
				genVotacion(i,j)

	print "0 0"

if __name__ == '__main__':
	main(sys.argv[1:])