# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.11

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
CMAKE_COMMAND = /Users/ntoniolo/.brew/Cellar/cmake/3.11.4/bin/cmake

# The command to remove a file.
RM = /Users/ntoniolo/.brew/Cellar/cmake/3.11.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/ntoniolo/base/scop/cJSON

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/ntoniolo/base/scop/cJSON/build

# Include any dependencies generated for this target.
include tests/CMakeFiles/compare_tests.dir/depend.make

# Include the progress variables for this target.
include tests/CMakeFiles/compare_tests.dir/progress.make

# Include the compile flags for this target's objects.
include tests/CMakeFiles/compare_tests.dir/flags.make

tests/CMakeFiles/compare_tests.dir/compare_tests.c.o: tests/CMakeFiles/compare_tests.dir/flags.make
tests/CMakeFiles/compare_tests.dir/compare_tests.c.o: ../tests/compare_tests.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ntoniolo/base/scop/cJSON/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object tests/CMakeFiles/compare_tests.dir/compare_tests.c.o"
	cd /Users/ntoniolo/base/scop/cJSON/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/compare_tests.dir/compare_tests.c.o   -c /Users/ntoniolo/base/scop/cJSON/tests/compare_tests.c

tests/CMakeFiles/compare_tests.dir/compare_tests.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/compare_tests.dir/compare_tests.c.i"
	cd /Users/ntoniolo/base/scop/cJSON/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ntoniolo/base/scop/cJSON/tests/compare_tests.c > CMakeFiles/compare_tests.dir/compare_tests.c.i

tests/CMakeFiles/compare_tests.dir/compare_tests.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/compare_tests.dir/compare_tests.c.s"
	cd /Users/ntoniolo/base/scop/cJSON/build/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ntoniolo/base/scop/cJSON/tests/compare_tests.c -o CMakeFiles/compare_tests.dir/compare_tests.c.s

# Object files for target compare_tests
compare_tests_OBJECTS = \
"CMakeFiles/compare_tests.dir/compare_tests.c.o"

# External object files for target compare_tests
compare_tests_EXTERNAL_OBJECTS =

tests/compare_tests: tests/CMakeFiles/compare_tests.dir/compare_tests.c.o
tests/compare_tests: tests/CMakeFiles/compare_tests.dir/build.make
tests/compare_tests: libcjson.1.7.7.dylib
tests/compare_tests: tests/libunity.dylib
tests/compare_tests: tests/CMakeFiles/compare_tests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ntoniolo/base/scop/cJSON/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable compare_tests"
	cd /Users/ntoniolo/base/scop/cJSON/build/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/compare_tests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
tests/CMakeFiles/compare_tests.dir/build: tests/compare_tests

.PHONY : tests/CMakeFiles/compare_tests.dir/build

tests/CMakeFiles/compare_tests.dir/clean:
	cd /Users/ntoniolo/base/scop/cJSON/build/tests && $(CMAKE_COMMAND) -P CMakeFiles/compare_tests.dir/cmake_clean.cmake
.PHONY : tests/CMakeFiles/compare_tests.dir/clean

tests/CMakeFiles/compare_tests.dir/depend:
	cd /Users/ntoniolo/base/scop/cJSON/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ntoniolo/base/scop/cJSON /Users/ntoniolo/base/scop/cJSON/tests /Users/ntoniolo/base/scop/cJSON/build /Users/ntoniolo/base/scop/cJSON/build/tests /Users/ntoniolo/base/scop/cJSON/build/tests/CMakeFiles/compare_tests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : tests/CMakeFiles/compare_tests.dir/depend

