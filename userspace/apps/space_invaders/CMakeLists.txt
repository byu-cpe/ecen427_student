include_directories(.)

add_library(space_invaders_graphics
    Graphics.cpp
    Sprites.cpp
    Sprite.cpp
    resources/sprites.c
)

add_executable(space_invaders 
    main.cpp

    Globals.cpp
    Score.cpp
    Lives.cpp

    GameObject.cpp

    Gameplay.cpp
    Bunker.cpp
    Bunkers.cpp
    BunkerBlock.cpp
    Tank.cpp
    UFO.cpp
    
    Bullets.cpp
    Bullet.cpp

    Aliens.cpp
    Alien.cpp

    HighScores.cpp
)


target_link_libraries(space_invaders space_invaders_graphics buttons switches intc audio_config)
deploy_to_board(space_invaders)