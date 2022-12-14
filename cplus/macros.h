#include <etl/result.h>

#define TRY(statement)                              \
    ({                                              \
        auto res = statement;                       \
        if (res.is_err()) {                         \
            return res.error();                     \
        }                                           \
        res.value();                                \
    })