#ifndef ASCII_CONVERTER_HPP
#define ASCII_CONVERTER_HPP

/// @file ascii_converter.hpp
/// @brief Header file for ASCII image and video conversion functions

#include <opencv2/opencv.hpp>

/// @brief Takes the path of the image and converts it into ASCII image
/// @param image_path Path of the image can be relative or absolute
/// @param width Resized width of the image in pixels
/// @param height Resized height of the image in pixels
/// @param output Output string that will hold ASCII image
void convert_image(const std::string& image_path, int width, int height, std::string& output);

/// @brief Takes the image as opencv Mat object and converts it into ASCII image
/// @param image OpenCV Mat object containing the image
/// @param output Output string that will hold ASCII image
void convert_image(cv::Mat &image, std::string& output);

/// @brief Takes the path of the video and converts it into ASCII video
/// @param video_path Path of the video can be relative or absolute
/// @param width Resized width of the video in pixels
/// @param height Resized height of the video in pixels
/// @param output Output string that will hold ASCII video
void convert_video(const std::string& video_path, int width, int height, std::string& output);

/// @brief Takes the video as opencv VideoCapture object and converts it into ASCII video
/// @param video OpenCV VideoCapture object containing the video
/// @param output Output string that will hold ASCII video
void convert_video(cv::VideoCapture &video, std::string& output);

/// @brief Maps a pixel value to an ASCII character based on the provided character set
/// @param pixel Pixel value (0-255)
/// @param ascii_chars Vector of ASCII characters to map to
/// @return Corresponding ASCII character
char mapToAscii(const uchar& pixel, const std::vector<char>& ascii_chars);

/// @brief Gets the combined pixel value from a 1x2 block in the image
/// @param image OpenCV Mat object containing the image
/// @param x X coordinate of the pixel
/// @param y Y coordinate of the pixel
/// @return Combined pixel value from the 1x2 block
uchar getCombinedPixel(const cv::Mat& image, int x, int y);

/// @brief Converts the image to grayscale
/// @param image OpenCV Mat object containing the image
void toGrayscale(cv::Mat &image);

#endif