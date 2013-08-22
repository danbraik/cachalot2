TEMPLATE = app
#CONFIG += console
#CONFIG -= qt

# debug
#LIBS += -L/usr/local/lib/ -lsfml-graphics-d -lsfml-window-d -lsfml-audio-d -lsfml-system-d
# release
LIBS += -L/usr/local/lib/ -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system

SOURCES += main.cpp \
    AnimatedLabel.cpp \
    Button.cpp \
    Slider.cpp \
    MusicPlayer.cpp \
    Label.cpp \
    History.cpp

HEADERS += \
    AnimatedLabel.hpp \
    Button.hpp \
    Slider.hpp \
    MusicPlayer.hpp \
    Label.hpp \
    History.hpp
