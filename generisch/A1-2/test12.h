#pragma once

#include <cassert>
#include <iostream>
#include <typeinfo>

#include "vec.h"

using namespace std;
using namespace my;

template<typename T, int N>
void test_vec() {

    #ifndef NDEBUG
    cout << "======================" << endl;
    cout << "     Testing Vec<" << typeid(T).name() << ", " << N << ">" << endl;
    cout << "======================" << endl;

    {
        // do not tolerate any memory overhead
        cout << "  sizeof(Vec<T,N>) == N*sizeof(T) bytes: ";
        if(N>0) {
            assert( sizeof(Vec<T,N>) == N*sizeof(T) );
        }
        cout << "passed." << endl;
    }

    {
        cout << "  constructor & index operator: ";
        Vec<T,N> a;
        for (int i = 0; i < N; ++i) {
            assert( a[i] == T{} ); // T{} ist 0 bei numerischen typen
        }
        
        for (int i = 0; i < N; ++i) {
            a[i] = static_cast<T>(i+1); // fuellen mit 1, 2, 3, ...
        }

        for (int i = 0; i < N; ++i) {
            assert( a[i] == static_cast<T>(i + 1) );
        }
        cout << "passed." << endl;
    }

    {
        cout << "  read-only access to const object: ";
        Vec<T,N> temp;
        for (int i = 0; i < N; ++i) {
            temp[i] = static_cast<T>(i+1); // fuellen mit 1, 2, 3, ...
        }

        const Vec<T,N> a = temp;
        for (int i = 0; i < N; ++i) {
            assert( a[i] == static_cast<T>(i + 1) );
        }
        // the next line will throw a compiler error if there is no proper "operator[] const"
        cout << "passed." << endl;
    }

    {
        cout << "  write access to a non-const object: ";
        Vec<T,N> a;
        if (N > 1) {
            a[0] = static_cast<T>(1);
            a[1] = static_cast<T>(4);
            assert( a[0] == static_cast<T>(1) && a[1] == static_cast<T>(4) );
        }
        
        cout << "passed." << endl;
    }

    {
        cout << "  comparison: ";        
        Vec<T,N> a, b, c, d;
        for (int i = 0; i < N; ++i) {
            a[i] = static_cast<T>(i+1); // fuellen mit 1, 2, 3, ...
            b[i] = static_cast<T>(i+1); // fuellen mit 1, 2, 3, ...
            c[i] = static_cast<T>(i+2); // fuellen mit 1, 2, 3, ...
            d[i] = static_cast<T>(i+3); // fuellen mit 1, 2, 3, ...
        }
        assert( a == b );
        assert( a == a );
        assert( !(a != b) );

        if(N > 0) {
            assert( a != c );
            assert( b != d );
        }
        cout << "passed." << endl;
    }
    
    {
        // should work out of the box when using std container (!)
        cout << "  assignment: "; 
        Vec<T,N> a, b;
        for (int i = 0; i < N; ++i) {
            a[i] = static_cast<T>(i+1); // fuellen mit 1, 2, 3, ...
            b[i] = static_cast<T>(i+10); // fuellen mit 10, 11, 12, ...
        }
        a = b;
        assert( a == b );
        cout << "passed." << endl;
    }
    
    {
        cout << "  addition: ";
        Vec<T,N> a, b, sum_ab, sum_bc;
        for (int i = 0; i < N; ++i) {
            auto x = static_cast<T>(i+1); // fuellen mit 1, 2, 3, ...
            auto y = static_cast<T>(i+10); // fuellen mit 10, 11, 12, ...
            a[i] = x;
            b[i] = y;
            sum_ab[i] = x + y;
        }
        a += b;
        assert( a == sum_ab );     // <--- OK
        auto c = a + b;     // <--- OK
        for (int i = 0; i < N; ++i) {
            sum_bc[i] = a[i] + b[i];
        }
        
        assert( (c == sum_bc) );    // <--- OK
        cout << "passed." << endl;
    }
    
    {
        cout << "  unary minus: ";
        Vec<T,N> a, b;
        for (int i = 0; i < N; ++i) {
            a[i] = static_cast<T>(i+1); // 1, 2, ...
            b[i] = static_cast<T>(-(i+1)); // "gegenteilwerte -1, -2, ..."
        }
        assert( (-a == b) );
        cout << "passed." << endl;
    }
    
    {
        cout << "  dot product: ";
        Vec<T,N> a;
        auto sum_dot = T{};
        for (int i = 0; i < N; ++i) {
            a[i] = static_cast<T>(i+1); // 1, 2, ...
            sum_dot += static_cast<T>(i+1) * static_cast<T>(i+1);
        }
        assert(( dot(a,a) == sum_dot ));
        cout << "passed." << endl;
    }

    {
        // these tests will not compile if you forgot to declare 
        // some methods const
        cout << "  constness: ";
        Vec<T,N> a;
        Vec<T,N> sum, neg;
        auto dot_result = T{};

        for (int i = 0; i < N; ++i) {
            a[i] = static_cast<T>(i+1); // 1, 2, ...
            sum[i] = static_cast<T>(2 * (i+1)); // 2, 4, ...
            neg[i] = static_cast<T>(-(i+1)); // -1, -2, ...
            dot_result += static_cast<T>(i+1) * static_cast<T>(i+1);
        }

        const Vec<T,N> b = a;

        if (N>0) assert( b[0] == static_cast<T>(1) );
        assert ( b == b );
        assert( ! (b != b) );
        assert( b+b == sum );
        assert( -b == neg );
        assert(( dot(b,b) == dot_result ));
        cout << "passed." << endl;
    }

    cout << "all Vec<T,N> tests passed." << endl << endl;   

#endif // not NDEBUG
}