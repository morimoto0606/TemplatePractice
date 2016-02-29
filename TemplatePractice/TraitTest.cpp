#include <iostream>
using namespace std;

template <typename T>
struct TypeTrait {
  enum { typeid_ = -1 };
};

#define DEFINE_TRAIT(type, id)   \
  template <>                    \
  struct TypeTrait<type> {       \
    enum { typeid_ = id};        \
  };

DEFINE_TRAIT(int, 1);
DEFINE_TRAIT(float, 2);
DEFINE_TRAIT(double, 3);

// prevent compiler warning because variable unused
template <typename X>
void no_unused_warning(X x) {}

template <typename T>
void foo(const T& v)
{
  //// Compile-time type filtering
  //char Invalid_Argument_DataType_To_foo[TypeTrait<T>::typeid_];
  //no_unused_warning(Invalid_Argument_DataType_To_foo);

  // Runtime type identification
  switch (TypeTrait<T>::typeid_)
  {
    case TypeTrait<int>::typeid_:
      cout << "Receive integer" << endl; break;
    case TypeTrait<float>::typeid_:
      cout << "Receive float" << endl; break;
    case TypeTrait<double>::typeid_:
      cout << "Receive double" << endl; break;
    default: cout << "Receive unknown type" << endl;
  }

  // ...
}

int main(int argc, char *argv[])
{
  foo(1);
  foo(1.0f);
  foo(1.0);
  foo(static_cast<short>(1));

  return 0;
}