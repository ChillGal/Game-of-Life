# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.17

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

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.2.4\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\gchan\Documents\CLion\GameOfLife

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\gchan\Documents\CLion\GameOfLife\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/GameOfLife.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/GameOfLife.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/GameOfLife.dir/flags.make

CMakeFiles/GameOfLife.dir/main.c.obj: CMakeFiles/GameOfLife.dir/flags.make
CMakeFiles/GameOfLife.dir/main.c.obj: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\gchan\Documents\CLion\GameOfLife\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/GameOfLife.dir/main.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\GameOfLife.dir\main.c.obj   -c C:\Users\gchan\Documents\CLion\GameOfLife\main.c

CMakeFiles/GameOfLife.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GameOfLife.dir/main.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\gchan\Documents\CLion\GameOfLife\main.c > CMakeFiles\GameOfLife.dir\main.c.i

CMakeFiles/GameOfLife.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GameOfLife.dir/main.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\gchan\Documents\CLion\GameOfLife\main.c -o CMakeFiles\GameOfLife.dir\main.c.s

CMakeFiles/GameOfLife.dir/engine.c.obj: CMakeFiles/GameOfLife.dir/flags.make
CMakeFiles/GameOfLife.dir/engine.c.obj: ../engine.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\gchan\Documents\CLion\GameOfLife\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/GameOfLife.dir/engine.c.obj"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles\GameOfLife.dir\engine.c.obj   -c C:\Users\gchan\Documents\CLion\GameOfLife\engine.c

CMakeFiles/GameOfLife.dir/engine.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/GameOfLife.dir/engine.c.i"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\gchan\Documents\CLion\GameOfLife\engine.c > CMakeFiles\GameOfLife.dir\engine.c.i

CMakeFiles/GameOfLife.dir/engine.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/GameOfLife.dir/engine.c.s"
	C:\MinGW\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\gchan\Documents\CLion\GameOfLife\engine.c -o CMakeFiles\GameOfLife.dir\engine.c.s

# Object files for target GameOfLife
GameOfLife_OBJECTS = \
"CMakeFiles/GameOfLife.dir/main.c.obj" \
"CMakeFiles/GameOfLife.dir/engine.c.obj"

# External object files for target GameOfLife
GameOfLife_EXTERNAL_OBJECTS =

GameOfLife.exe: CMakeFiles/GameOfLife.dir/main.c.obj
GameOfLife.exe: CMakeFiles/GameOfLife.dir/engine.c.obj
GameOfLife.exe: CMakeFiles/GameOfLife.dir/build.make
GameOfLife.exe: CMakeFiles/GameOfLife.dir/linklibs.rsp
GameOfLife.exe: CMakeFiles/GameOfLife.dir/objects1.rsp
GameOfLife.exe: CMakeFiles/GameOfLife.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\gchan\Documents\CLion\GameOfLife\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable GameOfLife.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\GameOfLife.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/GameOfLife.dir/build: GameOfLife.exe

.PHONY : CMakeFiles/GameOfLife.dir/build

CMakeFiles/GameOfLife.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\GameOfLife.dir\cmake_clean.cmake
.PHONY : CMakeFiles/GameOfLife.dir/clean

CMakeFiles/GameOfLife.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\gchan\Documents\CLion\GameOfLife C:\Users\gchan\Documents\CLion\GameOfLife C:\Users\gchan\Documents\CLion\GameOfLife\cmake-build-debug C:\Users\gchan\Documents\CLion\GameOfLife\cmake-build-debug C:\Users\gchan\Documents\CLion\GameOfLife\cmake-build-debug\CMakeFiles\GameOfLife.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/GameOfLife.dir/depend

