# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/260/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/260/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/vlad/Desktop/Visual_Computing_h-da

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/vlad/Desktop/Visual_Computing_h-da/cmake-build-debug

# Utility rule file for uninstall.

# Include any custom commands dependencies for this target.
include libs/glm-master/CMakeFiles/uninstall.dir/compiler_depend.make

# Include the progress variables for this target.
include libs/glm-master/CMakeFiles/uninstall.dir/progress.make

libs/glm-master/CMakeFiles/uninstall:
	cd /home/vlad/Desktop/Visual_Computing_h-da/cmake-build-debug/libs/glm-master && /snap/clion/260/bin/cmake/linux/x64/bin/cmake -P /home/vlad/Desktop/Visual_Computing_h-da/cmake-build-debug/libs/glm-master/cmake_uninstall.cmake

uninstall: libs/glm-master/CMakeFiles/uninstall
uninstall: libs/glm-master/CMakeFiles/uninstall.dir/build.make
.PHONY : uninstall

# Rule to build all files generated by this target.
libs/glm-master/CMakeFiles/uninstall.dir/build: uninstall
.PHONY : libs/glm-master/CMakeFiles/uninstall.dir/build

libs/glm-master/CMakeFiles/uninstall.dir/clean:
	cd /home/vlad/Desktop/Visual_Computing_h-da/cmake-build-debug/libs/glm-master && $(CMAKE_COMMAND) -P CMakeFiles/uninstall.dir/cmake_clean.cmake
.PHONY : libs/glm-master/CMakeFiles/uninstall.dir/clean

libs/glm-master/CMakeFiles/uninstall.dir/depend:
	cd /home/vlad/Desktop/Visual_Computing_h-da/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/vlad/Desktop/Visual_Computing_h-da /home/vlad/Desktop/Visual_Computing_h-da/libs/glm-master /home/vlad/Desktop/Visual_Computing_h-da/cmake-build-debug /home/vlad/Desktop/Visual_Computing_h-da/cmake-build-debug/libs/glm-master /home/vlad/Desktop/Visual_Computing_h-da/cmake-build-debug/libs/glm-master/CMakeFiles/uninstall.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : libs/glm-master/CMakeFiles/uninstall.dir/depend

