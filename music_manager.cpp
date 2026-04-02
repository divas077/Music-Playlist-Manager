#include <iostream>
#include <string>
#include <cstdlib>   // for rand()
#include <ctime>     // for srand(time(0))
using namespace std;

// ─────────────────────────────────────────────
//  A single song stored as a node in the list
// ─────────────────────────────────────────────
struct Song {
    int    id;
    string name;
    string artist;
    Song*  prev;   // pointer to the previous song
    Song*  next;   // pointer to the next song

    // Constructor – fills in the song details when we create a node
    Song(int id, string name, string artist) {
        this->id     = id;
        this->name   = name;
        this->artist = artist;
        this->prev   = nullptr;
        this->next   = nullptr;
    }
};

// ─────────────────────────────────────────────
//  The Playlist – manages all songs
// ─────────────────────────────────────────────
class Playlist {
private:
    Song* head;      // first song in the list
    Song* tail;      // last  song in the list
    Song* current;   // the song that is "playing" right now
    int   totalSongs;

public:
    // Constructor – start with an empty playlist
    Playlist() {
        head       = nullptr;
        tail       = nullptr;
        current    = nullptr;
        totalSongs = 0;
    }

    // ── Destructor: free all memory when playlist is destroyed ──
    ~Playlist() {
        Song* temp = head;
        while (temp != nullptr) {
            Song* next = temp->next;
            delete temp;
            temp = next;
        }
    }

    // ── Add a song at the END of the playlist ──
    void addSong(int id, string name, string artist) {
        Song* newSong = new Song(id, name, artist);

        if (head == nullptr) {          // list is empty
            head    = newSong;
            tail    = newSong;
            current = newSong;          // auto-select first song
        } else {
            // link new song after the current tail
            tail->next    = newSong;
            newSong->prev = tail;
            tail          = newSong;    // update tail pointer
        }

        totalSongs++;
        cout << "Added: \"" << name << "\" by " << artist << "\n";
    }

    // ── Delete a song by its ID ──
    void deleteSongByID(int id) {
        Song* temp = head;

        while (temp != nullptr) {
            if (temp->id == id) {
                removeSong(temp);
                return;
            }
            temp = temp->next;
        }
        cout << "Song with ID " << id << " not found.\n";
    }

    // ── Delete a song by its Name ──
    void deleteSongByName(string name) {
        Song* temp = head;

        while (temp != nullptr) {
            if (temp->name == name) {
                removeSong(temp);
                return;
            }
            temp = temp->next;
        }
        cout << "Song \"" << name << "\" not found.\n";
    }

    // ── Search for a song by Name and print details ──
    void searchByName(string name) {
        Song* temp = head;

        while (temp != nullptr) {               // O(n) linear scan
            if (temp->name == name) {
                cout << "Found → ID: " << temp->id
                     << " | Name: "   << temp->name
                     << " | Artist: " << temp->artist << "\n";
                return;
            }
            temp = temp->next;
        }
        cout << "Song \"" << name << "\" not found.\n";
    }

    // ── Play the NEXT song (move current forward) ──
    void playNext() {
        if (current == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }
        if (current->next == nullptr) {
            cout << "Already at the last song.\n";
            return;
        }
        current = current->next;
        cout << "Now playing: \"" << current->name
             << "\" by "          << current->artist << "\n";
    }

    // ── Play the PREVIOUS song (move current backward) ──
    void playPrev() {
        if (current == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }
        if (current->prev == nullptr) {
            cout << "Already at the first song.\n";
            return;
        }
        current = current->prev;
        cout << "Now playing: \"" << current->name
             << "\" by "          << current->artist << "\n";
    }

    // ── Show which song is currently selected ──
    void showCurrentSong() {
        if (current == nullptr) {
            cout << "No song is playing.\n";
            return;
        }
        cout << "Current song: \"" << current->name
             << "\" by "           << current->artist
             << " (ID: "           << current->id << ")\n";
    }

    // ── Shuffle: reorder nodes using pointer manipulation (no extra array) ──
    //    Strategy: Fisher-Yates style – walk the list and swap node DATA
    //    (swapping data is simpler and equally correct for a beginner)
    void shuffle() {
        if (totalSongs < 2) {
            cout << "Need at least 2 songs to shuffle.\n";
            return;
        }

        srand(time(0));   // seed random number generator

        // Collect all node pointers into a temporary array for easy indexing
        Song** nodes = new Song*[totalSongs];
        Song*  temp  = head;
        for (int i = 0; i < totalSongs; i++) {
            nodes[i] = temp;
            temp     = temp->next;
        }

        // Fisher-Yates shuffle: swap node DATA (id, name, artist) in-place
        for (int i = totalSongs - 1; i > 0; i--) {
            int j = rand() % (i + 1);

            // Swap id, name, artist between nodes[i] and nodes[j]
            swap(nodes[i]->id,     nodes[j]->id);
            swap(nodes[i]->name,   nodes[j]->name);
            swap(nodes[i]->artist, nodes[j]->artist);
        }

        delete[] nodes;   // free temp array
        current = head;   // reset current to new first song
        cout << "Playlist shuffled! Now playing from the beginning.\n";
    }

    // ── Print every song in the playlist ──
    void displayAll() {
        if (head == nullptr) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "\n========== Playlist (" << totalSongs << " songs) ==========\n";
        Song* temp = head;
        int   pos  = 1;
        while (temp != nullptr) {
            // Mark the currently playing song with ">>"
            string marker = (temp == current) ? ">>" : "  ";
            cout << marker << " " << pos << ". [ID:" << temp->id << "] "
                 << temp->name << " - " << temp->artist << "\n";
            pos++;
            temp = temp->next;
        }
        cout << "===============================================\n\n";
    }

private:
    // ── Helper: unlink and delete a specific node ──
    void removeSong(Song* song) {
        // Fix the previous node's "next" pointer
        if (song->prev != nullptr)
            song->prev->next = song->next;
        else
            head = song->next;   // song was head, update head

        // Fix the next node's "prev" pointer
        if (song->next != nullptr)
            song->next->prev = song->prev;
        else
            tail = song->prev;   // song was tail, update tail

        // If the deleted song was the current one, move current forward/back
        if (current == song) {
            if (song->next != nullptr)      current = song->next;
            else if (song->prev != nullptr) current = song->prev;
            else                            current = nullptr;
        }

        cout << "Deleted: \"" << song->name << "\"\n";
        delete song;
        totalSongs--;
    }
};

// ─────────────────────────────────────────────
//  Main – simple terminal menu
// ─────────────────────────────────────────────
int main() {
    Playlist playlist;
    int choice;

    // Pre-load a few songs so you can test right away
    playlist.addSong(1, "Blinding Lights",  "The Weeknd");
    playlist.addSong(2, "Shape of You",     "Ed Sheeran");
    playlist.addSong(3, "Levitating",       "Dua Lipa");
    playlist.addSong(4, "Stay",             "Kid Laroi");
    playlist.addSong(5, "Peaches",          "Justin Bieber");

    do {
        cout << "\n====== Music Playlist Manager ======\n";
        cout << "1. Display all songs\n";
        cout << "2. Add a song\n";
        cout << "3. Delete song by ID\n";
        cout << "4. Delete song by Name\n";
        cout << "5. Search by Name\n";
        cout << "6. Play Next\n";
        cout << "7. Play Previous\n";
        cout << "8. Show Current Song\n";
        cout << "9. Shuffle Playlist\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();   // flush the newline from input buffer

        if (choice == 1) {
            playlist.displayAll();

        } else if (choice == 2) {
            int    id;
            string name, artist;
            cout << "Enter ID: ";     cin >> id;     cin.ignore();
            cout << "Enter Name: ";   getline(cin, name);
            cout << "Enter Artist: "; getline(cin, artist);
            playlist.addSong(id, name, artist);

        } else if (choice == 3) {
            int id;
            cout << "Enter ID to delete: ";
            cin >> id;
            playlist.deleteSongByID(id);

        } else if (choice == 4) {
            string name;
            cout << "Enter song name to delete: ";
            getline(cin, name);
            playlist.deleteSongByName(name);

        } else if (choice == 5) {
            string name;
            cout << "Enter song name to search: ";
            getline(cin, name);
            playlist.searchByName(name);

        } else if (choice == 6) {
            playlist.playNext();

        } else if (choice == 7) {
            playlist.playPrev();

        } else if (choice == 8) {
            playlist.showCurrentSong();

        } else if (choice == 9) {
            playlist.shuffle();

        } else if (choice != 0) {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
