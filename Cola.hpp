/**
 * \file Cola.hpp
 * Este archivo contiene la definici&oacute;n de la plantilla de clase Cola con elementos enlazados de forma circular.
 * \authors
S&aacute;nchez Montoy, Jes&uacute;s Axel
Portugal Arreola, Marian Bethsab&eacute;
 * \date 13/03/2026
 * \code{.cpp}
#include <iostream>
#include <string>
#include "Cola.hpp"

int main() {
    try {
        Cola<std::string> fila;

        fila.Agregar("Ana");
        fila.Agregar("Beto");
        fila.Agregar("Carlos");

        std::cout << "Personas en la fila: " << fila.ObtenerNumElem() << std::endl;
        std::cout << "El primero en la fila es: " << fila.ObtenerCabeza() << std::endl;

        std::cout << "\n--- Procesando la fila ---" << std::endl;

        while(!fila.EstaVacia()){
            std::cout << "Atendiendo a: " << fila.ObtenerCabeza() << std::endl;
            fila.Eliminar();
        }

        std::cout << "\nPersonas restantes: " << fila.ObtenerNumElem() << std::endl;

        // Si se saca a alguien de una cola vacia, se lanzara una excepcion
        // fila.Eliminar();

    } catch (const std::exception& error) {
        std::cerr << "Error: " << error.what() << std::endl;
    }

    return 0;
}
 * \endcode
 */

#ifndef COLA_HPP
#define COLA_HPP

#include <exception>

/**
 * \brief Plantilla de clase Cola implementada con elementos enlazados din&aacute;micamente en forma circular.
 *
 * \tparam T Tipo de dato que almacenar&aacute;n los elementos de la cola.
 */
template <typename T>
class Cola {

public:
    /** \brief Constructor por default que inicializa la cola vac&iacute;a.
     */
    Cola();

    /** \brief Destructor por default que libera la memoria din&aacute;mica.
     */
    ~Cola();

    /** \brief Constructor de copias.
     *
     * \param cola Referencia constante a la cola que se desea copiar.
     */
    Cola(const Cola& cola);

    /** \brief Operador de asignaci&oacute;n sobrecargado.
     *
     * \param cola Referencia constante a la cola que se va a asignar a la actual.
     * \return Una referencia a la cola actual (*this).
     * \throw ColaNoMemoria Lanza una excepci&oacute;n si no hay memoria disponible durante la asignaci&oacute;n.
     */
    Cola& operator=(const Cola& cola);

    /** \brief Agrega un nuevo elemento al final de la cola.
     *
     * \param valor Dato de tipo T que la cola guardar&aacute;.
     * \return void
     * \throw ColaNoMemoria Lanza una excepci&oacute;n si falla la asignaci&oacute;n de memoria para el nuevo elemento.
     */
    void Agregar(T valor);

    /** \brief Elimina el elemento que se encuentra al inicio de la cola.
     *
     * \return void
     *
     * \pre
     * La cola no debe estar vac&iacute;a antes de llamar al m&eacute;todo.
     * \throw ColaVacia Lanza una excepci&oacute;n porque no hay elementos para eliminar.
     */
    void Eliminar();

    /** \brief Obtiene el elemento al inicio de la cola.
     *
     * \return El dato almacenado en el primer elemento.
     *
     * \pre
     * La cola debe contener al menos un elemento.
     * \throw ColaVacia Lanza una excepci&oacute;n porque no existen elementos en la cola.
     */
    T ObtenerCabeza() const;

    /** \brief Obtiene el elemento ubicado al final de la cola.
     *
     * \return El dato almacenado en el &uacute;ltimo elemento.
     *
     * \pre
     * La cola debe contener al menos un elemento.
     * \throw ColaVacia Lanza una excepci&oacute;n porque no existen elementos en la cola.
     */
    T ObtenerCola() const;

    /** \brief M&eacute;todo para conocer el n&uacute;mero de elementos actuales en la cola.
     *
     * \return N&uacute;mero entero con la cantidad de elementos en la cola.
     */
    int ObtenerNumElem() const;

    /** \brief Conocer si la cola est&aacute; vac&iacute;a.
     *
     * \return true si la cola no tiene elementos, false en caso contrario.
     */
    bool EstaVacia() const;

    /** \brief Vac&iacute;a la cola y libera la memoria.
     *
     * \return void
     */
    void Vaciar();

    /** \brief Imprime los elementos de la cola.
     *
     * \return void
     */
    void Imprimir() const;

    /**
     * \brief Descripci&oacute;n de la clase/struct: Excepci&oacute;n lanzada cuando se intenta acceder o extraer de una cola vac&iacute;a.
     */
    class ColaVacia : public std::exception {
    public:
        /** \brief Constructor por default de la excepci&oacute;n ColaVacia.
         */
        ColaVacia() throw();

        /** \brief Devuelve una descripci&oacute;n del error al intentar operar con una cola vac&iacute;a.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

    /**
     * \brief Descripci&oacute;n de la clase/struct: Excepci&oacute;n lanzada cuando ocurren fallos de reserva de memoria.
     */
    class ColaNoMemoria : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n ColaNoMemoria.
         */
        ColaNoMemoria() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando no haya memoria disponible.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

private:
    int numElem;                        ///< Entero con el n&uacute;mero de elementos en la cola.

    /**
     * \brief Estructura para representar un elemento en la cola enlazada.
     */
    struct Elemento{
        T valor;                        ///< Dato almacenado en el elemento.
        Elemento *siguiente;            ///< Puntero al elemento siguiente.

        /** \brief Constructor de la estructura Elemento.
         * \param val Dato a almacenar.
         * \param sig Puntero al elemento siguiente.
         */
        Elemento(T val, Elemento *sig);
    };

    Elemento *ultimo;                   ///< Puntero que hace referencia al &uacute;ltimo elemento.
};

#include "Cola.tpp"

#endif // COLA_HPP
