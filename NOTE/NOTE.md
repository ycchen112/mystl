# NOTE
## STL源码解析p.57 template\<int inst\>
在class中有static成员，可以使用不同的inst值来获得不同的static成员
~~~C++
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

## STL源码解析p.57 static void (* set_malloc_handler(void (* f)())) ()
https://www.cnblogs.com/Chierush/p/3745520.html
~~~C++
static void (* set_malloc_handler(void (* f)())) ()
{
    void (* old)() = __malloc_alloc_oom_handler;
    __malloc_alloc_oom_handler = f;
    return(old);
}
~~~
set_malloc_handler是一个函数指针,参数为void (\*f)() —— 一个void (\*)()类型的函数指针f<br>
set_malloc_handler前面一个*号说明该函数返回一个函数指针，该函数参数列表为空，返回值为void
