#include <emscripten.h>
#include <cstdint>
#include <string>

extern "C" {

// web_onFileSelected is defined in SysDialog.cpp under #ifdef __EMSCRIPTEN__

EMSCRIPTEN_KEEPALIVE
void web_triggerDownload(const char* filename, const uint8_t* data, int size) {
    EM_ASM({
        const name = UTF8ToString($0);
        const bytes = HEAPU8.slice($1, $1 + $2);
        CasioEmuBridge.downloadFile(name, bytes);
    }, filename, data, size);
}

EMSCRIPTEN_KEEPALIVE
void web_triggerVibrate(int ms) {
    EM_ASM({ CasioEmuBridge.vibrate($0); }, ms);
}

}

