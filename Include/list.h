#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include "object.h"
#include "consobject.h"

ConsObject* Node(Object*);

Object* List(size_t, ...);

#endif