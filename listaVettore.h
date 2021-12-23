#ifndef LISTAVETTORE_H
#define LISTAVETTORE_H
#include "lista.h"

#define MAX 10

template <class T>
class vectorList : public linearList<T, int> {
public:
    typedef typename linearList<T, int>::valueType valueType;
    typedef typename linearList<T, int>::position position;

    //costruttori
    vectorList();
    vectorList(int);

    //distruttore
    ~vectorList();

    //metodi
    void createList();
    bool isEmpty() const;
    valueType readList(position) const;
    void writeList(position, valueType&);
    position _begin() const;
    position _last() const;
    bool _end(position) const;
    position next(position) const;
    position prec(position) const;
    void insList(position, valueType);
    void delList(position);
    void fillList(valueType&);

    vectorList<T>& operator=(const vectorList<T> &);
    bool operator==(const vectorList<T> &l);
    bool operator!=(const vectorList<T> &l);

private:
    valueType *elements;
    int lenght;
    int dim;

};

template <class T>
class orderedVectorList : public vectorList<T> {
    public:
        typedef typename vectorList<T>::valueType valueType;
        typedef typename vectorList<T>::position position;

        void insertOrdList(valueType);
        void removeOrdList(position);          //si potrebbe eliminare
        bool searchOrdList(valueType);
        void mergeOrdList(orderedVectorList<T> &ordList, bool duplicati);
    private:
    vectorList<T> listaOrdinata;
};

template <class T>
void orderedVectorList<T>::insertOrdList(orderedVectorList<T>::valueType elem) {
    if(vectorList<T>::isEmpty()) {
        vectorList<T>::insList(vectorList<T>::_begin(), elem);
    } else if(!vectorList<T>::isEmpty()) {
        position pos = vectorList<T>::_begin();
        bool check = false;

        while(!vectorList<T>::_end(pos) && check == false) {
            if(elem < vectorList<T>::readList(pos)) {
                vectorList<T>::insList(pos, elem);
                check = true;
            } else {
                pos = vectorList<T>::next(pos);
            }
        }

        if(vectorList<T>::_end(pos)) {
            vectorList<T>::insList(pos, elem);
        }
    }
}

template <class T>
void orderedVectorList<T>::removeOrdList(orderedVectorList<T>::position pos) {
    vectorList<T>::delList(pos);
}

template <class T>
bool orderedVectorList<T>::searchOrdList(orderedVectorList<T>::valueType elem) {
    position pos = vectorList<T>::_begin();
    bool check = false;

    while(!vectorList<T>::_end(pos) && check == false) {
        if(vectorList<T>::readList(pos) == elem) {
            check = true;
        }

        pos = vectorList<T>::next(pos);
    }

    return check;
}

template <class T>
void orderedVectorList<T>::mergeOrdList(orderedVectorList<T> &ordList, bool duplicati) {
    position pos = ordList._begin();

    while(!ordList._end(pos)) {
        if(searchOrdList(ordList.readList(pos))) {
            if(duplicati == true) {
                insertOrdList(ordList.readList(pos));
            }
        } else {
            insertOrdList(ordList.readList(pos));
        }

        pos = ordList.next(pos);
    }
}

//operazione di copia
template <class T>
vectorList<T>& vectorList<T>::operator=(const vectorList<T> &l) {
    if(this != &l) {
        dim = l.dim;
        lenght = l.lenght;
        delete this -> elements;
        this -> elements = new T[dim];
        for (int i = 0; i < dim; i++)
            elements[i] = l.elements[i];
    }

    return *this;
}

//operazione di confronto
template <class T>
bool vectorList<T>::operator==(const vectorList<T> &l) {
    if(this->lenght != l.lenght) {
        return false;
    }
    for (int i = 0; i < dim; i++) {
        if(elements[i] != l.elements[i]) {
            return false;
        }
    }
    return true;
}

template <class T>
bool vectorList<T>::operator!=(const vectorList<T> &l) {
    if(this->lenght != l.lenght) {
        return true;
    }

    for (int i = 0; i < dim; i++) {
        if(elements[i] != l.elements[i]) {
            return true;
        }
    }
    return false;
}

//realizzazione costruttori
template <class T>
vectorList<T>::vectorList() {
    dim = MAX;
    this->createList();
}

template <class T>
vectorList<T>::vectorList(int dimension) {
    dim = dimension;
    this->createList();
}

template <class T>
vectorList<T>::~vectorList() {
    delete[] elements;
}

//realizzazione metodi
template <class T>
void vectorList<T>::createList() {
    elements = new T[dim];
    lenght = 0;
}

template <class T>
bool vectorList<T>::isEmpty() const{
    if(lenght == 0) {
        return true;
    } else return false;
}

template <class T>
typename vectorList<T>::valueType vectorList<T>::readList(vectorList<T>::position pos) const{
    if((pos > 0) && (pos < lenght+1)) {
        return elements[pos - 1];
    }
}

template <class T>
void vectorList<T>::writeList(vectorList<T>::position pos, vectorList<T>::valueType &e) {
    if((pos > 0) && (pos < lenght+1)) {
        elements[pos - 1] = e;
    }
}

template <class T>
typename vectorList<T>::position vectorList<T>::_begin() const{
    return 1;
}

template <class T>
typename vectorList<T>::position vectorList<T>::_last() const {
    return lenght;
}

template <class T>
bool vectorList<T>::_end(vectorList<T>::position pos) const{
    if ((pos > 0) && (pos <= lenght + 1)) {
        if(pos == lenght + 1)
            return true;
        else
            return false;
    }
}

template <class T>
typename vectorList<T>::position vectorList<T>::next(vectorList<T>::position pos) const{
    if((pos > 0) && (pos < lenght + 1))
        return pos + 1;
    else return pos;
}

template <class T>
typename vectorList<T>::position vectorList<T>::prec(vectorList<T>::position pos) const{
    if((pos > 1) && (pos < lenght + 1))
        return (pos - 1);
    else return pos;
}

template <class T>
void vectorList<T>::insList(vectorList<T>::position pos, vectorList<T>::valueType e) {
    if((pos > 0) && (pos <= lenght + 1)) {
        for (int i = lenght; i >= pos; i--) {
            elements[i] = elements[i - 1];
        }
        elements[pos - 1] = e;
        lenght++;
    }
}

template <class T>
void vectorList<T>::delList(vectorList<T>::position pos) {
    if((pos > 0) && (pos < lenght+1)) {
        for (int i = pos-1; i < lenght-1; i++) {
            elements[i] = elements[i + 1];
        }
        lenght = lenght - 1;
    }
}


template <class T>
void vectorList<T>::fillList(vectorList<T>::valueType &noc) {
    while(noc > 0) {
        insList(_begin(), noc);
        noc--;
        lenght++;
    }
}

#endif // LISTAVETTORE_H
