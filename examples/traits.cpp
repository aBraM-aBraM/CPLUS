/*
* Inheritance and OOP as a whole is one of the greatest features of C++
* it allows us to simplify readabilty and have polymorphism
*
* Polymorphism is the ability to have a collection of types to be 
* treated as a type of their shared attributes & methods.
*
* The disadvantage of polymorphism in C++ is its implementation (vtables)
* Interfaces in C++ are a collection of virtual methods (practically an API)
* class can provide the same API by inheriting from given interfaces.
*
* When a class' implementation of a virtual function is called there's a jump
* to the virtual method table (vtable) that pairs the address of the corresponding
* class' implementation of the virtual function.
*
* vtables are not part of the c++ standard, they don't have a standard location in
* which they are stored and the entire concept of virtual functions may change between
* different compilers. 
*
* Instead of using virtual functions inheritances can be enforced in C++ in compile time
* using templates (traits). This allows the developer to have polymorphism and inheritance
* without vtables at all!
*
* currently I support polymorphism only in cpp14
*/


#include <etl/variant.h>
#include <etl/array.h>
#include <cstdio>
#include "include/macros.h"

// based on Bjarne Stroustrup in his C++ Style and Technique FAQ,
// crediting Alex Stepanov and Jeremy Siek for the use of pointer to function





template<typename T>
class ICompressable
{
public:
    INTERFACE(ICompressable)
    {
        METHOD(T*,compress,() const);
    }
    
};

// the macros expand the class in the following way:
// these macros expand to this:
    /*
template<typename T>
class ICompressable {
    public:
    ICompressable() {
        void(*p)() = Constraints; // makes sure constraints is evaluated
        static void Constraints()
        {
            // start of RTYPE_NAME_CONST expansion
            {
                T* (T::*_a_)() const = &T::compress; // makes sure compress exists at the given signature
                _a_; // remove unused variable warnings;
            }
        }
    }
};
*/

// template inheritance declaration
class Zip: public ICompressable<Zip>
{
    public:
    // call base interface's ctor to validate
    // function implementations in compilation time
    Zip(): ICompressable()
    {

    }

    // comment this function to see the compilation error
    // when Zip doesn't implement `compress`
    Zip* compress() const {
        printf("Zip compress!\n");
        return nullptr;
    }
};

class TarGZ: public ICompressable<TarGZ>
{
    public:
    TarGZ(): ICompressable()
    {

    }

    TarGZ* compress() const {
        printf("TarGZ compress!\n");
        return nullptr;
    }
};

using Compressable = etl::variant<Zip, TarGZ>;

int main()
{
    // Usage with polymorphism
    etl::array<Compressable, 2> compressables = {Zip(), TarGZ()};
    for (auto& c : compressables)
    {
        // this beauty is only available in cpp14
        etl::visit([](auto& compressable){compressable.compress();}, c);
    }
    return 0;
}