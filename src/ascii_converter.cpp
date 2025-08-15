#include "ascii_converter.hpp"

/// @brief ASCII character set used for conversion in decresing order of brightness since background of the terminal will be black
const std::string ascii_chars =  "@$B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\\|()1{}[]?-_+~<>i!lI;:,\"^`'.";

char mapToAscii(const uchar& pixel, const std::vector<char>& ascii_chars) {
    int index = static_cast<int>(pixel * (ascii_chars.size() - 1) / 255);
    return ascii_chars[index];
}
uchar getCombinedPixel(const cv::Mat& image, int x, int y) {
    int y1 = y;
    int y2 = y + 1;

    if (x < 0 || x >= image.cols || y1 < 0 || y1 >= image.rows || y2 < 0 || y2 >= image.rows) {
        return 0;
    }
    return (image.at<uchar>(y1, x) + image.at<uchar>(y2, x)) / 2;
}

void toGrayscale(cv::Mat &image) {
    if (image.channels() == 3) {
        cv::cvtColor(image, image, cv::COLOR_BGR2GRAY);
    } else if (image.channels() == 4) {
        cv::cvtColor(image, image, cv::COLOR_BGRA2GRAY);
    }
}

void convert_image(cv::Mat &image ,std::string &output){
    if (image.empty()) {
        output = "Image is empty!";
        return;
    }
    
    output.clear();
    for (int y = 0; y < image.rows; y += 2) {
        for (int x = 0; x < image.cols; x++) {
            uchar pixel = getCombinedPixel(image, x, y);
            output += mapToAscii(pixel, ascii_chars);
        }
        output += '\n';
    }
}

void convert_image(const std::string& image_path, int width, int height, std::string& output) {
    cv::Mat image = cv::imread(image_path);
    if (image.empty()) {
        output = "Image not found!";
        return;
    }
    
    cv::resize(image, image, cv::Size(width, height));
    toGrayscale(image);
    convert_image(image, output);
}