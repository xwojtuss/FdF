# FDF

FdF - a wireframe renderer using a parallel projection. It uses the miniLibX to render the image. You can create and display your own maps, animate and color them.

You can use WSAD and QE to rotate the image, arrow keys to move the image, () signs to decrease or increase the height, + and - signs to zoom in and out.

The scene is loaded via a file with the extention .fdf, the file consists of heights of points delimited by spaces, for example:
```
0 0 0
0 10 0
0 0 0
```
You can also add colors to your scene by adding the hex value for the color after a comma, for example:
```
0 0 0
0 10,0xff0000 0
0 0 0
```

## Getting Started

These instructions will help you get a copy of the project up and running.

### Dependencies

- gcc
- cc
- make
- X11 include files (package xorg)
- XShm extension must be present (package libxext-dev)
- Utility functions from BSD systems - development files (package libbsd-dev)

### Installing

1. Clone the repository:
```
git clone https://github.com/xwojtuss/FdF.git
```

2. Navigate to the project directory:
```
cd FdF
```

3. Run the make command to build the project:
```
make
```

## Running the project

You can pass different scenes to the program, the directory 'maps' has some example scenes:
```
./fdf [map to run]
```

You can also add animations to the image:
```
./fdf_bonus [map to run] [animation type]
```

You can choose from:
xysine, xsine, ysine, water, ripple, wind, shaky

## Authors

* **Wojtek Kornatowski** - [xwojtuss](https://github.com/xwojtuss)
