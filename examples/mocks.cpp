/*
* This is my implementation of mocking
* using trait interfaces, uncoupled to any standard library
*/
#include <cstdio>
#include "include/macros.h"
#include "include/mocks.h"

#include <etl/type_traits.h>
#include <etl/optional.h>


template<typename T>
class ICompressable
{
public:
    INTERFACE(ICompressable)
    {
        METHOD(int ,compress,());
    }
};

class MockCompress : public ICompressable<MockCompress>
{
    public:
    MockCompress(): ICompressable(){}
    int hook_compress() {
        printf("hooked!\n");return 0;
    }
    CREATE_MOCK_METHOD(int, compress,());
};

int hook_compress2()
{
    printf("hooked2!\n");
    return 0;
}


int main()
{
    MockCompress mock;
    
    MockMethod(mock, compress).set_return(4);

    // return value is the last set return value
    MockMethod(mock, compress).unhook();
    printf("ret val: %d\n" , mock.compress());
    printf("call count: %d\n\n", MockMethod(mock, compress).get_call_count());

    // return value is the value returned by the hooking function
    MockMethod(mock, compress).hook(&hook_compress2);
    printf("ret val: %d\n" , mock.compress());
    printf("call count: %d\n\n", MockMethod(mock, compress).get_call_count());

    // hook with member function
    MockMethod(mock, compress).hook(&MockCompress::hook_compress);
    printf("ret val: %d\n" , mock.compress());
    printf("call count: %d\n", MockMethod(mock, compress).get_call_count());

    return 0;
}