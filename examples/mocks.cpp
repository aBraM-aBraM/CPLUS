#include <cstdio>
#include "include/macros.h"
#include "include/mocks.h"

#include <etl/type_traits.h>

// wip

template<typename T>
class ICompressable
{
public:
    INTERFACE(ICompressable)
    {
        METHOD(void ,compress,());
    }
};


// this should be generated w/macros
class MockCompress : public ICompressable<MockCompress>
{
    
    public:
    MockCompress(): ICompressable()
    {

    }
    void hook_compress()
    {
        printf("hooked!\n"); // hooks would be used for mocking
    }

    struct compress_struct_t {
        void operator()()
        {
            call_count++;
            ((*this).*_func_)();    
        }
        decltype(&compress_struct_t::operator()) _func_;
        size_t call_count = 0;
    } compress_struct;

    void compress() {
        this->compress_struct.operator()();
    }
};


int main()
{
    MockCompress mock;
    MockMethod(mock, compress)._func_ =  reinterpret_cast<decltype(MockMethod(mock, compress)._func_)>(&MockCompress::hook_compress);
    mock.compress();
    printf("call count: %d", MockMethod(mock, compress).call_count);

    return 0;
}