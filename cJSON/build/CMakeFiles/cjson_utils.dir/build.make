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
include CMakeFiles/cjson_utils.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cjson_utils.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cjson_utils.dir/flags.make

CMakeFiles/cjson_utils.dir/cJSON_Utils.c.o: CMakeFiles/cjson_utils.dir/flags.make
CMakeFiles/cjson_utils.dir/cJSON_Utils.c.o: ../cJSON_Utils.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/ntoniolo/base/scop/cJSON/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/cjson_utils.dir/cJSON_Utils.c.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cjson_utils.dir/cJSON_Utils.c.o   -c /Users/ntoniolo/base/scop/cJSON/cJSON_Utils.c

CMakeFiles/cjson_utils.dir/cJSON_Utils.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cjson_utils.dir/cJSON_Utils.c.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/ntoniolo/base/scop/cJSON/cJSON_Utils.c > CMakeFiles/cjson_utils.dir/cJSON_Utils.c.i

CMakeFiles/cjson_utils.dir/cJSON_Utils.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cjson_utils.dir/cJSON_Utils.c.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/ntoniolo/base/scop/cJSON/cJSON_Utils.c -o CMakeFiles/cjson_utils.dir/cJSON_Utils.c.s

# Object files for target cjson_utils
cjson_utils_OBJECTS = \
"CMakeFiles/cjson_utils.dir/cJSON_Utils.c.o"

# External object files for target cjson_utils
cjson_utils_EXTERNAL_OBJECTS =

libcjson_utils.1.7.7.dylib: CMakeFiles/cjson_utils.dir/cJSON_Utils.c.o
libcjson_utils.1.7.7.dylib: CMakeFiles/cjson_utils.dir/build.make
libcjson_utils.1.7.7.dylib: libcjson.1.7.7.dylib
libcjson_utils.1.7.7.dylib: CMakeFiles/cjson_utils.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/ntoniolo/base/scop/cJSON/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C shared library libcjson_utils.dylib"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cjson_utils.dir/link.txt --verbose=$(VERBOSE)
	$(CMAKE_COMMAND) -E cmake_symlink_library libcjson_utils.1.7.7.dylib libcjson_utils.1.dylib libcjson_utils.dylib

libcjson_utils.1.dylib: libcjson_utils.1.7.7.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libcjson_utils.1.dylib

libcjson_utils.dylib: libcjson_utils.1.7.7.dylib
	@$(CMAKE_COMMAND) -E touch_nocreate libcjson_utils.dylib

# Rule to build all files generated by this target.
CMakeFiles/cjson_utils.dir/build: libcjson_utils.dylib

.PHONY : CMakeFiles/cjson_utils.dir/build

CMakeFiles/cjson_utils.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cjson_utils.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cjson_utils.dir/clean

CMakeFiles/cjson_utils.dir/depend:
	cd /Users/ntoniolo/base/scop/cJSON/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/ntoniolo/base/scop/cJSON /Users/ntoniolo/base/scop/cJSON /Users/ntoniolo/base/scop/cJSON/build /Users/ntoniolo/base/scop/cJSON/build /Users/ntoniolo/base/scop/cJSON/build/CMakeFiles/cjson_utils.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cjson_utils.dir/depend

