#include "backtracking.cpp"
#include <chrono>

int signo(int i){
	if(i < 0){
		return -1;
	}else{
		return 1;
	}
}

int main(int argc, char const *argv[]){	
	
	// Me llega por standar input las encuestas
	// la cantidad de respuestas en la encuesta
	std::cin;
	int personas, respuestas;
	std::cin >> personas >> respuestas;

	if(argc != 2 || argv[1] != "1" && argv[1] != "2" && argv[1] != "3" && argv[1] != "4"){
		std::cerr << "Parametros Incorrectos; El programa toma los siguientes paramentros:\n 	1- Backtracking sin podas. \n 	2- Backtracking solo con la poda de optimizacion a futuro.\n 	3- Backtracking solo con la poda de solucion mas grande.\n 	4- Backtracking con las dos podas.\n";		return 0;
	}


	// Leo el archivo hasta llegar al 0 0 que marca el final
	while(personas != 0 && respuestas!= 0){
		

		std::chrono::high_resolution_clock::time_point t1;
 		std::chrono::high_resolution_clock::time_point t2;
 		std::chrono::high_resolution_clock::time_point t1ConPodas;
 		std::chrono::high_resolution_clock::time_point t2ConPodas;
  		std::chrono::duration<double> time_span;
  		std::chrono::duration<double> time_spanConPodas;

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
				votos[i][i] = -1;
			}
		}


		personas--;
		// Resuelvo este caso con backtracking y guardo el resultado 
        // en el output
        int res;

        if(argv[1] == "1"){
			res = backtracking(votos,personas);
        }
        else if(argv[1] == "2"){
			res = backtrackingConPodaMax(votos,personas);
        }
        else if(argv[1] == "3")
		 	res = backtrackingConPodaFut(votos,personas);
		else {
			res = backtrackingConPodas(votos,personas);
		}

		std::cout << res  << std::endl;


		// Leo la nueva encuesta
		std::cin >> personas >> respuestas;
	}
	return 0;
}

