# SLImage
An image viewer I made for my custom image format because I was bored



# The Format Itself

In terms of the actual file format,

The first 4 bytes are the header bytes, used only to identify whether the file is an SLImage to begin with.
<br>
The bytes are defined as: {0xFF, 0xA5, 0xFF, 0xE8}

Following that, the next 8 bytes are used to determine the image dimensions, with 4 bytes for the image width and 4 bytes for the image height. The current max size of an image is 2048x2048.

Following those 8 bytes, the actual image data stream starts. A pixel is represented as a set of 4 simple bytes, with one for each color value (BGRA). This makes the datastream length equal to ((width*height) * 4), which is the number of bytes the processor will read to display.

Finally, the image can contain a description. The length of the description is defined in the first 4 bytes after the datastream, with the rest of the description residing immediately after.