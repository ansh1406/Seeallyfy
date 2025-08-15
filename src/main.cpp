#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

void print_help() {
    std::cout << "Usage: Seeallyfy [OPTIONS]\n"
                 "Options (long):\n"
                 "  --video-to-ascii <input_video> <output_file>   Convert video to ASCII and save\n"
                 "  --image-to-ascii <input_image> <output_file>   Convert image to ASCII and save\n"
                 "  --play-ascii-video <ascii_video_file>           Play ASCII video from file\n"
                 "  --view-ascii-image <ascii_image_file>           View ASCII image from file\n"
                 "  --video-to-ascii-and-play <input_video>         Convert video to ASCII and play\n"
                 "  --image-to-ascii-and-view <input_image>         Convert image to ASCII and view\n"
                 "  --help                                         Show this help message\n"
                 "Options (short):\n"
                 "  -v2a <video> <out>   Convert video to ASCII\n"
                 "  -i2a <image> <out>   Convert image to ASCII\n"
                 "  -pv <file>           Play ASCII video\n"
                 "  -pi <file>           View ASCII image\n"
                 "  -v2ap <video>        Convert and play video as ASCII\n"
                 "  -i2av <image>        Convert and view image as ASCII\n"
                 "  -h                   Show help\n";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_help();
        return 0;
    }

    std::string option = argv[1];

    if (option == "--help" || option == "-h") {
        print_help();
        return 0;
    } else if ((option == "--video-to-ascii" || option == "-v2a") && argc == 4) {
        std::string input_video = argv[2];
        std::string output_file = argv[3];
        // TODO: Convert video to ASCII and save to output_ascii
        std::cout << "Ascii video file saved to "<< output_file << std::endl;
    } else if ((option == "--image-to-ascii" || option == "-i2a") && argc == 4) {
        std::string input_image = argv[2];
        std::string output_file = argv[3];
        // TODO: Convert image to ASCII and save to output_ascii
        std::cout << "Ascii image file saved to" << output_file << std::endl;
    } else if ((option == "--play-ascii-video" || option == "-pv") && argc == 3) {
        std::string ascii_video_file = argv[2];
        // TODO: Play ASCII video from file
    } else if ((option == "--view-ascii-image" || option == "-pi") && argc == 3) {
        std::string ascii_image_file = argv[2];
        // TODO: View ASCII image from file
    } else if ((option == "--video-to-ascii-and-play" || option == "-v2ap") && argc == 3) {
        std::string input_video = argv[2];
        // TODO: Convert video to ASCII and play
        std::cout << "Ascii video file saved to " << input_video << std::endl;
    } else if ((option == "--image-to-ascii-and-view" || option == "-i2av") && argc == 3) {
        std::string input_image = argv[2];
        // TODO: Convert image to ASCII and view
        std::cout << "Ascii image file saved to " << input_image << std::endl;
    } else {
        std::cerr << "Invalid arguments!\n";
        print_help();
        return 1;
    }

    return 0;
}