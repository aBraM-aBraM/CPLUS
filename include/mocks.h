#include <etl/variant.h>
#include <etl/unordered_map.h>

#define MockMethod(mock, method) mock.m_##method

template <typename FuncType, typename ReturnType>
struct MockMetadata
{
    FuncType func = nullptr;
    size_t m_call_count = 0;
    ReturnType m_ret_val{};
};

#define CREATE_MOCK_METHOD(lhs, name, rhs)                                   \
    struct name##Func                                                        \
    {                                                                        \
        static lhs func(const name##Func *obj)                               \
        {                                                                    \
            obj->meta.m_call_count++;                                        \
            if (nullptr != obj->meta.func)                                   \
            {                                                                \
                return obj->meta.func();                                     \
            }                                                                \
            return obj->meta.m_ret_val;                                      \
        }                                                                    \
        using ReturnType = decltype(((name##Func *)nullptr)->func(nullptr)); \
        using FuncType = ReturnType (*)();                                   \
                                                                             \
        template <typename GenericFunc>                                      \
        void hook(GenericFunc hook_function)                                 \
        {                                                                    \
            meta.func = reinterpret_cast<FuncType>(hook_function);           \
        }                                                                    \
        void unhook()                                                        \
        {                                                                    \
            meta.func = nullptr;                                             \
        }                                                                    \
        void set_return(ReturnType value)                                    \
        {                                                                    \
            meta.m_ret_val = value;                                          \
        }                                                                    \
        size_t get_call_count() const                                        \
        {                                                                    \
            return meta.m_call_count;                                        \
        }                                                                    \
        bool was_called() const                                              \
        {                                                                    \
            return meta.m_call_count > 0;                                    \
        }                                                                    \
                                                                             \
        static size_t _get_map_size()                                        \
        {                                                                    \
            return sizeof(meta);                                             \
        }                                                                    \
                                                                             \
    private:                                                                 \
        mutable MockMetadata<FuncType, ReturnType> meta;                     \
    } m_##name;                                                              \
                                                                             \
    lhs name rhs                                                             \
    {                                                                        \
        return this->m_##name.func(&m_##name);                               \
    }
