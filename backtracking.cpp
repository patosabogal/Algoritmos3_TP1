#include <vector>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>

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

// Funcion para ver si el conjunto es consistente o no.
bool consistente(std::vector<std::vector<int> > votos, std::vector<int> confiables, int nodo, int personas){

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

// Backtracking posta
int recursion(std::vector<std::vector<int> > votos, std::vector<int> confiables, int nodo, int personas,int max){
	std::cout << "Nodo: " << nodo  <<std::endl;
	std::cout << "Confiables: ";
	imprimirVector(confiables);
	std::cout << std::endl;
	
	//  Si llegue al final, devuelvo el conjunto de confiables
	if(nodo == personas){ // personas/nodo +1????
		std::cout << "Llegue a una hoja. Tamaño: " << confiables.size() << std::endl;
		return confiables.size();
	}

	else{
        nodo++;
        std::vector<int> no_agrego = confiables;
        confiables.push_back(nodo); // agrego el nodo
        bool consistencia_agrego = consistente(votos,confiables,nodo,personas);
        if((consistencia_agrego)){
		    max = recursion(votos,confiables,nodo,personas,max);
		}
        return std::max(max,recursion(votos,no_agrego,nodo,personas,max));
	}
}

// Wrapper de la funcion de backtracking posta
int backtracking(std::vector<std::vector<int> > votos, int personas){

	std::vector<int> confiables;
	std::cout << "Pre llamada recursiva: " << confiables.size() << std::endl;
	int nodo = 0;

	int res = recursion(votos,confiables,nodo,personas,0);

	return res;
}

