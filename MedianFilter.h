#pragma once

class MedianFilter3 {
  private:
    int buf[3];
    int idx;
    bool filled;
  public:
    MedianFilter3();
    void push(int v);
    int median();
    void reset();
};
