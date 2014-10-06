/*
 * requiring or prohibiting creation objects on heap
 */

#include <list>
#include <iostream>

/* don't want std::size_t in global namespace
 * but encapsulated inside the std */
#include <cstddef>
#include <algorithm>

/*
 * "Effective C++", Item 27
 *
 * A mixin ("mix in") class is one that provides a single
 * well-defined capability and is designed to be compatible
 * with any other capabilities an inheriting class might
 * provide (see Item E7). Such classes are nearly always abstract.
 * We can therefore come up with an abstract mixin base class
 * that offers derived classes the ability to determine whether
 * a pointer was allocated from operator new
 */
class HeapTracked {                  // mixin class; keeps track of
public:                              // ptrs returned from op. new

  class MissingAddress{};            // exception class; see below

  virtual ~HeapTracked() = 0;
  static void *operator new( std::size_t size);
  static void operator delete( void *ptr);
  bool isOnHeap() const;

private:
  typedef const void* RawAddress;
  static std::list<RawAddress> addresses;
};

// mandatory definition of static class member
std::list<HeapTracked::RawAddress> HeapTracked::addresses;

// HeapTracked's destructor is pure virtual to make the
// class abstract. The destructor must still
// be defined, however, so we provide this empty definition.
HeapTracked::~HeapTracked() {}

/* main idea */
void * HeapTracked::operator new( std::size_t size)
{
  void *memPtr = ::operator new( size);  // get the memory
  addresses.push_front( memPtr);         // put its address at
                                         // the front of the list
  return memPtr;
}

void HeapTracked::operator delete( void *ptr)
{
  // get an "iterator" that identifies the list
  // entry containing ptr; see Item 35 for details
  std::list<RawAddress>::iterator it =
    std::find( addresses.begin(), addresses.end(), ptr);

  if ( it != addresses.end()) {       // if an entry was found
    addresses.erase( it);             // remove the entry
    ::operator delete( ptr);          // deallocate the memory
  } else {                            // otherwise
    throw MissingAddress();           // ptr wasn't allocated by
  }                                   // op. new, so throw an
}                                     // exception

bool HeapTracked::isOnHeap() const
{
  // get a pointer to the beginning of the memory
  // occupied by *this; see below for details
  const void *rawAddress = dynamic_cast< const void*>( this);

  // look up the pointer in the list of addresses
  // returned by operator new
  std::list<RawAddress>::iterator it =
    std::find( addresses.begin(), addresses.end(), rawAddress);

  return it != addresses.end();      // return whether it was
}

//
class Asset: public HeapTracked {
private:
  int a;
};

/* allow only stack allocation */
class OnlyStack {
    private:

    static void *operator new( std::size_t size);
    static void operator delete( void *ptr);
};

class NotHappy : public OnlyStack {
    int u;
};

/*
 *
 */
int main() {

    Asset a;
    Asset *ap = new Asset;

    std::cout << a.isOnHeap() << ap->isOnHeap();

    NotHappy n;
    NotHappy* pnh = new NotHappy; // error: OnlyStack::operator new is private

    return 0;
}
