# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HeatDiffusion.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HeatDiffusion.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HeatDiffusion.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HeatDiffusion.dir/flags.make

CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.o: CMakeFiles/HeatDiffusion.dir/flags.make
CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.o: /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp
CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.o: CMakeFiles/HeatDiffusion.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.o -MF CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.o.d -o CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.o -c /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp

CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp > CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.i

CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp -o CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.s

# Object files for target HeatDiffusion
HeatDiffusion_OBJECTS = \
"CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.o"

# External object files for target HeatDiffusion
HeatDiffusion_EXTERNAL_OBJECTS =

HeatDiffusion: CMakeFiles/HeatDiffusion.dir/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/src/HeatDiffusion.cpp.o
HeatDiffusion: CMakeFiles/HeatDiffusion.dir/build.make
HeatDiffusion: /usr/lib/x86_64-linux-gnu/openmpi/lib/libmpi_cxx.so
HeatDiffusion: /usr/lib/x86_64-linux-gnu/openmpi/lib/libmpi.so
HeatDiffusion: CMakeFiles/HeatDiffusion.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable HeatDiffusion"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HeatDiffusion.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HeatDiffusion.dir/build: HeatDiffusion
.PHONY : CMakeFiles/HeatDiffusion.dir/build

CMakeFiles/HeatDiffusion.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HeatDiffusion.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HeatDiffusion.dir/clean

CMakeFiles/HeatDiffusion.dir/depend:
	cd /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake/cmake-build-debug /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake/cmake-build-debug /mnt/c/Users/vojte/Documants/01_FEL/3.sem/PAG/labs/hw2_mpi_skeletons_cp/cmake/cmake-build-debug/CMakeFiles/HeatDiffusion.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/HeatDiffusion.dir/depend

