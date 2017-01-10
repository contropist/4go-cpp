#ifndef MAIN_H
#define MAIN_H


const float lsize = 20; // mutable data
const float rsize = lsize*2;

const float lspace = lsize/2;
const float rspace = rsize/3;

const float arena_height = 6*lsize + 5*lspace;
const float arena_width = 5*rsize + 4*rspace;

const float margin0 = lsize*5/10;
const float margin1 = lsize*27/10;
const float margin2 = lsize*9/10;

const float frame_size = margin0 + margin1 + margin2*2
                        + arena_height*2 + arena_width;

#endif // MAIN_H
