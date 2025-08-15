
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Try to open a video file (change path as needed)
    std::string videoPath = "../examples/animation.mp4";
    cv::VideoCapture cap(videoPath);

    if (!cap.isOpened()) {
        std::cerr << "Failed to open video file: " << videoPath << std::endl;
        std::cerr << "OpenCV video I/O (FFmpeg) may not be working." << std::endl;
        return -1;
    } else {
        std::cout << "Successfully opened video file: " << videoPath << std::endl;
        std::cout << "OpenCV video I/O (FFmpeg) is working!" << std::endl;
    }

    // Optionally, read and display the first frame
    cv::Mat frame;
    while(cap.read(frame) && !frame.empty()) {
        cv::imshow("First Frame", frame);
        cv::waitKey(0);
        cv::destroyAllWindows();
    }

    return 0;
}