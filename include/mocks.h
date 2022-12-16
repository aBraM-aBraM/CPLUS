
#define MockMethod(mock, method) mock.method##_struct

template <typename C, void (C::*M)()>
void AsFunc(void *p)
{
    (static_cast<C *>(p)->*M)();
}

#define CREATE_MOCK_METHOD(lhs, name, rhs)                                         \
    struct name##StructType                                                        \
    {                                                                              \
        static int func(name##StructType *obj)                                     \
        {                                                                          \
            obj->m_call_count++;                                                   \
            if (nullptr != obj->_func_)                                            \
            {                                                                      \
                return obj->_func_();                                              \
            }                                                                      \
            return obj->m_ret_val;                                                 \
        }                                                                          \
        using ReturnType = decltype(((name##StructType *)nullptr)->func(nullptr)); \
        using FuncType = ReturnType (*) rhs;                                       \
                                                                                   \
        template <typename GenericFunc>                                            \
        void hook(GenericFunc hook_function)                                       \
        {                                                                          \
            _func_ = reinterpret_cast<FuncType>(hook_function);                    \
        }                                                                          \
        void unhook()                                                              \
        {                                                                          \
            _func_ = nullptr;                                                      \
        }                                                                          \
        void set_return(ReturnType value)                                          \
        {                                                                          \
            m_ret_val = value;                                                     \
        }                                                                          \
        size_t get_call_count()                                                    \
        {                                                                          \
            return m_call_count;                                                   \
        }                                                                          \
        bool was_called()                                                          \
        {                                                                          \
            return m_call_count > 0;                                               \
        }                                                                          \
                                                                                   \
    private:                                                                       \
        FuncType _func_ = nullptr;                                                 \
        size_t m_call_count = 0;                                                   \
        ReturnType m_ret_val{};                                                    \
    } name##_struct;                                                               \
                                                                                   \
    lhs name rhs                                                                   \
    {                                                                              \
        return this->name##_struct.func(&name##_struct);                           \
    }
