#include <vector>

// Funcion para ver si es confiable o no, devuelve 1, -1 o 0
// si es confiable, ortiva o no lo voto nadie respectivamente.
int esConfiable(std::vector<char> confiables, std::vector<char> ortivas, int nodo , std::vector<std::vector<int> > votos){

	int confiabilidad = 0;
	// Me fijo que no haya votado como confiables a algun ortivas
	// o que haya votado ortiva a algun confiables
	bool votosConsistentes = true;
	for(int i = 0; i < confiables.size(); ++i){
		if(votos[nodo][i] < 0){
			votosConsistentes = false;
			break;
		}
	}

	// Si voto consistentemente, chequeo que dicen los confiables de el.
	if(votosConsistentes){
		for(int i = 0; i < ortivas.size(); ++i){
			if(votos[nodo][i] > 0){
				votosConsistentes == false;
				break;
			}
		}
	
		// Me fijo que dicen los confiables
		int opinionConfiables = 0;
		for (int i = 0; i < confiables.size(); ++i){

			if(votos[i][nodo] > 0){
				opinionConfiables++;
				break;
			}else if(votos[i][nodo] < 0){
				opinionConfiables--;
				break;
			}
		}
		return confiabilidad;

	// Si no voto consistentemente retorno que no es confiable
	}else{
		confiabilidad = -1;
		return confiabilidad;
	}
}

int recursion(std::vector<std::vector<int> > votos, std::vector<char> confiables, std::vector<char> ortivas, int nodo, int personas){

	//  Si llegue al final, devuelvo el conjunto de confiables
	if(nodo == personas){
		return confiables.size();
	}
	else{

		// Si es confiable, lo meto en el conjunto de confiables
		int confiabilidad = esConfiable(confiables,ortivas,nodo,votos);
		
		if(confiabilidad == 1){
			confiables.push_back(nodo);
			return recursion(votos,confiables,ortivas,nodo++,personas);
		}
		// Si es no es confiable, lo pongo con los ortivas
		else if(confiabilidad == -1){
			ortivas.push_back(nodo);
			return  recursion(votos,confiables,ortivas,nodo++,personas);
		}
		// Si nadie lo voto, tengo que llamar la recursion dos veces y tomo el maximo
		else{

			std::vector<char> confiablesAux = confiables;
			std::vector<char> ortivasAux = ortivas;

			confiablesAux.push_back(nodo);
			ortivasAux.push_back(nodo);

			nodo++;

			int asumoConfiable = recursion(votos,confiablesAux,ortivas,nodo,personas);
			int asumoOrtiva = recursion(votos,confiables,ortivasAux,nodo,personas);

			return std::max(asumoConfiable,asumoOrtiva);

		}
	}
}

int backtracking(std::vector<std::vector<int> > votos,int personas){

	std::vector<char> confiables;
	std::vector<char> ortivas;

	int nodo = 0;

	int res = recursion(votos,confiables,ortivas,nodo,personas);

	return res;
}

