int main(int argc, char const *argv[]){
	
	// Chequeo que la cantidad de parametros este bien
	if(argc != 3){
		printf("%s\n", "El algoritmo toma un file de entrada y un file de \
			salida como parametros");
	}

	// Guardo el archivo de entrada y de salida en sus respectivas variables
	char* entrada = argv[1];
	char* salida = argv[2];

	// Abro el archivo de entrada en modo lectura	
	std::fstream archivo;
	archivo.open(entrada,std::fstream::in);

	// Leo la primera linea y guardo la cantidad de personas y
	// la cantidad de respuestas en la encuesta
	char* linea;
	archivo.getline(linea);
	int personas = atoi(linea[0]);
	int respuestas = atoi(linea[2]);

	// Leo el archivo hasta llegar al 0 0 que marca el final
	while(personas != 0 && respuestas!= 0){
		
		// Creo la matriz "votos" donde voy a guardar las respuestas de cada
		// persona en la votacion. En la posicion votos[i][j] guardo "1" o "-1"
		// si la persona "i" voto que el sujeto "j" es confiable o no confiable
		// respectivamente; En caso de que no lo haya votado quedara el 0 de la
		// inicializacion

		int votos[personas][personas] = crear_matriz_de_ceros(personas,personas);

		for (int r = 0; r < respuestas; r++){

			// Leo las respuestas de la encuesta para llenar la matriz
			archivo.read(linea);
			int i = atoi(linea[0]);
			int j = atoi(linea[2]);

			if(j > 0){
				votos[i][j] = 1;
			}else{
				votos[i][abs(j)] = -1;
			}
		}

		// Resuelvo este caso con backtracking y guardo el resultado en el output
		int res = algoritmo_re_piola_de_back_tracking(votos);

		std::fstream out;
		out.open(out, std::fstream::app);
		out << res << std::endl;
		out.close();

	}

	return 0;
}

// Crea una matriz llena de 0s...
int[][] crear_matriz_de_ceros(int filas, int columnas){

	int matriz[filas][columnas];

	for (int i = 0; i < filas; ++i){
		for (int j = 0; i < columnas; ++j){

			matriz[i][j] = 0;
			
		}
	}
	return matriz;
}