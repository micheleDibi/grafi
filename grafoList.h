#ifndef GRAFOLIST_H
#define GRAFOLIST_H

#include "grafo.h"
#include "listaPuntatori.h"

class nodoG {
public:
    nodoG(int i) {
        nodoID = i;
    }
    nodoG() {}

    int getID() {
        return nodoID;
    }

    void setID(int ID) {
        nodoID = ID;
    }

private:
    int nodoID;
};

template <class P>
class infoArco {
public:
    P peso;
    nodoG dest;
};

template <class E, class P>
class infoNodo {
public:
    E etichetta;
    bool vuoto;
    linkedList<infoArco<P>> archi;

    infoNodo() {
        vuoto = true;
    }
};

template <class E, class P>
class grafoList : public grafo<E, P, nodoG> {
public:
    typedef E etichetta;
    typedef P peso;
    typedef nodoG nodo;
    typedef class Arco<peso, nodo> arco;
    typedef class grafo<etichetta, peso, nodo> grafo;
    typedef typename grafo::listaNodi listaNodi;
    typedef typename grafo::listaNodiPos listaNodiPos;

    grafoList(int);
    ~grafoList();
    bool vuoto() const;
    void insNodo(nodo&);
    void insArco(nodo, nodo, peso);
    void cancNodo(nodo);
    void cancArco(nodo, nodo);
    //bool esisteNodo(nodo);
    //bool esisteArco(arco);
    listaNodi adiacenti(nodo) const;
    listaNodi listNodi() const;
    etichetta leggiEtichetta(nodo) const;
    void scriviEtichetta(nodo, etichetta);
    peso leggiPeso(nodo, nodo) const;
    void scriviPeso(nodo, nodo, peso);
    int numNodi() const;
    int numArchi() const;

    int inDegree(nodo);

private:
    infoNodo<E, P> *matrice;
    int dim;
    int nNodi;
    int nArchi;

};

template <class E, class P>
grafoList<E, P>::grafoList(int dimensione) {
    dim = dimensione;
    nNodi = 0;
    nArchi = 0;
    matrice = new infoNodo<E, P>[dim];

    for(int i = 0; i < dim; i++) {
        matrice[i].archi.createList();
    }
}

template <class E, class P>
grafoList<E, P>::~grafoList() {
    delete[] matrice;
}

template <class E, class P>
bool grafoList<E, P>::vuoto() const {
    return (nNodi == 0);
}

template <class E, class P>
void grafoList<E, P>::insNodo(grafoList<E, P>::nodo &n) {
    int i = 0;
    if (nNodi < dim) {
        while(matrice[i].vuoto == false) {
            i++;
        }

        nNodi++;
        matrice[i].vuoto = false;
    }

    n.setID(i);
}

template <class E, class P>
void grafoList<E, P>::insArco(grafoList<E, P>::nodo n1, grafoList<E, P>::nodo n2, grafoList<E, P>::peso p) {
    infoArco<peso> I;
    I.peso = p;
    I.dest = n2;
    matrice[n1.getID()].archi.insList(matrice[n1.getID()].archi._begin(), I);
    nArchi++;
}

template <class E, class P>
void grafoList<E, P>::cancNodo(grafoList<E, P>::nodo n) {
    bool canc = true;

    //controllo sugli archi uscenti
    if(!matrice[n.getID()].archi.isEmpty()) {
        canc = false;
    }
    //controllo sugli archi entranti
    if(canc == true) {
        for(int i = 0; i < dim; i++) {
            typename linkedList<infoArco<peso>>::position p;
            p = matrice[i].archi.next(matrice[i].archi._begin());

            while(!matrice[i].archi._end(p) && canc == true) {
                if(matrice[i].archi.readList(p).dest.getID() == n.getID()) {
                    canc = false;
                }

                p = matrice[i].archi.next(p);
            }
        }
    }

    if(canc == true) {
        matrice[n.getID()].vuoto = true;
        nNodi--;
    }
}

template <class E, class P>
void grafoList<E, P>::cancArco(grafoList<E, P>::nodo n1, grafoList<E, P>::nodo n2) {
    typename linkedList<infoArco<peso>>::position p;
    p = matrice[n1.getID()].archi._begin();

    bool trovato = false;
    while(!matrice[n1.getID()].archi._end(p) && trovato == false) {
        if(matrice[n1.getID()].archi.readList(p).dest.getID() == n2.getID()) {
            trovato = true;
        }

        p = matrice[n1.getID()].archi.next(p);
    }

    if(trovato) {
        matrice[n1.getID()].archi.delList(p);
        nArchi--;
    }
}

template <class E, class P>
typename grafoList<E, P>::listaNodi grafoList<E, P>::adiacenti(grafoList<E, P>::nodo n1) const {
    grafoList<E, P>::listaNodi listN;

    typename linkedList<infoArco<peso>>::position p;
    p = matrice[n1.getID()].archi._begin();

    while(!matrice[n1.getID()].archi._end(p)) {
        //listN.insList(matrice[n1.getID()].archi._begin(), matrice[n1.getID()].archi.readList(p).dest);

        p = matrice[n1.getID()].archi.next(p);
    }

    return listN;
}

template <class E, class P>
typename grafoList<E, P>::listaNodi grafoList<E, P>::listNodi() const {
    listaNodi listN;

    for(int i = 0; i < dim; i++) {
        if(!matrice[i].vuoto) {
            nodo copy(i);
            listN.insList(listN._begin(), copy);
        }
    }

    return listN;
};

template <class E, class P>
typename grafoList<E, P>::etichetta grafoList<E, P>::leggiEtichetta(grafoList<E, P>::nodo n1) const {
    return matrice[n1.getID()].etichetta;
}

template <class E, class P>
void grafoList<E, P>::scriviEtichetta(grafoList<E, P>::nodo n, grafoList<E, P>::etichetta e) {
    matrice[n.getID()].etichetta = e;
}

template <class E, class P>
typename grafoList<E, P>::peso grafoList<E, P>::leggiPeso(grafoList<E, P>::nodo n1, grafoList<E, P>::nodo n2) const {
    typename linkedList<infoArco<peso>>::position p;
    p = matrice[n1.getID()].archi._begin();

    bool trovato = false;

    while(matrice[n1.getID()].archi._end(p) && trovato == false) {
        if(matrice[n1.getID()].archi.readList(p).dest.getID() == n2.getID()) {
            trovato = true;
        }
        p = matrice[n1.getID()].archi.next(p);
    }

    if(trovato == true) {
        return matrice[n1.getID()].archi.readList(p).peso;
    }
}

template <class E, class P>
void grafoList<E, P>::scriviPeso(grafoList<E, P>::nodo n1, grafoList<E, P>::nodo n2, grafoList<E, P>::peso p) {
    typename linkedList<infoArco<peso>>::position pos;
    pos = matrice[n1.getID()].archi._begin();

    bool trovato = false;

    while(matrice[n1.getID()].archi._end(pos) && trovato == false) {
        if(matrice[n1.getID()].archi.readList(pos).dest.getID() == n2.getID()) {
            trovato = true;
        }

        pos = matrice[n1.getID()].archi.next(pos);
    }

    if(trovato == true) {
        infoArco<peso> I;
        I.peso = p;
        I.dest = n2;
        matrice[n1.getID()].archi.writeList(pos, I);
    }
}

template <class E, class P>
int grafoList<E, P>::numNodi() const {
    return nNodi;
}

template <class E, class P>
int grafoList<E, P>::numArchi() const {
    return nArchi;
}


template <class E, class P>
int grafoList<E, P>::inDegree(grafoList<E, P>::nodo n) {
    int counter = 0;

    for(int i = 0; i < nNodi; i++) {
        if(matrice[i] != n.getID()) {
            typename linkedList<infoArco<peso>>::position p;
            p = matrice[i].archi._begin();

            while(!matrice[i].archi._end(p)) {

                if(matrice[i].archi.readList(p) == n.getID()) {
                    counter++;
                }

                p = matrice[i].archi.next(p);
            }
        }
    }

    return counter;
}

template <class E, class P>
int grafoList<E, P>::outDegree(grafoList<E, P>::nodo n) {
    int counter = 0;

    typename linkedList<infoArco<peso>>::position p;
    p = matrice[i].archi._begin();

    while(!matrice[n.getID()].archi._end(p)) {
        counter++;
        p = matrice[n.getID()].archi.next(p);
    }

    return counter;
}

#endif // GRAFOLIST_H
