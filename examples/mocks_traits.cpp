#include <etl/variant.h>
#include <etl/array.h>
#include <cstdio>
#include "include/macros.h"
#include "include/mocks.h"

template<typename T>
class IModifable
{
public:
    INTERFACE(IModifable)
    {
        METHOD(int,set,(int) const);
    }
    
};

// template inheritance declaration
class SQLite: public IModifable<SQLite>
{
    public:
    SQLite(): IModifable()
    {

    }
    int set(int n) const {
        printf("SQLite set with %d!\n", n);
        return 0;
    }
};

Variant(Modifable, SQLite);

class MockName(Modifable): public IModifable<MockName(Modifable)>
{
    public:
    MockName(Modifable)(): IModifable()
    {

    }
    CREATE_MOCK_METHOD(int , set, const);
};


int hello_world(int n) {
    printf("Mock set called with %d!\n", n);
    return 0;
}

class Bank {
public:
    Bank(Modifable database): m_modifable(database) {}
    bool deposit(int amount)
    {
        if(amount > 0) 
        {
            etl::visit([&](auto& modifable){modifable.set(amount);}, m_modifable);
            return true;
        }
        return false;
    }
    Modifable m_modifable;
};

int main()
{
    MockName(Modifable) mock;
    MockMethod(mock , set).hook(hello_world);
    

    struct A {
        A(const Modifable m): m_modifable(m){}
        Modifable m_modifable;
    } a = {mock};

    mock.set(3);

    etl::get<decltype(mock)>(a.m_modifable).set(3);

    Bank b(mock);

    // etl::get<decltype(mock)>(b.m_modifable).set(3);

    // const int deposit_value = 3;

    // if(!b.deposit(deposit_value))
    // {
    //     printf("test failed!\n");
    //     return 1;
    // }
    // if(MockMethod(mock, set).called_using(deposit_value))
    // {
    //     printf("I'm so happy my mock actually received the params I passed");
    // }
    // printf("test succeeded!\n");
 
    return 0;
}