#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <execution>
#include <iomanip>
#include <ranges>
constexpr int SIZE = 30;


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

template<typename T>
concept HasIterator = requires(T a)
{
    {a.begin()};
    {a.end()};
};


template<typename ...Args>
void printLine(Args... args)
{
    char sep = ' ';
    ((std::cout << args << sep), ...) << '\n';
}

template<HasIterator T>
void printLine(const T& arr)
{
    std::for_each(arr.begin(), arr.end(), [](const T::value_type& el) { std::cout << el << ' ';});
    std::cout<<'\n';
}

template<HasIterator T>
void mismatch(const T& vec1, T vec2)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    //vec2[mt() % SIZE] = mt() % SIZE;
    vec2.emplace_back(typename T::value_type{} + 5);

    const auto& [iter1, iter2] = std::mismatch(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());
    if(iter1 != vec1.end() && iter2 != vec2.end())
    {
        printLine(*iter1,"!=", *iter2);    
    }
    else
    {
        printLine("Arrays are equal");
    }
}



template<HasIterator T>
void adjacent(T& arr)
{
    const auto& it = std::adjacent_find(arr.begin(), arr.end());
    printLine("Vector:");
    printLine(arr);

    if(it != arr.end())
    {
        printLine("element =", *it);
    }

}

int main(int, char**)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    std::vector<int> arrayFirst;
    std::vector<int> arraySecond = {1, 2, 5, 5, 4, 4, 6, 6, 8};


    for(int i = 0; i < SIZE; ++i)
    {
        arrayFirst.push_back(mt() % SIZE);
    }
    
    int randomEl = mt() % SIZE;

    //mismatch(arrayFirst, arrayFirst);
    adjacent(arrayFirst);
    adjacent(arraySecond);

    return 0;
}
