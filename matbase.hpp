/** @file matebase.hpp
 *  @brief Header files for mat-to-base64 and base64-to-mat 
 *  
 *  Declaration of all functions 
 *  
 *  @author Karthikeya Rekulapalli
 *  @bug No bugs found 
 */


/* --- Project Includes --- */

#include <string>
#include <opencv2/imgproc/imgproc.hpp>
#include "opencv2/opencv.hpp"
#include <bits/stdc++.h> 
#include <omp.h>



std::string base64Encode(const unsigned char* Data, int DataByte);
std::string Mat2Base64(const cv::Mat &img);
std::string base64Decode(const char* Data, int DataByte);
cv::Mat Base2Mat(std::string &base64_data);


