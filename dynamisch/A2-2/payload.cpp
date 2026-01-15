#include "payload.h"

// instantiate the payload's static count
size_t Payload::count_ = 0;
size_t Payload::copy_count_ = 0;
size_t Payload::move_count_ = 0;


