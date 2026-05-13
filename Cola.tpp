/**
 * \file Cola.tpp
 * Este archivo contiene la implementaci&oacute;n de los m&eacute;todos de la plantilla de clase Cola.
 * \authors
    S&aacute;nchez Montoy, Jes&uacute;s Axel
    Portugal Arreola, Marian Bethsab&eacute;
 * \date 13/03/2026
 */

#include <iostream>

//**********************************************
// CONSTRUCTORES
//**********************************************

template <typename T>
Cola<T>::Cola()
{
    numElem = 0;
    ultimo = nullptr;
}

//**********************************************

template <typename T>
Cola<T>::~Cola()
{
    Vaciar();
}

//**********************************************

template <typename T>
Cola<T>::Cola(const Cola& Cola)
{
    numElem = 0;
    ultimo = nullptr;
    *this = Cola;
}

//***********************************

template <typename T>
Cola<T>& Cola<T>::operator=(const Cola& cola)
{

    if (this == &cola) return *this; // handle self assignment
    //assignment operator

    Vaciar();

    if(cola.ultimo == nullptr){
        return *this;
    }

    Elemento *visitado = cola.ultimo->siguiente;

    do{
        Agregar(visitado->valor);
        visitado = visitado->siguiente;
    }while(visitado != cola.ultimo->siguiente);

    return *this;

}

//**********************************************
// MÉTODOS DE CLASE
//**********************************************

template <typename T>
void Cola<T>::Agregar(T valor)
{
    try{
        Elemento *nuevo = new Elemento(valor, nullptr);

        if(EstaVacia()){
            nuevo->siguiente = nuevo;
        }else{
            nuevo->siguiente = ultimo->siguiente;
            ultimo->siguiente = nuevo;
        }

        ultimo = nuevo;
        ++numElem;

    }catch(const std::bad_alloc&){
        throw ColaNoMemoria();
    }
}

//**********************************************

template <typename T>
void Cola<T>::Eliminar()
{
    if(EstaVacia()){
        throw ColaVacia();
    }

    Elemento *porBorrar = ultimo->siguiente;

    if(ultimo == porBorrar){ // Si el ultimo elemento apunta a si mismo, osea hay solo un elemento
        ultimo = nullptr;
    }else{
        ultimo->siguiente = porBorrar->siguiente;
    }
    delete porBorrar;
    --numElem;
}

//**********************************************

template <typename T>
bool Cola<T>::EstaVacia() const
{
    if(ultimo == nullptr){
        return true;
    }

    return false;
}

//**********************************************

template <typename T>
void Cola<T>::Vaciar()
{
    while(!EstaVacia()) Eliminar();
}

//**********************************************

template <typename T>
T Cola<T>::ObtenerCabeza() const
{
    if(EstaVacia()) throw ColaVacia();
    return (ultimo->siguiente)->valor;
}

//**********************************************

template <typename T>
T Cola<T>::ObtenerCola() const
{
    if(EstaVacia()) throw ColaVacia();
    return ultimo->valor;
}

//***********************************

template <typename T>
int Cola<T>::ObtenerNumElem() const
{
    return numElem;
}

//***********************************

template <typename T>
void Cola<T>::Imprimir() const
{
    if(EstaVacia()){
        std::cout << "La cola est\240 vac\241a.";
        return;
    }

    Elemento *visitado = ultimo->siguiente;
    std::cout << "Cabeza-> ";

    do{
        std::cout << visitado->valor << ", ";
        visitado = visitado->siguiente;
    }while(visitado != ultimo->siguiente);

    if(!EstaVacia()) std::cout << "\b\b <- Ultimo";
}

//***********************************

template <typename T>
Cola<T>::Elemento::Elemento(T val, Elemento *sig /*=nullptr*/) : valor(val), siguiente(sig){}


//***********************************
// Implementación de la clase ColaVacia
//***********************************

template <typename T>
Cola<T>::ColaVacia::ColaVacia() throw() {}

//***********************************

template <typename T>
Cola<T>::ColaNoMemoria::ColaNoMemoria() throw(){}

//***********************************

template <typename T>
const char *Cola<T>::ColaVacia::what() const throw()
{
    return "La Cola se encuentra vac\241a.";
}

//***********************************

template <typename T>
const char *Cola<T>::ColaNoMemoria::what() const throw()
{
    return "No hay memoria disponible.";
}

//**********************************
// Flujos sobrecargados de entrada y salida
//**********************************

template <typename T>
std::ostream & operator<<(std::ostream & salida, const Cola<T> &cola)
{
    cola.Imprimir();
    return salida;
}

