#include "backtracking.cpp"

// Crea una matriz llena de 0s...
std::vector<std::vector<int> >  crearMatrizDeCeros(int filas, int columnas){

	std::vector<std::vector<int> >  matriz(filas,std::vector<int>(columnas,0));

	return matriz;
}

void imprimirVotos(std::vector<std::vector<int> > votos, int personas){

	for (int i = 1; i < personas+1; ++i)
	{
		for (int j = 1; j < personas+1; ++j)
		{
			std::cout << votos[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char const *argv[]){	
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

		std::vector<std::vector<int> >  votos = crearMatrizDeCeros(personas+1,personas+1);

		for (int r = 0; r < respuestas; r++){

			// Leo las respuestas de la encuesta para llenar la matriz
			int i;
			int j;

			std::cin >> i >> j;
			// El voto es positivo y no voto antes negativamente...
			if(j > 0 && votos[i][j] != -1){
				votos[i][j] = 1;
			}else{
				votos[i][abs(j)] = -1;
			}
		}

		imprimirVotos(votos,personas);

		// Resuelvo este caso con backtracking y guardo el resultado 
        // en el output
		int res = backtracking(votos,personas);

		std::cout;
		std::cout << "tamaño: " << res << std::endl;

		// Leo la nueva encuesta
		std::cin >> personas >> respuestas;
	}
	return 0;
}

