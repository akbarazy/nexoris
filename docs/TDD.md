# Nexoris: Technical Design Document (TDD)

Dokumen ini menjabarkan implementasi teknis tingkat rendah, struktur kode, algoritma, struktur data, dan arsitektur *software* yang menggerakkan Nexoris (dibangun menggunakan C++ dan Raylib).

## 1. Arsitektur Inti: Hybrid (OOP + ECS)
Engine Nexoris memisahkan manajemen lapis bawah dan logika *gameplay* menggunakan dua paradigma yang berbeda untuk mencapai performa (*cache locality*) dan skalabilitas maksimum.

### A. Layer Engine (OOP & Singleton)
Manajer global yang berumur sepanjang game berjalan. Berinteraksi dengan *hardware* (I/O) dan memori.
- **AssetManager**: Menyimpan *hash map* (*unordered_map*) dari tekstur, font, dan audio. Menggunakan prinsip *flyweight* untuk mencegah duplikasi resource.
- **WindowManager & UIManager**: Menangani kanvas *rendering* dengan algoritma *Resolution Scaling* independen untuk menjaga *aspect ratio* 2.5D.
- **InputManager**: Mengonversi kode tombol *hardware* menjadi struktur data *Event Aksi* abstrak.
- **SaveLoadManager**: Melakukan serialisasi dan deserialisasi struktur data *inventory/stats* menggunakan *library* `nlohmann/json`.
- **EventManager (Event Bus)**: Implementasi *Observer Pattern* untuk dekopel (*decoupling*) komunikasi sistem (misal: UI merespons perubahan stat dari *Gameplay* tanpa ketergantungan langsung).

### B. Layer Gameplay (Entity-Component-System murni via EnTT)
Menggunakan struktur data *SoA (Structure of Arrays)* yang disediakan oleh *library* `EnTT` (atau yang dikustomisasi).
- **Entity**: Hanya sebuah angka *integer* berukuran 32-bit (ID mask).
- **Component**: Struktur data *Plain Old Data (POD)* tanpa *method* atau fungsi logika (sepenuhnya dikemas dalam memori berdekatan / *contiguous memory*).
- **System**: Fungsi iterasi berkinerja tinggi yang memproses tupel (*tuple*) komponen per *frame*.

## 2. Struktur Data Komponen ECS (Logika Dunia)
- `Transform`: `{ float x, y; float z_index; float rotation; }`
- `Collider`: `{ float width, height; enum Type { SOLID, TRIGGER }; }`
- `Health`: `{ int current, max; float invincibility_timer; }`
- `Equipment`: `{ int weaponID, armorID, skinID; }` (Hanya referensi ID menuju data statis di JSON)
- `RoleProgression`: `{ int fighterExp, marksmanExp, mageExp; }`
- `Durability`: `{ int current, max; }`

## 3. Desain Sistem & Algoritma Inti
- **Y-Sorting Rendering (RenderSystem)**: Menggunakan algoritma pengurutan (`std::sort`) pada array/vektor komponen `Transform` berdasarkan nilai kordinat `y`. Entitas dengan `y` terkecil digambar lebih dulu (berada di belakang), menciptakan ilusi ruang 3D pada grafik 2D.
- **Spatial Partitioning (CollisionSystem)**: Untuk menghindari komputasi fisik O(N^2) dari benturan proyektil dan karakter, sistem menggunakan struktur data *Quadtree* atau *Spatial Grid Hashing* agar pengecekan deteksi tabrakan (*AABB - Axis-Aligned Bounding Box*) hanya terjadi pada entitas yang berdekatan.
- **Object Pooling**: Untuk *proyektil*, mencegah alokasi (`new`) dan dealokasi (`delete`) memori dinamis terus-menerus. Array tetap dialokasikan sejak awal; saat tertembak, entitas peluru hanya diubah status *flag*-nya menjadi aktif.
- **Finite State Machine (FSM)**: Digunakan pada `AIController` untuk transisi status musuh: `PATROL` -> `CHASE` -> `ATTACK` berdasarkan kalkulasi algoritma vektor jarak (*Distance Vector*).

## 4. Struktur Folder (Direktori Proyek)
```text
Nexoris/
├── src/
│   ├── engine/       # Manajer I/O, Resource (Singleton/OOP)
│   ├── game/         # Komponen, Sistem ECS, Entitas
│   ├── core/         # Struktur data utilitas abstrak, Event Bus
│   └── data/         # File JSON parser
├── include/          # File header proyek
├── assets/           # File biner (.png, .wav, .json)
└── CMakeLists.txt
```

## 5. Standar dan Aturan Kode (Anti-Patterns)
- **Jangan Hardcode Logika Konten**: Dilarang meletakkan *damage* senjata di dalam kode `.cpp`. Semua nilai harus diload dari `assets/data/items.json`.
- **Tidak Boleh Memiliki "Class Player"**: Jangan mewariskan `Entity` ke `Player`. Player hanya sebuah ID entitas yang dipasangi komponen `PlayerInput` dan dikontrol oleh `PlayerControlSystem`.
- **Pemisahan UI dan Game**: `CombatSystem` dilarang memanggil fungsi *DrawText*. Ia hanya boleh mengurangkan komponen `Health`, sementara `UIManager` membaca nilai tersebut secara terpisah.