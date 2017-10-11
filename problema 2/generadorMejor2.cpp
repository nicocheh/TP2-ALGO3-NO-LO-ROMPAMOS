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
	instancias.open ("instanciasMejor2.txt");

	std::srand(std::time(0));

	//mis instancias van a tener desde 1 hasta 100 servidores
	for (int n=1; n<=100; ++n) {
		//solo pruebo un caso aca que es que en el agm todos queden conectados a un nodo central
		for (int j=1; j<=1; ++j) {


			vector<vector<int>> matrizAdy(n+1 , vector<int>(n+1, -1)); //aca voy a guardar las aristas para despues cuando las genero automaticamente asegurarme de que no estoy ar5mando un multigrafo sin querer. Es redundancia porque como total no me importa la complejidad de esto lo hago así que facilita la generación del grafo.

			vector<tuple<int, int, int>> aristas;
			//aca voy a poner las aristas que despues van a ir en el input del algoritmo.
//seguro como es conexo se que quiero tener al menos una vez a cada nodo
//agrego a cada nodo con un vecino aleatorio entre los que son mas chicos que el. Total los nombres(numeros) de los nodos son un detalle.
//que 1 este con 2 es isomorfo con que 3 este con 2, y alguno tenia que estar conectado.


			for (int i=2; i<=n; ++i) {
				int vecino = 1;
				//hago que todos esten conectados al nodo 1 para que el camino máximo en el 2.2 sea de tamaño 1				
				int peso = std::rand() % ((n*n));
				aristas.push_back(make_tuple(i,vecino,peso));		
				matrizAdy[vecino][i] = peso;
				matrizAdy[i][vecino] = peso;
		
			}

			
			int aristasExtras = 0;
						
						
			//agrego las aristas extras para varias el grafo, pero que no son necesarias para que sea conexo
			for (int i=1; i<=aristasExtras; ++i) {
				int nodoOrigen=1;
				int vecino = 2;
				while (matrizAdy[vecino][nodoOrigen] != -1){
					nodoOrigen = (std::rand() % (n))+1;
					vecino = nodoOrigen;
					while (vecino == nodoOrigen) {
						vecino = (std::rand() % (n))+1;
					}
				}

				int peso = std::rand() % ((n*n));
				aristas.push_back(make_tuple(nodoOrigen,vecino,peso));	
				matrizAdy[vecino][nodoOrigen] = peso;
				matrizAdy[nodoOrigen][vecino] = peso;
			}

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


