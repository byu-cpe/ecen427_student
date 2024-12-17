add_executable(int_rate int_rate.cpp)
target_link_libraries(int_rate intc)
deploy_to_board(int_rate)