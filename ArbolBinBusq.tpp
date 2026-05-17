/**
 * \file ArbolAVL.tpp
 * \brief Este archivo contiene la implementaci&oacute;n de los m&eacute;todos de la clase ArbolAVL.
 * \author S&aacute;nchez Montoy, Jes&uacute;s Axel
 * \author Portugal Arreola, Marian Bethsab&eacute;
 */

#include "Cola.hpp"
#include <iostream>

using std::cout;
using std::endl;

//***********************************

template <typename T>
ArbolAVL<T>::ArbolAVL()
{
    raiz = nullptr;
    numNodos = 0;
}

//***********************************

template <typename T>
ArbolAVL<T>::~ArbolAVL()
{
    Vaciar();
}

//***********************************

template <typename T>
ArbolAVL<T>::ArbolAVL(const ArbolAVL& arbol)
{
    raiz = nullptr;
    numNodos = 0;
    *this = arbol;
}

//***********************************

template <typename T>
ArbolAVL<T>& ArbolAVL<T>::operator=(const ArbolAVL& arbol)
{
    if (this == &arbol) return *this;

    Vaciar();
    copiarPorNiveles(arbol);

    return *this;
}

//***********************************
// MÉTODOS PÚBLICOS
//***********************************

template <typename T>
void ArbolAVL<T>::AgregarNodo(T valor)
{
    bool seAgrego = false;

    try {
        raiz = agregarRecursivo(raiz, valor, seAgrego);
        if (seAgrego) numNodos++;
    } catch (const std::bad_alloc&){
        throw ArbolAVLNoMemoria();
    }
}

//***********************************

template <typename T>
bool ArbolAVL<T>::EliminarNodo(T valor)
{
    bool seElimino = false;
    raiz = eliminarRecursivo(raiz, valor, seElimino);
    if (seElimino) numNodos--;
    return seElimino;
}

//***********************************

template <typename T>
bool ArbolAVL<T>::BuscarNodo(T valor) const
{
    return buscarRecursivo(raiz, valor);
}

//***********************************

template <typename T>
int ArbolAVL<T>::ObtenerNumNodos() const
{
    return numNodos;
}

//***********************************

template <typename T>
void ArbolAVL<T>::Vaciar()
{
    vaciarRecursivo(raiz);
    raiz = nullptr;
    numNodos = 0;
}

//***********************************

template <typename T>
int ArbolAVL<T>::ObtenerAltura() const
{
    return altura(raiz);
}

//***********************************

template <typename T>
void ArbolAVL<T>::ImprimirAscendente() const
{
    if (raiz == nullptr){
        cout << "El \240rbol est\240 vac\241o." << endl;
        return;
    }

    inOrden(raiz);
    cout << endl;
}

//***********************************

template <typename T>
void ArbolAVL<T>::ImprimirDescendente() const
{
    if (raiz == nullptr){
        cout << "El \240rbol est\240 vac\241o." << endl;
        return;
    }
    inOrdenInverso(raiz);
    cout << endl;
}

//***********************************

template <typename T>
void ArbolAVL<T>::ImprimirPorNiveles() const
{
    if (raiz == nullptr) {
        cout << "El \240rbol est\240 vac\241o." << endl;
        return;
    }

    Cola<Nodo*> cola;
    cola.Agregar(raiz);

    while (!cola.EstaVacia()){
        Nodo* actual = cola.ObtenerCabeza();
        cola.Eliminar();

        cout << actual->valor << " ";

        if (actual->hijoIzq != nullptr) cola.Agregar(actual->hijoIzq);
        if (actual->hijoDer != nullptr) cola.Agregar(actual->hijoDer);
    }
    cout << endl;
}

//***********************************
// MÉTODOS DE UTILERÍA
//***********************************

template <typename T>
int ArbolAVL<T>::altura(Nodo* n) const
{
    if (n == nullptr){
        return 0;
    }

    return n->altura;
}

//***********************************

template <typename T>
int ArbolAVL<T>::maximo(int a, int b) const
{
    if (a > b) {
        return a;
    } else {
        return b;
    }
}

//***********************************

template <typename T>
int ArbolAVL<T>::factorEquilibrio(Nodo* n) const
{
    if (n == nullptr){
        return 0;
    }
    return altura(n->hijoIzq) - altura(n->hijoDer);
}

//***********************************
// ROTACIONES
//***********************************

template <typename T>
typename ArbolAVL<T>::Nodo* ArbolAVL<T>::rotSimpleDer(Nodo* n)
{
    Nodo* nIzq = n->hijoIzq;
    Nodo* centro = nIzq->hijoDer;

    nIzq->hijoDer = n;
    n->hijoIzq = centro;

    n->altura = maximo(altura(n->hijoIzq), altura(n->hijoDer)) + 1;
    nIzq->altura = maximo(altura(nIzq->hijoIzq), altura(nIzq->hijoDer)) + 1;

    return nIzq;
}

//***********************************

template <typename T>
typename ArbolAVL<T>::Nodo* ArbolAVL<T>::rotSimpleIzq(Nodo* n)
{
    Nodo* nDer = n->hijoDer;
    Nodo* centro = nDer->hijoIzq;

    nDer->hijoIzq = n;
    n->hijoDer = centro;

    n->altura = maximo(altura(n->hijoIzq), altura(n->hijoDer)) + 1;
    nDer->altura = maximo(altura(nDer->hijoIzq), altura(nDer->hijoDer)) + 1;

    return nDer;
}

//***********************************

template <typename T>
typename ArbolAVL<T>::Nodo* ArbolAVL<T>::rotDobleDer(Nodo* n)
{
    n->hijoIzq = rotSimpleIzq(n->hijoIzq);
    return rotSimpleDer(n);
}

//***********************************

template <typename T>
typename ArbolAVL<T>::Nodo* ArbolAVL<T>::rotDobleIzq(Nodo* n)
{
    n->hijoDer = rotSimpleDer(n->hijoDer);
    return rotSimpleIzq(n);
}

//***********************************
// MÉTODOS RECURSIVOS
//***********************************

template <typename T>
typename ArbolAVL<T>::Nodo* ArbolAVL<T>::agregarRecursivo(Nodo* subArbol, T valor, bool& seAgrego)
{
    if (subArbol == nullptr){
        seAgrego = true;
        return new Nodo(valor);
    }

    if (valor < subArbol->valor){
        subArbol->hijoIzq = agregarRecursivo(subArbol->hijoIzq, valor, seAgrego);
    }else if (valor > subArbol->valor){
        subArbol->hijoDer = agregarRecursivo(subArbol->hijoDer, valor, seAgrego);
    }else{
        return subArbol; // No se permiten repetidos
    }

    subArbol->altura = 1 + maximo(altura(subArbol->hijoIzq), altura(subArbol->hijoDer));
    int balance = factorEquilibrio(subArbol);

    // Balanceo
    if (balance > 1 && valor < subArbol->hijoIzq->valor) return rotSimpleDer(subArbol);
    if (balance < -1 && valor > subArbol->hijoDer->valor) return rotSimpleIzq(subArbol);
    if (balance > 1 && valor > subArbol->hijoIzq->valor) return rotDobleDer(subArbol);
    if (balance < -1 && valor < subArbol->hijoDer->valor) return rotDobleIzq(subArbol);

    return subArbol;
}

//***********************************

template <typename T>
typename ArbolAVL<T>::Nodo* ArbolAVL<T>::nodoMinimo(Nodo* n) const
{
    Nodo* actual = n;
    while (actual->hijoIzq != nullptr){
        actual = actual->hijoIzq;
    }
    return actual;
}

//***********************************

template <typename T>
typename ArbolAVL<T>::Nodo* ArbolAVL<T>::eliminarRecursivo(Nodo* subArbol, T valor, bool& seElimino)
{
    if (subArbol == nullptr) return subArbol;

    if (valor < subArbol->valor){
        subArbol->hijoIzq = eliminarRecursivo(subArbol->hijoIzq, valor, seElimino);
    }else if (valor > subArbol->valor){
        subArbol->hijoDer = eliminarRecursivo(subArbol->hijoDer, valor, seElimino);
    }else{
        seElimino = true;

        if ((subArbol->hijoIzq == nullptr) || (subArbol->hijoDer == nullptr)){
            Nodo* temp = subArbol->hijoIzq ? subArbol->hijoIzq : subArbol->hijoDer;

            if (temp == nullptr){
                temp = subArbol;
                subArbol = nullptr;
            }else{
                *subArbol = *temp;
            }
            delete temp;
        }else{
            Nodo* temp = nodoMinimo(subArbol->hijoDer);
            subArbol->valor = temp->valor;
            subArbol->hijoDer = eliminarRecursivo(subArbol->hijoDer, temp->valor, seElimino);
        }
    }

    if (subArbol == nullptr) return subArbol;

    subArbol->altura = 1 + maximo(altura(subArbol->hijoIzq), altura(subArbol->hijoDer));
    int balance = factorEquilibrio(subArbol);

    if (balance > 1 && factorEquilibrio(subArbol->hijoIzq) >= 0) return rotSimpleDer(subArbol);
    if (balance > 1 && factorEquilibrio(subArbol->hijoIzq) < 0) return rotDobleDer(subArbol);
    if (balance < -1 && factorEquilibrio(subArbol->hijoDer) <= 0) return rotSimpleIzq(subArbol);
    if (balance < -1 && factorEquilibrio(subArbol->hijoDer) > 0) return rotDobleIzq(subArbol);

    return subArbol;
}

//***********************************

template <typename T>
void ArbolAVL<T>::vaciarRecursivo(Nodo* subArbol)
{
    if (subArbol != nullptr){
        vaciarRecursivo(subArbol->hijoIzq);
        vaciarRecursivo(subArbol->hijoDer);
        delete subArbol;
    }
}

//***********************************

template <typename T>
bool ArbolAVL<T>::buscarRecursivo(Nodo* subArbol, T valor) const
{
    if (subArbol == nullptr) return false;

    if (valor == subArbol->valor){
        return true;
    }else if (valor < subArbol->valor){
        return buscarRecursivo(subArbol->hijoIzq, valor);
    }else{
        return buscarRecursivo(subArbol->hijoDer, valor);
    }
}

//***********************************

template <typename T>
void ArbolAVL<T>::inOrden(Nodo* subArbol) const
{
    if (subArbol != nullptr){
        inOrden(subArbol->hijoIzq);
        cout << subArbol->valor << " ";
        inOrden(subArbol->hijoDer);
    }
}

//***********************************

template <typename T>
void ArbolAVL<T>::inOrdenInverso(Nodo* subArbol) const
{
    if (subArbol != nullptr){
        inOrdenInverso(subArbol->hijoDer);
        cout << subArbol->valor << " ";
        inOrdenInverso(subArbol->hijoIzq);
    }
}

//***********************************

template <typename T>
void ArbolAVL<T>::copiarPorNiveles(const ArbolAVL& otroArbol)
{
    if (otroArbol.raiz == nullptr) return;

    Cola<Nodo*> cola;
    cola.Agregar(otroArbol.raiz);

    while (!cola.EstaVacia()){
        Nodo* actual = cola.ObtenerCabeza();
        cola.Eliminar();

        AgregarNodo(actual->valor);

        if (actual->hijoIzq != nullptr) cola.Agregar(actual->hijoIzq);
        if (actual->hijoDer != nullptr) cola.Agregar(actual->hijoDer);
    }
}

//***********************************
// EXCEPCIONES
//***********************************

template <typename T>
ArbolAVL<T>::ArbolAVLNoMemoria::ArbolAVLNoMemoria() throw() {}

//***********************************

template <typename T>
const char *ArbolAVL<T>::ArbolAVLNoMemoria::what() const throw()
{
    return "No hay memoria disponible.";
}
