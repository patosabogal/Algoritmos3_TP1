import random
import os
import numpy as np

tester = "../src/./tester"

def encuestasPosibles(n):
    res = []
    for i in range(1,n+1):
        for j in range(1,n+1):
            e1 = str(i) + " " + str(j) + '\n'
            e2 = str(i) + " " + str(-j) + '\n'
            res.append(e1)
            res.append(e2)
    return res


def generateRandomCase(n,i):
    """
    Genera una instancia elegida de forma aleatoria
    de n agentes e i encuestas respondidas.
    """

    out = str(n) + " " + str(i) + '\n'

    l = encuestasPosibles(n)
    op = random.sample(l,i)
    out += "".join(op)
    out += "0 0\n"
    return out

def generateBestCase(n):
    """
    Genera una instancia elegida del mejor caso en el
    cual ninguno de los agentes confia en si mismo de
    manera que todo conjunto no vacio es inconsistente.
    """
    out = str(n) + " " + str(n) + '\n'

    for k in range(1,n+1):
        out += str(k) + " " + str(-k) + '\n'

    out += "0 0\n"
    return out

def testToFile(test,fname):
    """
    Escribe el test a un archivo que se encuentra en path.
    """
    f = open(fname,"w")
    f.write(test)
    f.close()

def generateRandomCase_2(n,i):
    """
    Genera una instancia elegida de forma aleatoria
    de n agentes e i encuestas respondidas.
    """

    out = str(n) + " " + str(i) + '\n'

    l = encuestasPosibles(n)
    op = random.sample(l,i)
    out += "".join(op)
    return out


def generateWorstCase(n):

    """
    Genera una instancia del peor caso para el 
    algoritmo de Backtracking.
    """

    out = str(n) + " " + str(1) + '\n'
    out += "0 0\n"
    return out



def generateWC(n):

    """
    Genera una instancia de un caso exponencial 
    para el algoritmo de backtracking con la poda
    de altura.
    """

    pares = [x for x in range(1,n+1) if x%2 == 0]
    impares = [x for x in range(1,n+1) if x%2 == 1]
    out = str(n) + " " + str(n) + '\n'
    for a in range(1,n+1):
        if a%2==0:
            out += str(a) + " " + str(-impares.pop()) + '\n'
        else:
            out += str(a) + " " + str(-pares.pop()) + '\n'
    
    out += "0 0\n"
    return out




def testInstance(test, reps = 100, algorithm = "1"):
    inp = "fromTestInstance.txt"
    testToFile(test,inp)
    out = "testInstance.csv"
    os.system(tester + " " + inp + " " + out + " " + str(reps) + " " + algorithm)
    res = np.genfromtxt(out,delimiter=";")
    time = res[:,0]
    calls = res[:,1]
    os.remove(out)
    os.remove(inp)
    return time,calls



if __name__ == '__main__':
    #plot_testBestCases(30)
    generateTestFiles(20)
