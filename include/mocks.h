#include <etl/variant.h>
#include <etl/unordered_map.h>

#define MockMethod(mock, method) mock.m_##method

template <typename FuncType, typename ReturnType>
struct MockMetadata
{
    FuncType _func_ = nullptr;
    size_t m_call_count = 0;
    ReturnType m_ret_val{};
};

template <size_t INSTANCE_COUNT, typename FuncType, typename ReturnType>
using InstanceMetaMap = etl::unordered_map<size_t, MockMetadata<FuncType, ReturnType>, INSTANCE_COUNT>;

#define CREATE_MOCK_METHOD(lhs, name, rhs, instance_count)                                         \
    struct name##Func                                                                              \
    {                                                                                              \
        static lhs func(const name##Func *obj)                                                     \
        {                                                                                          \
            obj->meta->m_call_count++;                                                             \
            if (nullptr != obj->meta->_func_)                                                      \
            {                                                                                      \
                return obj->meta->_func_();                                                        \
            }                                                                                      \
            return obj->meta->m_ret_val;                                                           \
        }                                                                                          \
        using ReturnType = decltype(((name##Func *)nullptr)->func(nullptr));                       \
        using FuncType = ReturnType (*)();                                                         \
        using MapType = InstanceMetaMap<instance_count, FuncType, ReturnType>;                     \
        template <typename GenericFunc>                                                            \
        void hook(GenericFunc hook_function)                                                       \
        {                                                                                          \
            meta->_func_ = reinterpret_cast<FuncType>(hook_function);                              \
        }                                                                                          \
        void unhook()                                                                              \
        {                                                                                          \
            meta->_func_ = nullptr;                                                                \
        }                                                                                          \
        void set_return(ReturnType value)                                                          \
        {                                                                                          \
            meta->m_ret_val = value;                                                               \
        }                                                                                          \
        size_t get_call_count() const                                                              \
        {                                                                                          \
            return meta->m_call_count;                                                             \
        }                                                                                          \
        bool was_called() const                                                                    \
        {                                                                                          \
            return meta->m_call_count > 0;                                                         \
        }                                                                                          \
                                                                                                   \
        static size_t _get_map_size()                                                              \
        {                                                                                          \
            return sizeof(name##MetaMap);                                                          \
        }                                                                                          \
                                                                                                   \
    private:                                                                                       \
        static inline MapType name##MetaMap;                                                       \
        MockMetadata<FuncType, ReturnType> *meta = &name##MetaMap[reinterpret_cast<size_t>(this)]; \
    } m_##name;                                                                                    \
                                                                                                   \
    lhs name rhs                                                                                   \
    {                                                                                              \
        return this->m_##name.func(&m_##name);                                                     \
    }
