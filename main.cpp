#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <execution>
#include <iomanip>
#include <ranges>
#include <source_location>
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

void printFunctionName(const std::source_location location = std::source_location::current())
{
    std::string function = location.function_name();
    const auto& iterLast = std::find(function.begin(), function.end(), '(');
    auto iterStart = std::find(function.begin(), iterLast, ' ');
    std::string func_name;
    std::move(++iterStart, iterLast, std::back_inserter(func_name));
    std::cout << func_name << '\n';
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
void search(const T& vec1, T vec2)
{
    const auto& iter = std::search(vec1.begin(), vec1.end(), vec2.begin(), vec2.end());

    if(iter != vec1.end())
    {
        printLine("Position:", std::distance(vec1.begin(), iter), "First Symbal:", *iter);
    }
    else
    {
        printLine("String doesn't contain substring");
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

template<HasIterator T>
void find_end(const T& arr1, const T& arr2)
{
    printFunctionName();

    const auto& iter = std::find_end(arr1.begin(), arr1.end(), arr2.begin(), arr2.end());
    if(iter != arr1.end())
    {
        printLine("Position:", std::distance(arr1.begin(), iter), "First Symbal:", *iter);
    }

}

template<HasIterator T>
void find_first(const T& arr1, const T& arr2)
{
    printFunctionName();
    const auto& iter = std::find_first_of(arr1.begin(), arr1.end(), arr2.begin(), arr2.end());
    if(iter != arr1.end())
    {
        printLine("Position:", std::distance(arr1.begin(), iter), "First Symbal:", *iter);
    }
}

template<HasIterator T>
void copy_bacward_1(T& arr1)
{
    printFunctionName();
    T arr2 = T(arr1.size());
    std::copy_backward(arr1.begin(), arr1.end(), arr2.end());
    printLine("Vector1:");
    printLine(arr1);
    printLine("Vector2:");
    printLine(arr2);
}

template<HasIterator T>
void copy_bacward_2(const T& arr1)
{
    printFunctionName();
    T arr2;
    std::copy(arr1.rbegin(), arr1.rend(), std::back_inserter(arr2));
    printLine("Vector1:");
    printLine(arr1);
    printLine("Vector2:");
    printLine(arr2);
}

int main(int, char**)
{
    std::random_device rd;
    std::mt19937 mt(rd());

    if constexpr(false)
    {
        std::vector<int> arrayFirst(SIZE, 0);
        std::generate(arrayFirst.begin(), arrayFirst.end(), [&mt](){return mt() % SIZE;});
        std::generate_n(arrayFirst.begin(), 2*SIZE / 3, [n = 0]()mutable{return ++n;});

        mismatch(arrayFirst, arrayFirst);
        adjacent(arrayFirst);
    }

    if constexpr(false)
    {
        std::string name = "My name is Ihar  ";
        std::string searchWord = "Ihar";

        search(name, searchWord);
    }

    if constexpr(false)
    {
        std::string name = "My r name is Ih ";
        std::string searchWord = "Ihar";

        find_first(name, searchWord);
        find_end(name, searchWord);
    }
    if constexpr(true)
    {
         std::vector<int> arraySecond = {1, 2, 5, 5, 4, 4, 6, 6, 8};

        copy_bacward_1(arraySecond);
        copy_bacward_2(arraySecond);
    }

    return 0;
}