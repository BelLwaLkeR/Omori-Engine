#include "Rectangle.h"

int Omory::Rectangle::width()
{
    return right - left;
}

int Omory::Rectangle::height()
{
    return bottom - top;
}
