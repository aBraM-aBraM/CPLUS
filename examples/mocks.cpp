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
    int hook_compress()
    {
        printf("hooked!\n"); // hooks would be used for mocking
        return 0;
    }

    
    struct CompressStructType {
        int func()
        {
            m_call_count++; 
            if(nullptr != _func_) {
                return ((*this).*_func_)();
            }
            return m_ret_val;
        }
        using ReturnType = decltype(((CompressStructType*)nullptr)->func());
        using FuncType = decltype(&CompressStructType::func);

        template<typename GenericFunc>
        void hook(GenericFunc hook_function) {_func_ = reinterpret_cast<FuncType>(hook_function);}
        void unhook() {_func_ = nullptr;}
        void set_return(ReturnType value) {m_ret_val = value;}
        size_t get_call_count() {return m_call_count;}
        bool was_called() {return m_call_count > 0;}

        private:
        FuncType _func_ = nullptr;
        size_t m_call_count = 0;
        ReturnType m_ret_val {};

    } compress_struct;

    int compress() {
        return this->compress_struct.func();
    }
};


int main()
{
    MockCompress mock;
    MockMethod(mock, compress).set_return(4);
    MockMethod(mock, compress).hook(&MockCompress::hook_compress);
    printf("ret val: %d\n" , mock.compress());
    printf("call count: %d\n", MockMethod(mock, compress).get_call_count());

    MockMethod(mock, compress).unhook();
    printf("ret val: %d\n" , mock.compress());
    printf("call count: %d\n", MockMethod(mock, compress).get_call_count());

    return 0;
}