#include "cplus/macros.h"

etl::result<void, int> get_result(int a)
{
    if(a > 0) return etl::result<void, int>(a);
    return etl::result<void, int>();
}

int main() {
    return 0;
}
