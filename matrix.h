#ifndef SPARSE_MATRIX_MATRIX_H
#define SPARSE_MATRIX_MATRIX_H

#include <stdexcept>
#include "node.h"
using namespace std;

template <typename T>
class Matrix {
private:



public:
    unsigned rows, columns;
    vector<Node<T>*> x;
    vector<Node<T>*> y;
    Matrix(unsigned rows, unsigned columns):rows(rows),columns(columns)
    {
      for(int i=0;i<rows;i++) {
          x.push_back(new Node<T>());
      }
      for(int i=0;i<columns;i++) {
          y.push_back(new Node<T>());
      }

};


    void set(unsigned px, unsigned py, T data)
    {
        if(px>rows | py>columns)
        {
            throw std::invalid_argument("Out of range");
        }

        auto nuevo=new Node<T>(px,py,data);
        auto a=x[px];
        auto b=y[py];

        while(true)
        {
            if(!a->next)
            {
                a->next=nuevo;
                break;
            }
            if(a->next->posy>py)
            {
                nuevo->next=a->next;
                a->next=nuevo;
                break;
            }
            if(a->next->posy==py)
            {
                if(data!=0)
                {
                    a->next->data=data;
                }
                else{
                    auto aux=a->next;
                    a->next=a->next->next;
                    delete aux;
                }
                break;
            }
            a=a->next;
        }

        while(true)
        {
            if(!b->down)
            {
                b->down=nuevo;
                break;
            }
            if(b->down->posx>px)
            {
                nuevo->down=b->down;
                a->down=nuevo;
                break;
            }
            if(b->down->posx==px)
            {
                if(data!=0)
                {
                    b->down->data=data;
                }
                else{
                    auto aux=b->down;
                    b->down=b->down->down;

                    delete aux;
                }
                break;
            }
            b=b->down;
        }
    }


    T operator()(unsigned px, unsigned py)
    {
        if(px>rows | py>columns)
        {
            throw std::invalid_argument("Out of range");
        }
        auto a=x[px];
        auto b=y[py];

        while(true)
        {
            if(rows==0 | columns==0){break;

            }
            if(!a->next)
            {
                return 0;
            }
            if(a->next->posy>py)
            {
                return 0;
            }
            if(a->next->posy==py)
            {
                return a->next->data;
            }
            a=a->next;
        }

    }

    const Matrix<T> operator*(T scalar){
        auto r=this;
        Matrix<T> respuesta(rows,columns);
        for(int i=0;i<rows;i++)
        {
            for(auto j=(*this).x[i]->next;j!= nullptr;j=j->next)
            {
                respuesta.set(j->posx,j->posy,j->data*scalar);
            }
        }
        return respuesta;
    };


    Matrix<T> operator*(Matrix<T> other)
    {
        if(columns!=other.rows)
        {
            throw std::invalid_argument("Can't do the operation");
        }
        Matrix<T> respuesta(rows,other.columns);

        for(int i=0; i<rows; ++i) {
            for (int j = 0; j < other.columns; ++j) {
                int u=0;
                for (int z = 0; z < columns; ++z) {
                    u += (*this)(i,z)*other(z,j);
                }
                respuesta.set(i,j,u);
            }
        }
        return respuesta;
    };



    Matrix<T> operator+(Matrix<T> other)
    {
        if(rows!=other.rows and columns!=other.columns)
        {
            throw std::invalid_argument("Can't do the operation");
        }
        Matrix respuesta=Matrix(rows,columns);

           if( rows != other.rows | columns!=other.columns)
           {
               throw exception();
           }
           else
               {
                    for(int i=0;i<rows;i++)
                    {
                        auto aux1=x[i];
                        auto aux2=other.x[i];
                        while(aux1->next!= nullptr  | aux2->next!= nullptr) {
                            if (aux1->next != nullptr && aux2->next != nullptr)
                            {
                                if (aux1->next->posy < aux2->next->posy)
                                {
                                    respuesta.set(aux1->next->posx, aux1->next->posy, aux1->next->data);
                                    aux1=aux1->next;
                                }
                                else if (aux1->next->posy > aux2->next->posy)
                                {
                                    respuesta.set(aux2->next->posx, aux2->next->posy, aux2->next->data);
                                    aux2=aux2->next;
                                }
                                else if (aux1->next->posy == aux2->next->posy)
                                {
                                    respuesta.set(aux2->next->posx, aux2->next->posy, aux1->next->data+aux2->next->data);
                                    aux1=aux1->next;
                                    aux2=aux2->next;
                                }
                            }
                            if(aux1->next != nullptr and aux2->next == nullptr)
                            {
                                respuesta.set(aux1->next->posx, aux1->next->posy, aux1->next->data);
                                aux1=aux1->next;
                            }
                            if(aux1->next == nullptr and aux2->next != nullptr)
                            {
                                respuesta.set(aux2->next->posx, aux2->next->posy, aux2->next->data);
                                aux2=aux2->next;
                            }
                        }

                    }
                   return respuesta;
               }
    };
    Matrix<T> operator-(Matrix<T> other)
    {
        if(rows!=other.rows and columns!=other.columns)
        {
            throw std::invalid_argument("Can't do the operation");
        }
        Matrix respuesta=Matrix(rows,columns);

        if( rows != other.rows | columns!=other.columns)
        {
            throw exception();
        }
        else
        {
            for(int i=0;i<rows;i++)
            {
                auto aux1=x[i];
                auto aux2=other.x[i];
                while(aux1->next!= nullptr  | aux2->next!= nullptr) {
                    if (aux1->next != nullptr && aux2->next != nullptr)
                    {
                        if (aux1->next->posy < aux2->next->posy)
                        {
                            respuesta.set(aux1->next->posx, aux1->next->posy, aux1->next->data);
                            aux1=aux1->next;
                        }
                        else if (aux1->next->posy > aux2->next->posy)
                        {
                            respuesta.set(aux2->next->posx, aux2->next->posy, -aux2->next->data);
                            aux2=aux2->next;
                        }
                        else if (aux1->next->posy == aux2->next->posy)
                        {
                            respuesta.set(aux2->next->posx, aux2->next->posy, aux1->next->data-aux2->next->data);
                            aux1=aux1->next;
                            aux2=aux2->next;
                        }
                    }
                    if(aux1->next != nullptr and aux2->next == nullptr)
                    {
                        respuesta.set(aux1->next->posx, aux1->next->posy, aux1->next->data);
                        aux1=aux1->next;
                    }
                    if(aux1->next == nullptr and aux2->next != nullptr)
                    {
                        respuesta.set(aux2->next->posx, aux2->next->posy, -aux2->next->data);
                        aux2=aux2->next;
                    }
                }

            }
            return respuesta;
        }


    };
    Matrix<T> transpose()
    {
        Matrix<T> respuesta(columns,rows);
        for(auto i:x)
        {
            while(i->next!= nullptr)
            {
                respuesta.set(i->next->posy,i->next->posx,i->next->data);
                i=i->next;
            }
        }
        return respuesta;
    };
    void print()
    {
      for(auto i=0;i<x.size();i++)
      {
        int f=0;
        auto k=x[i]->next;
        for(auto j=0;j<columns;j++)
        {
            if (!k) {
              cout<<0<<" ";
            }
            else{
              for(int e=0;e<k->posy-f;e++)
              {
                cout<<0<<" ";
                j++;
              }
              f=k->posy+1;
              cout<<k->data<<" ";
              k=k->next;
            }
        }
        cout<<endl;
      }
    };

    void clear()
    {
                 for(int i=0;i<rows;i++){
             for (int j=0;j<columns;j++){
                 this->set(i,j,0);
             }
         }
    }

     ~Matrix()
     {
//        clear();
     };
};

#endif //SPARSE_MATRIX_MATRIX_H
