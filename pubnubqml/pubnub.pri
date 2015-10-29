HEADERS += pubnub_qt.h
SOURCES += pubnub_qt.cpp \
    $$PWD/../c-core/core/pubnub_ccore.c \
    $$PWD/../c-core/core/pubnub_assert_std.c \
    $$PWD/../c-core/core/pubnub_json_parse.c \
    $$PWD/../c-core/core/pubnub_helper.c

INCLUDEPATH += $$PWD/../c-core/core
DEPENDPATH += $$PWD/../c-core/core
