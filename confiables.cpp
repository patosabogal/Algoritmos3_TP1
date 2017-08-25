#include "backtracking.cpp"
#include <fstream>
#include <string>
#define to_digit(c) (c - '0')
// Crea una matriz llena de 0s...
std::vector<std::vector<int> >  crearMatrizDeCeros(int filas, int columnas){

	std::vector<std::vector<int> >  matriz(filas,std::vector<int>(columnas,0));

	for (int i = 0; i < filas; ++i){
		for (int j = 0; i < columnas; ++j){

			matriz[i][j] = 0;
			
		}
	}
	return matriz;
}

int main(int argc, char const *argv[]){	
	// Chequeo que la cantidad de parametros este bien
	if(argc != 3){
		printf("%s\n", "El algoritmo toma un file de entrada y \
			       	un file de salida como parametros");
	}

	// Guardo el archivo de entrada y de salida en sus respectivas
	// variables
	std::string entrada = argv[1];
	std::string salida = argv[2];

	// Abro el archivo de entrada en modo lectura	
	std::fstream archivo;
	archivo.open(entrada,std::fstream::in);

	// Leo la primera linea y guardo la cantidad de personas y
	// la cantidad de respuestas en la encuesta
	std::string linea;
	std::getline(archivo,linea);
	int personas = to_digit(linea[0]);
	int respuestas = to_digit(linea[2]);

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
			std::getline(archivo,linea);
			int i = to_digit(linea[0]);
			int j = to_digit(linea[2]);

			if(j > 0){
				votos[i][j] = 1;
			}else{
				votos[i][abs(j)] = -1;
			}
		}

		// Resuelvo este caso con backtracking y guardo el resultado 
        // en el output
		int res = backtracking(votos,personas);

		std::fstream out;
		out.open(salida, std::fstream::app|std::fstream::out);
		out << res << std::endl;
		out.close();

	}
	return 0;
}

