using namespace std;
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <ctime>
#include <fstream>






int main(){
	int trabajos;
	cin>>trabajos;
		while(trabajos!=0){
			vector<vector<int>> precios (trabajos);
			for(int i =0; i<trabajos; ++i){
				for (int j=0; j<i+1; ++j){
					int x;
					cin>>x;
					precios[i].push_back(x);	
				}	
			}
			//precios[a][b] tiene el costo de poner al trabajo a+1 sobre el trabajo b (donde b=0 es sobre maquina vacia)
			
			int costo=0;
			vector<vector<int>> anteriorlista(trabajos);
			//anteriorlista[h] es la lista de impresiones que hizo una maquina al llegar a la anterior impresion a la actual
			// hecha con el trabajo h en alguna maquina (h=0 es con una maquina vacia). Siempre esta ordenado
			
			vector<vector<int>> actuallista(trabajos);
			//actuallista[h] es la lista de impresiones que hizo una de las maquinas al llegar a la actual impresion hecha
			// con el trabajo h en alguna maquina (h=0 es con una maquina vacia). Siempre esta ordenado
			
			vector< int > anteriorcosto(trabajos);
			//anteriorcosto[h] es el costo minimo de llegar a la anterior impresion a la actual hecha con el trabajo h
			// en alguna maquina (h=0 es con una maquina vacia). 
			
			vector< int> actualcosto(trabajos);
			//actualcosto[h] es el costo minimo de llegar a la actual impresion hecha con el trabajo h en alguna maquina.
			//(h=0 es con una maquina vacia). 
					


			for (int q=0; q<trabajos; ++q){//recorro todos los trabajos (numerados 0,...,trabajos-1)
				actualcosto[q]=anteriorcosto[0]+precios[q][0];
				int elegido=0;
				//lo instancio en algo posible minimo, para luego poder ejecutar el minimo sin problemas. Notar que siempre
				//existe el precio de ponerlo sobre vacia.
				for(int h=0; h<q; ++h){
					//recorro sobre que trabajo esta en la maquina en la que no esta q+1 (h=0 es maquina vacia), es q+1 
					//porque la numeracion de los trabajos esta corrida aca, porque en precios lo esta, no recorro h=q 
					//porque en anteriorcosto a lo sumo puedo pedir por el trabajo q-1 (que seria poner anteriorcosto[q])
					//El caso h=q se ejecuta aparte. Actual es con la q+1 impresion ya colocada y anterior con la q.
						
			
					actualcosto[h]=anteriorcosto[h]+precios[q][q];
					//el costo minimo de llegar a la impresión q+1 esima hecha con el trabajo h en alguna maquina es 
					//el costo de llegar a la impresion q esima hecha con el trabajo h en una maquina y poner el q+1
					//sobre el q. Recordar la numeracion corrida de precios!
					
					actuallista[h]=anteriorlista[h];
					if(anteriorlista[h].size()!=0 and anteriorlista[h].back()==q){
						actuallista[h].push_back(q+1);//aca llevo bien numeradas las impresiones.
						//lo agrego a la lista si estaba el trabajo q, pues fue a la misma maquina que el trabajo q,
						//que como tengo ordenada la lista es el ultimo. Si estaba vacía no entro
					}
					
					actualcosto[q]=min(actualcosto[q],anteriorcosto[h]+precios[q][h]);
					//el costo minimo de llegar a la impresion q+1-esima hecha con el trabajo q en una maquina es el 
					//minimo costo de:
						// los que se obtienen de sumar el precio de poner a q+1 sobre el trabajo h con el costo de llegar
						// a la q esima impresion con h en una maquina
					if(actualcosto[q]==anteriorcosto[h]+precios[q][h]){elegido=h;}
					//hago esto de elegido para no copiar el vector todo el tiempo porque afecta complejidad
					
				}
				
				actuallista[q]=anteriorlista[elegido];
				if(anteriorlista[elegido].size()==0 or anteriorlista[elegido].back()!=q){
						actuallista[q].push_back(q+1);//aca llevo bien numeradas las impresiones.
						//lo agrego a la lista si  NO estaba el trabajo q, pues fue a la otra maquina que el trabajo q.
						//como la lista se mantiene ordenada, basta mirar el ultimo trabajo. Si estaba vacía ya entro
					}
			
				
				anteriorcosto=actualcosto;
				anteriorlista=actuallista;
			}
			
			int posicion= min_element(actualcosto.begin(),actualcosto.end())-actualcosto.begin();
			costo=*min_element(actualcosto.begin(),actualcosto.end());
			cout<<costo<< " ";
			cout<<actuallista[posicion].size()<< " ";
			int z=0;
			while(z<actuallista[posicion].size()-1){	
				cout<<actuallista[posicion][z]<< " ";
				++z;
			}		
			cout<<actuallista[posicion][z];
			
			cin>>trabajos;
			if(trabajos!=0){
				cout<<endl; //para que no termine con un endl de mas.
			}
	}
}
