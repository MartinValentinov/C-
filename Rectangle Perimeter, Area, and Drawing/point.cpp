#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

class Point {
    double x;
    double y;

public:
    Point() : x(0), y(0) {}
    Point(double x, double y) : x(x), y(y) {}

    double getX() const {
        return x;
    }

    double getY() const {
        return y;
    }

    Point(string str) {
        str.erase(remove(str.begin(), str.end(), '('), str.end());
        str.erase(remove(str.begin(), str.end(), ')'), str.end());    
        str.erase(remove(str.begin(), str.end(), ' '), str.end());

        size_t sep = str.find(',');
        
        string xStr = str.substr(0, sep);
        string yStr = str.substr(sep + 1);

        stringstream ssX(xStr);
        stringstream ssY(yStr);

        ssX >> x;
        ssY >> y;
    }
};

class Rectangle {
    Point p1;
    Point p2;
    int width;
    int height;

public:
    Rectangle(const Point& p1, const Point& p2) {
        this->p1 = Point(min(p1.getX(), p2.getX()), min(p1.getY(), p2.getY()));
        this->p2 = Point(max(p1.getX(), p2.getX()), max(p1.getY(), p2.getY()));
        width = abs(this->p2.getX() - this->p1.getX());
        height = abs(this->p2.getY() - this->p1.getY());
    }

    double getArea() const {
        return width * height;
    }

    double getPerimeter() const {
        return 2 * (width + height);
    }

    void drawRectInFile(ofstream& out) const {
        if (!out.is_open()) {
            throw runtime_error("Output file is not open");
        }

        for (int i = 0; i < height; i ++) {
            if (i == 0 || i == height - 1) {
                out << '*' << string(width - 2, '-') << '*' << endl;
            } else {
                out << '|' << string(width - 2, ' ') << '|' << endl;
            }
        }
    }
};

int main() {
    try {
        ifstream inputFile("point.txt");
        if (!inputFile.is_open()) {
            throw runtime_error("Could not open file");
        }

        string line;
        getline(inputFile, line);
        line = line.substr(1, line.size() - 2);
        size_t commaPos = line.find(';');

        string point1Str = line.substr(0, commaPos);
        string point2Str = line.substr(commaPos + 1);

        Point p1(point1Str);
        Point p2(point2Str);

        inputFile.close();

        Rectangle rect(p1, p2);

        ofstream outputFile("output1.txt");
        if (!outputFile.is_open()) {
            throw runtime_error("Could not open output file");
        }

        outputFile << "Area: " << rect.getArea() << endl;
        outputFile << "Perimeter: " << rect.getPerimeter() << endl;
        outputFile.close();

        ofstream outputFile2("output2.txt");
        if (!outputFile2.is_open()) {
            throw runtime_error("Could not open output file 2");
        }

        rect.drawRectInFile(outputFile2);
        outputFile2.close();
    }
    catch (const exception& e) {
        cout << "Error: " << e.what() << endl;
    }
}