#include <iostream>
#include <exception>
using namespace std;

class Vector
{
    int *data;
    size_t size;
    size_t capacity;
    const int id;

    void resize() {
        if(this->size < this->capacity) {
            return;
        }

        int tmpCap = this->capacity * 2;
        int* tmpData = new int[tmpCap];

        for (size_t i = 0; i < this->size; i ++) {
            tmpData[i] = this->data[i];
        }

        delete[] this->data;

        this->data = new int[tmpCap];

        for (size_t i = 0; i < this->size; i ++) {
            this->data[i] = tmpData[i];
        }

        this->capacity = tmpCap;

        delete[] tmpData;
    }

public:
    Vector(int id, int capacity)
        : id(id), capacity(capacity), size(0)
    {
        if (capacity <= 0) {
            throw invalid_argument("Capacity must be greater than 0");
        }
        if (id <= 0) {
            throw invalid_argument("Id must be greater than 0");
        }
        this->data = new int[capacity];
    }

    ~Vector() {
        if (this->data != NULL) {
            delete[] this->data;
        }
    }

    size_t getSize() const {
        return this->size;
    }

    size_t getCapacity() const {
        return this->capacity;
    }

    int getId() const {
        return this->id;
    }

    void pushBack(int number) {
        if (this->size >= this->capacity) {
            resize();
        }
        this->data[this->size] = number;
        this->size++;
    }

    int at(int index) const {
        if (index < 0 || index >= this->size) {
            throw out_of_range("Index out of range");
        }
        return this->data[index];
    }

    int insert(int index, int value) {
        if (index < 0 || index > this->size) {
            throw out_of_range("Index out of range");
        }
        resize();
        for (size_t i = this->size; i > index; i--)
        {
            this->data[i] = this->data[i - 1];
        }
        this->data[index] = value;
        this->size++;
        return 0;
    }

    int remove(int index) {
        if (index < 0 || index >= this->size) {
            throw out_of_range("Index out of range");
        }
        int tmp = this->data[index];
        for (size_t i = index; i < this->size - 1; i++)
        {
            this->data[i] = this->data[i + 1];
        }
        this->size--;
        return tmp;
    }

    int pop() {
        if (this->size == 0) {
            throw out_of_range("Vector is empty");
        }
        int tmp = this->data[this->size - 1];
        this->size--;
        return tmp;
    }
};