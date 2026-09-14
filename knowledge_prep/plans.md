# **Overall Plan**

1\. get a video, use ffmpeg convert it to frames in .ppm --- achieved.

2\. take 1 frame and convert RGB to YUV --- done

3\. naive compression --- using the yuv as a compression for now

4\. put it in ur own container --- apparently all u gotta do i just write to a file with certain headers

5\. share with friends --- doneee

6\. reverse compression algo -donee

7\. get frame back and compare -done

8\. repeat from step 2 for all the frames in the video using a frame buffer-  on it!!!!!1!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

9\. repeat whole process with different compression algos

\------------------------------------------------------------



## **Execution**

**1.**



**ffmpeg -i input.mp4 output\_%04d.ppm**

&#x09;-i input.mp4: Specifies your source video file.output\_%04d.ppm: Instructs FFmpeg to name the extracted frames sequentially. The %04d 	is a placeholder that outputs padded four-digit numbers (e.g., output\_0001.ppm, output\_0002.ppm, output\_0003.ppm)



**2.**

**reinterpret\_cast<> -** change datatype without changing binary data

**pixels.data(), .data() -** direct pointer to the 1st raw byte in a vector's underlying array



**READING THE DATA**

read the file the header includes P6(ppm files have a header to indicate what the file is for images P6 is used), width, height then the max range of the RGB 255 usually(idk if its different ever) (0-255) also a random space that u have to fetch so the pointer can move on to the actual content



**MANIPULATION OF THE RGB**

rgb can be stored in a big char array/vector each pixel has 3 cells for itself with its R G B in individual cells run a for loop to edit those



**conversion to YUV**

&#x20;float y =  0.299f \* rgb.r + 0.587f \* rgb.g + 0.114f \* rgb.b;

&#x20;float u = -0.168736f \* rgb.r - 0.331264f \* rgb.g + 0.500f \* rgb.b + 128.0f;

&#x20;float v =  0.500f \* rgb.r - 0.418688f \* rgb.g - 0.081312f \* rgb.b + 128.0f;

**yuv to rgb**

float r = y + 1.402f \* (v - 128.0f);

float g = y - 0.344136f \* (u - 128.0f) - 0.714136f \* (v - 128.0f); 

float b = y + 1.772f \* (u - 128.0f);  

