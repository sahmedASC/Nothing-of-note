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
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/hw9.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/hw9.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/hw9.dir/flags.make

CMakeFiles/hw9.dir/main.cpp.o: CMakeFiles/hw9.dir/flags.make
CMakeFiles/hw9.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/hw9.dir/main.cpp.o"
	C:/cygwin64/bin/g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw9.dir/main.cpp.o -c "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/main.cpp"

CMakeFiles/hw9.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw9.dir/main.cpp.i"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/main.cpp" > CMakeFiles/hw9.dir/main.cpp.i

CMakeFiles/hw9.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw9.dir/main.cpp.s"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/main.cpp" -o CMakeFiles/hw9.dir/main.cpp.s

CMakeFiles/hw9.dir/movie.cpp.o: CMakeFiles/hw9.dir/flags.make
CMakeFiles/hw9.dir/movie.cpp.o: ../movie.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/hw9.dir/movie.cpp.o"
	C:/cygwin64/bin/g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/hw9.dir/movie.cpp.o -c "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/movie.cpp"

CMakeFiles/hw9.dir/movie.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hw9.dir/movie.cpp.i"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/movie.cpp" > CMakeFiles/hw9.dir/movie.cpp.i

CMakeFiles/hw9.dir/movie.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hw9.dir/movie.cpp.s"
	C:/cygwin64/bin/g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/movie.cpp" -o CMakeFiles/hw9.dir/movie.cpp.s

# Object files for target hw9
hw9_OBJECTS = \
"CMakeFiles/hw9.dir/main.cpp.o" \
"CMakeFiles/hw9.dir/movie.cpp.o"

# External object files for target hw9
hw9_EXTERNAL_OBJECTS =

hw9.exe: CMakeFiles/hw9.dir/main.cpp.o
hw9.exe: CMakeFiles/hw9.dir/movie.cpp.o
hw9.exe: CMakeFiles/hw9.dir/build.make
hw9.exe: CMakeFiles/hw9.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable hw9.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hw9.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/hw9.dir/build: hw9.exe

.PHONY : CMakeFiles/hw9.dir/build

CMakeFiles/hw9.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/hw9.dir/cmake_clean.cmake
.PHONY : CMakeFiles/hw9.dir/clean

CMakeFiles/hw9.dir/depend:
	cd "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/cmake-build-debug" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/cmake-build-debug" "/cygdrive/c/Users/ahmeds7/Documents/Data Structures/hw9/cmake-build-debug/CMakeFiles/hw9.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/hw9.dir/depend

