# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx

# Include any dependencies generated for this target.
include CMakeFiles/builder_stream.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/builder_stream.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/builder_stream.dir/flags.make

CMakeFiles/builder_stream.dir/builder_stream.o: CMakeFiles/builder_stream.dir/flags.make
CMakeFiles/builder_stream.dir/builder_stream.o: builder_stream.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/builder_stream.dir/builder_stream.o"
	/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/builder_stream.dir/builder_stream.o -c /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx/builder_stream.cpp

CMakeFiles/builder_stream.dir/builder_stream.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/builder_stream.dir/builder_stream.i"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx/builder_stream.cpp > CMakeFiles/builder_stream.dir/builder_stream.i

CMakeFiles/builder_stream.dir/builder_stream.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/builder_stream.dir/builder_stream.s"
	/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx/builder_stream.cpp -o CMakeFiles/builder_stream.dir/builder_stream.s

CMakeFiles/builder_stream.dir/builder_stream.o.requires:

.PHONY : CMakeFiles/builder_stream.dir/builder_stream.o.requires

CMakeFiles/builder_stream.dir/builder_stream.o.provides: CMakeFiles/builder_stream.dir/builder_stream.o.requires
	$(MAKE) -f CMakeFiles/builder_stream.dir/build.make CMakeFiles/builder_stream.dir/builder_stream.o.provides.build
.PHONY : CMakeFiles/builder_stream.dir/builder_stream.o.provides

CMakeFiles/builder_stream.dir/builder_stream.o.provides.build: CMakeFiles/builder_stream.dir/builder_stream.o


# Object files for target builder_stream
builder_stream_OBJECTS = \
"CMakeFiles/builder_stream.dir/builder_stream.o"

# External object files for target builder_stream
builder_stream_EXTERNAL_OBJECTS =

builder_stream: CMakeFiles/builder_stream.dir/builder_stream.o
builder_stream: CMakeFiles/builder_stream.dir/build.make
builder_stream: CMakeFiles/builder_stream.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable builder_stream"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/builder_stream.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/builder_stream.dir/build: builder_stream

.PHONY : CMakeFiles/builder_stream.dir/build

CMakeFiles/builder_stream.dir/requires: CMakeFiles/builder_stream.dir/builder_stream.o.requires

.PHONY : CMakeFiles/builder_stream.dir/requires

CMakeFiles/builder_stream.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/builder_stream.dir/cmake_clean.cmake
.PHONY : CMakeFiles/builder_stream.dir/clean

CMakeFiles/builder_stream.dir/depend:
	cd /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx /home/golitij/cpp_a1/sand_box/test_mgDBcXXX/mongo-cxx-driver-r3.1.3/examples/bsoncxx/CMakeFiles/builder_stream.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/builder_stream.dir/depend

