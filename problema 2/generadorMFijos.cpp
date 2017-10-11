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
	instancias.open ("instanciasMFijos.txt");

	std::srand(std::time(0));

	//mis instancias van a tener desde 1 hasta 100 servidores
	for (int n=1; n<=100; ++n) {
		//para cada tamaño voy a probar 100 casos distintos 
		for (int j=1; j<=100; ++j) {


			vector<vector<int>> matrizAdy(n+1 , vector<int>(n+1, -1)); //aca voy a guardar las aristas para despues cuando las genero automaticamente asegurarme de que no estoy ar5mando un multigrafo sin querer. Es redundancia porque como total no me importa la complejidad de esto lo hago así que facilita la generación del grafo.

			vector<tuple<int, int, int>> aristas;
			//aca voy a poner las aristas que despues van a ir en el input del algoritmo.
//seguro como es conexo se que quiero tener al menos una vez a cada nodo
//agrego a cada nodo con un vecino aleatorio entre los que son mas chicos que el. Total los nombres(numeros) de los nodos son un detalle.
//que 1 este con 2 es isomorfo con que 3 este con 2, y alguno tenia que estar conectado.

			for (int i=2; i<=n; ++i) {
				int vecino = 1;
				if (i>2) {
					vecino = (std::rand() % (i-2))+1;
				}
				int peso = std::rand() % ((n*n));
				aristas.push_back(make_tuple(i,vecino,peso));		
				matrizAdy[vecino][i] = peso;
				matrizAdy[i][vecino] = peso;
		
			}

			int maxAristas = (n*(n-1))/2;
			//en estas instancias estoy buscando ver si la cantidad de enlaces afecta a la eficiencia, por
			//lo que no hago que este número sea aleatorio, le voy a dar valores fijos.
			int aristasExtras = 0;
			if (20<j && j<40) {
				aristasExtras=(maxAristas-(n-1))/10;
			}
			if (40<j && j<60) {
				aristasExtras = (maxAristas-(n-1))/5;
			}
			if (60<j && j<80) {
				aristasExtras = (maxAristas-(n-1))/2;
			}
			if (80<j) {
				aristasExtras = (maxAristas-(n-1));
			}

			int m = aristasExtras + n -1;

			assert (m<=((n*(n-1))/2));
						
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
		
			instancias << n << " " << m << "\n";
			for (vector<tuple<int,int,int>>::iterator it=aristas.begin(); it != aristas.end(); ++it) {
				instancias << get<0>(*it) << " " << get<1>(*it) << " " << get<2>(*it) << "\n"; 
			}

		}
	}

	

	instancias << "0" << "\n";
	return 0;
}


