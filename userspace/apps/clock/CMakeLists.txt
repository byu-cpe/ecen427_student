add_executable(clock clock.cpp)
target_link_libraries(clock intc buttons switches)
deploy_to_board(clock)