#include <vector>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

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


void imprimirVector(std::vector<int> v){

	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << v.at(i) << " ";
	}

}

bool in(int valor,std::vector<int> v){
	for (int i = 0; i < v.size(); ++i)
	{
		if(valor == v[i]){
			return true;
		}
	}
	return false;
}

bool consistente(std::vector<std::vector<int> > votos, std::vector<int> confiables, int nodo, int personas){	
	bool consistencia = true;
	if(in(nodo,confiables)){
		for (int i = 0; i < confiables.size(); ++i)
		{
			if(votos[nodo][confiables[i]] < 0 || votos[confiables[i]][nodo] < 0){
				consistencia=false;
				break;
			}
		}	
	}else{
		for (int i = 0; i < confiables.size(); ++i){
			if(votos[confiables[i]][nodo] > 0){
				consistencia=false;
				break;
			}
		}	
	}
	return consistencia;
}
// Funcion para ver si el conjunto es consistente o no.
bool consistente2(std::vector<std::vector<int> > votos, std::vector<int> confiables, int nodo, int personas){

	bool consistencia = true;
	// Primero chequeo que no haya inconsistencia entre el nuevo grupo.
	for(int i = 0; i < confiables.size(); ++i){
		for (int j = 0; j < confiables.size(); ++j){
			if(votos[confiables[i]][confiables[j]] < 0){
				consistencia = false;
				break;
			}
		}		
	}
	// Ahora chequeo que no haya inconsistencia entre el nuevo grupo
	// y los no agregados.
	for (int i = 0; i < confiables.size(); ++i){
		for (int j = 0; j < nodo && !in(j,confiables); ++j){
			if(votos[confiables[i]][j] > 0){
				consistencia = false;
			break;
			}	
		}
	}

	//std::cout << consistencia << std::endl;
	return consistencia;
}


bool consistenteConPodas(std::vector<std::vector<int> > votos, std::vector<int> confiables, int nodo, int personas){

	bool consistencia = true;
	if(in(nodo,confiables)){
		for (int i = 0; i < confiables.size(); ++i)
		{
			if(votos[nodo][confiables[i]] < 0 || votos[confiables[i]][nodo] < 0){
				consistencia=false;
				break;
			}
		}
		for (int i = 0; i < confiables.size(); ++i){
				for (int j = nodo+1; j < personas; ++j){
					if((votos[nodo][j] > 0 && votos[confiables[i]][nodo] < 0) || (votos[nodo][j] < 0 && votos[confiables[i]][nodo] > 0)){
						consistencia = false;
						break;
					}
				}
			}	
	}else{
		for (int i = 0; i < confiables.size(); ++i){
			if(votos[confiables[i]][nodo] > 0){
				consistencia=false;
				break;
			}
		}	
	}
	return consistencia;
}

// Backtracking posta
int recursion(std::vector<std::vector<int> > votos, std::vector<int> confiables, int nodo, int personas,int& iteracion){
	iteracion++;
	if(!consistente(votos,confiables,nodo,personas)) return 0;
	// Si llegue al final, devuelvo el conjunto de confiables
	if(nodo == personas){ // personas/nodo +1????
		return confiables.size();
	}

	else{
		nodo++;
		std::vector<int> no_agrego = confiables;
		confiables.push_back(nodo); // agrego el nodo
		return std::max(recursion(votos,no_agrego,nodo,personas,iteracion),recursion(votos,confiables,nodo,personas,iteracion));
	}
}	

int recursionConPodas(std::vector<std::vector<int> > votos, std::vector<int> confiables, int nodo, int personas, int& max, int& iteracion){
	iteracion++;
	if(max >= personas - nodo + confiables.size() || !consistenteConPodas(votos,confiables,nodo,personas)) return 0;
	// Si llegue al final, devuelvo el conjunto de confiables
	if(nodo == personas){ // personas/nodo +????
		if(confiables.size()>max) max = confiables.size();
		return confiables.size();
	}

	else{
		nodo++;
		std::vector<int> no_agrego = confiables;
		confiables.push_back(nodo); // agrego el nodo
		return std::max(recursionConPodas(votos,no_agrego,nodo,personas,max,iteracion),recursionConPodas(votos,confiables,nodo,personas,max,iteracion));
	}
}

// Wrapper de la funcion de backtracking posta
int backtracking(std::vector<std::vector<int> > votos, int personas){

	std::vector<int> confiables;
	std::cout << "Pre llamada recursiva: " << confiables.size() << std::endl;
	int nodo = 0;
	int iteracion = 0;
	int res = recursion(votos,confiables,nodo,personas,iteracion);
	std::cout << iteracion << std::endl;
	return res;
}




int backtrackingConPodas(std::vector<std::vector<int> > votos, int personas){

	std::vector<int> confiables;
	int nodo = 0;
	int max = 0;
	int iteracion = 0;
	int res = recursionConPodas(votos,confiables,nodo,personas,max,iteracion);
	std::cout << iteracion << std::endl;
	return res;
}

