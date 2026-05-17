/**
 * \file ArbolAVL.hpp
 * \brief Este archivo contiene la definici&oacute;n de la plantilla de clase ArbolAVL, un &aacute;rbol binario de b&uacute;squeda autobalanceado.
 * \authors
    S&aacute;nchez Montoy, Jes&uacute;s Axel
    Portugal Arreola, Marian Bethsab&eacute;
 * \date 16/05/2026
 * \code{.cpp}
 #include <iostream>

#include "ArbolAVL.hpp"

using namespace std;

int main(){

    try{
        ArbolAVL<int> miArbol;

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
        miArbol.Eliminar(30);

        cout << "Impresion como arbol despues de borrar:" << miArbol;

        cout << "Nodos restantes: " << miArbol.ObtenerNumNodos() << endl;

        cout << "\n-> Copiando arbol..." << endl;
        ArbolAVL<int> arbolCopia;
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
 * \endcode
 */
#ifndef ARBOLAVL_HPP_INCLUDED
#define ARBOLAVL_HPP_INCLUDED

#include <iostream>
#include <exception>

template<typename T> class ArbolAVL;
template<typename T> std::ostream& operator<<(std::ostream& salida, const ArbolAVL<T>& arbol);

/**
 * \brief Plantilla de clase que implementa un &aacute;rbol AVL (&aacute;rbol binario de b&uacute;squeda autobalanceado).
 *
 * Mantiene la propiedad de b&uacute;squeda y, tras cada inserci&oacute;n o eliminaci&oacute;n, se reequilibra
 * mediante rotaciones para que la diferencia de alturas entre sub&aacute;rboles nunca exceda de uno.
 */
template<typename T>
class ArbolAVL{
    /** \brief Operador de salida que imprime el &aacute;rbol en el flujo dado.
     *  \param salida Flujo de salida sobre el que se escribe.
     *  \param arbol &Aacute;rbol que se desea imprimir.
     *  \return Referencia al flujo de salida recibido.
     */
    friend std::ostream& operator<< <>(std::ostream& salida, const ArbolAVL<T>& arbol);
public:

    /** \brief Constructor por defecto. Crea un &aacute;rbol vac&iacute;o. */
    ArbolAVL();

    /** \brief Destructor. Libera toda la memoria din&aacute;mica del &aacute;rbol. */
    ~ArbolAVL();

    /** \brief Constructor de copias.
     *  \param arbol &Aacute;rbol del cual se realiza la copia.
     */
    ArbolAVL(const ArbolAVL& arbol);

    /** \brief Operador de asignaci&oacute;n.
     *  \param a &Aacute;rbol al cual se desea igualar este objeto.
     *  \return Una referencia a this.
     */
    ArbolAVL &operator=(const ArbolAVL &a);

    /** \brief Agrega un nuevo valor al &aacute;rbol y lo reequilibra si es necesario.
     *
     * \param valor T Valor que se desea insertar.
     * \return bool true si el valor se agreg&oacute;; false si ya exist&iacute;a (no se permiten repetidos).
     *
     */
    bool Agregar(T valor);

    /** \brief Elimina un valor del &aacute;rbol y lo reequilibra si es necesario.
     *
     * \param valor T Valor que se desea eliminar.
     * \return bool true si el valor se elimin&oacute;; false si no se encontr&oacute;.
     *
     */
    bool Eliminar(T valor);

    /** \brief Indica si un valor se encuentra en el &aacute;rbol.
     *
     * \param valor T Valor que se desea buscar.
     * \return bool true si el valor existe en el &aacute;rbol; false en caso contrario.
     *
     */
    bool BuscarNodo(T valor) const;

    /** \brief Regresa la cantidad de nodos que hay en el &aacute;rbol.
     *
     * \return int N&uacute;mero de nodos almacenados.
     *
     */
    int ObtenerNumNodos() const;

    /** \brief Regresa la altura del &aacute;rbol.
     *
     * \return int Altura del &aacute;rbol (0 si est&aacute; vac&iacute;o).
     *
     */
    int ObtenerAltura() const;

    /** \brief Nos dice si el &aacute;rbol est&aacute; vac&iacute;o o no.
     *
     * \return bool true si el &aacute;rbol no tiene nodos; false en caso contrario.
     *
     */
    bool EstaVacia() const;

    /** \brief Vac&iacute;a todo el &aacute;rbol y libera su memoria.
     *
     * \return void
     *
     */
    void Vaciar();

    /** \brief Imprime los valores del &aacute;rbol del menor al mayor (recorrido inorden).
     *
     * \return void
     *
     */
    void ImprimirAsc() const;

    /** \brief Imprime los valores del &aacute;rbol del mayor al menor (recorrido inorden inverso).
     *
     * \return void
     *
     */
    void ImprimirDesc() const;

    /** \brief Imprime los valores del &aacute;rbol por niveles en una sola l&iacute;nea.
     *
     * \return void
     *
     */
    void ImprimirPorNiveles() const;

    /** \brief Imprime el &aacute;rbol con su estructura jer&aacute;rquica, usando un salto de l&iacute;nea por nivel.
     *
     * \return void
     *
     */
    void ImprimirComoArbol() const;

    /**
     * \brief Excepci&oacute;n lanzada cuando ocurren fallos de memoria din&aacute;mica.
     */
    class ArbolNoMemoria : public std::exception {
    public:
        /** \brief Constructor por defecto de la excepci&oacute;n ArbolNoMemoria.
         */
        ArbolNoMemoria() throw();

        /** \brief Devuelve una descripci&oacute;n del error cuando no haya memoria disponible.
         *
         * \return Cadena de caracteres con el mensaje de error.
         */
        virtual const char *what() const throw();
    };

private:
    int numNodos; //!< Member variable "numNodos"

    /** \brief Estructura interna que representa un nodo del &aacute;rbol. */
    struct Nodo{
        T valor;              //!< Member variable "valor"
        int altura;           //!< Member variable "altura"
        Nodo *hijoIzq,        //!< Member variable "*hijoIzq"
             *hijoDer;        //!< Member variable "*hijoDer"

        /** \brief Constructor de Nodo.
         *  \param v Valor que almacena el nodo.
         *  \param hIzq Apuntador al hijo izquierdo (nullptr por defecto).
         *  \param hDer Apuntador al hijo derecho (nullptr por defecto).
         */
        Nodo(T v, Nodo *hIzq = nullptr, Nodo *hDer = nullptr);
    }*raiz; //!< Member variable "*raiz"

    // Funciones de utileria.

    /** \brief Funci&oacute;n recursiva de utiler&iacute;a que inserta un valor en un sub&aacute;rbol y lo reequilibra.
     *  \param valor Valor que se desea insertar.
     *  \param subRaiz Referencia al apuntador de la ra&iacute;z del sub&aacute;rbol.
     *  \return bool true si el valor se agreg&oacute;; false si ya exist&iacute;a.
     */
    bool Agregar(T valor, Nodo *& subRaiz);

    /** \brief Funci&oacute;n recursiva de utiler&iacute;a que elimina un valor de un sub&aacute;rbol y lo reequilibra.
     *  \param valor Valor que se desea eliminar.
     *  \param subRaiz Referencia al apuntador de la ra&iacute;z del sub&aacute;rbol.
     *  \return bool true si el valor se elimin&oacute;; false si no se encontr&oacute;.
     */
    bool Eliminar(T valor, Nodo *&subRaiz);

    /** \brief Busca la direcci&oacute;n del nodo de mayor valor de un sub&aacute;rbol (el m&aacute;s a la derecha).
     *
     *  Se utiliza al eliminar un nodo con dos hijos, para localizar al mayor de los menores.
     *
     *  \param subRaiz Referencia al apuntador de la ra&iacute;z del sub&aacute;rbol.
     *  \return Referencia al apuntador del nodo de mayor valor.
     */
    Nodo*& BuscarDirMenor(Nodo *& subRaiz);

    /** \brief Recorre e imprime un sub&aacute;rbol en inorden (de menor a mayor).
     *  \param subRaiz Apuntador a la ra&iacute;z del sub&aacute;rbol.
     *  \return void
     */
    void ImprimirInorden(Nodo *subRaiz) const;

    /** \brief Recorre e imprime un sub&aacute;rbol en inorden inverso (de mayor a menor).
     *  \param subRaiz Apuntador a la ra&iacute;z del sub&aacute;rbol.
     *  \return void
     */
    void ImprimirInordenInverso(Nodo *subRaiz) const;

    /** \brief Elimina recursivamente todos los nodos de un sub&aacute;rbol (recorrido postorden).
     *  \param subRaiz Referencia al apuntador de la ra&iacute;z del sub&aacute;rbol.
     *  \return void
     */
    void Podar(Nodo *&subRaiz);

    /** \brief Copia los nodos de otro &aacute;rbol recorri&eacute;ndolo por niveles.
     *
     *  Se copia por niveles para que el orden de inserci&oacute;n reproduzca la
     *  misma estructura del original; copiar en preorden podr&iacute;a producir un
     *  &aacute;rbol distinto tras el reequilibrio.
     *
     *  \param arbolOrigen &Aacute;rbol del cual se copian los nodos.
     *  \return void
     */
    void CopiarPorNiveles(const ArbolAVL &arbolOrigen);

    // Funciones de utileria propias del AVL.

    /** \brief Regresa la altura almacenada en un nodo.
     *  \param subRaiz Apuntador al nodo consultado.
     *  \return int Altura del nodo, o 0 si es nullptr.
     */
    int Altura(Nodo *subRaiz) const;

    /** \brief Regresa el mayor de dos enteros.
     *  \param a Primer entero.
     *  \param b Segundo entero.
     *  \return int El mayor entre a y b.
     */
    int Maximo(int a, int b) const;

    /** \brief Calcula el factor de equilibrio de un nodo.
     *  \param subRaiz Apuntador al nodo consultado.
     *  \return int Diferencia entre la altura del hijo izquierdo y la del derecho.
     */
    int FactorEquilibrio(Nodo *subRaiz) const;

    /** \brief Recalcula y actualiza la altura de un nodo a partir de la de sus hijos.
     *  \param subRaiz Apuntador al nodo cuya altura se actualiza.
     *  \return void
     */
    void ActualizarAltura(Nodo *subRaiz);

    /** \brief Verifica el equilibrio de un nodo y aplica la rotaci&oacute;n necesaria.
     *  \param subRaiz Referencia al apuntador del nodo que se reequilibra.
     *  \return void
     */
    void Reequilibrar(Nodo *&subRaiz);

    // Rotaciones

    /** \brief Realiza una rotaci&oacute;n simple a la izquierda sobre el nodo dado.
     *  \param subRaiz Referencia al apuntador del nodo sobre el que se rota.
     *  \return void
     */
    void RotSimpleIzq(Nodo *&subRaiz);

    /** \brief Realiza una rotaci&oacute;n simple a la derecha sobre el nodo dado.
     *  \param subRaiz Referencia al apuntador del nodo sobre el que se rota.
     *  \return void
     */
    void RotSimpleDer(Nodo *&subRaiz);

    /** \brief Realiza una rotaci&oacute;n doble a la izquierda (derecha-izquierda) sobre el nodo dado.
     *  \param subRaiz Referencia al apuntador del nodo sobre el que se rota.
     *  \return void
     */
    void RotDobleIzq(Nodo *&subRaiz);

    /** \brief Realiza una rotaci&oacute;n doble a la derecha (izquierda-derecha) sobre el nodo dado.
     *  \param subRaiz Referencia al apuntador del nodo sobre el que se rota.
     *  \return void
     */
    void RotDobleDer(Nodo *&subRaiz);
};
#include "ArbolAVL.tpp"
#endif // ARBOLAVL_HPP_INCLUDED
