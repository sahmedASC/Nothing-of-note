# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /cygdrive/c/Users/ahmeds7/.CLion2019.1/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/Users/ahmeds7/.CLion2019.1/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/lab11.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab11.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab11.dir/flags.make

CMakeFiles/lab11.dir/test_pq.cpp.o: CMakeFiles/lab11.dir/flags.make
CMakeFiles/lab11.dir/test_pq.cpp.o: ../test_pq.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab11.dir/test_pq.cpp.o"
	C:/cygwin64/bin/g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab11.dir/test_pq.cpp.o -c "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/test_pq.cpp"

CMakeFiles/lab11.dir/test_pq.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab11.dir/test_pq.cpp.i"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/test_pq.cpp" > CMakeFiles/lab11.dir/test_pq.cpp.i

CMakeFiles/lab11.dir/test_pq.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab11.dir/test_pq.cpp.s"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/test_pq.cpp" -o CMakeFiles/lab11.dir/test_pq.cpp.s

# Object files for target lab11
lab11_OBJECTS = \
"CMakeFiles/lab11.dir/test_pq.cpp.o"

# External object files for target lab11
lab11_EXTERNAL_OBJECTS =

lab11.exe: CMakeFiles/lab11.dir/test_pq.cpp.o
lab11.exe: CMakeFiles/lab11.dir/build.make
lab11.exe: CMakeFiles/lab11.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab11.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab11.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab11.dir/build: lab11.exe

.PHONY : CMakeFiles/lab11.dir/build

CMakeFiles/lab11.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab11.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab11.dir/clean

CMakeFiles/lab11.dir/depend:
	cd "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/cmake-build-debug" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/cmake-build-debug" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/lab11/cmake-build-debug/CMakeFiles/lab11.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/lab11.dir/depend

