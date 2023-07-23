# NOTE
## STL源码解析p.57 template<int inst>
在class中有static成员，可以使用不同的inst值来获得不同的static成员
~~~
template<int inst>
class _A
{
private:
    static int num;
public:
    static int get()
    {
        return num;
    }
};

template<>
int _A<0>::num = 0;

template<>
int _A<1>::num = 1;


int main()
{
    _A<0> A_0;
    _A<1> A_1;

    cout << "A_0: " << A_0.get() << endl;
    cout << "A_1: " << A_1.get() << endl;

    return 0;
}
/*
输出：
A_0: 0
A_1: 1
*/
~~~