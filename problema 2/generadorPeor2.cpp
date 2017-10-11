#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <tuple>
#include <cassert>
#include <queue>
#include <cstdio>
#include <stdlib.h>
#include <utility>
#include <chrono>

using namespace std;


int main() {


	int repeticiones = 0; 

	std::ofstream instancias;
	instancias.open ("instanciasPeor2.txt");

	std::srand(std::time(0));

	//mis instancias van a tener desde 1 hasta 100 servidores
	for (int n=1; n<=100; ++n) {
		//solo pruebo un caso, el de una tira, o un circuito. La idea es que el camino máximo quede de n nodos.
		for (int j=1; j<=1; ++j) {


			vector<vector<int>> matrizAdy(n+1 , vector<int>(n+1, -1)); //aca voy a guardar las aristas para despues cuando las genero automaticamente asegurarme de que no estoy ar5mando un multigrafo sin querer. Es redundancia porque como total no me importa la complejidad de esto lo hago así que facilita la generación del grafo.

			vector<tuple<int, int, int>> aristas;
			//aca voy a poner las aristas que despues van a ir en el input del algoritmo.
//seguro como es conexo se que quiero tener al menos una vez a cada nodo
//agrego a cada nodo con un vecino aleatorio entre los que son mas chicos que el. Total los nombres(numeros) de los nodos son un detalle.
//que 1 este con 2 es isomorfo con que 3 este con 2, y alguno tenia que estar conectado.

			for (int i=2; i<=n; ++i) {
				int vecino = i-1;
				//si cada uno está conectado al anterior el camino máximo queda de n nodos.
				int peso = std::rand() % ((n*n));
				aristas.push_back(make_tuple(i,vecino,peso));		
				matrizAdy[vecino][i] = peso;
				matrizAdy[i][vecino] = peso;
		
			}

			// para que no se generen caminos mas cortos
			int aristasExtras = 0;
					
			int m = aristasExtras + n -1;
			
			instancias << n << " " << m << "\n";
			for (vector<tuple<int,int,int>>::iterator it=aristas.begin(); it != aristas.end(); ++it) {
				instancias << get<0>(*it) << " " << get<1>(*it) << " " << get<2>(*it) << "\n"; 
			}

		}
	}

	

	instancias << "0" << "\n";
	return 0;
}


