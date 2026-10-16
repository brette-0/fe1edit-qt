#pragma once

#include <qbytearray.h>

#include "errors.h"

class Game {
public:
    enum class eTranslation {
        JAPANESE,
        ENGLISH,
        SPANISH,
        ITALIAN,
        ARABIC
    };

    Game(const QByteArray &rom, eTranslation translation);

private:
    eTranslation translation;
    QByteArray rom;
};