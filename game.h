#pragma once

#include "errors.h"

class Game {
    enum class eTranslation {
        JAPANESE,
        ENGLISH
    };

public:
     eError ParseConfig();

private:
    eTranslation translation = eTranslation::JAPANESE;
};