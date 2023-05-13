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

### Compile the program
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



















