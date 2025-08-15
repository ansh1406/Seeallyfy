#include "ascii_converter.hpp"

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