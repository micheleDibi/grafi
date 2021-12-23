#ifndef GRAFO_H
#define GRAFO_H

#include "listaVettore.h"

template <class P, class N>
class Arco {
public:
    N nodoPartenza;
    N nodoDestinazione;
    P peso;
};

template <class E, class P, class N>
class grafo{
public:
    typedef E etichetta;
    typedef P peso;
    typedef N nodo;

    typedef Arco<peso, nodo> arco;
    typedef vectorList<nodo> listaNodi;
    typedef typename listaNodi::position listaNodiPos;
    typedef vectorList<arco> listaArchi;

    virtual bool vuoto() const = 0;
    virtual void insNodo(nodo&) = 0;
    virtual void insArco(nodo, nodo, peso) = 0;
    virtual void cancNodo(nodo) = 0;
    virtual void cancArco(nodo, nodo) = 0;
    //virtual bool esisteNodo(nodo) = 0;
    //virtual bool esisteArco(arco) = 0;
    virtual listaNodi adiacenti(nodo) const = 0;
    virtual listaNodi listNodi() const = 0;
    virtual etichetta leggiEtichetta(nodo) const = 0;
    virtual void scriviEtichetta(nodo, etichetta) = 0;
    virtual peso leggiPeso(nodo, nodo) const = 0;
    virtual void scriviPeso(nodo, nodo, peso) = 0;

    virtual int numNodi() const = 0;
    virtual int numArchi() const = 0;

    virtual int inDegree(nodo);
    virtual int outDegree(nodo);
    //virtual double meanOutDegree();

};

#endif // GRAFO_H
