#include <iostream>

#include "ArbolBinBusq.hpp"

using namespace std;

int main(){
    try{
        ArbolBinBusq<int> miArbol;

        cout << "-> Agregando datos al arbol..." << endl;
        miArbol.Agregar(50); // Raiz
        miArbol.Agregar(30);
        miArbol.Agregar(70);
        miArbol.Agregar(20);
        miArbol.Agregar(40);
        miArbol.Agregar(60);
        miArbol.Agregar(80);

        cout << "Total de nodos: " << miArbol.ObtenerNumNodos() << endl;

        cout << "\n-> Imprimiendo arbol..." << endl;
        cout << "Orden Ascendente: ";
        miArbol.ImprimirAsc();
        cout << endl;

        cout << "Por Niveles: ";
        miArbol.ImprimirPorNiveles();
        cout << endl;

        cout << "Como arbol:" << miArbol;

        cout << "\n-> Buscando valores..." << endl;
        cout << "Buscando el 40: " << (miArbol.BuscarNodo(40) ? "Encontrado" : "No encontrado") << endl;
        cout << "Buscando el 99: " << (miArbol.BuscarNodo(99) ? "Encontrado" : "No encontrado") << endl;

        cout << "\nEliminando valores..." << endl;

        cout << "-> Eliminando el 20 (Nodo Hoja)..." << endl;
        miArbol.Eliminar(20);

        cout << "-> Eliminando el 30 (Nodo con dos hijos)..." << endl;
        // Al borrar el 30, tu funcion BuscarDirMayor deberia subir el 40 en su lugar
        miArbol.Eliminar(30);

        cout << "Impresion como arbol despues de borrar:" << miArbol;

        cout << "Nodos restantes: " << miArbol.ObtenerNumNodos() << endl;

        cout << "\n-> Copiando arbol..." << endl;
        ArbolBinBusq<int> arbolCopia;
        arbolCopia = miArbol;

        cout << "Impresion de la copia como arbol:" << miArbol;

        cout << "-> Vaciando..." << endl;
        miArbol.Vaciar();
        cout << "Esta vacio miArbol?: " << (miArbol.EstaVacia() ? "Si" : "No") << endl;

    }catch(const char* mensaje){
        cerr << "Error: " << mensaje << endl;
    }catch(const exception &error){
        cerr << "Error: " << error.what() << endl;
    }catch(...){
        cerr << "El programa tuvo un error inesperado." << endl;
    }

    system("pause");
    return 0;
}
