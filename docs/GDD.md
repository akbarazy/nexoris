# Nexoris: Game Design Document (GDD)

Dokumen ini berfokus secara eksklusif pada penjabaran fitur, mekanik, konten, dan pengalaman bermain (Gameplay) dari Nexoris.

## 1. Core Gameplay Loop
Siklus permainan utama yang akan dilakukan pemain berulang-ulang untuk mencapai progresi:
1. **Lobby/Hub World**: Pemain berinteraksi dengan NPC, mengatur inventory, dan memperbaiki senjata.
2. **Dungeon Run**: Pemain memasuki dungeon, melawan rentetan monster biasa, dan diakhiri dengan Boss Fight.
3. **Loot & Extraction**: Mengumpulkan material (*drops*) dan koin dari musuh yang dikalahkan.
4. **Craft & Upgrade**: Kembali ke Hub World untuk merakit perlengkapan dengan *tier* (tingkatan) yang lebih tinggi.
5. Mengulang siklus untuk menantang dungeon yang lebih sulit.

## 2. Mekanik Permainan Inti
- **Pertarungan Real-Time (Action-Combat)**: Berfokus pada pergerakan dinamis, penggunaan *dodge* (menghindar), dan membidik serangan (proyektil/area).
- **Progresi Berbasis Perlengkapan (Gear-based)**: Pemain tidak memiliki atribut stat dasar (seperti *Strength* atau *Agility* bawaan). 100% *Damage*, *Health*, dan *Defense* berasal dari senjata dan armor yang sedang dikenakan.
- **Sistem Tanpa Kelas (Classless & Destiny Board)**: Tidak ada pemilihan *Class* di awal permainan. Terdapat 3 "Role" (Fighter, Marksman, Mage). Jika pemain terus menggunakan pedang (Fighter), maka *Fighter EXP* akan bertambah. Level Fighter yang tinggi menjadi syarat untuk mengenakan pedang/armor tipe berat (*Heavy*) yang ber-tier tinggi.
- **Sistem Durabilitas**: Senjata dan armor memiliki titik keausan (*Durability*). Item tidak hancur menghilang, tetapi stat-nya akan menurun drastis saat aus dan wajib diperbaiki di fasilitas *Blacksmith*.

## 3. Fitur Kosmetik (Skin System)
Pemain dapat memakai "Skin" yang akan menggantikan visual atau *sprite* karakter secara utuh. Sistem ini berjalan terpisah dari *Equipment*, sehingga pemain tetap dapat terlihat epik tanpa harus memedulikan armor asli (yang mungkin bentuknya jelek namun stat-nya tinggi) yang sedang bersembunyi di baliknya.

## 4. Entitas & Interaksi Dunia
- **Player**: Avatar aksi, hanya dikustomisasi berdasarkan *gender* (Pria/Wanita).
- **Monster Biasa**: Makhluk dungeon dengan ragam perilaku AI (Pengejar, Penembak, Penghindar).
- **Boss**: Musuh raksasa dengan Health Bar tebal, memiliki fase pergantian serangan, dan *Loot Table* eksklusif.
- **Fasilitas (NPC/Objek)**: *Blacksmith* (Repair), *Crafting Table* (Merakit senjata/armor baru), *Chest* (Penyimpanan), dan *Portal* (Navigasi dungeon).

## 5. Database Konten Utama
### A. Kategori Senjata
- **Fighter (Melee)**: Pedang Pendek (cepat), Pedang Besar (lambat, *burst damage*), Palu (*stun*).
- **Marksman (Ranged)**: Busur (jarak jauh), Crossbow (cepat, *reload* jeda), Pisau Lempar (area sebar).
- **Mage (Magic)**: Tongkat Sihir (elemen proyektil), Buku Mantra (area efek).

### B. Kategori Armor (Tiga Slot: Kepala, Badan, Kaki)
- **Heavy Armor**: Stat *Defense* tinggi, cocok untuk Fighter.
- **Leather/Medium**: Keseimbangan *Defense* & bonus *Movement*, cocok untuk Marksman.
- **Cloth/Robe**: *Defense* rendah, bonus regenerasi/mana, cocok untuk Mage.

### C. Konsumsi & Material
- **Material Crafting**: Gigi Monster, Kulit Serigala, Inti Sihir, Besi Rongsokan, Kristal Bos.
- **Potion Bertingkat**: Minor/Major Health, Mana Potion, Stamina Potion.

### D. Sistem Kelangkaan Item (Rarity)
Menentukan stat pengali (*stat multiplier*), harga jual, dan kemungkinan mendapatkan efek khusus/pasif tambahan:
1. **Common** (Abu-abu)
2. **Uncommon** (Hijau)
3. **Rare** (Biru)
4. **Epic** (Ungu)
5. **Legendary** (Emas Oranye)
6. **Mythic** (Merah Bercahaya)
7. **Celestial** (Biru Muda Bercahaya / Cyan)
8. **Divine** (Putih Terang / Emas Putih)

### E. Tingkat Kesulitan Dungeon (Difficulty)
Menentukan pengali HP/Damage musuh, kepadatan musuh, serta kualitas jaminan barang jatuh (*Loot Table guarantee*):
1. **Easy**
2. **Normal**
3. **Hard**
4. **Expert**
5. **Extreme**
6. **Insane**
7. **Nightmare**
8. **Extinction**
