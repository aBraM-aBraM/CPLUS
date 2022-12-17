/*
 * This is my implementation of mocking
 * using trait interfaces, heapless using etl
 */
#include <cstdio>
#include "include/macros.h"
#include "include/mocks.h"

template <typename T>
class ICompressable
{
public:
    INTERFACE(ICompressable)
    {
        METHOD(int, compress, () const);
        METHOD(char *, get_str, (char*));
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
    // creates a mock for the given method (args are deduced)
    CREATE_MOCK_METHOD(int, compress, const); // int compress(args) const
    CREATE_MOCK_METHOD(char*, get_str,); // char* get_str(args)

    // behind the scenes CREATE_MOCK_METHOD creates an unordered_map for
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
    printf("ret val: %d\n", mock1.compress()); // ret val: 4
    printf("call count: %d\n\n", MockMethod(mock1, compress).get_call_count()); // call count: 1

    // return value is the value returned by the hooking function
    MockMethod(mock1, compress).hook(&hook_compress2);
    printf("ret val: %d\n", mock1.compress()); // hooked2!
                                               // ret val: 0 
    printf("call count: %d\n\n", MockMethod(mock1, compress).get_call_count()); // call count: 2

    // hook with member function
    MockMethod(mock1, compress).hook(&MockCompress::hook_compress);
    printf("ret val: %d\n", mock1.compress()); // hooked!
                                               // ret val: 0
    printf("call count: %d\n\n", MockMethod(mock1, compress).get_call_count()); // call count: 3

    // different mocks instance store different metadata
    MockCompress mock2;
    MockMethod(mock1, compress).unhook();
    MockMethod(mock1, compress).set_return(1);
    MockMethod(mock2, compress).set_return(2);

    printf("ret val1: %d\n", mock1.compress());   // ret val1: 1
    printf("ret val2: %d\n\n", mock2.compress()); // ret val2: 2

    printf("call count1: %d\n", MockMethod(mock1, compress).get_call_count());   // call count1: 4
    printf("call count2: %d\n\n", MockMethod(mock2, compress).get_call_count()); // call count2: 1

    MockMethod(mock1, get_str).set_return("Hello ");
    MockMethod(mock2, get_str).set_return("World!");

    printf("%s %s\n\n", mock1.get_str(nullptr), mock2.get_str(nullptr)); // Hello  World!

    printf("call count1: %d\n", MockMethod(mock1, get_str).was_called());     // call count1: 1
    printf("call count2: %d\n\n", MockMethod(mock2, get_str).get_call_count()); // call count2: 1

    const auto used_param = "I pass this value";
    const auto unused_param = "I don't pass this value";
    mock1.get_str(used_param);

    printf("used: %s ? %d\n", used_param, MockMethod(mock1, get_str).called_using(used_param)); // used I pass this value ? 1
    printf("used: %s ? %d\n", unused_param, MockMethod(mock1, get_str).called_using(unused_param)); // used I don't pass this value ? 0

    return 0;
}