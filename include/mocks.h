#include <etl/hash.h>

#define MockMethod(mock, method) mock.m_##method

template <typename T>
size_t hash(const T &v)
{
    return etl::hash<T>()(v);
}

template <>
size_t hash(const std::nullptr_t &null_ptr)
{
    return 0;
}

size_t hash()
{
    return 0;
}

template <typename T, typename... Args>
size_t hash(T first, Args... args)
{
    size_t h = etl::hash<T>()(first) ^ (hash(args...) << 1);
    return h;
}

template <typename FuncType, typename ReturnType>
struct MockMetadata
{
    FuncType func = nullptr;
    size_t m_call_count = 0;
    size_t m_last_params_hash = 0;
    ReturnType m_ret_val{};
};

#define CREATE_MOCK_METHOD(lhs, name, rhs)                                      \
    struct name##Func                                                           \
    {                                                                           \
        static lhs func(const name##Func *obj, size_t params_hash)              \
        {                                                                       \
            obj->meta.m_last_params_hash = params_hash;                         \
            obj->meta.m_call_count++;                                           \
            if (nullptr != obj->meta.func)                                      \
            {                                                                   \
                return obj->meta.func();                                        \
            }                                                                   \
            return obj->meta.m_ret_val;                                         \
        }                                                                       \
        using ReturnType = decltype(((name##Func *)nullptr)->func(nullptr, 0)); \
        using FuncType = ReturnType (*)();                                      \
                                                                                \
                                                                                \                                                                                
        template <typename GenericFunc>                                         \
        void hook(GenericFunc hook_function)                                    \
        {                                                                       \
            meta.func = reinterpret_cast<FuncType>(hook_function);              \
        }                                                                       \
        void unhook()                                                           \
        {                                                                       \
            meta.func = nullptr;                                                \
        }                                                                       \
        /* sets the return value, if the function is hooked the return value    \
        is the one returned by the hook */                                      \
        void set_return(ReturnType value)                                       \
        {                                                                       \
            meta.m_ret_val = value;                                             \
        }                                                                       \
        size_t get_call_count() const                                           \
        {                                                                       \
            return meta.m_call_count;                                           \
        }                                                                       \
        bool was_called() const                                                 \
        {                                                                       \
            return meta.m_call_count > 0;                                       \
        }                                                                       \
                                                                                \
        /* returns true if args are the last arguments the mock was             \
        called with */                                                          \
        template <typename... Args>                                             \
        bool called_using(Args... args)                                         \
        {                                                                       \
            return was_called() && hash(args...) == meta.m_last_params_hash;    \
        }                                                                       \
                                                                                \
        static size_t _get_map_size()                                           \
        {                                                                       \
            return sizeof(meta);                                                \
        }                                                                       \
                                                                                \
    private:                                                                    \
        mutable MockMetadata<FuncType, ReturnType> meta;                        \
    } m_##name;                                                                 \
                                                                                \
    template <typename... Args>                                                 \                                                                                
    lhs name(Args... args) rhs                                                  \
    {                                                                           \
        return this->m_##name.func(&m_##name, hash(args...));                   \
    }
