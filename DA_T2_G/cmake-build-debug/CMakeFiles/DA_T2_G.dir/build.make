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
CMAKE_SOURCE_DIR = /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DA_T2_G.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DA_T2_G.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DA_T2_G.dir/flags.make

CMakeFiles/DA_T2_G.dir/main.cpp.o: CMakeFiles/DA_T2_G.dir/flags.make
CMakeFiles/DA_T2_G.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DA_T2_G.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/DA_T2_G.dir/main.cpp.o -c /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/main.cpp

CMakeFiles/DA_T2_G.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/DA_T2_G.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/main.cpp > CMakeFiles/DA_T2_G.dir/main.cpp.i

CMakeFiles/DA_T2_G.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/DA_T2_G.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/main.cpp -o CMakeFiles/DA_T2_G.dir/main.cpp.s

# Object files for target DA_T2_G
DA_T2_G_OBJECTS = \
"CMakeFiles/DA_T2_G.dir/main.cpp.o"

# External object files for target DA_T2_G
DA_T2_G_EXTERNAL_OBJECTS =

DA_T2_G: CMakeFiles/DA_T2_G.dir/main.cpp.o
DA_T2_G: CMakeFiles/DA_T2_G.dir/build.make
DA_T2_G: CMakeFiles/DA_T2_G.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DA_T2_G"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DA_T2_G.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DA_T2_G.dir/build: DA_T2_G

.PHONY : CMakeFiles/DA_T2_G.dir/build

CMakeFiles/DA_T2_G.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DA_T2_G.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DA_T2_G.dir/clean

CMakeFiles/DA_T2_G.dir/depend:
	cd /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/cmake-build-debug /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/cmake-build-debug /mnt/c/Users/pedro/OneDrive/Documentos/GitHub/DA_PROJ2/DA_T2_G/cmake-build-debug/CMakeFiles/DA_T2_G.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DA_T2_G.dir/depend

