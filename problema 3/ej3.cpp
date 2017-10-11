#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

#define infinito 32767
#define fst first
#define snd second

using namespace std;

struct nodo{
    int ID;
    vector<int> rutasDe;
};
struct ruta{
	int numero;		//numero esta entre [0, r)
    int peso;		//peso>0
    pair<nodo,nodo> nodosQueConecta;
};

void agregarRuta(ruta& nuevaRuta, vector<nodo> nodos, vector<ruta>& rutasTotales, vector<ruta>& rutasPosibles, int f, int e1, int e2){
	//cout<<"entro a agregarRuta"<<endl;
    if (e1<=f){//fabrica-cliente
		//cout<<"fabrica-cliente"<<endl;
		nodos[0].rutasDe.push_back(nuevaRuta.numero);
		//cout<<"nodos[0]"<<endl;
		nodos[e2-f].rutasDe.push_back(nuevaRuta.numero);
		//cout<<"nodos[e2-f]"<<endl;
		rutasPosibles.push_back(nuevaRuta);							//ya lo agrega en los 1ros posibles
		//cout<<"agrega a rP"<<endl;
		nuevaRuta.nodosQueConecta = make_pair(nodos[0],nodos[e2-f]);
		//cout<<"make pair"<<endl;
	}else{
	if (e2<=f){//cliente-fabrica
		//cout<<"cliente-fabrica"<<endl;
		nodos[e1-f].rutasDe.push_back(nuevaRuta.numero);
		nodos[0].rutasDe.push_back(nuevaRuta.numero);		
		rutasPosibles.push_back(nuevaRuta);								//ya lo agrega en los 1ros posibles
		nuevaRuta.nodosQueConecta = make_pair(nodos[e1-f],nodos[0]);
	}else{//cliente-cliente
		//cout<<"cliente-cliente"<<endl;
		nodos[e1-f].rutasDe.push_back(nuevaRuta.numero);
		nodos[e2-f].rutasDe.push_back(nuevaRuta.numero);
		nuevaRuta.nodosQueConecta = make_pair(nodos[e1-f],nodos[e2-f]);
	}
	
	rutasTotales.push_back(nuevaRuta);
}
}

//TO DO: SACAR RUTASTOTALES, ES SOLO PARA EL DEBUG
int minPeso(vector<ruta> rutasPosibles, vector<ruta> rutasTotales){//devuelve el numero de la ruta con menos peso
	int res;
	int pesoMin= infinito;
	for (int i=0; i<rutasPosibles.size(); ++i){
		if (rutasPosibles[i].peso<pesoMin){
			cerr<<"pesoMin: "<<pesoMin<<" en la "<<i<<"-esima operacion"<<endl;
			res=rutasPosibles[i].numero;
			pesoMin=rutasPosibles[i].peso;
		}
	}
	cout<<"Ruta con menos peso: "<<res<<endl;
	cerr<<"pesoMin1: "<<pesoMin<<endl;
	cerr<<"pesoMin2: "<<rutasTotales[res].peso<<endl;
	return res;
}

bool estaEnAGM(vector<nodo> nodosAGM, nodo ciudad){
	bool res=false;
	
	int i=0; 
	while (i<nodosAGM.size() && not res){
		if (ciudad.ID==nodosAGM[i].ID) res=true;
		++i;
	}
	return res;
}

void actualizarPosibles(vector<ruta> rutasTotales, vector<nodo> nodosAGM, ruta rutaMinima, vector<ruta>& rutasPosibles, bool agreguePrimera){ //eliminar de rutasPosibles las asociadas a la ciudad nueva con las ciudades viejas
    if (agreguePrimera){//si la ciudad que agregue era la primera hay que ponerle fst
        for (int j=0; j<rutaMinima.nodosQueConecta.fst.rutasDe.size(); ++j){//recorre las rutas que salen de la nueva ciudad que agregamos
            if (estaEnAGM(nodosAGM, rutasTotales[rutaMinima.nodosQueConecta.fst.rutasDe[j]].nodosQueConecta.fst) && estaEnAGM(nodosAGM, rutasTotales[rutaMinima.nodosQueConecta.fst.rutasDe[j]].nodosQueConecta.snd)){
            //si la j-esima ruta que sale del nuevo nodo que agregamos une dos nodos que estan en el AGM
                //entonces borramos esa ruta de las rutasPosibles
                rutasPosibles.erase(rutasPosibles.begin()+j-1);
            }else{//sino, la agrego a las posibles
				rutasPosibles.push_back(rutasTotales[rutaMinima.nodosQueConecta.fst.rutasDe[j]]);
			}
        }
    }else{//sino, le ponemos snd
        for (int j=0; j<rutaMinima.nodosQueConecta.snd.rutasDe.size(); ++j){
            if (estaEnAGM(nodosAGM, rutasTotales[rutaMinima.nodosQueConecta.snd.rutasDe[j]].nodosQueConecta.fst) && estaEnAGM(nodosAGM, rutasTotales[rutaMinima.nodosQueConecta.snd.rutasDe[j]].nodosQueConecta.snd)){
            //si la j-esima ruta que sale del nuevo nodo que agregamos une dos nodos que estan en el AGM
                //entonces borramos esa ruta de las rutasPosibles
                rutasPosibles.erase(rutasPosibles.begin()+j-1);
            }else{
				rutasPosibles.push_back(rutasTotales[rutaMinima.nodosQueConecta.snd.rutasDe[j]]);
			}
        }        
    }
    //HASTA ACA ELIMINO
    
}


//TO DO: SACARLO. ES SOLO PARA DEBUG
/*
void cerrandoDebug(vector<nodo> nodos, vector<nodo> nodosAGM, vector<ruta> rutasTotales, vector<ruta> rutasAGM, vector<ruta> rutasPosibles){
	cout<<"nodos:"<<endl;
	cout<<"["<<endl<<endl;
	for(int i=0; i<nodos.size()-1;++i){
		cout<<"(ID: "<<nodos[i].ID<<". rutasDe: (";
		for (int j=0; j<nodos[i].rutasDe.size()-1;++j){
			cout<<nodos[i].rutasDe[j]<<", ";
		}
		cout<<nodos[i].rutasDe[nodos[i].rutasDe.size()-1]<<"), ";
	}
	cout<<"(ID: "<<nodos[nodos.size()-1].ID<<". rutasDe: (";
	for (int j=0; j<nodos[nodos.size()-1].rutasDe.size()-1;++j){
			cout<<nodos[nodos.size()-1].rutasDe[j]<<", ";
		}
		cout<<nodos[nodos.size()-1].rutasDe[nodos[nodos.size()-1].rutasDe.size()-1]<<")";
	
	
	if (nodosAGM.size()==0){
		cout<<"]"<<endl<<endl<<"[";
	}else{
		cout<<"]"<<endl<<endl<<"nodosAGM:"<<endl<<"[";
		for(int i=0; i<nodosAGM.size()-1;++i){
			cout<<"(ID: "<<nodosAGM[i].ID<<". rutasDe: (";
			for (int j=0; j<nodosAGM[i].rutasDe.size()-1;++j){
				cout<<nodosAGM[i].rutasDe[j]<<", ";
			}
			cout<<nodosAGM[i].rutasDe[nodosAGM[i].rutasDe.size()-1]<<"), ";
		}
		cout<<"(ID: "<<nodosAGM[nodosAGM.size()-1].ID<<". rutasDe: (";
		for (int j=0; j<nodosAGM[nodosAGM.size()-1].rutasDe.size()-1;++j){
				cout<<nodosAGM[nodosAGM.size()-1].rutasDe[j]<<", ";
			}
			cout<<nodosAGM[nodosAGM.size()-1].rutasDe[nodosAGM[nodosAGM.size()-1].rutasDe.size()-1]<<")";
	}
	
	
	/*
	if (rutasTotales.size()==0){
		cout<<"]"<<endl<<endl<<"[";
	}else{
		cout<<"]"<<endl<<endl<<"rutasTotales:"<<endl<<"[";
		for(int i=0; i<rutasTotales.size()-1;++i){
			cout<<"(numero: "<<rutasTotales[i].numero<<". peso: "<<rutasTotales[i].numero<<". nodos que conecta: ("<<rutasTotales[i].nodosQueConecta.fst<<", "<<rutasTotales[i].nodosQueConecta.snd<<")"<<"), ";
		}
		cout<<"(numero: "<<rutasTotales[rutasTotales.size()-1].numero<<". peso: "<<rutasTotales[rutasTotales.size()-1].numero<<". nodos que conecta: ("<<rutasTotales[rutasTotales.size()-1].nodosQueConecta.fst<<", "<<rutasTotales[rutasTotales.size()-1].nodosQueConecta.snd<<")"<<")";
	}	
	
	
	
	
	if (nodosAGM.size()==0){
		cout<<"]"<<endl<<endl<<"[";
	}else{
		cout<<"]"<<endl<<endl<<"rutasAGM:"<<endl<<"[";
		for(int i=0; i<rutasAGM.size()-1;++i){
			cout<<"(numero: "<<rutasAGM[i].numero<<". peso: "<<rutasAGM[i].numero<<". nodos que conecta: ("<<rutasAGM[i].nodosQueConecta.fst<<", "<<rutasAGM[i].nodosQueConecta.snd<<")"<<"), ";
		}
		cout<<"(numero: "<<rutasAGM[rutasAGM.size()-1].numero<<". peso: "<<rutasAGM[rutasAGM.size()-1].numero<<". nodos que conecta: ("<<rutasAGM[rutasAGM.size()-1].nodosQueConecta.fst<<", "<<rutasAGM[rutasAGM.size()-1].nodosQueConecta.snd<<")"<<")";
	}	
	
	
	

	if (nodosAGM.size()==0){
		cout<<"]"<<endl<<endl<<"[";
	}else{
		cout<<"]"<<endl<<endl<<"rutasPosibles:"<<endl<<"[";
		for(int i=0; i<rutasPosibles.size()-1;++i){
			cout<<"(numero: "<<rutasPosibles[i].numero<<". peso: "<<rutasPosibles[i].numero<<". nodos que conecta: ("<<rutasPosibles[i].nodosQueConecta.fst<<", "<<rutasPosibles[i].nodosQueConecta.snd<<")"<<"), ";
		}
		cout<<"(numero: "<<rutasPosibles[rutasPosibles.size()-1].numero<<". peso: "<<rutasPosibles[rutasPosibles.size()-1].numero<<". nodos que conecta: ("<<rutasPosibles[rutasPosibles.size()-1].nodosQueConecta.fst<<", "<<rutasPosibles[rutasPosibles.size()-1].nodosQueConecta.snd<<")"<<")";
	}
	
* /
	cout<<"]"<<endl<<endl;

}
*/






int main(){
int f, c, r;
cin>>f>>c>>r;
while(f != 0){
	vector<nodo> nodos;//nodos totales: estan ORDENADOS de forma rara: [0]=fabricas; de 1 a c son los clientes
    //ORDENADO por ID-f de nodo
    vector<nodo> nodosAGM;//nodos que se van guardando en el AGM. Al final deberia tener los mismos elementos que el anterior
    //MODIFICABLE
    vector<ruta> rutasTotales;//guarda el conjunto total de rutas
    //ORDENADO por numero de ruta
    vector<ruta> rutasAGM;//va guardando las rutas con menor peso que generan al AGM
    //MODIFICABLE
    vector<ruta> rutasPosibles;//guarda las rutas que tienen un extremo en el AGM y el otro en Totales
    //VARIABLE todo el tiempo
    
    int e1, e2, l;
    int costoTotal=0;

    nodo fabricas;
    fabricas.ID = 0;
    nodos.push_back(fabricas);				//el elemento 0 es el de las fabricas y el resto sigue la numeracion de c-f
    //cerr<<"nodos.size() = "<<nodos.size()<<endl;
    nodosAGM.push_back(fabricas);
    for (int i=f; i<f+c; ++i){										//para todos los clientes
        nodo nuevoNodo;													//crea un nuevo nodo
        nuevoNodo.ID=i;													//cuya ID es un numero entre f+1 y c+f
        nodos.push_back(nuevoNodo);										//lo agrego al cjto de nodos (que esta ordenado)
		//cerr<<"nodos.size() = "<<nodos.size()<<endl;
    }
    //cerr<<"nodos.size() = "<<nodos.size()<<" = c+1="<<c+1<<endl;
    assert(nodos.size()==c+1);
    
    for (int i=0; i<r; ++i){//inserta las rutas en rutasTotales
		cin>>e1>>e2>>l;
        if (e1>f || e2>f){//si ambos son menores (ie, conecta solo fabricas) no nos interesa hacer una ruta entre dos nodos con fabricas
			ruta nuevaRuta;
			nuevaRuta.numero=i;                     //a cada ruta la identificamos con nro (0<=numero<r)
			nuevaRuta.peso=l;
            agregarRuta(nuevaRuta, nodos, rutasTotales, rutasPosibles, f, e1, e2);
        }
        //cerr<<"Iteracion: "<<i<<". nodos.size() = "<<nodos.size()<<endl;
    }
    
    //cerrandoDebug(nodos, nodosAGM, rutasTotales, rutasAGM, rutasPosibles);
    
    for(int i=f+1; i<=f+c; ++i){///este es el ciclo posta del casi prim
        int numRuta = minPeso(rutasPosibles, rutasTotales);
        cout<<"pesoMin2: "<<rutasTotales[numRuta].peso<<endl;
        rutasAGM.push_back(rutasTotales[numRuta]);
        cerr<<"peso minimo: "<<rutasTotales[numRuta].peso<<endl;
        costoTotal+=rutasTotales[numRuta].peso;
        
        bool agreguePrimera;
        if (estaEnAGM(nodosAGM, rutasTotales[numRuta].nodosQueConecta.fst)){
        //si la primera ciudad de la ruta es la que esta en el agm
            //entonces que agregue la segunda ciudad al AGM
            nodosAGM.push_back(rutasTotales[numRuta].nodosQueConecta.snd);
            agreguePrimera=false;
        }else{//si la segunda ciudad de la ruta es la que esta en el agm
            //entonces que agregue la primera ciudad al AGM
            nodosAGM.push_back(rutasTotales[numRuta].nodosQueConecta.fst);
            agreguePrimera=true;
        }
        actualizarPosibles(rutasTotales, nodosAGM, rutasTotales[numRuta], rutasPosibles, agreguePrimera);
        /*
         * tomar el e de minimo peso de rutas
         * agregar e a rutasAGM
         * agregar la nueva ciudad a nodosAGM?
         * eliminar de rutasPosibles las asociadas a la ciudad nueva con las ciudades viejas
         * 
         */
    }
    cerr<<"nodos="<<nodos.size()<<" = nodosAGM="<<nodosAGM.size()<<endl;
    assert(nodos.size()==nodosAGM.size());

    cout<<costoTotal<<" "<<rutasAGM.size();
    for (int k=0; k<rutasAGM.size(); ++k){
        cout<<" "<<rutasAGM[k].nodosQueConecta.fst.ID<<" "<<rutasAGM[k].nodosQueConecta.snd.ID;
    }
    cout<<endl;
cin>>f>>c>>r;
}

return 0;
}

