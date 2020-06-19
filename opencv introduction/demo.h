#pragma once

// This is called "guarding" the header file, and should be present in every .h file.
// It prevents duplicate imports and all of the strange issues that can be the result.
// Use a standardized way to indicate the file name - don't use a short form in case it is accidentally duplicated. 
// Here, it is the full filename with a leading underscore and the dot replaced by an underscore
#ifndef _demo_h
#define _demo_h

#include "opencv2\opencv.hpp"

// Be very careful when using multiple namespaces! There can be overlaps, which can cause unexpected bugs
// "cv" does conflict with the "std" namespace. Only use one at most.
// I typically use cv in my opencv projects, but if you don't use it, you can still access everything. For example: "cv::Mat"
using namespace cv;

void do_something(Mat src);
void add_line(Mat src);

#endif