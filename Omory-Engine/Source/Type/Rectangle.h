#pragma once

namespace Omory {
  class Rectangle
  {
  public:
    Rectangle(int left, int top, int right, int bottom)
      :left(left),top(top),right(right),bottom(bottom){}
    Rectangle(int width, int height)
      :left(0),top(0),right(width),bottom(height){}
    Rectangle()
      :left(0),top(0),right(0),bottom(0){}
    int left;
    int right;
    int top;
    int bottom;
    int width();
    int height();
  private:

  };
}
