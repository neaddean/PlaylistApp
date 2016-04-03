#ifndef SONGINFO
#define SONGINFO

#include <vector>
#include <map>
#include <QString>

class SongInfo {
    struct SongData;

    typedef std::map<QString, SongData> SongMap_t;
    typedef std::multimap<int, std::vector<SongMap_t::value_type*>, std::greater<int>> PlayListMap_t;
    typedef std::vector<PlayListMap_t::value_type*> PlaylistVector_t;

    struct SongData {
        int number;
        int popularity;
        QString artist;
        PlaylistVector_t playlistVector;
    };

    SongMap_t songMap;
    PlayListMap_t playListMap;

    void printPlaylist(const PlayListMap_t::value_type playList);
    void printSong(const SongMap_t::value_type song);

    void removePlaylist(PlayListMap_t::iterator playlist);

public:
    SongInfo();
//    ~SongInfo();

    int loadSongFile(const QString filename);
    int addPlaylist(QStringList numberList, int popularity);
    int loadPlaylistFile(const QString filename);

    int getNumPlaylists();

    void printPlayListMap();
    void printSongMap();
};

#endif // SONGINFO

