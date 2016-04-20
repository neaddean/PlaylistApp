#ifndef SONGINFO
#define SONGINFO

#include <QVector>
#include <map>
#include <QString>

class SongInfo {
    struct SongData;

    typedef std::map<QString, SongData> SongMap_t;
    typedef QVector<SongMap_t::iterator> SongVector_t;
    typedef std::multimap<int, SongVector_t, std::greater<int>> PlayListMap_t;
    typedef QVector<PlayListMap_t::iterator> PlaylistVector_t;

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

    void printAllPlayLists();
    void printAllSongs();
};

#endif // SONGINFO

