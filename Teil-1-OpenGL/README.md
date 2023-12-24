# OpenGL Project

## First time setup - Linux Debian/Ubuntu
> ```commandline
> Could NOT find X11 (missing: X11_X11_INCLUDE_PATH X11_X11_LIB)
> ```
> can be solved with the following command in terminal:
> ```commandline
> sudo apt install libx11-dev
> ```

> ```commandline
>   CMake Error at libs/glfw-3.2.1/CMakeLists.txt:222 (message):
> The RandR library and headers were not found
> ```
> can be solved with the following command in terminal:
> ```commandline
> sudo apt install libxrandr-dev
> ```

> ```commandline
>   CMake Error at libs/glfw-3.2.1/CMakeLists.txt:231 (message):
> The Xinerama library and headers were not found
> ```
> can be solved with the following command in terminal:
> ```commandline
> sudo apt install libxinerama-dev
> ```

> ```commandline
>   CMake Error at libs/glfw-3.2.1/CMakeLists.txt:262 (message):
> The Xcursor libraries and headers were not found
> ```
> can be solved with the following command in terminal:
> ```commandline
> sudo apt install libxcursor-dev
> ```

> ```commandline
> CMake Error at /snap/clion/261/bin/cmake/linux/x64/share/cmake-3.27/Modules/FindPackageHandleStandardArgs.cmake:230 (message):
>   Could NOT find OpenGL (missing: OPENGL_opengl_LIBRARY OPENGL_glx_LIBRARY
>   OPENGL_INCLUDE_DIR)
> ```
> can be solved with the following command in terminal:
> ```commandline
> sudo apt install libgl1-mesa-dev
> ```

> ```commandline
> fatal error: GL/glu.h: No such file or directory
> 1205 | #    include <GL/glu.h>
>      |              ^~~~~~~~~~
> ```
> can be solved with the following command in terminal:
> ```commandline
> sudo apt install libglu1-mesa-dev
> ```

Now everything works as expected!