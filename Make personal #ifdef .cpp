// Перейти в Clion:  Settings -> Build, Execution, Deployment -> CMake.

// Написать в "CMake options":  -DYOUR_DEFINE_VARIABLE=1

// Добавить в файл CMakeLists.txt своего проекта:
if (YOUR_DEFINE_VARIABLE)
    add_definitions(-DYOUR_DEFINE_VARIABLE=1)
endif (YOUR_DEFINE_VARIABLE)
