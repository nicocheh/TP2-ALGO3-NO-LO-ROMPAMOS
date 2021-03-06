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
	instancias.open ("peorcaso2.txt");

	std::srand(std::time(0));

	//mis instancias van a tener desde 1 hasta 60 clientes inclusive
	for (int c=1; c<=60; ++c) {
	//elijo la cantidad de fabricas entre 1 y c
		for(int f=1; f<c;++f){
			//para cada tamaño voy a probar 10 casos distintos 
			for (int j=1; j<=10; ++j) {
				int n=f+c;
				vector<vector<int>> matrizAdy(n+1 , vector<int>(n+1, -1)); //aca voy a guardar las aristas para despues cuando las genero automaticamente asegurarme de que no estoy ar5mando un multigrafo sin querer. Es redundancia porque como total no me importa la complejidad de esto lo hago así que facilita la generación del grafo.
				vector<tuple<int, int, int>> aristas;
				//aca voy a poner las aristas que despues van a ir en el input del algoritmo.
				//seguro como es conexo se que quiero tener al menos una vez a cada nodo
				//agrego a cada nodo con un vecino aleatorio entre los que son mas chicos que el. Total los nombres(numeros) de los nodos son un detalle.
				//que 1 este con 2 es isomorfo con que 3 este con 2, y alguno tenia que estar conectado.

				for (int i=f+1; i<=n; ++i) {
					int vecino = 1;
					if (i>f+1) {
						vecino = (std::rand() % (i-2))+1;
					}
					int peso = std::rand() % ((n*n));
					aristas.push_back(make_tuple(i,vecino,peso));		
					matrizAdy[vecino][i] = peso;
					matrizAdy[i][vecino] = peso;
			
				}

				//las aristas pueden ir desde 0 hasta n^2, pero hay n-1 que ya las puse antes para asegurarme que el grafo sea conexo.
				int maxExtras = ((n*(n-1))/2)-(n-f);
				if (n<=2) {
					maxExtras = 1;
				}
				//int aristasExtras = maxExtras;//peor caso
				//int aristasExtras = 0;//mejor caso
				int aristasExtras = std::rand() % maxExtras +1;//random caso
						
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

				int m = aristasExtras + (n-f);
				
				instancias << f << " " << n-f << " " << m << endl;
				for (vector<tuple<int,int,int>>::iterator it=aristas.begin(); it != aristas.end(); ++it) {
					instancias << get<0>(*it) << " " << get<1>(*it) << " " << get<2>(*it) << endl; 
				}

			}
		}
	}

	

	instancias << "0" << endl;
	return 0;
}


