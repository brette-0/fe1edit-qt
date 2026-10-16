#include "game.h"


eError Game::Parse(const QByteArray &_rom, const eTranslation _translation) {
    rom         = _rom;
    translation = _translation;
    eError err;
    if (err = ParseMapData(); err != eError::OK) return err;    // needs known offset
    if (!attributes.nMaps) return eError::UnsupportedROM;      // cannot have 0 maps
    return err;
}

eError Game::ParseMapData() {
    // locate the value of final level (rodata) -> attribs
    const auto offset = GetMapCount();
    if (!offset) return eError::UnsupportedROM;
    attributes.nMaps = static_cast<unsigned char>(rom.at(offset));
    return eError::OK;
}

int Game::GetMapCount() {
    switch (translation) {
        case eTranslation::JAPANESE:
            return 0x0da7a;
        case eTranslation::ENGLISH:
            goto Default;
        case eTranslation::SPANISH:
            goto Default;
        case eTranslation::ITALIAN:
            goto Default;
        case eTranslation::ARABIC:
            goto Default;

        Default:
        default:
            return 0;
            break;
    }
}