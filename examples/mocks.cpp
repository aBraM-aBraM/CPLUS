#include <cstdio>
#include "include/macros.h"
#include "include/mocks.h"

#include <etl/type_traits.h>
#include <etl/optional.h>

// wip

template<typename T>
class ICompressable
{
public:
    INTERFACE(ICompressable)
    {
        METHOD(int ,compress,());
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
        int operator()()
        {
            m_call_count++; 
            return m_ret_val;
        }
        using return_t = decltype(((compress_struct_t*)nullptr)->operator()());
        void set_return(return_t value) {m_ret_val = value;}
        size_t get_call_count() {return m_call_count;}
        bool was_called() {return m_call_count > 0;}
        private:
        size_t m_call_count = 0;
        return_t m_ret_val {};

    } compress_struct;

    int compress() {
        return this->compress_struct.operator()();
    }
};


int main()
{
    MockCompress mock;
    MockMethod(mock, compress).set_return(4);
    printf("ret val: %d\n" , mock.compress());
    printf("call count: %d\n", MockMethod(mock, compress).get_call_count());

    return 0;
}