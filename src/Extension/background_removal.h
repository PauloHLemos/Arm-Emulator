#ifndef BACKGROUND_REMOVAL_H
#define BACKGROUND_REMOVAL_H
#include "definitions.h"

Frame *replace_background(Frame *frame_ptr, Frame *original_background_ptr, Frame *replacement_background_ptr);

#endif
