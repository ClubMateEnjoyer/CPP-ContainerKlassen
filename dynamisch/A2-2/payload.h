#ifndef PAYLOAD_H
#define PAYLOAD_H

#include <memory>

/*
 *  Payload serves for testing containers. It
 *  counts how many instances of this type
 *  currently exist, via a static counter. 
 *
 */
class Payload {

public:
    // data
    float x, y, z;

    // constructors
    Payload(float xx=0, float yy=0, float zz=0) : x(xx), y(yy), z(zz) { count_++; }
    Payload(const Payload& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { count_++; copy_count_++; }
    //Payload(const Payload&& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { count_++; move_count_++; } const geht doch garnicht?
    Payload(Payload&& rhs) : x(rhs.x), y(rhs.y), z(rhs.z) { count_++; move_count_++; }

    // destructor
    ~Payload()  { count_--; }

    // assignment - keeps count the same 
    Payload& operator=(const Payload& rhs) { x=rhs.x; y=rhs.y; z=rhs.z; copy_count_++; return *this; }
    // Payload& operator=(const Payload&& rhs) { x=rhs.x; y=rhs.y; z=rhs.z; return *this; } const?
    Payload& operator=(Payload&& rhs) { x=rhs.x; y=rhs.y; z=rhs.z; move_count_++; return *this; }

    // comparison
    bool operator==(const Payload& rhs) const { return x==rhs.x && y==rhs.y && z==rhs.z; }
    bool operator!=(const Payload& rhs) const { return ! (*this == rhs); }

    // tell count
    static size_t count() { return count_; }
    static size_t copy_count() { return copy_count_; }
    static size_t move_count() { return move_count_; }

    static void reset_counts() { copy_count_ = 0; move_count_ = 0; } 

private:
    static size_t count_;
    static size_t copy_count_;
    static size_t move_count_;
};


#endif // PAYLOAD_H
