# Drivers

Each control type gets its own driver: a `.h` file and a `.c` file with the same name. `led.h` and `led.c` are the example to follow, and `examples/led_example` shows them being used from `main`.


## Using a driver in a project

Add the `.c` file to `add_executable` and the `drivers` folder to `target_include_directories` in your `CMakeLists.txt`. `examples/led_example/CMakeLists.txt` shows how.
