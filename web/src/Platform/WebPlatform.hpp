#pragma once

#ifdef __EMSCRIPTEN__

#include <emscripten.h>
#include <string>

namespace casioemu {
namespace web {

inline void InitFilesystem() {
    EM_ASM({
        try {
            FS.mkdir('/working');
        } catch(e) {}
        try {
            FS.mount(IDBFS, {}, '/working');
        } catch(e) {}
        Module.syncdone = 0;
        FS.syncfs(true, function(err) {
            if (err) console.error('FS sync error:', err);
            Module.syncdone = 1;
        });
    });
}

inline void SyncFilesystem() {
    EM_ASM({
        FS.syncfs(false, function(err) {
            if (err) console.error('FS save error:', err);
        });
    });
}

inline void Vibrate(int milliseconds) {
    EM_ASM({ CasioEmuBridge.vibrate($0); }, milliseconds);
}

inline void TriggerFileUpload() {
    EM_ASM({ CasioEmuBridge.uploadFile(); });
}

inline void TriggerFolderUpload() {
    EM_ASM({ CasioEmuBridge.uploadFolder(); });
}

} // namespace web
} // namespace casioemu

#endif // __EMSCRIPTEN__

