/*
* Procedural programming is the usage of "return codes"
* instead of exceptions.
*
* Instead of using simple return codes like errno we can use
* results - A specialized union that holds either a returned value
* or a returned error. 
*
* Exceptions come with many disadvantages, they require their
* own section for stack unwinding (__exidx_start in arm for example)
*
* They are harder to debug, bloat the code (They add their
* entire handler) and create an impact on performance (roughly 5-15%)
*
* fun fact - results are a core part of the rust language
*/

#include <cstdio>
#include <etl/result.h>
#include "include/macros.h"

// I've declared to clear the usage of result
using value_t = int;
using error_t = char;

etl::result<value_t, error_t> is_natural(int n)
{
    if(n > 0) 
    {
        return etl::result<int, char>(n); // returns a result containing a value
    }
    return etl::result<int, char>('n'); // returns a result containing an error
}

etl::result<value_t, error_t> sum_naturals(int a, int b, int c)
{
    // if the result in try is an error returns the error itself
    // otherwise, evaluates to the value itself thus allowing assignment into `sum`
    int sum = TRY(is_natural(a));
    sum += TRY(is_natural(b));
    sum += TRY(is_natural(c));
    return sum;
}

// void function using result
etl::result<void, error_t> inc_natural(int& a)
{
    if(a > 0){
        a++;
        return etl::result<void, error_t>();
    }
    return etl::result<void, error_t>('n');
}

int main() {
    etl::result<value_t, error_t> sum_result =  sum_naturals(1,2,3);
    if (sum_result.is_error()){
        printf("error, isn't natural\n");
        return sum_result.error();
    }
    printf("sum: %d\n", sum_result.value());

    int not_natural = -1;

    etl::result<void, error_t> inc_result = inc_natural(not_natural);
    if(inc_result.is_error())
    {
        printf("error, isn't natural\n");
        return inc_result.error();
    }

    // output:
    // sum: 6
    // error, isn't natural

    return 0;
}
