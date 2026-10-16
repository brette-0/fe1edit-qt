#include "game.h"


Game::Game(const QByteArray &rom, const eTranslation translation) {
    this->rom = rom;
    this->translation = translation;
}
