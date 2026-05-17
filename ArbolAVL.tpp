/**
 * \file ArbolAVL.tpp
 * Este archivo contiene la implementaci&oacute;n de los m&eacute;todos de la plantilla de clase ArbolAVL.
 * \authors
    S&aacute;nchez Montoy, Jes&uacute;s Axel
    Portugal Arreola, Marian Bethsab&eacute;
 * \date 16/05/2026
 */

#include "Cola.hpp"

//***********************************************
// CONSTRUCTORES
//***********************************************

template<typename T>
ArbolAVL<T>::ArbolAVL() : numNodos(0), raiz(nullptr) {}

//***********************************************

template<typename T>
ArbolAVL<T>::~ArbolAVL()
{
    Vaciar();
}

//***********************************************

template<typename T>
ArbolAVL<T>::ArbolAVL(const ArbolAVL &arbol) : numNodos(0), raiz(nullptr)
{
    *this = arbol;
}

//***********************************************

template<typename T>
ArbolAVL<T> & ArbolAVL<T>::operator=(const ArbolAVL &arbol)
{
    if(this == &arbol) return *this;
    Vaciar();

    CopiarPorNiveles(arbol);
    return *this;
}

//***********************************************
// METODOS PUBLICOS
//***********************************************

template<typename T>
bool ArbolAVL<T>::Agregar(T valor)
{
    return Agregar(valor, raiz);
}

//***********************************************

template<typename T>
bool ArbolAVL<T>::Eliminar(T valor)
{
    return Eliminar(valor, raiz);
}

//***********************************************

template<typename T>
bool ArbolAVL<T>::BuscarNodo(T valor) const
{
    Nodo *visitado = raiz;

    while(visitado != nullptr){

        if(valor == visitado->valor){
            return true;
        }else if(valor < visitado->valor){
            visitado = visitado->hijoIzq;
        }else{
            visitado = visitado->hijoDer;
        }
    }

    return false;
}

//***********************************************

template<typename T>
int ArbolAVL<T>::ObtenerNumNodos() const
{
    return numNodos;
}

//***********************************************

template<typename T>
int ArbolAVL<T>::ObtenerAltura() const
{
    return Altura(raiz);
}

//***********************************************

template<typename T>
bool ArbolAVL<T>::EstaVacia() const
{
    return numNodos == 0;
}

//***********************************************

template<typename T>
void ArbolAVL<T>::Vaciar()
{
    Podar(raiz);
}

//***********************************************

template<typename T>
void ArbolAVL<T>::ImprimirAsc() const
{
    ImprimirInorden(raiz);
    std::cout << "\b\b ";
}

//***********************************************

template<typename T>
void ArbolAVL<T>::ImprimirDesc() const
{
    ImprimirInordenInverso(raiz);
    std::cout << "\b\b ";
}

//***********************************************

template<typename T>
void ArbolAVL<T>::ImprimirPorNiveles() const
{
    if(EstaVacia()) return;

    Cola<Nodo *> cola;
    Nodo *aux;

    cola.Agregar(raiz);

    while(!cola.EstaVacia()){

        aux = cola.ObtenerCabeza();
        cola.Eliminar();

        std::cout << aux->valor << ", ";
        if(aux->hijoIzq != nullptr) cola.Agregar(aux->hijoIzq);
        if(aux->hijoDer != nullptr) cola.Agregar(aux->hijoDer);
    }
    std::cout << "\b\b ";
}

//***********************************************

template<typename T>
void ArbolAVL<T>::ImprimirComoArbol() const
{
    if(EstaVacia()) return;

    Cola<Nodo *> cola;
    Nodo *aux;

    cola.Agregar(raiz);
    cola.Agregar(nullptr); // para indicar el primer nivel

    std::cout << std::endl;
    while(!cola.EstaVacia()){

        aux = cola.ObtenerCabeza();
        cola.Eliminar();

        if(aux != nullptr){
            std::cout << aux->valor << " ";

            if(aux->hijoIzq != nullptr) cola.Agregar(aux->hijoIzq);
            if(aux->hijoDer != nullptr) cola.Agregar(aux->hijoDer);
        }else{
            // Se debe de hacer salto de linea
            std::cout << std::endl;

            // Si la cola no está vacía, significa que se pone en la cola a los hijos del nivel anterior, entonces, se agrega un nuevo marcador para este nivel
            if(!cola.EstaVacia()){
                cola.Agregar(nullptr);
            }
        }
    }
}

//***********************************************
// METODOS PRIVADOS
//***********************************************

template<typename T>
bool ArbolAVL<T>::Agregar(T valor, Nodo *& subRaiz)
{
    if(subRaiz == nullptr){

        try{
            subRaiz = new Nodo(valor);
            ++numNodos;
            return true;
        }catch(const std::bad_alloc&){
            throw ArbolNoMemoria();
        }
    }
    else if(valor == subRaiz->valor) return false; // no repetidos

    bool seAgrego;
    if(valor < subRaiz->valor) seAgrego = Agregar(valor, subRaiz->hijoIzq);
    else seAgrego = Agregar(valor, subRaiz->hijoDer);

    // Tras la insercion recursiva, actualizamos altura y reequilibramos
    if(seAgrego) Reequilibrar(subRaiz);
    return seAgrego;
}

//***********************************************

template<typename T>
bool ArbolAVL<T>::Eliminar(T valor, Nodo *& subRaiz)
{
    if(subRaiz == nullptr) return false;

    bool seElimino;

    if(valor == subRaiz->valor){

        if(subRaiz->hijoIzq != nullptr && subRaiz->hijoDer != nullptr){
            Nodo *& dirMayorMenores = BuscarDirMenor(subRaiz->hijoIzq);
            subRaiz->valor = dirMayorMenores->valor;
            seElimino = Eliminar(dirMayorMenores->valor, dirMayorMenores);

        }else{

            Nodo *porBorrar = subRaiz;
            if(subRaiz->hijoIzq == nullptr && subRaiz->hijoDer == nullptr){
                subRaiz = nullptr;
            }else if(subRaiz->hijoIzq != nullptr && subRaiz->hijoDer == nullptr){
                subRaiz = subRaiz->hijoIzq;
            }else{
                subRaiz = subRaiz->hijoDer;
            }

            delete porBorrar;
            --numNodos;
            seElimino = true;
        }

    }else if(valor < subRaiz->valor) seElimino = Eliminar(valor, subRaiz->hijoIzq);
    else seElimino = Eliminar(valor, subRaiz->hijoDer);

    // Tras la eliminacion, si el subarbol sigue existiendo, lo reequilibramos.
    if(seElimino && subRaiz != nullptr) Reequilibrar(subRaiz);
    return seElimino;
}

//***********************************************

template<typename T>
typename ArbolAVL<T>::Nodo*& ArbolAVL<T>::BuscarDirMenor(Nodo *& subRaiz)
{
    // Vamos todo hacia la derecha hasta encontrar el nodo que no tiene hijo derecho (el mayor de los menores respecto al nodo que se esta eliminando).
    if(subRaiz->hijoDer == nullptr){
        return subRaiz;
    }
    return BuscarDirMenor(subRaiz->hijoDer);
}

//***********************************************

template<typename T>
void ArbolAVL<T>::ImprimirInorden(Nodo *subRaiz) const
{
    if(subRaiz != nullptr){
        ImprimirInorden(subRaiz->hijoIzq);
        std::cout << subRaiz->valor << ", ";
        ImprimirInorden(subRaiz->hijoDer);
    }
}

//***********************************************

template<typename T>
void ArbolAVL<T>::ImprimirInordenInverso(Nodo *subRaiz) const
{
    if(subRaiz != nullptr){
        ImprimirInordenInverso(subRaiz->hijoDer);
        std::cout << subRaiz->valor << ", ";
        ImprimirInordenInverso(subRaiz->hijoIzq);
    }
}

//***********************************************

template<typename T>
void ArbolAVL<T>::Podar(Nodo *& subRaiz)
{
    if(subRaiz != nullptr){
        Podar(subRaiz->hijoIzq);
        Podar(subRaiz->hijoDer);

        delete subRaiz;
        --numNodos;

        subRaiz = nullptr;

    }
}

//***********************************************

template<typename T>
void ArbolAVL<T>::CopiarPorNiveles(const ArbolAVL &arbolOrigen)
{
    if(arbolOrigen.raiz == nullptr) return;

    Cola<Nodo*> cola;
    cola.Agregar(arbolOrigen.raiz);

    while(!cola.EstaVacia()){
        Nodo* actual = cola.ObtenerCabeza();
        cola.Eliminar();

        this->Agregar(actual->valor); // Insertamos nivel por nivel

        if(actual->hijoIzq != nullptr) cola.Agregar(actual->hijoIzq);
        if(actual->hijoDer != nullptr) cola.Agregar(actual->hijoDer);
    }
}

//***********************************************
// FUNCIONES DE UTILERIA PROPIAS DEL AVL
//***********************************************

template<typename T>
int ArbolAVL<T>::Altura(Nodo *subRaiz) const
{
    if(subRaiz == nullptr) return 0;
    return subRaiz->altura;
}

//***********************************************

template<typename T>
int ArbolAVL<T>::Maximo(int a, int b) const
{
    if(a > b) return a;
    return b;
}

//***********************************************

template<typename T>
int ArbolAVL<T>::FactorEquilibrio(Nodo *subRaiz) const
{
    if(subRaiz == nullptr) return 0;
    return Altura(subRaiz->hijoIzq) - Altura(subRaiz->hijoDer);
}

//***********************************************

template<typename T>
void ArbolAVL<T>::ActualizarAltura(Nodo *subRaiz)
{
    if(subRaiz != nullptr){
        subRaiz->altura = 1 + Maximo(Altura(subRaiz->hijoIzq), Altura(subRaiz->hijoDer));
    }
}

//***********************************************

template<typename T>
void ArbolAVL<T>::Reequilibrar(Nodo *& subRaiz)
{
    // Primero se actualiza la altura del nodo con la informacion de sus hijos
    ActualizarAltura(subRaiz);

    int balance = FactorEquilibrio(subRaiz);

    // Caso desbalanceado hacia la izquierda.
    if(balance > 1){
        if(FactorEquilibrio(subRaiz->hijoIzq) >= 0) RotSimpleDer(subRaiz);
        else RotDobleDer(subRaiz);
    }
    // Caso desbalanceado hacia la derecha
    else if(balance < -1){
        if(FactorEquilibrio(subRaiz->hijoDer) <= 0) RotSimpleIzq(subRaiz);
        else RotDobleIzq(subRaiz);
    }
}

//***********************************************
// ROTACIONES
//***********************************************

template<typename T>
void ArbolAVL<T>::RotSimpleDer(Nodo *& subRaiz)
{
    Nodo *nIzq = subRaiz->hijoIzq;
    Nodo *centro = nIzq->hijoDer;

    nIzq->hijoDer = subRaiz;
    subRaiz->hijoIzq = centro;

    // Se actualizan alturas: primero el nodo que bajo, luego el que subio
    ActualizarAltura(subRaiz);
    ActualizarAltura(nIzq);

    subRaiz = nIzq; // nIzq pasa a ser la nueva subraiz
}

//***********************************************

template<typename T>
void ArbolAVL<T>::RotSimpleIzq(Nodo *& subRaiz)
{
    Nodo *nDer = subRaiz->hijoDer;
    Nodo *centro = nDer->hijoIzq;

    nDer->hijoIzq = subRaiz;
    subRaiz->hijoDer = centro;

    // Se actualizan alturas: primero el nodo que bajo, luego el que subio
    ActualizarAltura(subRaiz);
    ActualizarAltura(nDer);

    subRaiz = nDer; // nDer pasa a ser la nueva subraiz
}

//***********************************************

template<typename T>
void ArbolAVL<T>::RotDobleDer(Nodo *& subRaiz)
{
    RotSimpleIzq(subRaiz->hijoIzq);
    RotSimpleDer(subRaiz);
}

//***********************************************

template<typename T>
void ArbolAVL<T>::RotDobleIzq(Nodo *& subRaiz)
{
    RotSimpleDer(subRaiz->hijoDer);
    RotSimpleIzq(subRaiz);
}

//***********************************************
// CONSTRUCTOR DE NODO
//***********************************************

template<typename T>
ArbolAVL<T>::Nodo::Nodo(T v, Nodo *hIzq /*= nullptr*/, Nodo *hDer /*= nullptr*/) :
    valor(v), altura(1), hijoIzq(hIzq), hijoDer(hDer) {}

//***********************************
// EXCEPCIONES
//***********************************

template<typename T>
ArbolAVL<T>::ArbolNoMemoria::ArbolNoMemoria() throw() {}

//***********************************

template<typename T>
const char *ArbolAVL<T>::ArbolNoMemoria::what() const throw()
{
    return "No hay memoria disponible.";
}

//**********************************
// Flujos sobrecargados de entrada y salida
//**********************************

template<typename T>
std::ostream& operator<<(std::ostream& salida, const ArbolAVL<T>& arbol)
{
    arbol.ImprimirComoArbol();
    return salida;
}
