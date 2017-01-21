#ifndef MAIN_H
#define MAIN_H


constexpr float lsize = 20; // mutable data
constexpr float rsize = lsize*2;

constexpr float lspace = lsize/2;
constexpr float rspace = rsize/3;

constexpr float arena_height = 6*lsize + 5*lspace;
constexpr float arena_width = 5*rsize + 4*rspace;

constexpr float margin0 = lsize*5/10;
constexpr float margin1 = lsize*27/10;
constexpr float margin2 = lsize*9/10;

constexpr float frame_size = margin0 + margin1 + margin2*2
                        + arena_height*2 + arena_width;

#endif // MAIN_H
