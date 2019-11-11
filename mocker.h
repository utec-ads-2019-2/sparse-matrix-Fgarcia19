#ifndef MOCKER_H
#define MOCKER_H

#include <random>
#include <type_traits>

using namespace std;

#define MIN 0
#define MAX 10

class Mocker {
    private:
        mt19937 rng;

    public:
        Mocker() {
            rng.seed(random_device()());
        }

        int generateRandomInt(int min = MIN, int max = MAX)
        {
          uniform_int_distribution<mt19937::result_type> distribution(min, max);
          return distribution(rng);
        };
        char generateRandomChar()
        {
          int increment = generateRandomInt() % 26;
          return 'a' + increment;
        };

        template <typename T>
        T* generateRandomArray(unsigned int size) {
            T *elements = new T[size];
            for (int i = 0; i < size; i++) {
                if (is_same<T, int>::value) {
                    elements[i] = generateRandomInt();
                }
                else if (is_same<T, char>::value) {
                    elements[i] = generateRandomChar();
                }
            }

            return elements;
        }
};

#endif
