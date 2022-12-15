

// .: Result Macros :.
// based on oktal's result macros https://github.com/oktal/result

#define TRY(statement)                              \
    ({                                              \
        auto res = statement;                       \
        if (res.is_error()) {                       \
            return res.error();                     \
        }                                           \
        res.value();                                \
    })                                              \

#define TRY_VOID(statement)                         \
    ({                                              \
        auto res = statement;                       \
        if (res.is_error()) {                       \
            return res.error();                     \
        }                                           \
    })                                              \

// .: Template Interface Macros :. 

#define METHOD(lhs, name, rhs)  \
 {                              \
 lhs (T::*_a_)rhs = &T::name;   \
 _a_;                           \
 }                              \


#define INTERFACE(interface_name)                   \
    interface_name() { void (*p)() = Constraints; } \
    static void Constraints()                       \


