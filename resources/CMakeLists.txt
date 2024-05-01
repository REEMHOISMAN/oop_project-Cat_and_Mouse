# ---- playlist and level files ----
configure_file ("Playlist.txt" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Level001.txt" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Level002.txt" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("Level003.txt" ${CMAKE_BINARY_DIR} COPYONLY)

# ---- backgrounds ----
configure_file ("background.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("menu.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("help1.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("help2.png" ${CMAKE_BINARY_DIR} COPYONLY) #there is two pages of help.
configure_file ("InfoBoard.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("gameOver.png" ${CMAKE_BINARY_DIR} COPYONLY)

# ---- game objects png ----
configure_file ("wall.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("mouse.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("cat.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("life.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("cheese.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("key.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("door.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("timer.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("popCat.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("freeze.png" ${CMAKE_BINARY_DIR} COPYONLY)

# ---- buttons ----
configure_file ("exit.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("newGame.png" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("help.png" ${CMAKE_BINARY_DIR} COPYONLY)

# ---- backgrounds music ----
configure_file ("music.ogg" ${CMAKE_BINARY_DIR} COPYONLY)

# ---- sounds ----
configure_file ("lostLife.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("freeze.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("levelPassed.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("lifeSound.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("door.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("key.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("eatCheese.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("popCat.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("time.ogg" ${CMAKE_BINARY_DIR} COPYONLY)
configure_file ("button.ogg" ${CMAKE_BINARY_DIR} COPYONLY)

# ---- font ----
configure_file ("ghostclan.ttf" ${CMAKE_BINARY_DIR} COPYONLY)