# Seeallyfy

Seeallyfy is a command-line tool for converting videos and images to ASCII art, viewing ASCII images, and playing ASCII videos in the terminal. It uses OpenCV for image and video processing.

## Features

- Convert video to ASCII art and save to file
- Convert image to ASCII art and save to file
- Play ASCII video from file in terminal
- View ASCII image from file in terminal
- Combine conversion and viewing/playing in one command
- Customizable width, height, and FPS for ASCII output

## Requirements

- OpenCV (with FFmpeg support for video I/O)
- C++17 compiler (tested with MinGW-w64 and MSVC)
- Windows (DLL auto-copy logic in CMakeLists.txt)

## Build Instructions

1. Download the zlib source folder and place it inside the `includes` directory:
   - You can get zlib from https://zlib.net/ or https://github.com/madler/zlib
   - Place the contents of the zlib folder in `includes/zlib`
2. Install OpenCV and ensure FFmpeg DLLs are available.
3. Configure and build with CMake:

   ```sh
   mkdir build
   cd build
   cmake ..
   cmake --build . --config Release
   ```

4. The required OpenCV and FFmpeg DLLs will be copied to your output folder automatically.

## Usage

```
Seeallyfy [OPTIONS] [Optional options]

Options (long):
  --video-to-ascii <input_video> <output_file>               Convert video to ASCII and save
  --image-to-ascii <input_image> <output_file>               Convert image to ASCII and save
  --play-ascii-video <ascii_video_file>                      Play ASCII video from file
  --view-ascii-image <ascii_image_file>                      View ASCII image from file
  --video-to-ascii-and-play <input_video> <output_file>      Convert video to ASCII and play
  --image-to-ascii-and-view <input_image> <output_file>      Convert image to ASCII and view
  --help                                                     Show this help message

Options (short):
  -v2a <video> <out>   Convert video to ASCII
  -i2a <image> <out>   Convert image to ASCII
  -pv <file>           Play ASCII video
  -pi <file>           View ASCII image
  -v2ap <video> <out>  Convert and play video as ASCII
  -i2av <image> <out>  Convert and view image as ASCII
  -h                   Show help

Optional options (no spaces):
  --width<width>        Set width for ASCII conversion (default: 200)
  --height<height>      Set height for ASCII conversion (default: 100)
  --fps<fps>            Set frames per second for ASCII video (default: 12)
```

## Example Commands

- Convert video to ASCII:
  ```
  Seeallyfy --video-to-ascii input.mp4 out.txt --width120 --height40 --fps15
  ```
- Play ASCII video:
  ```
  Seeallyfy --play-ascii-video out.txt --fps20
  ```
- Convert and view image:
  ```
  Seeallyfy -i2av image.png out.txt --width80 --height30
  ```


## Credits

- OpenCV (https://opencv.org/)
- FFmpeg (https://ffmpeg.org/)