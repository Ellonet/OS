# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /usr/local/APP/jetbrains/clion/2018.2.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /usr/local/APP/jetbrains/clion/2018.2.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cs/usr/ellonet/Desktop/OS/OS/ex2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cs/usr/ellonet/Desktop/OS/OS/ex2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ex2_test1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ex2_test1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ex2_test1.dir/flags.make

CMakeFiles/ex2_test1.dir/uthreads.cpp.o: CMakeFiles/ex2_test1.dir/flags.make
CMakeFiles/ex2_test1.dir/uthreads.cpp.o: ../uthreads.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/ellonet/Desktop/OS/OS/ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ex2_test1.dir/uthreads.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex2_test1.dir/uthreads.cpp.o -c /cs/usr/ellonet/Desktop/OS/OS/ex2/uthreads.cpp

CMakeFiles/ex2_test1.dir/uthreads.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex2_test1.dir/uthreads.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/ellonet/Desktop/OS/OS/ex2/uthreads.cpp > CMakeFiles/ex2_test1.dir/uthreads.cpp.i

CMakeFiles/ex2_test1.dir/uthreads.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex2_test1.dir/uthreads.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/ellonet/Desktop/OS/OS/ex2/uthreads.cpp -o CMakeFiles/ex2_test1.dir/uthreads.cpp.s

CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.o: CMakeFiles/ex2_test1.dir/flags.make
CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.o: ../sleeping_threads_list.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/ellonet/Desktop/OS/OS/ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.o -c /cs/usr/ellonet/Desktop/OS/OS/ex2/sleeping_threads_list.cpp

CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/ellonet/Desktop/OS/OS/ex2/sleeping_threads_list.cpp > CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.i

CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/ellonet/Desktop/OS/OS/ex2/sleeping_threads_list.cpp -o CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.s

CMakeFiles/ex2_test1.dir/test1.cpp.o: CMakeFiles/ex2_test1.dir/flags.make
CMakeFiles/ex2_test1.dir/test1.cpp.o: ../test1.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cs/usr/ellonet/Desktop/OS/OS/ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ex2_test1.dir/test1.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ex2_test1.dir/test1.cpp.o -c /cs/usr/ellonet/Desktop/OS/OS/ex2/test1.cpp

CMakeFiles/ex2_test1.dir/test1.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ex2_test1.dir/test1.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /cs/usr/ellonet/Desktop/OS/OS/ex2/test1.cpp > CMakeFiles/ex2_test1.dir/test1.cpp.i

CMakeFiles/ex2_test1.dir/test1.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ex2_test1.dir/test1.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /cs/usr/ellonet/Desktop/OS/OS/ex2/test1.cpp -o CMakeFiles/ex2_test1.dir/test1.cpp.s

# Object files for target ex2_test1
ex2_test1_OBJECTS = \
"CMakeFiles/ex2_test1.dir/uthreads.cpp.o" \
"CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.o" \
"CMakeFiles/ex2_test1.dir/test1.cpp.o"

# External object files for target ex2_test1
ex2_test1_EXTERNAL_OBJECTS =

ex2_test1: CMakeFiles/ex2_test1.dir/uthreads.cpp.o
ex2_test1: CMakeFiles/ex2_test1.dir/sleeping_threads_list.cpp.o
ex2_test1: CMakeFiles/ex2_test1.dir/test1.cpp.o
ex2_test1: CMakeFiles/ex2_test1.dir/build.make
ex2_test1: CMakeFiles/ex2_test1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cs/usr/ellonet/Desktop/OS/OS/ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ex2_test1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ex2_test1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ex2_test1.dir/build: ex2_test1

.PHONY : CMakeFiles/ex2_test1.dir/build

CMakeFiles/ex2_test1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ex2_test1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ex2_test1.dir/clean

CMakeFiles/ex2_test1.dir/depend:
	cd /cs/usr/ellonet/Desktop/OS/OS/ex2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cs/usr/ellonet/Desktop/OS/OS/ex2 /cs/usr/ellonet/Desktop/OS/OS/ex2 /cs/usr/ellonet/Desktop/OS/OS/ex2/cmake-build-debug /cs/usr/ellonet/Desktop/OS/OS/ex2/cmake-build-debug /cs/usr/ellonet/Desktop/OS/OS/ex2/cmake-build-debug/CMakeFiles/ex2_test1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ex2_test1.dir/depend

