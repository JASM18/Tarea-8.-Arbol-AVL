//#include <iostream>

#include "Cola.hpp"

//***********************************************
// CONSTRUCTORES
//***********************************************

template<typename T>
ArbolBinBusq<T>::ArbolBinBusq() : numNodos(0), raiz(nullptr)
{
    //numNodos = 0;
    //raiz = nullptr;
}

//***********************************************

template<typename T>
ArbolBinBusq<T>::~ArbolBinBusq()
{
    Vaciar();
}

//***********************************************

template<typename T>
ArbolBinBusq<T>::ArbolBinBusq(const ArbolBinBusq &arbol) : numNodos(0), raiz(nullptr)
{
    *this = arbol;
}

//***********************************************

template<typename T>
ArbolBinBusq<T> & ArbolBinBusq<T>::operator=(const ArbolBinBusq &arbol)
{
    if(this == &arbol) return *this;
    Vaciar();

    CopiarEnPreorden(arbol.raiz);
    return *this;
}

//***********************************************
// METODOS PUBLICOS
//***********************************************

template<typename T>
bool ArbolBinBusq<T>::Agregar(T valor)
{
    return Agregar(valor, raiz);
}

//***********************************************

template<typename T>
void ArbolBinBusq<T>::Eliminar(T valor)
{
    Eliminar(valor,raiz);
}

//***********************************************

template<typename T>
bool ArbolBinBusq<T>::BuscarNodo(T valor) const
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
int ArbolBinBusq<T>::ObtenerNumNodos() const
{
    return numNodos;
}

//***********************************************

template<typename T>
bool ArbolBinBusq<T>::EstaVacia() const
{
    return numNodos == 0;
}

//***********************************************

template<typename T>
void ArbolBinBusq<T>::Vaciar()
{
    Podar(raiz);
}

//***********************************************

template<typename T>
void ArbolBinBusq<T>::ImprimirAsc() const
{
    ImprimirInorden(raiz);
    std::cout << "\b\b ";
}

//***********************************************

template<typename T>
void ArbolBinBusq<T>::ImprimirPorNiveles() const
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
void ArbolBinBusq<T>::ImprimirComoArbol() const
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

            // Si la cola no está vacía, significa que se pone en la cola a los hijos del nivel anterior
            // Entonces, se agrega un nuevo marcador para este nivel
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
bool ArbolBinBusq<T>::Agregar(T valor, Nodo *& subRaiz)
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
    else if(valor == subRaiz->valor) return false; // no permitimos repetidos.
    else if(valor < subRaiz->valor) return Agregar(valor, subRaiz->hijoIzq);
    else return Agregar(valor, subRaiz->hijoDer);
}

//***********************************************

template<typename T>
void ArbolBinBusq<T>::Eliminar(T valor, Nodo *& subRaiz)
{
    if(subRaiz == nullptr) return;
    else if(valor == subRaiz->valor){

        if(subRaiz->hijoIzq != nullptr && subRaiz->hijoDer != nullptr){
            Nodo *& dirMayorMenores = BuscarDirMayor(subRaiz->hijoIzq);
            subRaiz->valor = dirMayorMenores->valor;
            Eliminar(dirMayorMenores->valor, dirMayorMenores);

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
            return;

        }

    }else if(valor < subRaiz->valor) Eliminar(valor, subRaiz->hijoIzq);
    else Eliminar(valor, subRaiz->hijoDer);
}


//***********************************************

template<typename T>
typename ArbolBinBusq<T>::Nodo*& ArbolBinBusq<T>::BuscarDirMayor(Nodo *& subRaiz)
{
    // Vamos todo hacia la derecha hasta encontrar el nodo que no tiene hijo derecho
    if(subRaiz->hijoDer == nullptr){
        return subRaiz;
    }
    return BuscarDirMayor(subRaiz->hijoDer);
}

//***********************************************

template<typename T>
void ArbolBinBusq<T>::ImprimirInorden(Nodo *subRaiz) const
{
    if(subRaiz != nullptr){
        ImprimirInorden(subRaiz->hijoIzq);
        std::cout << subRaiz->valor << ", ";
        ImprimirInorden(subRaiz->hijoDer);
    }

}

//***********************************************

template<typename T>
void ArbolBinBusq<T>::Podar(Nodo *& subRaiz)
{
    // Postorden: izq, derecha, luego subraiz.
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
void ArbolBinBusq<T>::CopiarEnPreorden(Nodo* subRaizOrigen)
{
    if(subRaizOrigen != nullptr){

        this->Agregar(subRaizOrigen->valor); // Se agrega el valor actual

        CopiarEnPreorden(subRaizOrigen->hijoIzq); // vamos pa la izquierda
        CopiarEnPreorden(subRaizOrigen->hijoDer); // vamos pa la derecha
    }
}

//***********************************************
// CONSTRUCTOR DE NODO
//***********************************************

template<typename T>
ArbolBinBusq<T>::Nodo::Nodo(T v, Nodo *hIzq /*= nullptr*/, Nodo *hDer /*= nullptr*/) :
    valor(v), hijoIzq(hIzq), hijoDer(hDer) {}

//***********************************
// EXCEPCIONES
//***********************************

template<typename T>
ArbolBinBusq<T>::ArbolNoMemoria::ArbolNoMemoria() throw() {}

//***********************************

template<typename T>
const char *ArbolBinBusq<T>::ArbolNoMemoria::what() const throw()
{
    return "No hay memoria disponible.";
}

//**********************************
// Flujos sobrecargados de entrada y salida
//**********************************

template<typename T>
std::ostream& operator<<(std::ostream& salida, const ArbolBinBusq<T>& arbol)
{
    arbol.ImprimirComoArbol();
    return salida;
}
