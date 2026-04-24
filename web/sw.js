const CACHE_VERSION = 'v1';
const CACHE_NAME = `casioemu-${CACHE_VERSION}`;

const ASSETS = [
    '/',
    '/index.html',
    '/casioemu_web.js',
    '/casioemu_web.wasm',
    '/manifest.json'
];

self.addEventListener('install', (e) => {
    e.waitUntil(caches.open(CACHE_NAME).then(cache => cache.addAll(ASSETS)));
});

self.addEventListener('fetch', (e) => {
    e.respondWith(caches.match(e.request).then(response => {
        return response || fetch(e.request);
    }));
});

self.addEventListener('activate', (e) => {
    e.waitUntil(
        caches.keys().then(cacheNames => {
            return Promise.all(
                cacheNames.filter(name => name !== CACHE_NAME)
                    .map(name => caches.delete(name))
            );
        })
    );
});

