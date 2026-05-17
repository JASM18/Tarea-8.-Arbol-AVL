/**
 * \file main.cpp
 * \brief Este archivo contiene la ejecuci&oacute;n principal y el men&uacute; interactivo para probar la clase ArbolAVL.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 * \date 16/05/2026
 */

#include <iostream>

#include "CapturaSegura.hpp"
#include "ArbolAVL.hpp"

using namespace std;

/**
 * \brief Opciones del men&uacute; principal para el &aacute;rbol AVL.
 */
enum Opciones_principales {
    AGREGAR = 1,        ///< Agrega un nuevo valor al &aacute;rbol.
    ELIMINAR,           ///< Elimina un valor del &aacute;rbol.
    BUSCAR,             ///< Verifica si un valor existe en el &aacute;rbol.
    NUMNODOS,           ///< Muestra el total de nodos del &aacute;rbol.
    ALTURA,             ///< Muestra la altura del &aacute;rbol.
    ESTAVACIA,          ///< Indica si el &aacute;rbol no tiene nodos.
    IMP_ASC,            ///< Imprime los valores del menor al mayor.
    IMP_DESC,           ///< Imprime los valores del mayor al menor.
    IMP_NIVELES,        ///< Imprime los valores por niveles en una sola l&iacute;nea.
    IMP_ARBOL,          ///< Imprime el &aacute;rbol con su estructura jer&aacute;rquica.
    VACIAR,             ///< Elimina todos los nodos del &aacute;rbol.
    SALIR               ///< Termina la ejecuci&oacute;n del programa.
};

int main()
{
    int opcion = -1;
    ArbolAVL<int> arbol;

    int valor;

    do{
        cout << "==================================" << endl;
        cout << "Tarea 8. \240rbol AVL" << endl;
        cout << "==================================" << endl << endl;

        cout << "--- \265RBOL ACTUAL ---" << endl;
        if(arbol.EstaVacia()){
            cout << "El \240rbol est\240 vac\241o." << endl;
        }else{
            arbol.ImprimirComoArbol();
        }
        cout << "--------------------" << endl << endl;

        cout << "Opciones:" << endl;
        cout << "\t" << AGREGAR << ") Agregar un valor." << endl;
        cout << "\t" << ELIMINAR << ") Eliminar un valor." << endl;
        cout << "\t" << BUSCAR << ") Buscar un valor." << endl;
        cout << "\t" << NUMNODOS << ") Obtener n\243mero total de nodos." << endl;
        cout << "\t" << ALTURA << ") Obtener la altura del \240rbol." << endl;
        cout << "\t" << ESTAVACIA << ") Saber si el \240rbol est\240 vac\241o." << endl;
        cout << "\t" << IMP_ASC << ") Imprimir en orden ascendente." << endl;
        cout << "\t" << IMP_DESC << ") Imprimir en orden descendente." << endl;
        cout << "\t" << IMP_NIVELES << ") Imprimir por niveles." << endl;
        cout << "\t" << IMP_ARBOL << ") Imprimir como \240rbol." << endl;
        cout << "\t" << VACIAR << ") Vaciar todo el \240rbol." << endl;
        cout << "\t" << SALIR << ") Salir del programa." << endl;

        do{
            CapturarNumero(opcion, "Elige una opci\242n: ");
        }while(opcion > SALIR || opcion < AGREGAR);

        if(opcion == SALIR) continue;

        try{
            cout << "- - - - -" << endl;
            switch(opcion){

                case AGREGAR:
                    CapturarNumero(valor, "Valor a agregar: ");
                    if(arbol.Agregar(valor)) cout << "Valor agregado correctamente." << endl;
                    else cout << "El valor ya exist\241a en el \240rbol." << endl;
                break;

                case ELIMINAR:
                    if(arbol.EstaVacia()){
                        cout << "El \240rbol est\240 vac\241o, no hay nada que eliminar." << endl;
                    }else{
                        CapturarNumero(valor, "Valor a eliminar: ");
                        if(arbol.Eliminar(valor)) cout << "Valor eliminado correctamente." << endl;
                        else cout << "El valor no existe en el \240rbol." << endl;
                    }
                break;

                case BUSCAR:
                    CapturarNumero(valor, "Valor a buscar: ");
                    if(arbol.BuscarNodo(valor)) cout << "El valor S\326 se encuentra en el \240rbol." << endl;
                    else cout << "El valor NO se encuentra en el \240rbol." << endl;
                break;

                case NUMNODOS:
                    cout << "El \240rbol tiene " << arbol.ObtenerNumNodos() << " nodos." << endl;
                break;

                case ALTURA:
                    cout << "La altura del \240rbol es: " << arbol.ObtenerAltura() << endl;
                break;

                case ESTAVACIA:
                    if(arbol.EstaVacia()) cout << "El \240rbol S\326 est\240 vac\241o." << endl;
                    else cout << "El \240rbol NO est\240 vac\241o." << endl;
                break;

                case IMP_ASC:
                    if(arbol.EstaVacia()){
                        cout << "El \240rbol est\240 vac\241o." << endl;
                    }else{
                        cout << "Orden ascendente: ";
                        arbol.ImprimirAsc();
                        cout << endl;
                    }
                break;

                case IMP_DESC:
                    if(arbol.EstaVacia()){
                        cout << "El \240rbol est\240 vac\241o." << endl;
                    }else{
                        cout << "Orden descendente: ";
                        arbol.ImprimirDesc();
                        cout << endl;
                    }
                break;

                case IMP_NIVELES:
                    if(arbol.EstaVacia()){
                        cout << "El \240rbol est\240 vac\241o." << endl;
                    }else{
                        cout << "Por niveles: ";
                        arbol.ImprimirPorNiveles();
                        cout << endl;
                    }
                break;

                case IMP_ARBOL:
                    if(arbol.EstaVacia()){
                        cout << "El \240rbol est\240 vac\241o." << endl;
                    }else{
                        cout << "Estructura del \240rbol:";
                        arbol.ImprimirComoArbol();
                    }
                break;

                case VACIAR:
                    arbol.Vaciar();
                    cout << "El \240rbol ha sido vaciado por completo." << endl;
                break;
            }

        }catch(const char* mensaje){
            cerr << "Error: " << mensaje << endl;
        }catch(const exception &error){
            cerr << "Error: " << error.what() << endl;
        }catch(...){
            cerr << "El programa tuvo un error inesperado." << endl;
        }

        cout << endl;
        system ("pause");
        system("CLS");
    }while(opcion != SALIR);

    cout << "\nEl programa ha terminado." << endl;

    system("pause");
    return 0;
}
