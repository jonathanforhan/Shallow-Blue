add_library("Engine" SHARED engine.cpp
                            game.cpp
                            fen.cpp
                            )

target_include_directories("Engine" PUBLIC ".")
