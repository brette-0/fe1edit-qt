#pragma once

#include <qbytearray.h>
#include <QtEndian>

#include "errors.h"

class Game {
public:
    struct Attributes {
        int nMaps;
    };

    enum class eTranslation {
        JAPANESE,
        ENGLISH,
        SPANISH,
        ITALIAN,
        ARABIC
    };

    static eError Parse(const QByteArray &_rom, eTranslation _translation);


private:
    static eError               ParseMapData();
    [[nodiscard]]
    static int                  GetMapCount();
    static inline auto          translation = eTranslation::JAPANESE;
    static inline QByteArray    rom{ };
    static inline Attributes    attributes{ };
};