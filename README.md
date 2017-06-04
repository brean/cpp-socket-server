# cpp-server-template
configurable C/C++ multi-threaded socket server template for Unix-based systems with logging as basis for different projects to get data from different clients and process it directly in C/C++

Use this template to create your own server.

# used libaries
This project needs
 * POSIX Threads for threading (aka pthread, provided by glibc, included in Unix-Systems)
 * [Boost.Log](https://github.com/boostorg/log) for logging
 * [yaml-cpp](https://github.com/jbeder/yaml-cpp/) for configuration

# requirements installation
For fedora:
```
# dnf install glibc-devel boost-devel yaml-cpp-devel
```

# compile and run demo
This project uses [CMake](https://cmake.org/) for compilation. Just run
```
$ cmake CMakeList.txt
```

to create all files required for compiling, then run make to compile

```
$ make
```

you can now compile and start one of the example servers (e.g. the broadcast server):

```
$ cd examples/broadcast
$ cmake CMakeList.txt && make
$ cd -
$ ./examples/broadcast/broadcast
```

Thison example accepts connections from port 7000 (configured in the config.yml). Take a look at the example clients(TODO!) or connect using telnet:
```
$ telnet localhots 7000
```

# configuration
If you like to change the port or adress the server is listening on just change the config.yml-file in the main folder.

# example projects
(TODO)
