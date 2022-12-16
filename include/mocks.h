
#define MockMethod(mock, method) mock.method##_struct

template <typename C, void (C::*M)()>
void AsFunc(void* p)
{
    (static_cast<C*>(p)->*M)();
}