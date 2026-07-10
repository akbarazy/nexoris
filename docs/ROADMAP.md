# Nexoris: Detailed Development Roadmap (0% to 100%)

Berdasarkan arsitektur *Hybrid (OOP + ECS)* pada [nexoris_technical_document.md](file:///c:/Users/Alfarizy/Documents/Programming%20Volume%203/Projects/nexoris/docs/nexoris_technical_document.md), berikut adalah panduan eksekusi langkah demi langkah yang sangat detail untuk Anda jalankan. 

Prinsip utama roadmap ini adalah **"Engine First, Gameplay Second"**. Jangan pernah melompat membuat musuh sebelum sistem pergerakan layar (Window) Anda sempurna.

---

## Tahap 1: Fondasi Engine & Infrastruktur (0% - 15%)
*Fokus: Jangan ada entitas game dulu. Buat layar hitam yang bisa merespons input dan memuat aset.*

- [ ] **1. Setup Proyek & CMake**
  - Buat struktur folder sesuai TDD (`src/engine/`, `src/game/`, `assets/`, dll).
  - Setup `CMakeLists.txt` untuk menautkan (link) library **Raylib** dan **EnTT**.
- [ ] **2. Core Window & Game Loop (`WindowManager`)**
  - Buat `WindowManager` (Singleton/Service).
  - Buat Game Loop utama (`while (!WindowShouldClose())`).
  - Implementasikan *Resolution Independent Rendering* (Render target/Canvas) agar game 2.5D tidak *stretch* (meregang) saat di- *fullscreen* atau di- *resize*.
- [ ] **3. Sistem Input Sentral (`InputManager`)**
  - Buat `InputManager` yang membungkus fungsi input Raylib (`IsKeyPressed`, dll).
  - Petakan tombol *keyboard/gamepad* ke aksi logis (misal: `KEY_E` -> `ACTION_INTERACT`).
- [ ] **4. Manajemen Aset (`AssetManager`)**
  - Buat fungsi untuk memuat gambar (`.png`) dan suara (`.wav`/`.ogg`) ke memori.
  - Terapkan sistem *caching* (misal menggunakan `std::unordered_map`) agar *texture* yang sama tidak dimuat dua kali ke VRAM.
- [ ] **5. Event Bus (`EventManager`)**
  - Implementasikan *Observer Pattern*.
  - Buat sistem agar bagian kode manapun bisa melakukan `Subscribe` ke sebuah event (contoh: `OnWindowResize`) dan melakukan `Publish` event.

> [!IMPORTANT]
> **Checklist Validasi Tahap 1:** Anda memiliki jendela kosong. Jika Anda menekan tombol 'Spasi', konsol mencetak "Spasi ditekan" (lewat EventManager), dan sebuah gambar contoh berhasil di-render di tengah layar tanpa bocor memori (Memory Leak).

---

## Tahap 2: Integrasi ECS & Rendering Dasar (15% - 30%)
*Fokus: Menghubungkan EnTT dengan Raylib untuk mulai menggambar sesuatu di layar menggunakan arsitektur data murni.*

- [ ] **1. Setup EnTT Registry**
  - Buat instansiasi `entt::registry` yang akan menyimpan seluruh entitas di *Scene* aktif.
- [ ] **2. Definisi Komponen Dasar (`components/`)**
  - Buat struct `Transform` (x, y, z-index).
  - Buat struct `Renderable` (pointer ke texture di AssetManager, source rect untuk animasi).
- [ ] **3. Render System (`RenderSystem`)**
  - Buat sistem yang me- *loop* semua entitas yang memiliki `Transform` dan `Renderable`.
  - **Krusial:** Implementasikan **Y-Sorting** (Z-Sorting). Urutkan (sort) entitas berdasarkan nilai `Transform.y` dari terkecil ke terbesar sebelum fungsi `DrawTexture` dipanggil. Ini wajib untuk perspektif 2.5D Top-down!
- [ ] **4. Kamera Cerdas (`CameraSystem`)**
  - Buat sistem kamera yang mengikuti suatu target (Entitas Pemain) dengan efek *lerp* (pergerakan halus, tidak kaku).

---

## Tahap 3: Pemain, Pergerakan & Dunia (Hub World Dasar) (30% - 50%)
*Fokus: Karakter bisa berjalan di lingkungan dan menabrak tembok.*

- [ ] **1. Factory Pattern untuk Entitas**
  - Buat `EntityFactory::CreatePlayer(registry, x, y)` untuk men- *spawn* pemain dengan komponen lengkap.
- [ ] **2. Sistem Pergerakan (`MovementSystem` & `PlayerControlSystem`)**
  - Buat `PlayerInput` component.
  - `PlayerControlSystem` membaca `InputManager` dan mengubah target kecepatan (*velocity*) di komponen `Transform`.
  - `MovementSystem` mengeksekusi perpindahan posisi.
- [ ] **3. Animasi Dasar (`AnimationSystem`)**
  - Buat komponen `Animator`. Ubah *source rect* pada `Renderable` berdasarkan *timer* dan status pergerakan (diam/berjalan).
- [ ] **4. Sistem Tabrakan / Fisika Solid (`CollisionSystem`)**
  - Buat komponen `Collider` (AABB - Axis-Aligned Bounding Box).
  - Muat peta sederhana (bisa dari array 2D atau tilemap ringan).
  - Buat logika agar *Collider* pemain tidak bisa melewati *Collider* tembok (Sliding collision, agar jika menabrak sudut, pemain tetap meluncur maju).

---

## Tahap 4: UI, Interaksi & Data Eksternal (50% - 70%)
*Fokus: Membangun sistem yang memungkinkan pemain berbicara dengan NPC atau membuka peti (Fondasi Hub World).*

- [ ] **1. Komponen Interaksi (`Interactable`)**
  - Buat komponen `Interactable` dengan radius deteksi dan tipe interaksi (NPC, Chest, Anvil).
- [ ] **2. Sistem UI Dasar (`UIManager`)**
  - Buat *manager* (OOP) untuk menggambar teks dan panel UI. UI tidak boleh di- *render* sebagai entitas ECS (agar tidak terkena Y-Sorting kamera).
- [ ] **3. Sistem Interaksi Lintas Layer (`InteractionSystem`)**
  - Jika pemain menekan tombol aksi (E/F) di dekat `Interactable`, kirim event lewat `EventManager` (misal: `Event_OpenUI_Blacksmith`).
  - `UIManager` menangkap event tersebut, mem- *pause* ECS (menghentikan pergerakan), dan memunculkan jendela UI.
- [ ] **4. Arsitektur Data JSON (Persiapan Item)**
  - Gunakan *library* JSON (seperti `nlohmann/json`).
  - Buat sistem untuk mem- *parsing* `items.json` ke dalam memori komputer saat *loading screen*.

---

## Tahap 5: Core Combat (Dungeon) (70% - 85%)
*Fokus: Sistem pertarungan, nyawa, musuh, dan perpindahan antar *scene* (Hub -> Dungeon).*

- [ ] **1. Scene Management Lanjutan (`SceneManager`)**
  - Buat sistem transisi aman. Saat pindah dari `HubWorldScene` ke `DungeonScene`, bersihkan (`clear`) EnTT registry, muat peta baru, dan ciptakan ulang Entitas Pemain di pintu masuk dungeon.
- [ ] **2. Atribut RPG Dasar**
  - Buat komponen `Health`, `Stats` (Damage, Defense).
  - Buat UI untuk merender Bar HP Pemain.
- [ ] **3. Logika Menyerang (Melee & Ranged)**
  - Melee: Saat tombol serang ditekan, ciptakan Entitas tak terlihat (*Hitbox/DamageBox*) di depan pemain selama 0.2 detik.
  - Ranged: Ciptakan Entitas `Projectile` yang bergerak maju secara lurus. **(Gunakan Object Pooling jika bisa).**
- [ ] **4. Musuh & AI Dasar (`AIController`)**
  - Ciptakan *EnemyFactory*. Buat *State Machine* sederhana di komponen musuh (IDLE, CHASE, ATTACK).
- [ ] **5. Sistem Resolusi Tempur (`CombatSystem`)**
  - Cek benturan (*collision*) antara `DamageBox`/`Projectile` dengan `Collider` musuh/pemain.
  - Kurangi `Health` berdasarkan `Stats` penyerang dan korban. Tambahkan efek *knockback* dan *Invincibility Frames* (berkedip putih selama 0.5 detik).

> [!CAUTION]
> **Hindari Bug ECS di sini:** Jangan panggil fungsi hancurkan entitas (`registry.destroy()`) tepat saat Anda sedang melakukan iterasi (looping) pada *registry* tersebut. Tandai entitas dengan komponen `Dead/Destroyed` terlebih dahulu, lalu hancurkan di akhir *frame* pada sistem terpisah (`CleanupSystem`).

---

## Tahap 6: Ekosistem RPG (Progression & Item) (85% - 95%)
*Fokus: Menggabungkan pertempuran dengan siklus ekonomi game (Loot, Leveling, Repair).*

- [ ] **1. Sistem Inventory & Loot**
  - Jika musuh `Dead`, ciptakan entitas `Loot Drop` di lokasinya.
  - Buat pemain bisa mengambil *loot* untuk dimasukkan ke komponen `Inventory`.
- [ ] **2. Equipment & Durability**
  - Buat sistem agar pemain bisa memasang senjata dari `Inventory` ke slot *Equipment*. Senjata ini akan mengubah nilai komponen `Stats` pemain.
  - Integrasikan ke `CombatSystem`: Setiap kali pemain berhasil memukul musuh, kurangi nilai `Durability` senjata tersebut.
- [ ] **3. Role Progression System**
  - Hitung jenis serangan yang mengenai musuh. Jika memakai pedang, tambah nilai di `ExpFighter`. Jika naik level, tingkatkan HP/Damage dasar.
- [ ] **4. Mekanik Hub (Crafting & Repair)**
  - Tulis logika untuk `UIManager` di Hub World agar bisa membaca resep dari data JSON, mengecek isi `Inventory` pemain, dan menukar material menjadi item baru.

---

## Tahap 7: Polishing, Save System & Rilis (95% - 100%)
*Fokus: Membuat game terasa "nyaman" dimainkan dan menyimpan data (Save/Load).*

- [ ] **1. Sistem Save & Load (`SaveLoadManager`)**
  - Serialisasi komponen Pemain (Level, EXP, isi Inventory, Equipment yang sedang dipakai) ke dalam format file `.json` atau `.dat` di folder lokal (*AppData/Documents*).
- [ ] **2. Game Feel & Juiciness**
  - Tambahkan efek *Screen Shake* (kamera bergetar) saat terjadi *Critical Hit* atau saat pemain terkena serangan.
  - Tambahkan entitas *Particle Emitter* (darah, percikan api).
  - Tambahkan *Audio Spatial* / sfx untuk langkah kaki, ayunan senjata, dan UI hover.
- [ ] **3. Debugging & Profiling**
  - Pastikan memori (RAM/VRAM) tidak membesar seiring waktu.
  - Pastikan FPS stabil saat ada ratusan peluru di layar.
- [ ] **4. Build Final**
  - Matikan semua pesan console *debug*.
  - *Compile Release Build* menggunakan CMake.

---

### Saran Eksekusi Cepat:
Saat mulai koding pertama kali besok, buka `src/main.cpp`, panggil `InitWindow()` dari Raylib, buat loop kosong, lalu *commit* ke Git. Mulailah mencentang **Tahap 1, Poin 1 & 2**!
