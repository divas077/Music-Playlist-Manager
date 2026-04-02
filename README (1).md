# 🎵 Music Playlist Manager

A terminal-based music playlist manager written in **C++**, built using a **Doubly Linked List** data structure. Supports song insertion, deletion, search, bidirectional navigation, and shuffle — all without using STL containers.

---

## 📋 Features

| Feature | Description |
|---|---|
| ➕ Add Song | Insert a song at the end of the playlist |
| ❌ Delete by ID | Remove a song using its unique ID |
| ❌ Delete by Name | Remove a song using its title |
| 🔍 Search | Find a song by name — O(n) time complexity |
| ▶️ Play Next | Navigate forward through the playlist |
| ◀️ Play Previous | Navigate backward through the playlist |
| 🔀 Shuffle | Reorder songs using pointer manipulation (no secondary data structure) |
| 📋 Display All | Print every song with the currently playing song highlighted |

---

## 🗂️ Data Structure

The playlist is implemented as a **Doubly Linked List**, where each node (`Song`) holds:

```
[ prev ] ← [ id | name | artist ] → [ next ]
```

- `head` — points to the first song  
- `tail` — points to the last song  
- `current` — tracks the song currently "playing"

This allows **O(1)** forward and backward navigation without an array or index.

---

## 🚀 Getting Started

### Prerequisites

- A C++ compiler (g++ recommended)
- C++11 or later

### Compile

```bash
g++ music_playlist.cpp -o playlist
```

### Run

```bash
./playlist
```

On Windows:
```bash
playlist.exe
```

---

## 🖥️ Usage

When you run the program, a menu is shown:

```
====== Music Playlist Manager ======
1. Display all songs
2. Add a song
3. Delete song by ID
4. Delete song by Name
5. Search by Name
6. Play Next
7. Play Previous
8. Show Current Song
9. Shuffle Playlist
0. Exit
```

The playlist comes pre-loaded with 5 songs so you can test immediately.  
The `>>` marker in the display shows which song is currently selected.

---

## 🧠 Key Concepts Used

### Doubly Linked List
Each `Song` node has a `prev` and `next` pointer, enabling navigation in both directions — no index or array needed.

### Manual Memory Management
Every `new Song(...)` is paired with a `delete` call. The destructor frees all nodes when the playlist goes out of scope, preventing memory leaks.

### Shuffle (Fisher-Yates)
The shuffle swaps song **data** (id, name, artist) in-place across nodes using a temporary pointer array for indexing. The linked list structure itself is never duplicated or rebuilt.

### Search — O(n)
Search and deletion scan the list from `head` to `tail`, stopping at the first match.

---

## 📁 File Structure

```
music_playlist.cpp    ← All source code (single file)
README.md             ← This file
```

---

## 🔧 Can It Play Actual Audio?

Not in the current version — it manages song metadata only. To add real audio playback, you could:

- **Easy:** Use `system("afplay song.mp3")` (macOS) or `system("start song.mp3")` (Windows) to call your OS media player
- **Better:** Integrate a library like [SFML](https://www.sfml-dev.org/) (`sf::Music`) or [miniaudio](https://miniaud.io/) for in-program playback

This would require storing a file path in each `Song` node and triggering playback when `current` changes.

---

## 📌 Complexity Summary

| Operation | Time Complexity |
|---|---|
| Add song | O(1) |
| Delete by ID / Name | O(n) |
| Search by Name | O(n) |
| Play Next / Prev | O(1) |
| Shuffle | O(n) |
| Display all | O(n) |

---

## 👤 Author

Built as a Data Structures project in C++.  
Feel free to fork, extend, or use as a learning reference.
