# SLImage
An image viewer I made for my custom image format because I was bored

# Usage

There are 2 main modes to the program, read/view, and editor mode. To view a SLImage, simply do:

`./SLImage r </path/to/your/slimage>`

This will open a window containing the image itself.

The 2nd mode, editor, will open/create an image to edit. If no image is provided, it will default to the name unnamed.slmg.
<br>
The editor itself is quite simple, however is currently only keybind driven (GUI will be implemented later). A color can be chosen by using the numpad keys, Numpad 7/4 to increase/decrease red value, Numpad 8/5 to increase/decrease green value, and Numpad 9/6 to increase/decrease blue value. After your color has been selected, you can draw that color using LMB. The image can be saved by clicking S or Q, where Q will save and exit. To exit without saving, press ESC. To open an image in editor mode, do:


`./SLImage e </path/to/your/slimage>`

If the executable is run with no arguments, it will default to opening an editor for an image named unnamed.slmg.

# The Format Itself

In terms of the actual file format,

The first 4 bytes are the header bytes, used only to identify whether the file is an SLImage to begin with.
<br>
The bytes are defined as: {0xFF, 0xA5, 0xFF, 0xE8}

Following that, the next 8 bytes are used to determine the image dimensions, with 4 bytes for the image width and 4 bytes for the image height. The current max size of an image is nonexistent.

Following those 8 bytes, the actual image data stream starts. A pixel is represented as a set of 4 simple bytes, with one for each color value (ABGR). This makes the datastream length equal to ((width*height) * 4), which is the number of bytes the processor will read to display.

Finally, the image can contain a description. The length of the description is defined in the first 4 bytes after the datastream, with the rest of the description residing immediately after.