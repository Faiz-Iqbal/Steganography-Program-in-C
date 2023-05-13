# Who I am

- Student ID: <p>H00361901</p>

# Program design
<p>My program uses a set of functions, getPPM(), showPPM(), readPPM(), encode(),decode() and an additional function copyFile() which we will see later.
<br><br>
The program starts with defining a struct for Pixel and PPM. The pixel struct stores the RGB values of a pixel from an image. The PPM struct stores the data such as (Width, Height, Maximum value) of the image read from the PPM file. PPM also includes a pointer which points to a dynamically allocated array containing the pixel data. <br><br>

Moving on to the functions: <br><br>
getPPM(): The getPPM function takes a pointer to a file as input, and returns img a file of type struct ppm containing data about the PPM image. The function starts with allocating memory, then has an error checking statement that checks whether the file is in P3 format. Then the image data (Width, Height, Maximum value) is read from the file and stored in the allocated memory. Then the RGB values of each pixel is read and stored in the pixelsArray. 
<br><br>
ShowPPM(): The showPPM function takes a pointer to a PPM image and prints out the image in P3 format, which includes the header data and rgb values.
<br><br>
Encode(): This functions input parameters are, the string message you want to encode and file you want to encode to. Here the copyFile function is used to create a copy of the original image, and changing values in red pixels randomly to match the ASCII value of each character in the text.
<br><br>
Decode(): The decode function takes 2 PPM images as inputs. The original image and the image that has encoded string. The function decodes the data by comparing the red values of corresponding pixels in both the images.
<br><br>
copyFile(): This function creates a new PPM file and copies values from an existing PPM file. The values include the header data and rgb values, this function is later used to encode messages into an image.
 </p>
 <br><br>
# Choice of data structures and algorithms
<p>Data structures used in this program were Struct Pixel and Struct PPM, and the Algorithms included, encode and decode which are mentioned above.
Struct PPM consists of the format the PPM file is in eg.P3, the dimensions of the PPM file (width, height, max) and pixelsArray which dynamically allocated array containing the pixel data. <br>
The pixels struct on the other hand stores the RGB values of the image.</p>