#include <iostream>

using namespace std;

class String
{
    char *data;
    size_t size;

public:
    /**
     * @brief Construct a new String object and it should have a default value of ""
     *
     */
    String() {
        this->data = new char[1];
        this->data[0] = '\0';
        this->size = 0;
    }

    /**
     * @brief Construct a new String object with the provided value
     *
     * @param str
     */
    String(const char *str) {
        if (str[0] == '\0') {
            this->data = new char[1];
            this->data[0] = '\0';
            this->size = 0;
            return;
        }

        for (this->size = 0; str[this->size] != '\0'; this->size++);

        this->data = new char[this->size + 1];
        for (size_t i = 0; i < this->size; i ++) {
            this->data[i] = str[i];
        }
        this->data[this->size] = '\0';
    }

    /**
     * @brief Destroy the String object
     *
     */
    ~String() {
        delete[] this->data;
    }

    /**
     * @brief Returns the string as a C-style string - char*
     *
     * @return const char*
     */
    char *toCString() const {
        char* tmp = new char[this->size + 1];
        for (size_t i = 0; i < this->size; i++) {
            tmp[i] = this->data[i];
        }
        tmp[this->size] = '\0';
        return tmp;
    }

    /**
     * @brief Returns the length of the string
     *
     * @return size_t
     */
    size_t length() const {
        return this->size;
    }

    /**
     * @brief Appends a character to the string
     *
     * @param ch
     */
    void append(char ch) {
        char* tmp = new char[this->size + 2];
        for (size_t i = 0; i < this->size; i ++) {
            tmp[i] = this->data[i];
        }

        tmp[this->size] = ch;
        tmp[this->size + 1] = '\0';

        delete[] this->data;

        this->data = new char[this->size + 2];

        for (size_t i = 0; i < this->size + 1; i ++) {
            this->data[i] = tmp[i];
        }
        this->size ++;

        delete[] tmp;
    }

    /**
     * @brief Append the provided string to the current string
     *
     * @param str
     */
    void concat(const char *str) {
        if (str[0] == '\0') {
            return;
        }

        if (this->size == 0) {
            this->data = new char[1];
            this->data[0] = '\0';
        }

        size_t sumSize = this->size;
        for (size_t i = 0; str[i] != '\0'; i++) {
            sumSize++;
        }

        char* tmp = new char[sumSize + 1];
        for (size_t i = 0; i < size; i ++) {
            tmp[i] = this->data[i];
        }

        for (size_t i = 0; str[i] != '\0'; i ++) {
            tmp[size + i] = str[i];
        }

        tmp[sumSize] = '\0';

        delete[] this->data;

        this->data = new char[sumSize + 1];

        this->size = sumSize;

        for (size_t i = 0; i < size; i ++) {
            this->data[i] = tmp[i];
        }
    }

    /**
     * @brief Compares 2 strings
     *
     * @param other
     * @return int 0 if the strings are equal, 1 if the current string is greater, -1 if the current string is smaller
     */
    int compare(const String &other) const {
        if (this->size == 0 && other.size == 0) {
            return 0;
        }

        size_t minSize = this->size < other.size ? this->size : other.size;

        for (size_t i = 0; i < minSize; i ++) {
            if (this->data[i] < other.data[i]) {
                return -1;
            }
            else if (this->data[i] > other.data[i]) {
                return 1;
            }
        }

        if(this->size > other.size) {
            return 1;
        }

        else if(this->size < other.size) {
            return -1;
        }

        return 0;
    }
};