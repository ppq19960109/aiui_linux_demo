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
CMAKE_SOURCE_DIR = /home/ppq/aiui/samples

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ppq/aiui/samples/build_x64

# Include any dependencies generated for this target.
include CMakeFiles/aiui_sample.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/aiui_sample.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/aiui_sample.dir/flags.make

CMakeFiles/aiui_sample.dir/src/demo.cpp.o: CMakeFiles/aiui_sample.dir/flags.make
CMakeFiles/aiui_sample.dir/src/demo.cpp.o: ../src/demo.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ppq/aiui/samples/build_x64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/aiui_sample.dir/src/demo.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aiui_sample.dir/src/demo.cpp.o -c /home/ppq/aiui/samples/src/demo.cpp

CMakeFiles/aiui_sample.dir/src/demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aiui_sample.dir/src/demo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ppq/aiui/samples/src/demo.cpp > CMakeFiles/aiui_sample.dir/src/demo.cpp.i

CMakeFiles/aiui_sample.dir/src/demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aiui_sample.dir/src/demo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ppq/aiui/samples/src/demo.cpp -o CMakeFiles/aiui_sample.dir/src/demo.cpp.s

CMakeFiles/aiui_sample.dir/src/demo.cpp.o.requires:

.PHONY : CMakeFiles/aiui_sample.dir/src/demo.cpp.o.requires

CMakeFiles/aiui_sample.dir/src/demo.cpp.o.provides: CMakeFiles/aiui_sample.dir/src/demo.cpp.o.requires
	$(MAKE) -f CMakeFiles/aiui_sample.dir/build.make CMakeFiles/aiui_sample.dir/src/demo.cpp.o.provides.build
.PHONY : CMakeFiles/aiui_sample.dir/src/demo.cpp.o.provides

CMakeFiles/aiui_sample.dir/src/demo.cpp.o.provides.build: CMakeFiles/aiui_sample.dir/src/demo.cpp.o


CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o: CMakeFiles/aiui_sample.dir/flags.make
CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o: ../src/speech_recognizer.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ppq/aiui/samples/build_x64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o   -c /home/ppq/aiui/samples/src/speech_recognizer.c

CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ppq/aiui/samples/src/speech_recognizer.c > CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.i

CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ppq/aiui/samples/src/speech_recognizer.c -o CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.s

CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o.requires:

.PHONY : CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o.requires

CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o.provides: CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o.requires
	$(MAKE) -f CMakeFiles/aiui_sample.dir/build.make CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o.provides.build
.PHONY : CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o.provides

CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o.provides.build: CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o


CMakeFiles/aiui_sample.dir/src/linuxrec.c.o: CMakeFiles/aiui_sample.dir/flags.make
CMakeFiles/aiui_sample.dir/src/linuxrec.c.o: ../src/linuxrec.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ppq/aiui/samples/build_x64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/aiui_sample.dir/src/linuxrec.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/aiui_sample.dir/src/linuxrec.c.o   -c /home/ppq/aiui/samples/src/linuxrec.c

CMakeFiles/aiui_sample.dir/src/linuxrec.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/aiui_sample.dir/src/linuxrec.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ppq/aiui/samples/src/linuxrec.c > CMakeFiles/aiui_sample.dir/src/linuxrec.c.i

CMakeFiles/aiui_sample.dir/src/linuxrec.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/aiui_sample.dir/src/linuxrec.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ppq/aiui/samples/src/linuxrec.c -o CMakeFiles/aiui_sample.dir/src/linuxrec.c.s

CMakeFiles/aiui_sample.dir/src/linuxrec.c.o.requires:

.PHONY : CMakeFiles/aiui_sample.dir/src/linuxrec.c.o.requires

CMakeFiles/aiui_sample.dir/src/linuxrec.c.o.provides: CMakeFiles/aiui_sample.dir/src/linuxrec.c.o.requires
	$(MAKE) -f CMakeFiles/aiui_sample.dir/build.make CMakeFiles/aiui_sample.dir/src/linuxrec.c.o.provides.build
.PHONY : CMakeFiles/aiui_sample.dir/src/linuxrec.c.o.provides

CMakeFiles/aiui_sample.dir/src/linuxrec.c.o.provides.build: CMakeFiles/aiui_sample.dir/src/linuxrec.c.o


CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o: CMakeFiles/aiui_sample.dir/flags.make
CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o: ../src/jsoncpp/json_reader.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ppq/aiui/samples/build_x64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o -c /home/ppq/aiui/samples/src/jsoncpp/json_reader.cpp

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ppq/aiui/samples/src/jsoncpp/json_reader.cpp > CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.i

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ppq/aiui/samples/src/jsoncpp/json_reader.cpp -o CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.s

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o.requires:

.PHONY : CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o.requires

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o.provides: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o.requires
	$(MAKE) -f CMakeFiles/aiui_sample.dir/build.make CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o.provides.build
.PHONY : CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o.provides

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o.provides.build: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o


CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o: CMakeFiles/aiui_sample.dir/flags.make
CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o: ../src/jsoncpp/json_value.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ppq/aiui/samples/build_x64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o -c /home/ppq/aiui/samples/src/jsoncpp/json_value.cpp

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ppq/aiui/samples/src/jsoncpp/json_value.cpp > CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.i

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ppq/aiui/samples/src/jsoncpp/json_value.cpp -o CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.s

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o.requires:

.PHONY : CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o.requires

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o.provides: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o.requires
	$(MAKE) -f CMakeFiles/aiui_sample.dir/build.make CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o.provides.build
.PHONY : CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o.provides

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o.provides.build: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o


CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o: CMakeFiles/aiui_sample.dir/flags.make
CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o: ../src/jsoncpp/json_writer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ppq/aiui/samples/build_x64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o -c /home/ppq/aiui/samples/src/jsoncpp/json_writer.cpp

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ppq/aiui/samples/src/jsoncpp/json_writer.cpp > CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.i

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ppq/aiui/samples/src/jsoncpp/json_writer.cpp -o CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.s

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o.requires:

.PHONY : CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o.requires

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o.provides: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o.requires
	$(MAKE) -f CMakeFiles/aiui_sample.dir/build.make CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o.provides.build
.PHONY : CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o.provides

CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o.provides.build: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o


# Object files for target aiui_sample
aiui_sample_OBJECTS = \
"CMakeFiles/aiui_sample.dir/src/demo.cpp.o" \
"CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o" \
"CMakeFiles/aiui_sample.dir/src/linuxrec.c.o" \
"CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o" \
"CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o" \
"CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o"

# External object files for target aiui_sample
aiui_sample_EXTERNAL_OBJECTS =

/home/ppq/aiui/bin_x64/aiui_sample: CMakeFiles/aiui_sample.dir/src/demo.cpp.o
/home/ppq/aiui/bin_x64/aiui_sample: CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o
/home/ppq/aiui/bin_x64/aiui_sample: CMakeFiles/aiui_sample.dir/src/linuxrec.c.o
/home/ppq/aiui/bin_x64/aiui_sample: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o
/home/ppq/aiui/bin_x64/aiui_sample: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o
/home/ppq/aiui/bin_x64/aiui_sample: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o
/home/ppq/aiui/bin_x64/aiui_sample: CMakeFiles/aiui_sample.dir/build.make
/home/ppq/aiui/bin_x64/aiui_sample: CMakeFiles/aiui_sample.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ppq/aiui/samples/build_x64/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable /home/ppq/aiui/bin_x64/aiui_sample"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/aiui_sample.dir/link.txt --verbose=$(VERBOSE)
	/usr/bin/cmake -E copy /home/ppq/aiui/samples/../libs/x64/libaiui.so /home/ppq/aiui/samples/../bin_x64
	/usr/bin/cmake -E copy /home/ppq/aiui/samples/../libs/x64/libvtn_mic1.so /home/ppq/aiui/samples/../bin_x64
	/usr/bin/cmake -E copy_directory /home/ppq/aiui/samples/AIUI /home/ppq/aiui/samples/../bin_x64/AIUI

# Rule to build all files generated by this target.
CMakeFiles/aiui_sample.dir/build: /home/ppq/aiui/bin_x64/aiui_sample

.PHONY : CMakeFiles/aiui_sample.dir/build

CMakeFiles/aiui_sample.dir/requires: CMakeFiles/aiui_sample.dir/src/demo.cpp.o.requires
CMakeFiles/aiui_sample.dir/requires: CMakeFiles/aiui_sample.dir/src/speech_recognizer.c.o.requires
CMakeFiles/aiui_sample.dir/requires: CMakeFiles/aiui_sample.dir/src/linuxrec.c.o.requires
CMakeFiles/aiui_sample.dir/requires: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_reader.cpp.o.requires
CMakeFiles/aiui_sample.dir/requires: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_value.cpp.o.requires
CMakeFiles/aiui_sample.dir/requires: CMakeFiles/aiui_sample.dir/src/jsoncpp/json_writer.cpp.o.requires

.PHONY : CMakeFiles/aiui_sample.dir/requires

CMakeFiles/aiui_sample.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/aiui_sample.dir/cmake_clean.cmake
.PHONY : CMakeFiles/aiui_sample.dir/clean

CMakeFiles/aiui_sample.dir/depend:
	cd /home/ppq/aiui/samples/build_x64 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ppq/aiui/samples /home/ppq/aiui/samples /home/ppq/aiui/samples/build_x64 /home/ppq/aiui/samples/build_x64 /home/ppq/aiui/samples/build_x64/CMakeFiles/aiui_sample.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/aiui_sample.dir/depend
