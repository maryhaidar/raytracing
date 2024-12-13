
![raytracing_motion_blur](https://github.com/user-attachments/assets/4364f313-129c-4755-a01c-6174720c0e2f)

Raytracing project based on the "Ray Tracing in One Weekend" series:

Title (series): “Ray Tracing in One Weekend Series”

Author: Peter Shirley, Trevor David Black, Steve Hollasch

Version/Edition: v4.0.1

Date: 2024-08-30

URL (series): https://raytracing.github.io


**Building**

In order to build using CMake, go to the root project directory and run the following command to create a debug version of the executable:

```shell
cmake --build build
```

And for an optimised configuration on Windows:

```shell
cmake --build build --config release
```


**Running the program**

You can run the program on Windows by either executing the binaries in the build directory:

```shell
build\Debug > .\Raytracer.exe # Will generate an image named `image.bmp`
build\Debug > .\Raytracer.exe my_filename # File name override
```
Or by running the optimised version:

```shell
build\Release > .\Raytracer.exe
build\Release > .\Raytracer.exe my_filename
```
