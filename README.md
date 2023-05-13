# Steganography Program in C
This is a steganography program which encodes and decodes secret messages in bitmap images. An RGB colour bitmap image consists of a grid of pixels, each of which has red, green and blue colour values. To encode text inside an image, the program will replace the red value in successive random pixels in the image with characters from the text, outputting a new image.

## Image Format
Plain PPM format images. This is one of a family of simple open source image formats, designed to be read and written easily by C programs. See the PPM specification for full details of PPM and Plain PPM.
A Plain PPM file consists of ASCII text:
P3
```
# comment1
# ...
# commentN
width height
max
r1 g1 b1
r2 g2 b2
r3 g3 b3
...
```
where
- P3: code indicating Plain PPM format
- comment: arbitrary optional comment text
- width: integer number of columns
- height:  integer number of rows
- max: integer maximum colour value - usually 255
- ri bi gi: integers between 0 and max for pixel i's red, green and blue values
All integers are in decimal.

## Getting started
- You will need a Linux C development environment
- Clone the project into your working environment 

## Running the program
#### Compile the program
- Open the project folder in your integrated terminal environment 
- A make file has been provided to compile all the files. Run the make file using the following command
```
make
```
#### Encoding a message into an image
When encoding, the program should be invoked as:
```
./steg e red.ppm>out.ppm 
```
Where "e" starts encode mode. After running this the program must now prompt for a message to encode, and output the new image to stdout (in this case we have redirected it to a file).

#### Decoding a message from a file
To decode the text, the program will compare the new image with the old image, and extract characters from the new one where it differs from the old one
When decoding, the program should be invoked as:
```
./steg d red.ppm out.ppm 
```

## Program Design
My program uses a set of functions, getPPM(), showPPM(), readPPM(), encode(),decode() and an additional function copyFile() which we will see later.
<br><br>
The program starts with defining a struct for Pixel and PPM. The pixel struct stores the RGB values of a pixel from an image. The PPM struct stores the data such as (Width, Height, Maximum value) of the image read from the PPM file. PPM also includes a pointer which points to a dynamically allocated array containing the pixel data. <br><br>

Moving on to the functions: <br><br>
- getPPM(): The getPPM function takes a pointer to a file as input, and returns img a file of type struct ppm containing data about the PPM image. The function starts with allocating memory, then has an error checking statement that checks whether the file is in P3 format. Then the image data (Width, Height, Maximum value) is read from the file and stored in the allocated memory. Then the RGB values of each pixel is read and stored in the pixelsArray. 
<br><br>
- ShowPPM(): The showPPM function takes a pointer to a PPM image and prints out the image in P3 format, which includes the header data and rgb values.
<br><br>
- Encode(): This functions input parameters are, the string message you want to encode and file you want to encode to. Here the copyFile function is used to create a copy of the original image, and changing values in red pixels randomly to match the ASCII value of each character in the text.
<br><br>
- Decode(): The decode function takes 2 PPM images as inputs. The original image and the image that has encoded string. The function decodes the data by comparing the red values of corresponding pixels in both the images.
<br><br>
- copyFile(): This function creates a new PPM file and copies values from an existing PPM file. The values include the header data and rgb values, this function is later used to encode messages into an image.
 </p>
 <br><br>
 
## Choice of Data structures and algorithms
<p>Data structures used in this program were Struct Pixel and Struct PPM, and the Algorithms included, encode and decode which are mentioned above.
Struct PPM consists of the format the PPM file is in eg.P3, the dimensions of the PPM file (width, height, max) and pixelsArray which dynamically allocated array containing the pixel data. <br>
The pixels struct on the other hand stores the RGB values of the image.</p>

















