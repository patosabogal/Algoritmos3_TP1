#include "backtracking.cpp"

int signo(int i){
	if(i < 0){
		return -1;
	}else{
		return 1;
	}
}

int main(int argc, char const *argv[]){	
	
	bool con_poda = false;
	//std::cout << argv[1] << std::endl;
	int poda = atoi(argv[1]);
	if(poda == 1){
		con_poda = true;
	}

	// Me llega por standar input las encuestas
	// la cantidad de respuestas en la encuesta
	std::cin;
	int personas, respuestas;
	std::cin >> personas >> respuestas;

	// Leo el archivo hasta llegar al 0 0 que marca el final
	while(personas != 0 && respuestas!= 0){
		
		// Creo la matriz "votos" donde voy a guardar las 
		// respuestas de cada persona en la votacion.
		// En la posicion votos[i][j] guardo "1" o "-1" si la 
		// persona "i" voto que el sujeto "j" es confiable o
		// no confiable respectivamente; En caso de que no lo haya
		//  votado quedara el 0 de la inicializacion de la matriz

		std::vector<std::vector<int> >  votos = crearMatrizDeCeros(personas,personas);

		for (int r = 0; r < respuestas; r++){

			// Leo las respuestas de la encuesta para llenar la matriz
			int i;
			int j;

			std::cin >> i >> j;
			i--;
			// El voto es positivo y no voto antes negativamente...
			if(votos[i][abs(j)-1] == 0){
				votos[i][abs(j)-1] = signo(j);
			}else if (signo(j) != votos[i][abs(j)-1]){
				votos[i][abs(j)-1] = -1;
			}
		}

		//imprimirVotos(votos,personas);
		personas--;
		// Resuelvo este caso con backtracking y guardo el resultado 
        // en el output
        int res;
        if(con_poda){
        	//std::cout << "Con poda." << std::endl;
			res = backtrackingConPodas(votos,personas);
		}else{
        	//std::cout << "Sin poda." << std::endl;
			res = backtracking(votos,personas);
 
		}
		std::cout << res << std::endl;

		// Leo la nueva encuesta
		std::cin >> personas >> respuestas;
	}
	return 0;
}

