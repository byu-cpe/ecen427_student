add_executable(leds_test leds_test.cpp)
target_link_libraries(leds_test buttons switches leds)
deploy_to_board(leds_test)
