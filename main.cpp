#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <execution>
#include <iomanip>
constexpr int SIZE = 100;

class EightBytes
{
private:
    int32_t value;
    int32_t value1;

public:
    EightBytes() : value(0), value1(0)
    {
        std::cout<< "ctor\n";
    }
    void Value(int32_t val) {
        value = val;
        std::cerr << "set value: " << value <<std::endl;
        }
    int32_t Value() {return value;}

    void Value1(int32_t val) {
        value1 = val;
        std::cerr << "set value: " << value1 <<std::endl;
        }
    int32_t Value1() {return value1;}
    void Print()
    {
        std::cout << "EightBytes\t" << Value1() << "\t" << Value() << "\n";
    }
};

class FourBytes
{
private:
    int32_t value;

public:
    FourBytes() : value(0)
    {
        std::cout<< "ctor\n";
    }
    void Value(int32_t val) {
        value = val;
        std::cerr << "set value: " << value <<std::endl;
        }
    int32_t Value() {return value;}
    void Print()
    {
        std::cout  << "FourBytes\t" << Value() << "\n";
    }
};
template<typename ...Args>
void printLine(Args... args)
{
    char sep = ' ';
    ((std::cout << args << sep), ...) << '\n';
}

int main(int, char**) {


    std::random_device rd;
    std::mt19937 mt(rd());

    std::vector<int> array;

    for(int i = 0; i < SIZE; ++i)
    {
        array.push_back(mt() % SIZE);
    }
    int randomEl = mt() % SIZE;

    printLine("Count =", std::count(array.cbegin(), array.cend(), randomEl), "Elements");

    return 0;
}
