// The program is for adjacency matrix representation of the graph
 
#include <stdio.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class Grafo
{
public:
    Grafo();
    Grafo(int nodos);
    vector< vector<int> > prim();
private:
    const int INF = numeric_limits<int>::max();
    int cn; //cantidad de nodos
    vector< vector<int> > ady; //matriz de adyacencia
};
//**** Finaliza Archivo grafo.h *****//


//**** Comienza Archivo grafo.cpp *****//
Grafo::Grafo()
{
}

Grafo::Grafo(int nodos)
{
    this->cn = nodos;
        this->ady = vector< vector<int> > (cn);

        for(int i = 0; i < cn; i++)
            ady[i] = vector<int> (cn, INF);
}

vector< vector<int> > Grafo :: prim(){
    // uso una copia de ady porque necesito eliminar columnas
    vector< vector<int> > adyacencia = this->ady;
    vector< vector<int> > arbol(cn);
    vector<int> markedLines;
    vector<int> :: iterator itVec;

    // Inicializo las distancias del arbol en INF.
    for(int i = 0; i < cn; i++)
        arbol[i] = vector<int> (cn, INF);

    int padre = 0;
    int hijo = 0;
    while(markedLines.size() + 1 < cn){
        padre = hijo;
        // Marco la fila y elimino la columna del nodo padre.
        markedLines.push_back(padre);
        for(int i = 0; i < cn; i++)
            adyacencia[i][padre] = INF;

        // Encuentro la menor distancia entre las filas marcadas.
        // El nodo padre es la linea marcada y el nodo hijo es la columna del minimo.
        int min = INF;
        for(itVec = markedLines.begin(); itVec != markedLines.end(); itVec++)
            for(int i = 0; i < cn; i++)
                if(min > adyacencia[*itVec][i]){
                    min = adyacencia[*itVec][i];
                    padre = *itVec;
                    hijo = i;
                }

        arbol[padre][hijo] = min;
        arbol[hijo][padre] = min;
    }
    return arbol;
}

int main(){
	Grafo g;
	return 0;
	}

/**
// A utility function to find the vertex with minimum key value, from
// the set of vertices not yet included in MST
int minKey(int key[], bool mstSet[])
{
   // Initialize min value
   int min = INT_MAX, min_index;
 
   for (int v = 0; v < 5; v++)
     if (mstSet[v] == false && key[v] < min)
         min = key[v], min_index = v;
 
   return min_index;
}
 
// A utility function to print the constructed MST stored in parent[]
int printMST(int parent[], int n, int graph[5][5])
{
   printf("Edge   Weight\n");
   for (int i = 1; i < V; i++)
      printf("%d - %d    %d \n", parent[i], i, graph[i][parent[i]]);
}
 
// Function to construct and print MST for a graph represented using adjacency
// matrix representation
void primMST(int graph[5][5])
{
     int parent[5]; // Array to store constructed MST
     int key[5];   // Key values used to pick minimum weight edge in cut
     bool mstSet[5];  // To represent set of vertices not yet included in MST
 
     // Initialize all keys as INFINITE
     for (int i = 0; i < 5; i++)
        key[i] = INT_MAX, mstSet[i] = false;
 
     // Always include first 1st vertex in MST.
     key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
     parent[0] = -1; // First node is always root of MST 
 
     // The MST will have V vertices
     for (int count = 0; count < 5-1; count++)
     {
        // Pick the minimum key vertex from the set of vertices
        // not yet included in MST
        int u = minKey(key, mstSet);
 
        // Add the picked vertex to the MST Set
        mstSet[u] = true;
 
        // Update key value and parent index of the adjacent vertices of
        // the picked vertex. Consider only those vertices which are not yet
        // included in MST
        for (int v = 0; v < 5; v++)
 
           // graph[u][v] is non zero only for adjacent vertices of m
           // mstSet[v] is false for vertices not yet included in MST
           // Update the key only if graph[u][v] is smaller than key[v]
          if (graph[u][v] && mstSet[v] == false && graph[u][v] <  key[v])
             parent[v]  = u, key[v] = graph[u][v];
     }
 
     // print the constructed MST
     printMST(parent, V, graph);
}
 
 
// driver program to test above function
int main()
{
   /* Let us create the following graph
          2    3
      (0)--(1)--(2)
       |   / \   |
      6| 8/   \5 |7
       | /     \ |
      (3)-------(4)
            9          * /
   int graph[5][5] = {{0, 2, 0, 6, 0},
                      {2, 0, 3, 8, 5},
                      {0, 3, 0, 0, 7},
                      {6, 8, 0, 0, 9},
                      {0, 5, 7, 9, 0},
                     };
 
    // Print the solution
    primMST(graph);
 
    return 0;
}*/
