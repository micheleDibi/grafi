#ifndef GRAFOMAT_H
#define GRAFOMAT_H

#include "grafo.h"

class nodog {
public:
    nodog(int i) {
        nodoID = i;
    }
    nodog() {}

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
class info_arco {
public:
    P peso;
    bool vuoto;

    info_arco() {
        vuoto = true;
    }
};

template <class E, class P>
class info_nodo {
public:
    E etichetta;
    bool vuoto;
    info_arco<P> *archi;

    info_nodo() {
        vuoto = true;
    }

    ~info_nodo() {
        if(!vuoto) {
            delete[] archi;
        }
    }
};

template <class E, class P>
class grafoMat : public grafo<E, P, nodog> {
public:
    typedef E etichetta;
    typedef P peso;
    typedef nodog nodo;
    typedef Arco<peso, nodo> arco;
    typedef grafo<etichetta, peso, nodo> grafoL;
    typedef typename grafoL::listaNodi listaNodi;
    typedef typename grafoL::listaNodiPos listaNodiPos;

    grafoMat(int dimensione) {
        dim = dimensione;
        nNodi = 0;
        nArchi = 0;

        matrice = new info_nodo<E, P>[dim];
        for(int i = 0; i < dim; i++) {
            matrice[i].archi = new info_arco<P>[dim];
        }
    }

    ~grafoMat() {
        delete[] matrice;
    }

    bool vuoto() const {
        return (nNodi == 0);
    }

    void insNodo(nodo &n) {
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

    void insArco(nodo n1, nodo n2, peso p) {
        matrice[n1.getID()].archi[n2.getID()].peso = p;
        matrice[n1.getID()].archi[n2.getID()].vuoto = false;
        nArchi++;
    }

    void cancNodo(nodo n) {
        bool canc = true;

        for(int i = 0; i < dim && canc == true; i++) {
            if(!matrice[n.getID()].archi[i].vuoto) {
                canc = false;
            }
        }

        if(canc == true) {
            for(int i = 0; i < dim && canc == true; i++) {
                if(matrice[i].archi[n.getID()].vuoto == false) {
                    canc = false;
                }
            }
        }

        if(canc == true) {
            delete[] matrice[n.getID()].archi;
            matrice[n.getID()].vuoto = true;
            nNodi--;
        }
    }

    void cancArco(nodo n1, nodo n2) {
        matrice[n1.getID()].archi[n2.getID()].vuoto = true;
        nArchi--;
    }

    //bool esisteNodo(nodo);
    //bool esisteArco(arco);

    listaNodi adiacenti(nodo n1) const {
        listaNodi list;

        for(int i = 0; i < dim; i++) {
            if(matrice[n1.getID()].archi[i].vuoto == false) {
                list.insList(list._begin(), new nodog(i));
            }
        }

        return list;
    }


    listaNodi listNodi() const {
        listaNodi listN;

        for (int i = 0; i < dim; i++) {
            if(!matrice[i].vuoto()) {
                listN.insList(listN._begin(), new nodog(i));
            }
        }

        return listN;
    };

    etichetta leggiEtichetta(nodo n1) const {
        return matrice[n1.getID()].etichetta;
    }

    void scriviEtichetta(nodo n, etichetta e) {
        matrice[n.getID()].etichetta = e;
    }

    peso leggiPeso(nodo n1, nodo n2) const {
        return matrice[n1.getID()].archi[n2.getID()].peso;
    }

    void scriviPeso(nodo n1, nodo n2, peso p) {
        matrice[n1.getID()].archi[n2.getID()].peso = p;
    }

    int numNodi() const {
        return nNodi;
    }

    int numArchi() const {
        return nArchi;
    }

private:
    info_nodo<E, P> *matrice;
    int dim;
    int nNodi;
    int nArchi;
};

#endif // GRAFOMAT_H
