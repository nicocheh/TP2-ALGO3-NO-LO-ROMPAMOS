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


bool estaba(vector<pair<int,int>> rutas, int eje1, int eje2){
    bool res=false;
    int i=0;
    while (not res && i<rutas.size()){
        if (eje1==rutas[i].first){
            if (eje2==rutas[i].second){
                res=true;
            }
        }
        ++i;
    }
    return res;
}


ofstream instancias("ej3-C.txt");

int main() {
    
    std::srand(std::time(0));
    
    //output = min+(rand()%(max-min+1))
    //rand() % 5 + 1; sería en el intervalo: [1,5]
    for (int c=50; c>1; --c){//ciclo total: fijamos c = [2,20]. c=1 es el caso trivial
        cerr<<"c="<<c<<endl;
        for (int repeticiones=0; repeticiones<50; ++repeticiones){    
            int f, r;
            f = 5 + rand() % (c-1);                 //random de f=[1,c)
            r = c+f-1 + rand() % ((c+f)*(c+f)-1);     //random de r=[c+f-1,(c+f)^2]
            instancias <<f << " "<<c<<" "<<r<<"\n";
            vector<pair<int,int>> rutas;
            
    
            for (int j=f+1; j<c+f; ++j){//ingresa las rutas para garantizar la conexidad entre fabricas y clientes
                int eje1 = 1 + rand() % (j-1);          //ruta=[1,j)
                int peso = 1 + rand() % 100;            //peso=[1,100]
                instancias <<eje1 << " "<<j<<" "<<peso<<"\n";
                rutas.push_back(make_pair(eje1,j));
            }
    
            for (int k=c+f; k<r; ++k){//ingresa el resto de las rutas
                int eje1 = 1 + rand() % (c+f);          //eje1=[1,c+f]
                int eje2 = 1 + rand() % (c+f);          //eje2=[1,c+f]
                int peso = 1 + rand() % 100;            //peso=[1,100]
                
                
                while (eje1==eje2 || estaba(rutas, min(eje1,eje2), max(eje1,eje2))) {//si llega a pasar que eje1=eje2 (pseudografo) o que ya estaba agregada esa ruta
                    //cambio el eje2 hasta que este todo ok
                    cerr<<"entra al while. c="<<c<<" repes="<<repeticiones<<" k="<<k<<endl;
                    //cerr<<"Antes: eje1 = "<<eje1<<" y eje2 = "<<eje2<<endl;
                    if (not eje1==eje2) eje2 = eje2 + ((1 + rand()) % (c+f));
                    eje1 = eje1 + ((1 + rand()) % (c+f));
                    //cerr<<"Despues: eje1 = "<<eje1<<" y eje2 = "<<eje2<<endl;
                }
                
                rutas.push_back(make_pair(min(eje1,eje2), max(eje1,eje2)));
                
                instancias <<eje1 << " "<<eje2<<" "<<peso<<"\n";
               
               
            }
        }
        for (int l=0; l<10; ++l){
            cerr<<"ITERACION NUMERO "<<c<<endl;
        }
    }
    instancias << "0" << "\n";
    cerr<<"termine"<<endl;
    return 0;
}

