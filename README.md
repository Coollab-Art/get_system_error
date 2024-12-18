# get_system_error

## Including

To add this library to your project, simply add these two lines to your *CMakeLists.txt*:
```cmake
add_subdirectory(path/to/get_system_error)
target_link_libraries(${PROJECT_NAME} PRIVATE Cool::get_system_error)
```

Then include it as:
```cpp
#include "Cool/get_system_error.hpp"
```

## Running the tests

Simply use "tests/CMakeLists.txt" to generate a project, then run it.<br/>
If you are using VSCode and the CMake extension, this project already contains a *.vscode/settings.json* that will use the right CMakeLists.txt automatically.
