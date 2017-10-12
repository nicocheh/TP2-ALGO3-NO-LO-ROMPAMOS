#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <tuple>
#include <cassert>
#include <queue>
#include<chrono>

using namespace std;

#define ya std::chrono::high_resolution_clock::now

void actualizoVecinos(int proximo, int cantServidores, vector<vector<int>> & matrizAdy, vector<pair<int,bool>> & adyacentesAlAGM) {

	for (int i=1; i<=cantServidores; ++i) {
		
		//solo tiene sentido actualizar los vecinos, ie que la matriz de adyacencia no tenga -1
		if (matrizAdy[proximo][i] != -1) {

			int distanciaNueva = matrizAdy[proximo][i];

			if (adyacentesAlAGM[i].first == -1) {
				adyacentesAlAGM[i].first = proximo;
			}

			int distanciaVieja = matrizAdy[i][adyacentesAlAGM[i].first];

			//actualizo la distancia del vecino este.
			if (distanciaVieja == -1) {
				adyacentesAlAGM[i].first = proximo;
			} else {
				if (distanciaNueva < distanciaVieja) {
					adyacentesAlAGM[i].first = proximo;
				}
			}
		}
	}
	return;
}



int agarraElMasCercano(vector<pair<int,bool>> & adyacentesAlAGM, vector<vector<int>> & matrizAdy) {

	int nuevoNodo = -1;
	// el nuevo nodo es el que voy a agregar al AGM, el que está más cerca.

	for (int i=1; i<adyacentesAlAGM.size(); ++i) {
		
		if (adyacentesAlAGM[i].second == false && adyacentesAlAGM[i].first != -1) {

			if (nuevoNodo == -1) {
				nuevoNodo = i;
			} else {
				int candidatoACercano = matrizAdy[i][adyacentesAlAGM[i].first];
				int masCercanoActual = matrizAdy[nuevoNodo][adyacentesAlAGM[nuevoNodo].first];
				if (candidatoACercano < masCercanoActual) {
					nuevoNodo = i;
				}
			}


		}
	}


	return nuevoNodo;
}


// la consultora1 va a usar el algoritmo de prim para devolver el AGM de este grafo.
// lo devuelve en forma de listas de adyacencia para facilitarle el trabajo a la consultora 2.
tuple<vector<vector<int>>, int, vector<vector<int>>> consultora1(vector<vector<int>> & matrizAdy, int cantServidores) {

	// el -1 significa que no encontré ningun nodo en mi AGM que sea adyacente al nodo i.
	// el int es el nodo del AGM vecino al nodo i, el bool es para marcar si i está en el AGM o todavía no
	// (i, adyacentesAlAGM[i].first) define la arista que estoy agregando al AGM
	vector<pair<int, bool>> adyacentesAlAGM(cantServidores+1, make_pair(-1, false));
	// acá voy a ir buscando el nodo a menor distancia (ie la arista más chica con un nodo
	// ya pintado y el otro no) para agregar en cada paso.


	// este es el arbol que devuelvo en forma de lista de adyacencias
	vector<vector<int>> listaVecinosAGM(cantServidores+1);

	// esta representación del arbol la devuelvo para que sea más facil coutear las aristas como las piden.
	// como es un arbol se que la cantidad de enlaces no es mayor a la cantidad de servidores
	vector<vector<int>> matrizIncidenciaAGM(cantServidores+1, vector<int>(cantServidores+1, 0));


	// agrego un nodo cualquiera y actualizo todos sus vecinos
	adyacentesAlAGM[1] = make_pair(1, true);
	actualizoVecinos(1, cantServidores, matrizAdy, adyacentesAlAGM);


	int costoDelAGM = 0;

	// en la iteración i empiezo con i nodos y termino con i+1 nodos. En la iteración
	// cantServidores-1 tengo un arbol con todos los nodos de mi grafo original.
	for (int i=1; i<cantServidores; ++i) {

		int proximo = agarraElMasCercano(adyacentesAlAGM, matrizAdy);
		
		adyacentesAlAGM[proximo].second = true; //al más cercano lo fijo.

		//agrego esa arista fijada (ie los dos nodos que une) al AGM que devuelvo
		listaVecinosAGM[proximo].push_back(adyacentesAlAGM[proximo].first);
		listaVecinosAGM[adyacentesAlAGM[proximo].first].push_back(proximo);

		costoDelAGM = costoDelAGM + matrizAdy[proximo][adyacentesAlAGM[proximo].first];

		matrizIncidenciaAGM[i][proximo] = 1;
		matrizIncidenciaAGM[i][adyacentesAlAGM[proximo].first] = 1;

		actualizoVecinos(proximo, cantServidores, matrizAdy, adyacentesAlAGM);
	}


	return make_tuple(listaVecinosAGM, costoDelAGM, matrizIncidenciaAGM);
}



//devuelve uno de los nodos más lejanos al nodo de entrada usando BFS
tuple<int, vector<int>> BFSMasLejano(int inNodo, vector<vector<int>> & listaVecinosAGM) {

	queue<int> nodosAExplorar;
	nodosAExplorar.push(inNodo);

	vector<int> distAlInNodo(listaVecinosAGM.size(), -1);
	distAlInNodo[inNodo] = 0;

	//se que como es un arbol, solo se va a quedar vacía la cola al haber explorado todos los nodos
	while ( ! nodosAExplorar.empty()) {

		int actual = nodosAExplorar.front();

		for(vector<int>::iterator it = listaVecinosAGM[actual].begin(); it != listaVecinosAGM[actual].end(); ++it) {
		    
		    //como es un arbol hay un único camino entre cualquier par de nodos, el único vecino que no debería
		    //tener distancia infinita es el padre del actual, es decir por el cual llegamos al actual
		    //y su distancia debería ser menor
		    assert(distAlInNodo[*it] == -1 || distAlInNodo[*it] < distAlInNodo[actual]+1);


		    //si tienen distancia infinita es que todavía no los revisé, los agrego a la cola 
		    //y actualizo su distancia
		    if (distAlInNodo[*it] == -1 ) {
		    	nodosAExplorar.push(*it);
		    	distAlInNodo[*it] = distAlInNodo[actual]+1;
		    }
		 }
		//saco el que acabo de explorar de la cola para pasar a mirar el próximo
		nodosAExplorar.pop();
	}
	
		
	int outNodo = inNodo;
	//ahora voy a agarrar el más lejano al original
	for(int i = 1; i < distAlInNodo.size(); ++i) {
		if (distAlInNodo[i] > distAlInNodo[outNodo]) {
			outNodo = i;
		}
	}
		
	// ahora voy construyendo el camino máximo para después simplemente agarrar la mitad,
	// lo construyo agarrando el nodo que seguro quiero (el más lejano) y de ahí agarrar
	// cualquier vecino suyo que tenga exactamente distancia 1 menor que él, es volver a 
	// recorrer el arbol en la dirección opuesta, no agrega complejidad.
	// Como es 1 arbol va a haber solo 1 vecino con distancia 1 menor, si no habría un ciclo
	// pero aunque hubiera varios todos me servirían porque llevarían al original.
	vector<int> caminoMaximo;
	caminoMaximo.push_back(outNodo);
	int actual = outNodo;
		
	//quiero terminar cuando llegue al nodo del que partí
	while (distAlInNodo[actual] != 0) {
		
		int anterior=outNodo;
		for(vector<int>::iterator it = listaVecinosAGM[actual].begin(); it != listaVecinosAGM[actual].end(); ++it) {
			if (distAlInNodo[*it] == distAlInNodo[actual]-1) {
				anterior = *it;
			}
		}
	
		if (anterior != outNodo){
			caminoMaximo.push_back(anterior);
			actual = anterior;
		}
	}

	return make_tuple(outNodo, caminoMaximo);
}




// la consultora 2 usa dos veces Breadth First Algorithm para encontrar el camino más largo
// del arbol de entrada, luego agarra el nodo en el medio de ese camino, que va a ser la mejor
// raiz para minimizar la altura del arbol enraízado.
tuple<int,int> consultora2(vector<vector<int>> & listaVecinosAGM) {

	//v1 va a ser un extremo del camino más largo del arbol, v2 va a ser el otro
	tuple<int, vector<int>> rta1 = BFSMasLejano(1, listaVecinosAGM);
	int v1 = get<0>(rta1);
	tuple<int, vector<int>> rta2 = BFSMasLejano(v1, listaVecinosAGM);
	std::vector<int> caminoMaximo = get<1>(rta2);

	return make_tuple(caminoMaximo[caminoMaximo.size() / 2], caminoMaximo.size());
}









int main() {

	// cantServidores es la cantidad de nodos del grafo del cual quiero encontrar AGM y raiz de ese AGM
	int cantServidores = 0; 
	// cantEnlaces es la cantidad de aristas del grafo del cual quiero encontrar AGM y raiz de ese AGM
	int cantEnlaces = 0;

	#ifdef TIEMPOS	
	//hago el header del csv
	std::cout << "cantServidores," << "cantEnlaces," << "costoDelAGM," << "maxPathSize," << "tiempoConsultora1," << "tiempoConsultora2," "\n";

	#endif	


	while (true) {

		cin >> cantServidores;
		if (cantServidores==0) {
			return 0;
		}

		cin >> cantEnlaces;

		vector<vector<int>> matrizAdy(cantServidores+1, vector<int>(cantServidores+1, -1)); 
		// como se que los enlaces tienen pesos positivos,
		// si en la matriz hay un -1 es que no hay enlace entre esos servidores


		for (int i=1; i<=cantEnlaces; ++i) {
			int s1 = 0;
			int s2 = 0;
			int peso = 0;
			cin >> s1 >> s2 >> peso;

			matrizAdy[s1][s2] = peso;
			matrizAdy[s2][s1] = peso;
		}

		tuple<int,int> rtaConsultora2;		
		vector<vector<int>> listaVecinosAGM;
		int costoDelAGM;
		vector<vector<int>> matrizIncidenciaAGM;
		tuple<vector<vector<int>>, int, vector<vector<int>>> rtaConsultora1;
		
		#ifdef TIEMPOS
		auto startTime1 = ya();
		for (int i=1; i<=10; ++i) {
			rtaConsultora1 = consultora1(matrizAdy, cantServidores);	
		}
		auto endTime1 = ya();
		#else
		rtaConsultora1 = consultora1(matrizAdy, cantServidores);	
		#endif


		listaVecinosAGM = get<0>(rtaConsultora1);
		costoDelAGM = get<1>(rtaConsultora1);
		matrizIncidenciaAGM = get<2>(rtaConsultora1);


		#ifdef TIEMPOS
		auto startTime2 = ya();
		for (int i=1; i<=10; ++i) {
			rtaConsultora2 = consultora2(listaVecinosAGM);
		}
		auto endTime2 = ya();
		#else 
		rtaConsultora2 = consultora2(listaVecinosAGM);
		#endif
		
		#ifdef TIEMPOS
		auto tiempo1 = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime1-startTime1).count();
		auto tiempo2 = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime2-startTime2).count();

		cout << cantServidores << " " << cantEnlaces << " " <<	costoDelAGM << " ";
		cout << get<1>(rtaConsultora2) << " " << tiempo1/10 << " " << tiempo2/10 << "\n";
		#else
		
		cout << costoDelAGM << " " << get<0>(rtaConsultora2) << " " << cantServidores-1 << " ";


		for (int i=1; i<=cantServidores; ++i) {
			for (int j=1; j<=cantServidores; ++j) {
				if (matrizIncidenciaAGM[i][j] == 1) {
					cout << j << " ";
				}
			}
		}
		
		#endif

	}
}



