# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/alex/Projects/FileSorting

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alex/Projects/FileSorting/build

# Include any dependencies generated for this target.
include CMakeFiles/CorrectTest.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/CorrectTest.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/CorrectTest.dir/flags.make

CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o: CMakeFiles/CorrectTest.dir/flags.make
CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o: ../Tests/CorrectTest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/FileSorting/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o -c /home/alex/Projects/FileSorting/Tests/CorrectTest.cpp

CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Projects/FileSorting/Tests/CorrectTest.cpp > CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.i

CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Projects/FileSorting/Tests/CorrectTest.cpp -o CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.s

CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o.requires:

.PHONY : CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o.requires

CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o.provides: CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o.requires
	$(MAKE) -f CMakeFiles/CorrectTest.dir/build.make CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o.provides.build
.PHONY : CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o.provides

CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o.provides.build: CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o


CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o: CMakeFiles/CorrectTest.dir/flags.make
CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o: ../FileSorting/SortingFunctions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alex/Projects/FileSorting/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o"
	/usr/bin/clang++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o -c /home/alex/Projects/FileSorting/FileSorting/SortingFunctions.cpp

CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.i"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alex/Projects/FileSorting/FileSorting/SortingFunctions.cpp > CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.i

CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.s"
	/usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alex/Projects/FileSorting/FileSorting/SortingFunctions.cpp -o CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.s

CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o.requires:

.PHONY : CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o.requires

CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o.provides: CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o.requires
	$(MAKE) -f CMakeFiles/CorrectTest.dir/build.make CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o.provides.build
.PHONY : CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o.provides

CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o.provides.build: CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o


# Object files for target CorrectTest
CorrectTest_OBJECTS = \
"CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o" \
"CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o"

# External object files for target CorrectTest
CorrectTest_EXTERNAL_OBJECTS =

CorrectTest: CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o
CorrectTest: CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o
CorrectTest: CMakeFiles/CorrectTest.dir/build.make
CorrectTest: /usr/lib/libgtest.so
CorrectTest: CMakeFiles/CorrectTest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alex/Projects/FileSorting/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable CorrectTest"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CorrectTest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/CorrectTest.dir/build: CorrectTest

.PHONY : CMakeFiles/CorrectTest.dir/build

CMakeFiles/CorrectTest.dir/requires: CMakeFiles/CorrectTest.dir/Tests/CorrectTest.cpp.o.requires
CMakeFiles/CorrectTest.dir/requires: CMakeFiles/CorrectTest.dir/FileSorting/SortingFunctions.cpp.o.requires

.PHONY : CMakeFiles/CorrectTest.dir/requires

CMakeFiles/CorrectTest.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/CorrectTest.dir/cmake_clean.cmake
.PHONY : CMakeFiles/CorrectTest.dir/clean

CMakeFiles/CorrectTest.dir/depend:
	cd /home/alex/Projects/FileSorting/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alex/Projects/FileSorting /home/alex/Projects/FileSorting /home/alex/Projects/FileSorting/build /home/alex/Projects/FileSorting/build /home/alex/Projects/FileSorting/build/CMakeFiles/CorrectTest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/CorrectTest.dir/depend

