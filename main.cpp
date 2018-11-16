#include <cstddef>
#include <cstdlib>
#include <string>
#include <chrono>

#include "Vector.h"
#include "LinkedList.h"

namespace
{

template <typename T>
using LinearCollection = aisdi::LinkedList<T>;
using Vector= aisdi::Vector<T>;
void perfomTestLinearCollection()
{
    LinearCollection<std::string> collection;
    for(int i=0; i<100000; i++)
        collection.append(10);


}

void perfomTestVector()
{
    Vector<std::string> collection;
    for(int i=0; i<100000; i++)
        collection.append(10);
}


} // namespace

int main(int argc, char** argv)
{
    const std::size_t repeatCount = argc > 1 ? std::atoll(argv[1]) : 10000;//long long int atoll ( const char * str );
    auto startLinearCollection = std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < repeatCount; ++i)
        perfomTestLinearCollection();

    auto finishLinearCollection = std::chrono::high_resolution_clock::now() ;
    std::cout<<"Czas LinearCollection = "<<(finishLinearCollection-startLinearCollection )<<std::endl;

    auto startVector= std::chrono::high_resolution_clock::now();

    for (std::size_t i = 0; i < repeatCount; ++i)
        perfomTestVector();

    auto finishVector = std::chrono::high_resolution_clock::now();
    std::cout<<"Czas LinearCollection = "<<(finishVector-startVector)<<std::endl;

    return 0;

}
