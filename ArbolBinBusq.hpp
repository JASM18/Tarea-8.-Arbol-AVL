#ifndef ARBOLBINBUSQ_HPP
#define ARBOLBINBUSQ_HPP

#include <iostream>
#include <exception>

template<typename T> class ArbolBinBusq;
template<typename T> std::ostream& operator<<(std::ostream& salida, const ArbolBinBusq<T>& arbol);


template<typename T>
class ArbolBinBusq{
    friend std::ostream& operator<< <>(std::ostream& salida, const ArbolBinBusq<T>& arbol);
public:

    // Constructores
    ArbolBinBusq();
    ~ArbolBinBusq();
    ArbolBinBusq(const ArbolBinBusq& arbol);
    ArbolBinBusq &operator=(const ArbolBinBusq &a);

    // Métodos
    bool Agregar(T valor);
    void Eliminar(T valor);

    bool BuscarNodo(T valor) const;

    int ObtenerNumNodos() const;

    bool EstaVacia() const;
    void Vaciar();

    void ImprimirAsc() const; // del menor al mayor
    void ImprimirPorNiveles() const; // se imprime con la estructura del arbol pero bien feo en una sola linea
    void ImprimirComoArbol() const; // se imprime como si fuera un arbol con saltos de linea


    // Clase excepcion
    class ArbolNoMemoria : public std::exception {
    public:
        ArbolNoMemoria() throw();
        virtual const char *what() const throw();
    };

private:
    int numNodos;

    // Estructura de nodo
    struct Nodo{
        T valor;
        Nodo *hijoIzq, *hijoDer;
        Nodo(T v, Nodo *hIzq = nullptr, Nodo *hDer = nullptr);

    }*raiz;

    // Funciones de utileria.
    bool Agregar(T valor, Nodo *& subRaiz);
    void Eliminar(T valor, Nodo *&subRaiz);

    Nodo*& BuscarDirMayor(Nodo *& subRaiz);

    void ImprimirInorden(Nodo *subRaiz) const;

    void Podar(Nodo *&subRaiz);

    void CopiarEnPreorden(Nodo* subRaizOrigen);
};

#include "ArbolBinBusq.tpp"

#endif // ARBOLBINBUSQ_HPP
