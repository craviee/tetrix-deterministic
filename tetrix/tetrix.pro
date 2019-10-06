QT += widgets
CONFIG += c++17

HEADERS       = tetrixboard.h \
                tetrixanalyzer.h \
                tetrixmoviment.h \
                tetrixpiece.h \
                tetrixwindow.h
SOURCES       = main.cpp \
                tetrixanalyzer.cpp \
                tetrixboard.cpp \
                tetrixpiece.cpp \
                tetrixwindow.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/tetrix
INSTALLS += target
