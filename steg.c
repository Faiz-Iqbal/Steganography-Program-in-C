#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 255;

/* The RGB values of a pixel. */
struct Pixel {
    int red;
    int green;
    int blue;
};

/* An image loaded from a PPM file. */
/*The declaration of struct PPM, which holds the image read from a PPM file. This includes the information from the PPM header (width, height, max), and a pointer to a dynamically-allocated array containing the pixel data*/
struct PPM {
    /* TODO: Question 1 */
    char format[3]; //stores the format of the image
    int width; //stores width of the image
    int height; //stores height of the image
    int max; //stores max value of the image
    
    //pointer to a dynamically-allocated array containing the pixel data.
    struct Pixel *pixelsArray; 

};

/* Reads an image from an open PPM file.
 * Returns a new struct PPM, or NULL if the image cannot be read. */
struct PPM *getPPM(FILE * f)
{
    /* TODO: Question 2a */
    //allocate memory for the struct PPM and assign it to a pointer img, using malloc. The size is
    //dynamic,since we are using sizeof(struct PPM).
    struct PPM *img = (struct PPM *)malloc(sizeof(struct PPM));

    //reads the format of the image from the file in type string.
    fscanf(f, "%s", img->format); 

    //error condition to see if image is in P3 format
    if (strcmp(img->format,"P3") != 0){ 
        //if the image is not in P3 format, print an error message and return NULL
        printf("Incorrect image file, Image file has to be in the P3 format\n");
        return NULL;
    }

    //Scan function to read the width, height and max value of the image from the file.
    fscanf(f, "%d", &img->width); //read the width of the image
    fscanf(f, "%d", &img->height); //read the height of the image
    fscanf(f, "%d", &img->max); //read the max value of the image

    //Allocate memory for the pixelsArray using the width and height of the image.
    img->pixelsArray = (struct Pixel *)malloc(sizeof(struct Pixel)*(img->width * img->height));

    int t; //variable that will store the red, green and blue values of the pixel
    int j = 0; //counter to cycle through pixelsArray
    while(j<(img->width * img->height)){
        t = fscanf(f, "%d", &img->pixelsArray[j].red); //read the red value of the pixel and store it in the array
        t = fscanf(f, "%d", &img->pixelsArray[j].green); //read the green value of the pixel and store it in the array
        t = fscanf(f, "%d", &img->pixelsArray[j].blue); //read the blue value of the pixel and store it in the array
        j++;
    }
    return img; //return the pointer to the struct PPM

    
}

/* Write img to stdout in PPM format. */
void showPPM(const struct PPM *img)
{
    /* TODO: Question 2b */
    //Print format of the image, which in this case is P3 or Plain PPM.
    printf("P3\n");

    //Print width, height and max value of the image eg. 500 500 255
    printf("%d %d\n%d\n", img->width, img->height, img->max);

    //Iterate through the pixelsArray and print the red, green and blue values of the pixel
    int x = 0; //counter to cycle through pixelsArray
    for(x=0; x<(img->height * img->width); ++x){ //for x = 0 to the number of pixels in the image
    // derived by multiplying the width and height of the image, print the RGB values of the pixel.
        printf("%d %d %d\n", //print the RGB values of the pixel
        img->pixelsArray[x].red, //print the red value of the pixel
        img->pixelsArray[x].green, //print the green value of the pixel
        img->pixelsArray[x].blue); //print the blue value of the pixel
    }
}

/* Opens and reads a PPM file, returning a pointer to a new struct PPM.
 * On error, prints an error message and returns NULL. */
struct PPM *readPPM(const char *filename)
{
    /* Open the file for reading */
    FILE *f = fopen(filename, "r");
    if (f == NULL) {
        fprintf(stderr, "File %s could not be opened.\n", filename);
        return NULL;
    }

    /* Load the image using getPPM */
    struct PPM *img = getPPM(f);

    /* Close the file */
    fclose(f);

    if (img == NULL) {
        fprintf(stderr, "File %s could not be read.\n", filename);
        return NULL;
    }

    return img;
}

//Function to copy data(Width, height, max and RGB values) from one ppm file to another. This mfunction will be called later in the encode function to encode the text into the image.
struct PPM *copyFile(const struct PPM *old){
    //declaring a pointer to a struct PPM and allocating memory to it using malloc for the new ppm file.
    struct PPM *new = (struct PPM *)malloc(sizeof(struct PPM));

    //copying the data from the old ppm file to the new ppm file.
    strcpy(new->format, old->format);
    //copies the width from the old ppm file to the new ppm file.
    new->width = old->width;
    //copies the height from the old ppm file to the new ppm file.
    new->height = old->height;
    //copies the max value from the old ppm file to the new ppm file.
    new->max = old->max;

    //allocating memory for the pixelsArray for the new PPM using the width and height of the image multiplied by the size of the struct Pixel.
    new->pixelsArray = (struct Pixel *)malloc(sizeof(struct Pixel)*(new->width * new->height));
    
    //loop to copy the RGB values from the old ppm file to the new ppm file.
    for (int i=0; i<(new->width * new->height); i++){
        //copies red value from the old ppm file to the new ppm file.
        new->pixelsArray[i].red = old->pixelsArray[i].red;
        //copies green value from the old ppm file to the new ppm file.
        new->pixelsArray[i].green = old->pixelsArray[i].green;
        //copies blue value from the old ppm file to the new ppm file.
        new->pixelsArray[i].blue = old->pixelsArray[i].blue;
    }
    return new; //returns new ppm file

}

/* Encode the string text into the red channel of image img.
 * Returns a new struct PPM, or NULL on error. */
struct PPM *encode(const char *text, const struct PPM *img)
{
    /* TODO: Question 2c */
    //Use the copyFile function to copy the data from the original ppm file to a new ppm file.
    struct PPM *encImg = copyFile(img);

    //Calculates number of pixels to be encoded in the image. This is done by dividing the number of pixels in the image by the length of the text to be encoded, and adding 1 to consider the null character.
    int numOfPix = ((img->height * img->width)/(strlen(text)+1));
    //random declares a variable to store the random number generated, then generates a random number between 0 and the number of pixels -1.
    int random; //variable to store the random number generated.
    random = rand() % numOfPix; //generates a random number between 0 and the number of pixels -1.

    int i = 0; //integer to keep track of the position of the character in the text.
    int j = random; //integer to initialize starting position of the pixel to be encoded. By starting j at a random location in the image ensures that the same image will not be encoded the same way every time making it more secure and hard to predict the encode pattern.
    while (i <strlen(text)){ //while loop condition iterates through each value untill the end of file is reached.
        //if statement cheecks if the red value of the pixel is equal to the character in the text, if it is, it increments j by 1.
        if (encImg->pixelsArray[j].red == text[i]){
            j++; //Increment j.
        }else{ //if the red value of the pixel is not equal to the character in the text, it assigns the red value of the pixel to the character in the text.
            encImg->pixelsArray[j].red = text[i];
            i++; //Increments i.
            j += random; //Increments j by the random number generated.
        }
    }
    //if encImg is NULL that means that the message did not encode successfully, which then outputs an error message and returns NULL.
    if (encImg == NULL){
        //error message is outputted using the standard error output stream or stderr.
        fprintf(stderr, "Message did not encode successfully\n");
        return NULL; //NULL is returned.
    }else{
        //if the message was encoded successfully, then the success message is outputted and encImg is returned.
        fprintf(stderr, "Message successfully encoded\n");
        return encImg;
    }

}

/* Extract the string encoded in the red channel of newimg, by comparing it
 * with oldimg. The two images must have the same size.
 * Returns a new C string, or NULL on error. */
char *decode(const struct PPM *oldimg, const struct PPM *newimg)
{
    /* TODO: Question 2d */
    int i =0; //variable is used to iterate through the pixels in the image.
    int j =0; //variable to keep track of the index of the character in the decoded text. Incremented only when a character is successfully decoded.

    //if statement checks if the width and height of the two images are the same, if they are not, then an error message is outputted and NULL is returned.
    if((oldimg->width != newimg->width) || (oldimg->height != newimg->height)){
        //error message is outputted using the standard error output stream or stderr.
        fprintf(stderr, "The two images must have the same size\n");
        return NULL; //Null is returned.
    }else{
        //if the width and height of the two images are the same, then the decoded text is extracted from the image.
        char *string = (char *)malloc(sizeof(char)*(oldimg->width * oldimg->height));
        //while loop iterates through each pixel in the image.
        while (i < (oldimg->width * oldimg->height)){
            //if the red value of the pixel in the old image is not equal to the red value of the pixel in the new image, it means there is encoded text in that pixel, so the red value of that pixel is added to the decoded string at index j.
            if (oldimg->pixelsArray[i].red != newimg->pixelsArray[i].red){
                string[j] = newimg->pixelsArray[i].red;
                //increments j by 1.
                j++;
            }
            //increments i by 1.
            i++;
        }
        return string;
    }
}

/* TODO: Question 3 */
int main(int argc, char *argv[])
{
    /* Initialise the random number generator, using the time as the seed */
    srand(time(NULL));

    /* Parse command-line arguments */
    if (argc == 3 && strcmp(argv[1], "t") == 0) {
        /* Mode "t" - test PPM reading and writing */

        struct PPM *img = readPPM(argv[2]);
        showPPM(img);

    } else if (argc == 3 && strcmp(argv[1], "e") == 0) {
        /* Mode "e" - encode PPM */

        struct PPM *oldimg = readPPM(argv[2]);
        //prompt for a message from the user, and read it into a string
        //This is done by declaring a pointer to a char array and allocating memory to it using malloc, then using fgets to read the input from the user and store it in the char array.
        char *toEnc = (char *)malloc(sizeof(char)*255);
        //fgets reads the input from the user and stores it in the char array.
        fgets(toEnc, 255, stdin);
        /* TODO: prompt for a message from the user, and read it into a string */

        struct PPM *newimg = encode(toEnc, oldimg);
        showPPM(newimg);
        /* TODO: encode the text into the image with encode, and assign to newimg */

        /* TODO: write the image to stdout with showPPM */

    } else if (argc == 4 && strcmp(argv[1], "d") == 0) {
        /* Mode "d" - decode PPM */

        //get original file filename from argv, load it with
        //readPPM, then assign to oldimg
        struct PPM *oldimg = readPPM(argv[2]);
        /* get encoded file filename from argv, load it with
           readPPM, then assign to newimg */
        struct PPM *newimg = readPPM(argv[3]);
        // allocates memory for an array of 255 values, since that is the maximum size of the message that can be encoded in the image.
        char *message = (char *)malloc(255);
        //char *message = (char *)malloc(MAX);
        //call decode with oldimg and newimg, and assign the result to message
        message = decode(oldimg, newimg);

        //if message is NULL, then an error message is outputted and 1 is returned.
        if(message == NULL){
            //error message is outputted using the standard error output stream or stderr.
            fprintf(stderr, "Error decoding message");
            return 1; //1 is returned.
        }else{
            //if the message was decoded successfully, then the decoded message is outputted.
            printf("Decoded message: %s", message);
            
        }

    } else {
        fprintf(stderr, "Unrecognised or incomplete command line.\n");
        return 1;
    }

    return 0;
}
