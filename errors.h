#pragma once


enum class eError {
    OK,
    UnsupportedROM,
};

inline const char* GetErrorContext(const eError error) {
    switch (error) {
        case eError::OK:
            return nullptr;
        case eError::UnsupportedROM:
            return "This ROM is likely either malformed, missing an NES2.0 header, has externally modified code or is an unsupported translation";
    }

    return "Error Context Fetching failed";
}