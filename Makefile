# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.9.4/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.9.4/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/fleur/Epitech/cpp/cpp_spider

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/fleur/Epitech/cpp/cpp_spider

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.9.4/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.9.4/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/fleur/Epitech/cpp/cpp_spider/CMakeFiles /Users/fleur/Epitech/cpp/cpp_spider/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/fleur/Epitech/cpp/cpp_spider/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named module_keyboard

# Build rule for target.
module_keyboard: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 module_keyboard
.PHONY : module_keyboard

# fast build rule for target.
module_keyboard/fast:
	$(MAKE) -f CMakeFiles/module_keyboard.dir/build.make CMakeFiles/module_keyboard.dir/build
.PHONY : module_keyboard/fast

#=============================================================================
# Target rules for targets named spider_serveur

# Build rule for target.
spider_serveur: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 spider_serveur
.PHONY : spider_serveur

# fast build rule for target.
spider_serveur/fast:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/build
.PHONY : spider_serveur/fast

#=============================================================================
# Target rules for targets named http_server

# Build rule for target.
http_server: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 http_server
.PHONY : http_server

# fast build rule for target.
http_server/fast:
	$(MAKE) -f CMakeFiles/http_server.dir/build.make CMakeFiles/http_server.dir/build
.PHONY : http_server/fast

#=============================================================================
# Target rules for targets named spider_client

# Build rule for target.
spider_client: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 spider_client
.PHONY : spider_client

# fast build rule for target.
spider_client/fast:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/build
.PHONY : spider_client/fast

#=============================================================================
# Target rules for targets named module_explorer

# Build rule for target.
module_explorer: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 module_explorer
.PHONY : module_explorer

# fast build rule for target.
module_explorer/fast:
	$(MAKE) -f CMakeFiles/module_explorer.dir/build.make CMakeFiles/module_explorer.dir/build
.PHONY : module_explorer/fast

sources/AIntervalService.o: sources/AIntervalService.cpp.o

.PHONY : sources/AIntervalService.o

# target to build an object file
sources/AIntervalService.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/AIntervalService.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/AIntervalService.cpp.o
.PHONY : sources/AIntervalService.cpp.o

sources/AIntervalService.i: sources/AIntervalService.cpp.i

.PHONY : sources/AIntervalService.i

# target to preprocess a source file
sources/AIntervalService.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/AIntervalService.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/AIntervalService.cpp.i
.PHONY : sources/AIntervalService.cpp.i

sources/AIntervalService.s: sources/AIntervalService.cpp.s

.PHONY : sources/AIntervalService.s

# target to generate assembly for a file
sources/AIntervalService.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/AIntervalService.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/AIntervalService.cpp.s
.PHONY : sources/AIntervalService.cpp.s

sources/APacketServer.o: sources/APacketServer.cpp.o

.PHONY : sources/APacketServer.o

# target to build an object file
sources/APacketServer.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/APacketServer.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/APacketServer.cpp.o
.PHONY : sources/APacketServer.cpp.o

sources/APacketServer.i: sources/APacketServer.cpp.i

.PHONY : sources/APacketServer.i

# target to preprocess a source file
sources/APacketServer.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/APacketServer.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/APacketServer.cpp.i
.PHONY : sources/APacketServer.cpp.i

sources/APacketServer.s: sources/APacketServer.cpp.s

.PHONY : sources/APacketServer.s

# target to generate assembly for a file
sources/APacketServer.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/APacketServer.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/APacketServer.cpp.s
.PHONY : sources/APacketServer.cpp.s

sources/AUdpServer.o: sources/AUdpServer.cpp.o

.PHONY : sources/AUdpServer.o

# target to build an object file
sources/AUdpServer.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/AUdpServer.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/AUdpServer.cpp.o
.PHONY : sources/AUdpServer.cpp.o

sources/AUdpServer.i: sources/AUdpServer.cpp.i

.PHONY : sources/AUdpServer.i

# target to preprocess a source file
sources/AUdpServer.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/AUdpServer.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/AUdpServer.cpp.i
.PHONY : sources/AUdpServer.cpp.i

sources/AUdpServer.s: sources/AUdpServer.cpp.s

.PHONY : sources/AUdpServer.s

# target to generate assembly for a file
sources/AUdpServer.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/AUdpServer.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/AUdpServer.cpp.s
.PHONY : sources/AUdpServer.cpp.s

sources/IntervalService.o: sources/IntervalService.cpp.o

.PHONY : sources/IntervalService.o

# target to build an object file
sources/IntervalService.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/IntervalService.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/IntervalService.cpp.o
.PHONY : sources/IntervalService.cpp.o

sources/IntervalService.i: sources/IntervalService.cpp.i

.PHONY : sources/IntervalService.i

# target to preprocess a source file
sources/IntervalService.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/IntervalService.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/IntervalService.cpp.i
.PHONY : sources/IntervalService.cpp.i

sources/IntervalService.s: sources/IntervalService.cpp.s

.PHONY : sources/IntervalService.s

# target to generate assembly for a file
sources/IntervalService.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/IntervalService.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/IntervalService.cpp.s
.PHONY : sources/IntervalService.cpp.s

sources/LocalDB.o: sources/LocalDB.cpp.o

.PHONY : sources/LocalDB.o

# target to build an object file
sources/LocalDB.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/LocalDB.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/LocalDB.cpp.o
.PHONY : sources/LocalDB.cpp.o

sources/LocalDB.i: sources/LocalDB.cpp.i

.PHONY : sources/LocalDB.i

# target to preprocess a source file
sources/LocalDB.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/LocalDB.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/LocalDB.cpp.i
.PHONY : sources/LocalDB.cpp.i

sources/LocalDB.s: sources/LocalDB.cpp.s

.PHONY : sources/LocalDB.s

# target to generate assembly for a file
sources/LocalDB.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/LocalDB.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/LocalDB.cpp.s
.PHONY : sources/LocalDB.cpp.s

sources/MapDB.o: sources/MapDB.cpp.o

.PHONY : sources/MapDB.o

# target to build an object file
sources/MapDB.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/MapDB.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/MapDB.cpp.o
.PHONY : sources/MapDB.cpp.o

sources/MapDB.i: sources/MapDB.cpp.i

.PHONY : sources/MapDB.i

# target to preprocess a source file
sources/MapDB.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/MapDB.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/MapDB.cpp.i
.PHONY : sources/MapDB.cpp.i

sources/MapDB.s: sources/MapDB.cpp.s

.PHONY : sources/MapDB.s

# target to generate assembly for a file
sources/MapDB.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/MapDB.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/MapDB.cpp.s
.PHONY : sources/MapDB.cpp.s

sources/MongoDB.o: sources/MongoDB.cpp.o

.PHONY : sources/MongoDB.o

# target to build an object file
sources/MongoDB.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/MongoDB.cpp.o
.PHONY : sources/MongoDB.cpp.o

sources/MongoDB.i: sources/MongoDB.cpp.i

.PHONY : sources/MongoDB.i

# target to preprocess a source file
sources/MongoDB.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/MongoDB.cpp.i
.PHONY : sources/MongoDB.cpp.i

sources/MongoDB.s: sources/MongoDB.cpp.s

.PHONY : sources/MongoDB.s

# target to generate assembly for a file
sources/MongoDB.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/MongoDB.cpp.s
.PHONY : sources/MongoDB.cpp.s

sources/Packet.o: sources/Packet.cpp.o

.PHONY : sources/Packet.o

# target to build an object file
sources/Packet.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/Packet.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/Packet.cpp.o
.PHONY : sources/Packet.cpp.o

sources/Packet.i: sources/Packet.cpp.i

.PHONY : sources/Packet.i

# target to preprocess a source file
sources/Packet.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/Packet.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/Packet.cpp.i
.PHONY : sources/Packet.cpp.i

sources/Packet.s: sources/Packet.cpp.s

.PHONY : sources/Packet.s

# target to generate assembly for a file
sources/Packet.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/Packet.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/Packet.cpp.s
.PHONY : sources/Packet.cpp.s

sources/PacketManager.o: sources/PacketManager.cpp.o

.PHONY : sources/PacketManager.o

# target to build an object file
sources/PacketManager.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/PacketManager.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/PacketManager.cpp.o
.PHONY : sources/PacketManager.cpp.o

sources/PacketManager.i: sources/PacketManager.cpp.i

.PHONY : sources/PacketManager.i

# target to preprocess a source file
sources/PacketManager.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/PacketManager.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/PacketManager.cpp.i
.PHONY : sources/PacketManager.cpp.i

sources/PacketManager.s: sources/PacketManager.cpp.s

.PHONY : sources/PacketManager.s

# target to generate assembly for a file
sources/PacketManager.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/PacketManager.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/PacketManager.cpp.s
.PHONY : sources/PacketManager.cpp.s

sources/UdpEndpoint.o: sources/UdpEndpoint.cpp.o

.PHONY : sources/UdpEndpoint.o

# target to build an object file
sources/UdpEndpoint.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/UdpEndpoint.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/UdpEndpoint.cpp.o
.PHONY : sources/UdpEndpoint.cpp.o

sources/UdpEndpoint.i: sources/UdpEndpoint.cpp.i

.PHONY : sources/UdpEndpoint.i

# target to preprocess a source file
sources/UdpEndpoint.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/UdpEndpoint.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/UdpEndpoint.cpp.i
.PHONY : sources/UdpEndpoint.cpp.i

sources/UdpEndpoint.s: sources/UdpEndpoint.cpp.s

.PHONY : sources/UdpEndpoint.s

# target to generate assembly for a file
sources/UdpEndpoint.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/UdpEndpoint.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/UdpEndpoint.cpp.s
.PHONY : sources/UdpEndpoint.cpp.s

sources/client/Client.o: sources/client/Client.cpp.o

.PHONY : sources/client/Client.o

# target to build an object file
sources/client/Client.cpp.o:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/Client.cpp.o
.PHONY : sources/client/Client.cpp.o

sources/client/Client.i: sources/client/Client.cpp.i

.PHONY : sources/client/Client.i

# target to preprocess a source file
sources/client/Client.cpp.i:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/Client.cpp.i
.PHONY : sources/client/Client.cpp.i

sources/client/Client.s: sources/client/Client.cpp.s

.PHONY : sources/client/Client.s

# target to generate assembly for a file
sources/client/Client.cpp.s:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/Client.cpp.s
.PHONY : sources/client/Client.cpp.s

sources/client/ModuleCommunication.o: sources/client/ModuleCommunication.cpp.o

.PHONY : sources/client/ModuleCommunication.o

# target to build an object file
sources/client/ModuleCommunication.cpp.o:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/ModuleCommunication.cpp.o
.PHONY : sources/client/ModuleCommunication.cpp.o

sources/client/ModuleCommunication.i: sources/client/ModuleCommunication.cpp.i

.PHONY : sources/client/ModuleCommunication.i

# target to preprocess a source file
sources/client/ModuleCommunication.cpp.i:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/ModuleCommunication.cpp.i
.PHONY : sources/client/ModuleCommunication.cpp.i

sources/client/ModuleCommunication.s: sources/client/ModuleCommunication.cpp.s

.PHONY : sources/client/ModuleCommunication.s

# target to generate assembly for a file
sources/client/ModuleCommunication.cpp.s:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/ModuleCommunication.cpp.s
.PHONY : sources/client/ModuleCommunication.cpp.s

sources/client/ModuleManager.o: sources/client/ModuleManager.cpp.o

.PHONY : sources/client/ModuleManager.o

# target to build an object file
sources/client/ModuleManager.cpp.o:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/ModuleManager.cpp.o
.PHONY : sources/client/ModuleManager.cpp.o

sources/client/ModuleManager.i: sources/client/ModuleManager.cpp.i

.PHONY : sources/client/ModuleManager.i

# target to preprocess a source file
sources/client/ModuleManager.cpp.i:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/ModuleManager.cpp.i
.PHONY : sources/client/ModuleManager.cpp.i

sources/client/ModuleManager.s: sources/client/ModuleManager.cpp.s

.PHONY : sources/client/ModuleManager.s

# target to generate assembly for a file
sources/client/ModuleManager.cpp.s:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/ModuleManager.cpp.s
.PHONY : sources/client/ModuleManager.cpp.s

sources/client/main.o: sources/client/main.cpp.o

.PHONY : sources/client/main.o

# target to build an object file
sources/client/main.cpp.o:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/main.cpp.o
.PHONY : sources/client/main.cpp.o

sources/client/main.i: sources/client/main.cpp.i

.PHONY : sources/client/main.i

# target to preprocess a source file
sources/client/main.cpp.i:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/main.cpp.i
.PHONY : sources/client/main.cpp.i

sources/client/main.s: sources/client/main.cpp.s

.PHONY : sources/client/main.s

# target to generate assembly for a file
sources/client/main.cpp.s:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/client/main.cpp.s
.PHONY : sources/client/main.cpp.s

sources/client/modules/ModuleExplorer.o: sources/client/modules/ModuleExplorer.cpp.o

.PHONY : sources/client/modules/ModuleExplorer.o

# target to build an object file
sources/client/modules/ModuleExplorer.cpp.o:
	$(MAKE) -f CMakeFiles/module_explorer.dir/build.make CMakeFiles/module_explorer.dir/sources/client/modules/ModuleExplorer.cpp.o
.PHONY : sources/client/modules/ModuleExplorer.cpp.o

sources/client/modules/ModuleExplorer.i: sources/client/modules/ModuleExplorer.cpp.i

.PHONY : sources/client/modules/ModuleExplorer.i

# target to preprocess a source file
sources/client/modules/ModuleExplorer.cpp.i:
	$(MAKE) -f CMakeFiles/module_explorer.dir/build.make CMakeFiles/module_explorer.dir/sources/client/modules/ModuleExplorer.cpp.i
.PHONY : sources/client/modules/ModuleExplorer.cpp.i

sources/client/modules/ModuleExplorer.s: sources/client/modules/ModuleExplorer.cpp.s

.PHONY : sources/client/modules/ModuleExplorer.s

# target to generate assembly for a file
sources/client/modules/ModuleExplorer.cpp.s:
	$(MAKE) -f CMakeFiles/module_explorer.dir/build.make CMakeFiles/module_explorer.dir/sources/client/modules/ModuleExplorer.cpp.s
.PHONY : sources/client/modules/ModuleExplorer.cpp.s

sources/client/modules/ModuleKeyboard.o: sources/client/modules/ModuleKeyboard.cpp.o

.PHONY : sources/client/modules/ModuleKeyboard.o

# target to build an object file
sources/client/modules/ModuleKeyboard.cpp.o:
	$(MAKE) -f CMakeFiles/module_keyboard.dir/build.make CMakeFiles/module_keyboard.dir/sources/client/modules/ModuleKeyboard.cpp.o
.PHONY : sources/client/modules/ModuleKeyboard.cpp.o

sources/client/modules/ModuleKeyboard.i: sources/client/modules/ModuleKeyboard.cpp.i

.PHONY : sources/client/modules/ModuleKeyboard.i

# target to preprocess a source file
sources/client/modules/ModuleKeyboard.cpp.i:
	$(MAKE) -f CMakeFiles/module_keyboard.dir/build.make CMakeFiles/module_keyboard.dir/sources/client/modules/ModuleKeyboard.cpp.i
.PHONY : sources/client/modules/ModuleKeyboard.cpp.i

sources/client/modules/ModuleKeyboard.s: sources/client/modules/ModuleKeyboard.cpp.s

.PHONY : sources/client/modules/ModuleKeyboard.s

# target to generate assembly for a file
sources/client/modules/ModuleKeyboard.cpp.s:
	$(MAKE) -f CMakeFiles/module_keyboard.dir/build.make CMakeFiles/module_keyboard.dir/sources/client/modules/ModuleKeyboard.cpp.s
.PHONY : sources/client/modules/ModuleKeyboard.cpp.s

sources/json.o: sources/json.cpp.o

.PHONY : sources/json.o

# target to build an object file
sources/json.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/json.cpp.o
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/json.cpp.o
.PHONY : sources/json.cpp.o

sources/json.i: sources/json.cpp.i

.PHONY : sources/json.i

# target to preprocess a source file
sources/json.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/json.cpp.i
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/json.cpp.i
.PHONY : sources/json.cpp.i

sources/json.s: sources/json.cpp.s

.PHONY : sources/json.s

# target to generate assembly for a file
sources/json.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/json.cpp.s
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/json.cpp.s
.PHONY : sources/json.cpp.s

sources/server/Server.o: sources/server/Server.cpp.o

.PHONY : sources/server/Server.o

# target to build an object file
sources/server/Server.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/server/Server.cpp.o
.PHONY : sources/server/Server.cpp.o

sources/server/Server.i: sources/server/Server.cpp.i

.PHONY : sources/server/Server.i

# target to preprocess a source file
sources/server/Server.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/server/Server.cpp.i
.PHONY : sources/server/Server.cpp.i

sources/server/Server.s: sources/server/Server.cpp.s

.PHONY : sources/server/Server.s

# target to generate assembly for a file
sources/server/Server.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/server/Server.cpp.s
.PHONY : sources/server/Server.cpp.s

sources/server/https_examples.o: sources/server/https_examples.cpp.o

.PHONY : sources/server/https_examples.o

# target to build an object file
sources/server/https_examples.cpp.o:
	$(MAKE) -f CMakeFiles/http_server.dir/build.make CMakeFiles/http_server.dir/sources/server/https_examples.cpp.o
.PHONY : sources/server/https_examples.cpp.o

sources/server/https_examples.i: sources/server/https_examples.cpp.i

.PHONY : sources/server/https_examples.i

# target to preprocess a source file
sources/server/https_examples.cpp.i:
	$(MAKE) -f CMakeFiles/http_server.dir/build.make CMakeFiles/http_server.dir/sources/server/https_examples.cpp.i
.PHONY : sources/server/https_examples.cpp.i

sources/server/https_examples.s: sources/server/https_examples.cpp.s

.PHONY : sources/server/https_examples.s

# target to generate assembly for a file
sources/server/https_examples.cpp.s:
	$(MAKE) -f CMakeFiles/http_server.dir/build.make CMakeFiles/http_server.dir/sources/server/https_examples.cpp.s
.PHONY : sources/server/https_examples.cpp.s

sources/server/main.o: sources/server/main.cpp.o

.PHONY : sources/server/main.o

# target to build an object file
sources/server/main.cpp.o:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/server/main.cpp.o
.PHONY : sources/server/main.cpp.o

sources/server/main.i: sources/server/main.cpp.i

.PHONY : sources/server/main.i

# target to preprocess a source file
sources/server/main.cpp.i:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/server/main.cpp.i
.PHONY : sources/server/main.cpp.i

sources/server/main.s: sources/server/main.cpp.s

.PHONY : sources/server/main.s

# target to generate assembly for a file
sources/server/main.cpp.s:
	$(MAKE) -f CMakeFiles/spider_serveur.dir/build.make CMakeFiles/spider_serveur.dir/sources/server/main.cpp.s
.PHONY : sources/server/main.cpp.s

sources/ssl/Base64.o: sources/ssl/Base64.cpp.o

.PHONY : sources/ssl/Base64.o

# target to build an object file
sources/ssl/Base64.cpp.o:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/ssl/Base64.cpp.o
.PHONY : sources/ssl/Base64.cpp.o

sources/ssl/Base64.i: sources/ssl/Base64.cpp.i

.PHONY : sources/ssl/Base64.i

# target to preprocess a source file
sources/ssl/Base64.cpp.i:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/ssl/Base64.cpp.i
.PHONY : sources/ssl/Base64.cpp.i

sources/ssl/Base64.s: sources/ssl/Base64.cpp.s

.PHONY : sources/ssl/Base64.s

# target to generate assembly for a file
sources/ssl/Base64.cpp.s:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/ssl/Base64.cpp.s
.PHONY : sources/ssl/Base64.cpp.s

sources/ssl/CryptAES.o: sources/ssl/CryptAES.cpp.o

.PHONY : sources/ssl/CryptAES.o

# target to build an object file
sources/ssl/CryptAES.cpp.o:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/ssl/CryptAES.cpp.o
.PHONY : sources/ssl/CryptAES.cpp.o

sources/ssl/CryptAES.i: sources/ssl/CryptAES.cpp.i

.PHONY : sources/ssl/CryptAES.i

# target to preprocess a source file
sources/ssl/CryptAES.cpp.i:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/ssl/CryptAES.cpp.i
.PHONY : sources/ssl/CryptAES.cpp.i

sources/ssl/CryptAES.s: sources/ssl/CryptAES.cpp.s

.PHONY : sources/ssl/CryptAES.s

# target to generate assembly for a file
sources/ssl/CryptAES.cpp.s:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/ssl/CryptAES.cpp.s
.PHONY : sources/ssl/CryptAES.cpp.s

sources/ssl/CryptRSA.o: sources/ssl/CryptRSA.cpp.o

.PHONY : sources/ssl/CryptRSA.o

# target to build an object file
sources/ssl/CryptRSA.cpp.o:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/ssl/CryptRSA.cpp.o
.PHONY : sources/ssl/CryptRSA.cpp.o

sources/ssl/CryptRSA.i: sources/ssl/CryptRSA.cpp.i

.PHONY : sources/ssl/CryptRSA.i

# target to preprocess a source file
sources/ssl/CryptRSA.cpp.i:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/ssl/CryptRSA.cpp.i
.PHONY : sources/ssl/CryptRSA.cpp.i

sources/ssl/CryptRSA.s: sources/ssl/CryptRSA.cpp.s

.PHONY : sources/ssl/CryptRSA.s

# target to generate assembly for a file
sources/ssl/CryptRSA.cpp.s:
	$(MAKE) -f CMakeFiles/spider_client.dir/build.make CMakeFiles/spider_client.dir/sources/ssl/CryptRSA.cpp.s
.PHONY : sources/ssl/CryptRSA.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... module_keyboard"
	@echo "... spider_serveur"
	@echo "... http_server"
	@echo "... spider_client"
	@echo "... module_explorer"
	@echo "... sources/AIntervalService.o"
	@echo "... sources/AIntervalService.i"
	@echo "... sources/AIntervalService.s"
	@echo "... sources/APacketServer.o"
	@echo "... sources/APacketServer.i"
	@echo "... sources/APacketServer.s"
	@echo "... sources/AUdpServer.o"
	@echo "... sources/AUdpServer.i"
	@echo "... sources/AUdpServer.s"
	@echo "... sources/IntervalService.o"
	@echo "... sources/IntervalService.i"
	@echo "... sources/IntervalService.s"
	@echo "... sources/LocalDB.o"
	@echo "... sources/LocalDB.i"
	@echo "... sources/LocalDB.s"
	@echo "... sources/MapDB.o"
	@echo "... sources/MapDB.i"
	@echo "... sources/MapDB.s"
	@echo "... sources/MongoDB.o"
	@echo "... sources/MongoDB.i"
	@echo "... sources/MongoDB.s"
	@echo "... sources/Packet.o"
	@echo "... sources/Packet.i"
	@echo "... sources/Packet.s"
	@echo "... sources/PacketManager.o"
	@echo "... sources/PacketManager.i"
	@echo "... sources/PacketManager.s"
	@echo "... sources/UdpEndpoint.o"
	@echo "... sources/UdpEndpoint.i"
	@echo "... sources/UdpEndpoint.s"
	@echo "... sources/client/Client.o"
	@echo "... sources/client/Client.i"
	@echo "... sources/client/Client.s"
	@echo "... sources/client/ModuleCommunication.o"
	@echo "... sources/client/ModuleCommunication.i"
	@echo "... sources/client/ModuleCommunication.s"
	@echo "... sources/client/ModuleManager.o"
	@echo "... sources/client/ModuleManager.i"
	@echo "... sources/client/ModuleManager.s"
	@echo "... sources/client/main.o"
	@echo "... sources/client/main.i"
	@echo "... sources/client/main.s"
	@echo "... sources/client/modules/ModuleExplorer.o"
	@echo "... sources/client/modules/ModuleExplorer.i"
	@echo "... sources/client/modules/ModuleExplorer.s"
	@echo "... sources/client/modules/ModuleKeyboard.o"
	@echo "... sources/client/modules/ModuleKeyboard.i"
	@echo "... sources/client/modules/ModuleKeyboard.s"
	@echo "... sources/json.o"
	@echo "... sources/json.i"
	@echo "... sources/json.s"
	@echo "... sources/server/Server.o"
	@echo "... sources/server/Server.i"
	@echo "... sources/server/Server.s"
	@echo "... sources/server/https_examples.o"
	@echo "... sources/server/https_examples.i"
	@echo "... sources/server/https_examples.s"
	@echo "... sources/server/main.o"
	@echo "... sources/server/main.i"
	@echo "... sources/server/main.s"
	@echo "... sources/ssl/Base64.o"
	@echo "... sources/ssl/Base64.i"
	@echo "... sources/ssl/Base64.s"
	@echo "... sources/ssl/CryptAES.o"
	@echo "... sources/ssl/CryptAES.i"
	@echo "... sources/ssl/CryptAES.s"
	@echo "... sources/ssl/CryptRSA.o"
	@echo "... sources/ssl/CryptRSA.i"
	@echo "... sources/ssl/CryptRSA.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

