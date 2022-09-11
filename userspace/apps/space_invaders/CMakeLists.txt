include_directories(.)

add_executable(space_invaders 
    main.cpp

    Globals.cpp
    Score.cpp
    Lives.cpp

    Graphics.cpp
    Sprite.cpp
    Sprites.cpp
    resources/sprites.c

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


target_link_libraries(space_invaders buttons switches intc audio_config)
