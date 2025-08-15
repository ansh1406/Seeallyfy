#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "ascii_converter.hpp"

void view_ascii_image(const std::string &image_path)
{
    std::ifstream file(image_path);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << image_path << std::endl;
        return;
    }
    std::cout << file.rdbuf();
}

void play_ascii_video(const std::string &video_path)
{
    std::ifstream file(video_path);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << video_path << std::endl;
        return;
    }
    std::string frame;
    std::string line;
    std::vector<std::string> ascii_video;

    std::string header;
    int width, height, fps;
    if (std::getline(file, header))
    {
        std::cout << "Video Header: " << header << std::endl;
        std::istringstream iss(header);
        iss >> width >> height >> fps;
    }
    else
    {
        std::cerr << "Error reading video header." << std::endl;
        return;
    }
    while (std::getline(file, line))
    {
        for (int lines = 1; lines < height; ++lines)
        {
            if (std::getline(file, line))
                frame += line + "\n";
            else
                break;
        }
        ascii_video.push_back(frame);
        frame.clear();
    }
    const int delayMs = 1000 / fps;
    for (const auto &ascii_frame : ascii_video)
    {
        std::cout
            << ascii_frame << "\n"
            << std::flush;
        cv::waitKey(delayMs);
    }
}

void print_help()
{
    std::cout << "Usage: Seeallyfy [OPTIONS] [Optional options]\n"
                 "Options (long):\n"
                 "  --video-to-ascii <input_video> <output_file>               Convert video to ASCII and save\n"
                 "  --image-to-ascii <input_image> <output_file>               Convert image to ASCII and save\n"
                 "  --play-ascii-video <ascii_video_file>                      Play ASCII video from file\n"
                 "  --view-ascii-image <ascii_image_file>                      View ASCII image from file\n"
                 "  --video-to-ascii-and-play <input_video> <output_file>      Convert video to ASCII and play\n"
                 "  --image-to-ascii-and-view <input_image> <output_file>      Convert image to ASCII and view\n"
                 "  --help                                                     Show this help message\n"
                 "Options (short):\n"
                 "  -v2a <video> <out>   Convert video to ASCII\n"
                 "  -i2a <image> <out>   Convert image to ASCII\n"
                 "  -pv <file>           Play ASCII video\n"
                 "  -pi <file>           View ASCII image\n"
                 "  -v2ap <video>        Convert and play video as ASCII\n"
                 "  -i2av <image>        Convert and view image as ASCII\n"
                 "  -h                   Show help\n";
    "Optional options (long)(No spaces):\n"
    "  --width<width>        Set width for ASCII conversion (default: 200)\n"
    "  --height<height>      Set height for ASCII conversion (default: 100)\n"
    "  --fps<fps>            Set frames per second for ASCII video (default: 12)\n";
    "Optional options (short)(No spaces):\n"
    "  -w<width>             Set width for ASCII conversion (default: 200)\n"
    "  -h<height>            Set height for ASCII conversion (default: 100)\n"
    "  -f<fps>               Set frames per second for ASCII video (default: 12)\n";
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        print_help();
        return 0;
    }

    int width = 200, height = 100, fps = 12;
    for (int i = 2; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg.find("--width") == 0)
        {
            width = std::stoi(arg.substr(7));
        }
        else if (arg.find("--height") == 0)
        {
            height = std::stoi(arg.substr(8));
        }
        else if (arg.find("--fps") == 0)
        {
            fps = std::stoi(arg.substr(5));
        }
        else if (arg.find("-w") == 0)
        {
            width = std::stoi(arg.substr(2));
        }
        else if (arg.find("-h") == 0)
        {
            height = std::stoi(arg.substr(2));
        }
        else if (arg.find("-f") == 0)
        {
            fps = std::stoi(arg.substr(2));
        }
    }

    std::string option = argv[1];

    if (option == "--help" || option == "-h")
    {
        print_help();
        return 0;
    }
    else if ((option == "--video-to-ascii" || option == "-v2a") && argc >= 4)
    {
        std::string input_video = argv[2];
        std::string output_file = argv[3];
        convert_video(input_video, width, height, fps, output_file);
        std::cout << "Ascii video file saved to " << output_file << std::endl;
    }
    else if ((option == "--image-to-ascii" || option == "-i2a") && argc >= 4)
    {
        std::string input_image = argv[2];
        std::string output_file = argv[3];
        convert_image(input_image, width, height, output_file);
        std::cout << "Ascii image file saved to" << output_file << std::endl;
    }
    else if ((option == "--play-ascii-video" || option == "-pv") && argc >= 3)
    {
        std::string ascii_video_file = argv[2];
        play_ascii_video(ascii_video_file);
    }
    else if ((option == "--view-ascii-image" || option == "-pi") && argc >= 3)
    {
        std::string ascii_image_file = argv[2];
        view_ascii_image(ascii_image_file);
    }
    else if ((option == "--video-to-ascii-and-play" || option == "-v2ap") && argc >= 4)
    {
        std::string input_video = argv[2];
        std::string output_file = argv[3];
        convert_video(input_video, width, height, fps, output_file);
        std::cout << "Ascii video file saved to " << input_video << std::endl;
        play_ascii_video(output_file);
    }
    else if ((option == "--image-to-ascii-and-view" || option == "-i2av") && argc >= 4)
    {
        std::string input_image = argv[2];
        std::string output_file = argv[3];
        convert_image(input_image, width, height, output_file);
        std::cout << "Ascii image file saved to " << input_image << std::endl;
        view_ascii_image(output_file);
    }
    else
    {
        std::cerr << "Invalid arguments!\n";
        print_help();
        return 1;
    }

    return 0;
}