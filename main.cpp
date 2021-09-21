#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <execution>
#include <iomanip>
#include <concepts>
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
template<typename T>
concept Iterator = requires(T a)
{
    {a.begin()};
    {a.end()};
};

template<Iterator T>
void mismatch(const T& vec1, T vec2)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    //vec2[mt() % SIZE] = mt() % SIZE;

    auto [iter1, iter2] = std::mismatch(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
    printLine(*iter1,"!=", *iter2);
}

int main(int, char**) {


    std::random_device rd;
    std::mt19937 mt(rd());

    std::vector<int> arrayFirst;
    std::vector<int> arraySecond;


    for(int i = 0; i < SIZE; ++i)
    {
        arrayFirst.push_back(mt() % SIZE);
        arraySecond.push_back(mt() % SIZE);
    }
    int randomEl = mt() % SIZE;

    mismatch(arrayFirst, arraySecond);

    return 0;
}
