#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <ctime>
#include <fstream>
#include <tuple>
#include <cassert>
#include <queue>


using namespace std;


void actualizoVecinos(int proximo, int n, vector<vector<int>> & matrizAdy, vector<pair<int,bool>> & adyacentesAlG) {

	for (int i=1; i<=n; ++i) {
		
		//solo tiene sentido actualizar los vecinos, ie que la matriz de adyacencia no tenga -1
		if (matrizAdy[proximo][i] != -1) {

			int distanciaNueva = matrizAdy[proximo][i];

			if (adyacentesAlG[i].first == -1) {
				adyacentesAlG[i].first = proximo;
			}

			int distanciaVieja = matrizAdy[i][adyacentesAlG[i].first];

			//actualizo la distancia del vecino este.
			if (distanciaVieja == -1) {
				adyacentesAlG[i].first = proximo;
			} else {
				if (distanciaNueva < distanciaVieja) {
					adyacentesAlG[i].first = proximo;
				}
			}
		}
	}
	return;
}



int agarraElMasCercano(vector<pair<int,bool>> & adyacentesAlG, vector<vector<int>> & matrizAdy, int f) {

	int nuevoNodo = -1;
	// el nuevo nodo es el que voy a agregar al G, el que está más cerca.

	for (int i=f+1; i<adyacentesAlG.size(); ++i) {
		//AL AGARARRAR EL MAS CERCANO SOLO AGARRO EL QUE SEA CLIENTE
		if (adyacentesAlG[i].second == false && adyacentesAlG[i].first != -1) {

			if (nuevoNodo == -1) {
				nuevoNodo = i;
			} else {
				int candidatoACercano = matrizAdy[i][adyacentesAlG[i].first];
				int masCercanoActual = matrizAdy[nuevoNodo][adyacentesAlG[nuevoNodo].first];
				if (candidatoACercano < masCercanoActual) {
					nuevoNodo = i;
				}
			}


		}
	}


	return nuevoNodo;
}


// la consultora1 va a usar el algoritmo de prim para devolver el G de este grafo.
// lo devuelve en forma de listas de adyacencia para facilitarle el trabajo a la consultora 2.
tuple<vector<vector<int>>, int, vector<vector<int>>> PrimModificado(vector<vector<int>> & matrizAdy, int n, int f) {

	// el -1 significa que no encontré ningun nodo en mi G que sea adyacente al nodo i.
	// el int es el nodo del G vecino al nodo i, el bool es para marcar si i está en el G o todavía no
	// (i, adyacentesAlG[i].first) define la arista que estoy agregando al G
	vector<pair<int, bool>> adyacentesAlG(n+1, make_pair(-1, false));
	// acá voy a ir buscando el nodo a menor distancia (ie la arista más chica con un nodo
	// ya pintado y el otro no) para agregar en cada paso.


	// este es el arbol que devuelvo en forma de lista de adyacencias
	vector<vector<int>> listaVecinosG(n+1);

	// esta representación del arbol la devuelvo para que sea más facil coutear las aristas como las piden.
	// como es un arbol se que la cantidad de enlaces no es mayor a la cantidad de servidores
	vector<vector<int>> matrizIncidenciaG(n+1, vector<int>(n+1, 0));


	// agrego un nodo cualquiera y actualizo todos sus vecinos
	for (int j=1;j<=f;++j){
		adyacentesAlG[j] = make_pair(j, true);
		actualizoVecinos(j, n, matrizAdy, adyacentesAlG);
		//ACA PONGO COMO INICIALES A TODOS LOS QUE SON FABRICAS
	}

	int costoDelG = 0;

	// en la iteración i empiezo con 0 clientes y termino con i clientes. En la iteración
	// cantClientes tengo un arbol con todos los nodos de mi grafo original.
	for (int i=1; i<=n-f; ++i) {
		//REPITO TANTAS VECES COMO CLIENTES HAY
		int proximo = agarraElMasCercano(adyacentesAlG, matrizAdy,f);

		//assert(proximo != -1);
		
		adyacentesAlG[proximo].second = true; //al más cercano lo fijo.

		//agrego esa arista fijada (ie los dos nodos que une) al G que devuelvo
		listaVecinosG[proximo].push_back(adyacentesAlG[proximo].first);
		listaVecinosG[adyacentesAlG[proximo].first].push_back(proximo);

		costoDelG = costoDelG + matrizAdy[proximo][adyacentesAlG[proximo].first];

		matrizIncidenciaG[i][proximo] = 1;
		matrizIncidenciaG[i][adyacentesAlG[proximo].first] = 1;

		actualizoVecinos(proximo, n, matrizAdy, adyacentesAlG);
	}


	return make_tuple(listaVecinosG, costoDelG, matrizIncidenciaG);
}

//BASICAMENTE LO QUE HAGO ES MANDARLE EN VEZ DE CANT DE SERVIDORES F+C

int main(){
	
	//std::ofstream instancias;
	//instancias.open ("instanciasRandom2.csv");

	int f,c,r;
	cin>>f;
	int contador=0;
	while( f!=0){
		cin >>c>>r;
		vector<vector<int>> matrizAdy(f+c+1, vector<int>(f+c+1, -1)); 
		// como se que los enlaces tienen pesos positivos,
		// si en la matriz hay un -1 es que no hay enlace entre esos servidores
		
		for (int i=1; i<=r; ++i) {
			int s1 = 0;
			int s2 = 0;
			int peso = 0;
			cin >> s1 >> s2 >> peso;

			matrizAdy[s1][s2] = peso;
			matrizAdy[s2][s1] = peso;
		}
		
		std::clock_t start = clock();
		auto resPrim = PrimModificado(matrizAdy,f+c, f);		
		auto listaVecinosG = get<0>(resPrim);
		auto costoDelG = get<1>(resPrim);
		auto matrizIncidenciaG = get<2>(resPrim);
		std::clock_t fin = clock();
		long long int tiempo = fin-start;
		
		
		//cout << costoDelG << " ";
		
		//ACA HICE ESTE FOR SUPER CABEZA, PARA CONTAR CUANTOS HAY EN EL CAMINO, COPIE LO DE ABAJO Y CONTE
		//Y DIVIDO POR DOS
		int cantaristas=0;
		for (int i=1; i<=f+c; ++i) {
			for (int j=1; j<=f+c; ++j) {
				if (matrizIncidenciaG[i][j] == 1) {
					cantaristas++;
				}
			}
		}
		//cout << cantaristas/2 << " ";

		for (int i=1; i<=f+c; ++i) {
			for (int j=1; j<=f+c; ++j) {
				if (matrizIncidenciaG[i][j] == 1) {
					//cout << j << " ";
				}
			}
		}
		//cout<<endl;
		cout << f << " " << c << " " << r << " " << costoDelG << " " << cantaristas/2 << " " << tiempo << " " << "\n";
		
		cin>>f;
		++contador;
		cerr<<"Iteracion "<<contador<<endl;
	}
}
