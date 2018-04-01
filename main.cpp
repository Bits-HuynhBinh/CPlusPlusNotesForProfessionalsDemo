#include <iostream>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <tuple>
#include <map>
#include <assert.h>
#include <functional>
#include <random>
#include <chrono>
#include "mingw.thread.h"
#include <future>

using namespace std;

#define OUT
// This is an object-like macro
#define PI 3.14159265358979

// This is a function-like macro.
// Note that we can use previously defined macros
// in other macro definitions (object-like or function-like)
// But watch out, its quite useful if you know what you're doing, but the
// Compiler doesn't know which type to handle, so using inline functions instead
// is quite recommended (But e.g. for Minimum/Maximum functions it is quite useful)
#define AREA(r) (PI*(r)*(r))



class Foo
{
    int data;

    Foo(int data)
    {
        this->data = data;
    }

    ~Foo(){}


    Foo& operator=(const Foo& another)
    {
        data = another.data;
        return *this;
    }
};


struct Rng
{
    float arr[3];
// pointers are iterators
    const float* begin() const {return &arr[0];}
    const float* end() const {return &arr[3];}
    float* begin() {return &arr[0];}
    float* end() {return &arr[3];}
};


std::tuple<int, float, std::string> foo(int a)
{
    int aa = 3;
    float b = 3.6;
    //return std::make_tuple(aa, b, "hahaha");
    return {aa, b, "hahaha"};

}

void function1(int a, int b, int& c, int& d)
{
    c = a - b;
    d = a + b;
}

void function2(int a, int b, int* c, int* d)
{
    *c = a - b;
    *d = a + b;
}


void function3(int a, int b, OUT int& c)
{
    c =  a + b;
}


inline  int add(int a, int b)
{
    return a + b;
}

class A
{
public:
    function<void(int, const string&)> m_CbFunc = nullptr;
    void foo()
    {
        if (m_CbFunc)
        {
            m_CbFunc(100, "event fired");
        }
    }
};


class B
{
public:
    B()
    {
        auto aFunc = bind(&B::eventHandler, this, std::placeholders::_1,
                               std::placeholders::_2);
        //anObjA.m_CbFunc = aFunc;
    }
    void eventHandler(int i, const std::string& s)
    {
        std::cout << s << ": " << i << std::endl;
    }
    void DoSomethingOnA()
    {
        anObjA.foo();
    }
    A anObjA;
};

class ListNode
{
    int data;
    ListNode *next;
    ListNode(int val):data(val),next(NULL)
    {

    }
};


void function4(int a, int b)
{

    cout << "function 4 run on thread " << a++ << endl;
    cout << "function 4 run on thread " << a++ << endl;
    cout << "function 4 run on thread " << a++ << endl;
    cout << "function 4 run on thread " << a++ << endl;
}

class Bar
{
public:
    void foo(int a)
    {
        std::cout << "WTF: " << a << '\n';
    }
};

void function5(int& a)
{
    a = 118;
}

int square(unsigned int i){
    return i*i;
}

int main()
{
    cout << endl;



    //async
    //future<int> fff = std::async(launch::async, square, 11);
    //std::cout << "square currently running\n"; //do something while square is running
    //std::cout << "result is " << fff.get() << '\n'; //getting the result from square
    //end async

    //thread
    int v1 = 2;
    thread t4{function5, ref(v1)};

    cout << "Thread ref: " << v1 << endl;
    cout << "Thread ref: " << v1 << endl;
    cout << "Thread ref: " << v1 << endl;
    cout << "Thread ref: " << v1 << endl;
    cout << "Thread ref: " << v1 << endl;
    cout << "Thread ref: " << v1 << endl;
    cout << "Thread ref: " << v1 << endl;

    auto lambda = [](int ab)
    {
        cout << "Hehehe: " << ab << endl;
    };

    thread t3(lambda, 112);

    Bar bar;
    std::thread t2(&Bar::foo, &bar, 10);

    std::thread t1(function4, 10, 20);

    cout << "continue before thread join 1" << endl;
    cout << "continue before thread join 2" << endl;
    cout << "continue before thread join 3" << endl;
    cout << "continue before thread join 4" << endl;

    //thread join: mean waiting for the thread done the job, then continue other task
    t1.join();

    cout << "hahaha" << endl;
    // end thread

    // They can be used like this:
    double pi_macro = PI;
    double area_macro = AREA(4.6);
    cout << "pi: " << pi_macro << "area: " << area_macro << endl;

    //Lambdas
    int p = 3;
    auto f = [p](int x) -> int { return p*x; };
    auto f1 = [p](int x) {return p * x; };
    auto f2 = [](int a, int b) {return a + b; };
    auto f3 = [](){return 4;};
    auto f4 = [](){};
    auto f5 = [&p](int x) -> int {return ++p * x;};
    //end

    int r = f5(5);
    cout << r << endl;

    /*auto now = chrono::system_clock::now();
    std::chrono::duration<double> elapsed = chrono::system_clock::now() - now;
    cout << "now: " << elapsed << endl;*/



    // start
    random_device crypto_random_generator;
    uniform_int_distribution<int> int_distribution(0,9);

    int actual_distribution[10] = {0,0,0,0,0,0,0,0,0,0};

    for(int i = 0; i < 10000; i++)
    {
        int result = int_distribution(crypto_random_generator);

        actual_distribution[result]++;
    }

    for(int i = 0; i < 10; i++)
    {
        std::cout << actual_distribution[i] << " ";
    }
    //end

    vector<int> vec1 = {1,2,3,4,5,6};
    int* pt1 = &vec1[0];
    //++pt1;
    //++pt1;
    cout << *pt1 << endl;

    for(int i = 0; i < vec1.size(); i++)
    {
        cout << *pt1 << endl;
        pt1++;
    }


    /*char* charss = "hello Barron";
    array<char, 12> arrChar;
    memcpy(arrChar.data(), charss, 12);
    cout << "Ha: " << arrChar.data() << endl;*/


    int *pi = new int(4);
    int *pi2 = pi;
    pi = new int(16);

    cout << "pi: " << *pi << endl;
    cout << "pi2: " << *pi2 << endl;
    //assert(pi2 != pi); //Will always pass.

    int *numberPointer1 = new int(3);

    int *numberPointer;
    std::cout << "The numberPointer points to the memory address " << numberPointer << ".\n";

    int a = 100;
    int& addressPointToA = a;
    int* pointerStoreAddressOfA = &a;

    addressPointToA = 10;
    *pointerStoreAddressOfA = 20;

    cout << "a: " << a << endl;
    cout << "address of a: " << &a << endl;
    cout << "another address point to a: " << addressPointToA << endl;
    cout << "pointer of a: " << &pointerStoreAddressOfA << endl;


    int x = 10;
    int& xx = x;
    int* xxx = &x;

    xx = 20;
    *xxx = 50;

    cout << "x:" << x << "xx:" << xx << endl;
    cout << "xxx:" << *xxx << endl;

    int ccccc;

    function3(3,1, ccccc);
    std::cout << ccccc << std::endl;

    int cccc;
    int dddd;

    function2(6, 3, &cccc, &dddd);
    std::cout << cccc << std::endl << dddd << std::endl;
    std::cout << std::endl;

   /* int* ccc;
    int* ddd;

    function2(6, 3, ccc, ddd);
    std::cout << *ccc << std::endl << ddd << std::endl;
    std::cout << std::endl;*/



    int cc;
    int dd;

    function1(5, 2, cc, dd);
    std::cout << cc << dd << std::endl;



    std::map<std::string, int> aMap;
    aMap.insert({"a", 1});
    aMap.insert({"b", 2});

    for(auto val : aMap)
    {
        std::cout << val.first << val.second << std::endl;
    }

    auto vars = foo(4);
    int var1 = std::get<0>(vars);
    float var2 = std::get<1>(vars);
    std::string var3 = std::get<2>(vars);




    char c = getchar();

    switch (c)
    {
        case 'y':
            std::cout << "yes" << std::endl;
            break;
        case 'n':
            std::cout << "no" << std::endl;
            break;
        default:
            std::cout << "default" << std::endl;
            abort();

    }


    bool boolValue;
    std::cin >> std::boolalpha >> boolValue;
    std::cout << "Value \"" << std::boolalpha << boolValue
              << "\" was parsed as " << std::noboolalpha << boolValue;

    std::string const prepared_data = "abcasd";
    {
        // Open a file for writing.
        std::ofstream output("foo.txt");
        // Write data.
        output << prepared_data;
    } // The ofstream will go out of scope here.// Its destructor will take care of closing the file properly.


    std::ifstream src("test2.txt");
    std::ofstream dst("copy1.txt");
    if(src.is_open())
    {
       dst << src.rdbuf();
    }
    //c++17
    //std::fileystem::copy_file("source_filename", "dest_filename");


    std::vector<std::string> strings;
    std::ifstream ifs("test2.txt");
    std::string s;
    while (ifs >> s)
    {
        //std::cout << "0:" << s << std::endl;
        strings.push_back(s);
    }

    for(int i =0; i < strings.size(); i++)
    {
        std::cout << "1:" << strings[i] << std::endl;
    }

    std::string str;
    std::ifstream is("test2.txt");

    std::stringstream buffer;
    buffer << is.rdbuf();
    is.close();
    std::cout << "AAAAA:" << buffer.str() << std::endl;
    std::cout << "BBBBB" << std::endl;

    char charr[4];
    is.read(charr, 4);
    std::cout << charr << std::endl;

    while (!is.eof())
    {
        std::getline(is, str);
        std::cout << str << std::endl;
    }


    std::string firstname, lastname;
    std::fstream fileStream;
    fileStream.open("test2.txt");
    if(fileStream.is_open())
    {
        //fileStream.read(data, 3);
        //std::cout << data << std::endl;
        //fileStream << "yes I am in";
        fileStream >> lastname;
        fileStream >> firstname;
        std::cout << lastname << firstname << std::endl;
    }



    std::ofstream of = std::ofstream("test1.txt");
    if(of.is_open())
    {
        //os << "hahahaha";
        std::cout << "done " << std::endl;
        of.write("hahaha", 6);

        if (of.bad())
        {
            // Failed to write!
        }

    }

    return 0;
}



void test_01()
{
    int arrs[5] = {1,2,3,4,5};
    int i = 0;

    for(auto& val : arrs)
    {
        val = val * 2;

        std::cout << "val " << val << std::endl;
        std::cout << "arr i " << arrs[i] << std::endl;


        std::cout << "&val " << &val << std::endl;
        std::cout << "&arr i " << &arrs[i] << std::endl;

        i++;
    }



    Rng rng = {{0.4f, 12.5f, 16.234f}};

    std::cout << rng.begin() << std::endl;
    std::cout << rng.begin() << std::endl;

    for(auto val: rng)
    {
        std::cout << val << " ";
    }


    /*float *arr = new float[3]{0.4f, 12.5f, 16.234f};
    for(auto val: arr) //Compile error.
    {
        std::cout << val << " ";
    }*/

    int aaa = 0b1111; //15
    int bbb = aaa << 1;
    std::cout << "bbb: " << bbb << std::endl;

    int aa = 0b1010;
    int bb = 0b0101;
    //         1111
    int cc = aa | bb;
    std::cout << "cc: " << cc << std::endl;


    int a = 5;
    int b = 12;
    int c = a | b;
    std::cout << "C: " << c << std::endl;

    int value;

    //std::cout << "enter:" << std::endl;
    //std::cin >> value;
    //std::cout << "Value: " << value << std::endl;

    std::vector<int> arrays = {1,2,3,4,5,6,7};

    for(auto& val : arrays)
    {
        std::cout << val << std::endl;
    }


    int* ptr = new int[10];
    ptr[0] = 12;
    ptr[2] = 15;
    ptr[3] = 17;

    std::cout << ptr[0] << std::endl;
    std::cout << ptr[1] << std::endl;
    std::cout << ptr[2] << std::endl;
    std::cout << ptr[3] << std::endl;
    std::cout << ptr[4] << std::endl;
    std::cout << ptr << std::endl;
    std::cout << &ptr << std::endl;
    std::cout << &ptr[0] << std::endl;
}