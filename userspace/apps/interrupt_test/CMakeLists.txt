add_executable(interrupt_test main.cpp)
target_link_libraries(interrupt_test buttons switches intc)
deploy_to_board(interrupt_test)
