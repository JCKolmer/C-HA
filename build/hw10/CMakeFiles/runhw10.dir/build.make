# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jojo/JoaquimK_tasks

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jojo/JoaquimK_tasks/build

# Include any dependencies generated for this target.
include hw10/CMakeFiles/runhw10.dir/depend.make

# Include the progress variables for this target.
include hw10/CMakeFiles/runhw10.dir/progress.make

# Include the compile flags for this target's objects.
include hw10/CMakeFiles/runhw10.dir/flags.make

hw10/CMakeFiles/runhw10.dir/run.cpp.o: hw10/CMakeFiles/runhw10.dir/flags.make
hw10/CMakeFiles/runhw10.dir/run.cpp.o: ../hw10/run.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jojo/JoaquimK_tasks/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object hw10/CMakeFiles/runhw10.dir/run.cpp.o"
	cd /home/jojo/JoaquimK_tasks/build/hw10 && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runhw10.dir/run.cpp.o -c /home/jojo/JoaquimK_tasks/hw10/run.cpp

hw10/CMakeFiles/runhw10.dir/run.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runhw10.dir/run.cpp.i"
	cd /home/jojo/JoaquimK_tasks/build/hw10 && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jojo/JoaquimK_tasks/hw10/run.cpp > CMakeFiles/runhw10.dir/run.cpp.i

hw10/CMakeFiles/runhw10.dir/run.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runhw10.dir/run.cpp.s"
	cd /home/jojo/JoaquimK_tasks/build/hw10 && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jojo/JoaquimK_tasks/hw10/run.cpp -o CMakeFiles/runhw10.dir/run.cpp.s

# Object files for target runhw10
runhw10_OBJECTS = \
"CMakeFiles/runhw10.dir/run.cpp.o"

# External object files for target runhw10
runhw10_EXTERNAL_OBJECTS =

hw10/runhw10: hw10/CMakeFiles/runhw10.dir/run.cpp.o
hw10/runhw10: hw10/CMakeFiles/runhw10.dir/build.make
hw10/runhw10: hw10/libhw10.a
hw10/runhw10: hw10/CMakeFiles/runhw10.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jojo/JoaquimK_tasks/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable runhw10"
	cd /home/jojo/JoaquimK_tasks/build/hw10 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runhw10.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
hw10/CMakeFiles/runhw10.dir/build: hw10/runhw10

.PHONY : hw10/CMakeFiles/runhw10.dir/build

hw10/CMakeFiles/runhw10.dir/clean:
	cd /home/jojo/JoaquimK_tasks/build/hw10 && $(CMAKE_COMMAND) -P CMakeFiles/runhw10.dir/cmake_clean.cmake
.PHONY : hw10/CMakeFiles/runhw10.dir/clean

hw10/CMakeFiles/runhw10.dir/depend:
	cd /home/jojo/JoaquimK_tasks/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jojo/JoaquimK_tasks /home/jojo/JoaquimK_tasks/hw10 /home/jojo/JoaquimK_tasks/build /home/jojo/JoaquimK_tasks/build/hw10 /home/jojo/JoaquimK_tasks/build/hw10/CMakeFiles/runhw10.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : hw10/CMakeFiles/runhw10.dir/depend

