TEMPLATE = app
QT = gui core phonon sql
CONFIG += qt warn_on console release
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/player.ui
HEADERS = src/player.h src/database.h 
SOURCES = src/player.cpp src/database.cpp  src/main.cpp
