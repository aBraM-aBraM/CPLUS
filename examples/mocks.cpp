/*
 * This is my implementation of mocking
 * using trait interfaces, uncoupled to any standard library
 */
#include <cstdio>
#include "include/macros.h"
#include "include/mocks.h"

#include <etl/type_traits.h>
#include <etl/unordered_map.h>
#include <etl/string.h>

template <typename T>
class ICompressable
{
public:
    INTERFACE(ICompressable)
    {
        METHOD(int, compress, () const);
        METHOD(char *, get_str, ());
    }
};

class MockCompress : public ICompressable<MockCompress>
{
public:
    MockCompress() : ICompressable() {}
    int hook_compress()
    {
        printf("hooked!\n");
        return 0;
    }
    static const int INSTANCE_COUNT = 2;
    // creates a mock for the given method
    CREATE_MOCK_METHOD(int, compress, () const, INSTANCE_COUNT);
    CREATE_MOCK_METHOD(char*, get_str, (), INSTANCE_COUNT);

    // behind the scenes CREATE_MOCK_METHOD creates a static unordered_map for
    // meta data. The size of this map can be evaluated in the following manner:
    const size_t size = MockCompress::compressFunc::_get_map_size();
};

int hook_compress2()
{
    printf("hooked2!\n");
    return 0;
}

int main()
{
    MockCompress mock1;

    MockMethod(mock1, compress).set_return(4);

    // return value is the last set return value
    MockMethod(mock1, compress).unhook();
    printf("ret val: %d\n", mock1.compress());
    printf("call count: %d\n\n", MockMethod(mock1, compress).get_call_count());

    // return value is the value returned by the hooking function
    MockMethod(mock1, compress).hook(&hook_compress2);
    printf("ret val: %d\n", mock1.compress());
    printf("call count: %d\n\n", MockMethod(mock1, compress).get_call_count());

    // hook with member function
    MockMethod(mock1, compress).hook(&MockCompress::hook_compress);
    printf("ret val: %d\n", mock1.compress());
    printf("call count: %d\n\n", MockMethod(mock1, compress).get_call_count());

    // different mocks instance store different metadata
    MockCompress mock2;
    MockMethod(mock1, compress).unhook();
    MockMethod(mock1, compress).set_return(1);
    MockMethod(mock2, compress).set_return(2);

    printf("ret val1: %d\n", mock1.compress());
    printf("ret val2: %d\n\n", mock2.compress());

    printf("call count1: %d\n", MockMethod(mock1, compress).get_call_count());
    printf("call count2: %d\n\n", MockMethod(mock2, compress).get_call_count());

    MockMethod(mock1, get_str).set_return("Hello ");
    MockMethod(mock2, get_str).set_return("World!");

    printf("%s %s\n\n", mock1.get_str(), mock2.get_str());

    printf("call count1: %d\n", MockMethod(mock1, get_str).was_called());
    printf("call count2: %d\n", MockMethod(mock2, get_str).get_call_count());

    return 0;
}