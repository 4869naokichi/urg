add_executable(test test.cpp)
find_package(Python3 COMPONENTS Development NumPy)
target_include_directories(test PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS} ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(test urg speak Python3::Python Python3::NumPy)