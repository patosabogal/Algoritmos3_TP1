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

	for (int i = 0; i < personas; ++i)
	{
		for (int j = 0; j < personas; ++j)
		{
			if(votos[i][j]>0) std::cout << "+"<< votos[i][j] << " ";
			else if(votos[i][j]< 0)std::cout <<votos[i][j] << " ";
			else std::cout << " " << votos[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

std::vector<int> personas_restantes(int personas){

	std::vector<int> restantes;
	for (int i = 0; i <= personas; ++i)
	{
		restantes.push_back(i);
	}
	return restantes;
}


void imprimirConfiables(std::vector<int> v){
	std::cout << "Confiables: " << std::endl;
	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << v.at(i)+1 << " ";
	}
	std::cout << std::endl;
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

bool consistente(std::vector<std::vector<int> > votos, std::vector<int> confiables, std::vector<int> recorridos){	
	bool consistencia = true;
	for (int i = 0; i < confiables.size(); ++i){
		// Si lo votaron no confiable o voto a alguien no confiable
		if(votos[confiables.back()][confiables[i]] < 0 || votos[confiables[i]][confiables.back()] < 0){
			consistencia=false;
			break;
		}
	}

	// Si pido uno ya descartado adentro
		for (int i = 0; i < confiables.size(); ++i){
			for (int j = 0; j < recorridos.size(); ++j){
				if((!in(recorridos[j],confiables)) && (votos[confiables[i]][recorridos[j]]> 0)){
					consistencia=false;
					break;
				}
			}
		}
	return consistencia;
}


// Backtracking posta
int recursion(std::vector<std::vector<int> > votos, std::vector<int> confiables, std::vector<int> recorridos, std::vector<int> restantes){

	if(!consistente(votos,confiables,recorridos)) return 0;
	// Si llegue al final, devuelvo el conjunto de confiables
	if(restantes.size() == 0){ // personas/nodo +1????
		return confiables.size();
	}

	else{
		int nuevo = restantes.back();
		restantes.pop_back();
		std::vector<int> no_agrego = confiables;
		confiables.push_back(nuevo); // agrego el nodo
		recorridos.push_back(nuevo); // agrego el nodo
		return std::max(recursion(votos,no_agrego,recorridos,restantes),recursion(votos,confiables,recorridos,restantes));
	}
}	


// Wrapper de la funcion de backtracking posta
int backtracking(std::vector<std::vector<int> > votos, int personas){

	std::vector<int> confiables;
	std::vector<int> recorridos;
	std::vector<int> restantes = personas_restantes(personas);
	int res = recursion(votos,confiables,recorridos,restantes);
	return res;

}


bool consistenteConPoda(std::vector<std::vector<int> > votos, std::vector<int> confiables, std::vector<int> recorridos, std::vector<int> restantes){

	bool consistencia = true;

		for (int i = 0; i < confiables.size(); ++i){
			// Si lo votaron no confiable o voto a alguien no confiable
			if(votos[confiables.back()][confiables[i]] < 0 || votos[confiables[i]][confiables.back()] < 0){
				consistencia=false;
				break;
			}
		}

		// Si pido uno ya descartado adentro
		for (int i = 0; i < confiables.size(); ++i){
			for (int j = 0; j < recorridos.size(); ++j){
				if(!in(i,confiables) && votos[confiables[i]][recorridos[j]]> 0){
					consistencia=false;
					break;
				}
			}
		}


		for (int i = 0; i < confiables.size(); ++i){
			for (int j = 0; j < restantes.size(); ++j){
				// votos inconsistentes a futuro con los de afuera
				if((votos[confiables.back()][restantes[j]] > 0 && votos[confiables[i]][restantes[j]] < 0) || (votos[confiables.back()][restantes[j]] < 0 && votos[confiables[i]][restantes[j]] > 0)){
					consistencia = false;
					break;
				}
			}
		}
		
	return consistencia;
}


int recursionConPodas(std::vector<std::vector<int> > votos, std::vector<int> confiables, std::vector<int> recorridos, std::vector<int> restantes, int& solucionMax){

	if(solucionMax > restantes.size() + confiables.size() || !consistenteConPoda(votos,confiables,recorridos,restantes)) return 0;
	// Si llegue al final, devuelvo el conjunto de confiables
	if(restantes.size()==0){
		if(confiables.size()> solucionMax) solucionMax = confiables.size();
		return confiables.size();
	}

	else{
		int nuevo = restantes.back();
		restantes.pop_back();
		std::vector<int> no_agrego = confiables;
		confiables.push_back(nuevo); // agrego el nodo
		recorridos.push_back(nuevo); // agrego el nodo
		return std::max(recursionConPodas(votos,no_agrego,recorridos,restantes,solucionMax),recursionConPodas(votos,confiables,recorridos,restantes,solucionMax));
	}
}



int backtrackingConPodas(std::vector<std::vector<int> > votos, int personas){

	std::vector<int> confiables;
	std::vector<int> recorridos;
	std::vector<int> restantes = personas_restantes(personas);
	int solucionMax = 0;
	int res = recursionConPodas(votos,confiables,recorridos,restantes,solucionMax);

	return res;
}

int recursionConPodaMax(std::vector<std::vector<int> > votos, std::vector<int> confiables, std::vector<int> recorridos, std::vector<int> restantes, int& solucionMax){

	if(solucionMax > restantes.size() + confiables.size() || !consistente(votos,confiables,recorridos)) return 0;
	// Si llegue al final, devuelvo el conjunto de confiables
	if(restantes.size()==0){
		if(confiables.size() > solucionMax) solucionMax = confiables.size();
		return confiables.size();
	}

	else{
		int nuevo = restantes.back();
		restantes.pop_back();
		std::vector<int> no_agrego = confiables;
		confiables.push_back(nuevo); // agrego el nodo
		recorridos.push_back(nuevo); // agrego el nodo
		return std::max(recursionConPodaMax(votos,no_agrego,recorridos,restantes,solucionMax),recursionConPodaMax(votos,confiables,recorridos,restantes,solucionMax));
	}
}


int backtrackingConPodaMax(std::vector<std::vector<int> > votos, int personas){

	std::vector<int> confiables;
	std::vector<int> recorridos;
	std::vector<int> restantes = personas_restantes(personas);
	int solucionMax = 0;
	int res = recursionConPodaMax(votos,confiables,recorridos,restantes,solucionMax);

	return res;
}

int recursionConPodaFut(std::vector<std::vector<int> > votos, std::vector<int> confiables, std::vector<int> recorridos, std::vector<int> restantes){

	if(!consistenteConPoda(votos,confiables,recorridos,restantes)) return 0;
	// Si llegue al final, devuelvo el conjunto de confiables
	if(restantes.size()==0){
		return confiables.size();
	}

	else{
		int nuevo = restantes.back();
		restantes.pop_back();
		std::vector<int> no_agrego = confiables;
		confiables.push_back(nuevo); // agrego el nodo
		recorridos.push_back(nuevo); // agrego el nodo
		return std::max(recursionConPodaFut(votos,no_agrego,recorridos,restantes),recursionConPodaFut(votos,confiables,recorridos,restantes));
	}
}


int backtrackingConPodaFut(std::vector<std::vector<int> > votos, int personas){

	std::vector<int> confiables;
	std::vector<int> recorridos;
	std::vector<int> restantes = personas_restantes(personas);
	int res = recursionConPodaFut(votos,confiables,recorridos,restantes);

	return res;
}