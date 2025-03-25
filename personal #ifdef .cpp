// в CMakeLists.txt
add_definitions(-DYOUR_DEFINE_VARIABLE=1)

// Теперь в main.cpp можно писать
#ifdef YOUR_DEFINE_VARIABLE
    ...
#endif
