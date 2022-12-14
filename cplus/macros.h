
// based on oktal's macros https://github.com/oktal/result

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

