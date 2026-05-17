#ifndef ARBOLAVL_HPP_INCLUDED
#define ARBOLAVL_HPP_INCLUDED

#include <iostream>

template <typename T>
class ArbolAVL {
public:

    //metodos para el buen funcionamiento de la clase
    ArbolAVL();
    ~ArbolAVL();
    ArbolAVL(const ArbolAVL& arbol);
    ArbolAVL& operator=(const ArbolAVL& arbol);

    void AgregarNodo(T valor);
    bool EliminarNodo(T valor);
    bool BuscarNodo(T valor) const;
    int ObtenerNumNodos() const;
    void Vaciar();
    int ObtenerAltura() const;

    void ImprimirAscendente() const;
    void ImprimirDescendente() const;
    void ImprimirPorNiveles() const;

    /**
     * \brief Descripci&oacute;n de la clase: Excepci&oacute;n lanzada cuando ocurren fallos de memoria din&aacute;mica.
     */
    class ArbolAVLNoMemoria : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n GraficaNoMemoria.
         */
        ArbolAVLNoMemoria() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando no haya memoria disponible.
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

private:

    int numNodos;

    struct Nodo {
        T valor;
        int altura;
        Nodo *hijoIzq, *hijoDer;

        //se inicia con altura 1
        Nodo(T v, Nodo *hIzq = nullptr, Nodo *hDer = nullptr) : valor(v), altura(1), hijoIzq(hIzq), hijoDer(hDer){}
    };

    Nodo *raiz;
    int altura(Nodo* n) const;
    int maximo(int a, int b) const;
    int factorEquilibrio(Nodo* n) const;

    // Rotaciones
    Nodo* rotSimpleIzq(Nodo* n);
    Nodo* rotSimpleDer(Nodo* n);
    Nodo* rotDobleIzq(Nodo* n);
    Nodo* rotDobleDer(Nodo* n);

    Nodo* agregarRecursivo(Nodo* subArbol, T valor, bool& seAgrego);
    Nodo* eliminarRecursivo(Nodo* subArbol, T valor, bool& seElimino);
    Nodo* nodoMinimo(Nodo* n) const;
    void vaciarRecursivo(Nodo* subArbol);
    bool buscarRecursivo(Nodo* subArbol, T valor) const;

    void inOrden(Nodo* subArbol) const;
    void inOrdenInverso(Nodo* subArbol) const;

    void copiarPorNiveles(const ArbolAVL& otroArbol);
};

#include "ArbolAVL.tpp"

#endif // ARBOLAVL_HPP_INCLUDED
