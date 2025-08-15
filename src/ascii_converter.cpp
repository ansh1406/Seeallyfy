#include "ascii_converter.hpp"

#include <fstream>

/// @brief ASCII character set used for conversion in decresing order of brightness since background of the terminal will be black
const std::string ascii_chars = "@$B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";

char mapToAscii(const uchar &pixel, const std::string &ascii_chars)
{
    int index = static_cast<int>(pixel * (ascii_chars.size() - 1) / 256);
    return ascii_chars[index];
}
uchar getCombinedPixel(const cv::Mat &image, int x, int y)
{
    int y1 = y;
    int y2 = y + 1;

    if (x < 0 || x >= image.cols || y1 < 0 || y1 >= image.rows || y2 < 0 || y2 >= image.rows)
    {
        return 0;
    }
    return (image.at<uchar>(y1, x) + image.at<uchar>(y2, x)) / 2;
}

void toGrayscale(cv::Mat &image)
{
    if (image.channels() == 3)
    {
        cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    }
    else if (image.channels() == 4)
    {
        cv::cvtColor(image, image, cv::COLOR_BGRA2GRAY);
    }
}

void convert_image(cv::Mat &image, std::string &output)
{
    if (image.empty())
    {
        output = "Image is empty!";
        return;
    }

    output.clear();
    for (int y = 0; y < image.rows; y += 2)
    {
        for (int x = 0; x < image.cols; x++)
        {
            uchar pixel = getCombinedPixel(image, x, y);
            output += mapToAscii(pixel, ascii_chars);
        }
        output += '\n';
    }
}

void convert_image(const std::string &image_path, int width, int height, std::string &output_path)
{
    cv::Mat image = cv::imread(image_path);
    if (image.empty())
    {
        return;
    }
    std::string output;
    cv::resize(image, image, cv::Size(width, height));
    toGrayscale(image);
    convert_image(image, output);
    std::ofstream ofs(output_path);
    if (ofs.is_open())
    {
        ofs << output;
        ofs.close();
    }
    else
    {
        std::cerr << "Error opening output file: " << output_path << std::endl;
    }
}

void convert_video(cv::VideoCapture &video, int width, int height, std::string &output)
{
    if (!video.isOpened())
    {
        output = "Video capture is not opened!";
        return;
    }
    output.clear();
    cv::Mat frame;
    while (video.read(frame))
    {
        cv::resize(frame, frame, cv::Size(width, height));
        toGrayscale(frame);
        std::string asciiImage;
        convert_image(frame, asciiImage);
        output += asciiImage;
    }
}

void convert_video(const std::string &video_path, int width, int height, int fps, std::string &output_path)
{
    cv::VideoCapture video(video_path);
    if (!video.isOpened())
    {
        return;
    }
    std::string output;
    std::string header = std::to_string(width) + " " + std::to_string(height / 2) + " " + std::to_string(fps) + "\n";
    convert_video(video, width, height, output);
    std::ofstream ofs(output_path);
    if (ofs.is_open())
    {
        ofs << header;
        ofs << output;
        ofs.close();
    }
    else
    {
        std::cerr << "Error opening output file: " << output_path << std::endl;
    }
}