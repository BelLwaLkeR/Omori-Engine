#include "Rectangle.h"
#include <assert.h>

unsigned int Omory::Rectangle::width() const
{
  assert(right > left);
  return right - left;
}

unsigned int Omory::Rectangle::height() const
{
  assert(bottom > top);
  return bottom - top;
}
