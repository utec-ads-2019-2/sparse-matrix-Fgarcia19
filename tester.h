#ifndef TESTER_H
#define TESTER_H

#include <stdexcept>
#include <iostream>
#include <assert.h>
#include <vector>
#include <algorithm>

#include "mocker.h"
#include "matrix.h"

using namespace std;


#ifndef NDEBUG
#   define ASSERT(condition, message) \
    do { \
        if (! (condition)) { \
            std::cerr << "Assertion `" #condition "` failed in " << __FILE__ \
                      << " line " << __LINE__ << ": " << message << std::endl; \
            std::terminate(); \
        } \
    } while (false)
#else
#   define ASSERT(condition, message) do { } while (false)
#endif

#define NUMBER_OF_TESTS 10


class Tester {
    private:
        template <typename T>
        static T** producto(T** A,int k, int m1,T**B,int m2, int n)
        {
            T** C=new int*[k];
            for(int i=0;i<k;++i)
            {
                C[i]=new T[n];
            }

            for(int i=0; i<k; ++i) {
                for (int j = 0; j < n; ++j) {
                    C[i][j] = 0;
                    for (int z = 0; z < m1; ++z)
                        C[i][j] += A[i][z] * B[z][j];
                }
            }

            return C;
        };

        template <typename T>
        static void testMatrix(unsigned int rows, unsigned int columns)
        {
          Mocker mocker;
          T **matrix1 = buildMatrix<T>(rows, columns);
          Matrix<T> test1 = setMatrix<T>(matrix1, rows, columns);

          unsigned int scalar = mocker.generateRandomInt(10);
          Matrix<T> result = test1*scalar;
          for (int i = 0; i < rows; ++i) {
              for (int j = 0; j < columns; ++j) {
                  ASSERT(result(i, j) == matrix1[i][j]*scalar, "There is a problem with the scalar multiplication");
              }
          }
          int **matrix2 = buildMatrix<T>(rows, columns);
          Matrix<T> test2 = setMatrix<T>(matrix2, rows, columns);
          result = test1 + test2;
          for (int i = 0; i < rows; ++i) {
              for (int j = 0; j < columns; ++j) {
                  ASSERT(result(i, j) == matrix1[i][j] + matrix2[i][j], "There is a problem with the addition");
              }
          }

          result = test1 - test2;
          for (int i = 0; i < rows; ++i) {
              for (int j = 0; j < columns; ++j) {
                  ASSERT(result(i, j) == matrix1[i][j] - matrix2[i][j], "There is a problem with the subtraction");
              }
          }

          result=test1.transpose().transpose();
          for (int i = 0; i < rows; ++i) {
              for (int j = 0; j < columns; ++j) {
                  ASSERT(result(i, j) == matrix1[i][j], "There is a problem with the transpose");
              }
            }

            auto a=transponer(matrix2,rows,columns);
            auto test3=setMatrix(a,columns,rows);
            auto m=producto(matrix1,rows,columns,a,columns,rows);
            result=(test1*test3);
          for (int i = 0; i < rows; i++) {
                for (int j = 0; j < columns; j++) {
                    ASSERT(result(i, j) == m[i][j], "There is a problem with the multiplication");
                }
            }
        };

        template <typename T>
        static T** transponer(T** matrix, unsigned int rows, unsigned int columns)
        {
            T** respuesta=new int*[columns];
            for(int i=0;i<columns;++i)
            {
                respuesta[i]=new T[rows];
            }
            for(int i=0;i<columns;i++)
            {
                for(int j=0;j<rows;j++)
                {
                    respuesta[i][j]=matrix[j][i];
                }
            }
            return respuesta;
        }

        template <typename T>
        static T** buildMatrix(unsigned int rows, unsigned int columns)
        {
          Mocker mocker;

          T **matrix = new int*[rows];
          for (int i = 0; i < rows; ++i) {
              matrix[i] = mocker.generateRandomArray<T>(columns);
          }

          return matrix;
        };

        template <typename T>
        static Matrix<T> setMatrix(T **&matrix, unsigned int rows, unsigned int columns)
        {
          Matrix<T> result(rows, columns);
          for (int i = 0; i < rows; ++i) {
              for (int j = 0; j < columns; ++j) {
                  result.set(i, j, matrix[i][j]);
                  ASSERT(result(i, j) == matrix[i][j], "There is a problem with the set or operator()");
              }
          }
          return result;
        };

    public:
        static void execute()
        {
          Mocker mocker;
          for (int i = 0; i < NUMBER_OF_TESTS; ++i) {
              unsigned int rows = mocker.generateRandomInt(10);
              unsigned int columns = mocker.generateRandomInt(10);
              testMatrix<int>(rows, columns);
          }
            cout<<"Test finished"<<endl;
        };
};

#endif
