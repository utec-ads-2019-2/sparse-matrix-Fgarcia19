#ifndef SPARSE_MATRIX_NODE_H
#define SPARSE_MATRIX_NODE_H

template <typename T>
class Matrix;

template <typename T>
class Node {
protected:
    int data,posx,posy;
    Node<T> *next, *down;
public:
    Node():next(nullptr),down(nullptr){};
    Node(int x,int y,int data):posx(x),posy(y),data(data),next(nullptr),down(nullptr){};
    friend class Matrix<T>;
    void killself()
    {
        if(next!= nullptr)
            next->killself();
        delete this;
    }
};

#endif //SPARSE_MATRIX_NODE_H
