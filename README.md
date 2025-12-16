# SLImage
An image viewer I made for my custom image format because I was bored

This is still very in progress, check out the [Todo List](#Todo)
# Usage

There are 2 main modes to the program, read/view, and editor mode. To view a SLImage, simply do:

`./SLImage r </path/to/your/slimage>`

This will open a window containing the image itself.

The 2nd mode, editor, will open/create an image to edit. If the image doesn't already exist, a width and height will need to be specified. If no image is provided, it will default to unnamed.slmg.
<br>
The editor itself is quite simple, however is currently only [keybind](#Keybinds) driven (GUI will be implemented later). A color can be chosen using the numpad keys, where the current color selected will be outputted to terminal. Similarly, a brush size can also be selected. After your color and brush has been selected, you can draw that color wherever you'd like on the window. The image can then be safely saved an exited. To open an image in editor mode, do:


`./SLImage e </path/to/your/slimage> <width> <height>`

If the executable is run with no arguments, it will default to opening an editor for an image named unnamed.slmg.
## Keybinds

- LMB: Draw
- \+ : Increase brush size
- \- : Decrease brush size
- Numpad7: Increase red value
- Numpad4: Decrease red value
- Numpad8: Increase green value
- Numpad5: Decrease green value
- Numpad9: Increase blue value
- Numpad6: Decrease blue value
- Numpad1: Increase alpha (currently unused)
- Numpad0: Decrease alpha (currently unused)
- S: Save image
- Q:  Save and quit
- ESC: Exit without saving

# The Format Itself

In terms of the actual file format,

The first 4 bytes are the header bytes, used only to identify whether the file is an SLImage to begin with.
<br>
The bytes are defined as: {0xFF, 0xA5, 0xFF, 0xE8}

Following that, the next 8 bytes are used to determine the image dimensions, with 4 bytes for the image width and 4 bytes for the image height. The current max size of an image is nonexistent.

Following those 8 bytes, the actual image data stream starts. A pixel is represented as a set of 4 simple bytes, with one for each color value (ABGR). This makes the datastream length equal to ((width*height) * 4), which is the number of bytes the processor will read to display.

Finally, the image can contain a description. The length of the description is defined in the first 4 bytes after the datastream, with the rest of the description residing immediately after.

# Todo

- Implement GUI (Color picker, brushes, etc...)
- Implement more brushes
- Implement scalable window/zoom
- Implement color opacity
- Implement image descriptions
- PNG to SLImage tool
- Bucket fill tool (?)
- Optimize and clean up editor code