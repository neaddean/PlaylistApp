#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

struct SongData;

typedef map<string, SongData> SongMap_t;
typedef multimap<int, vector<SongMap_t::value_type*>> PlayListMap_t;

struct SongData {
    int number;
    int popularity;
    string artist;
    vector<PlayListMap_t::value_type*> playlistVector;
};

void printPlaylist(const PlayListMap_t::value_type playList) {
    cout << "Playlist popularity: " << playList.first << endl;
    for (auto &x: playList.second)
        cout << "\t" << x->first << endl;
    cout << endl;
}

void printPlayListMap(const PlayListMap_t playListMap) {
    for (auto x: playListMap)
        printPlaylist(x);
}


void printSong(const SongMap_t::value_type song) {
    cout << "song name: " << song.first << endl;
    if (!(song.second.artist.empty())){
        cout << "song artist: " << song.second.artist << endl;
        cout << "song popularity: " << song.second.popularity << endl;
        cout << "song number: " << song.second.number << endl;
    }
    cout <<endl;
}

void printSongMap(const map<string, SongData> &songMap){
    for (auto x: songMap)
        printSong(x);
}

void printvector(const vector<string> v)
{
    for (auto x: v){
        cout << x << " ";
    }
    cout << endl;
}

int loadSongs(SongMap_t &songMap, const string filename) {
    string line;

    ifstream songListFile(filename);

    if (!songListFile.is_open())
        return -1;

    while (getline(songListFile, line)) {
        istringstream iss(line);
        string songName;
        SongData data;

        iss >> data.number;
        iss.ignore(256, '\t'); // read in tab
        getline(iss, songName, '\t');
        getline(iss, data.artist);

        songMap[songName] = data;
    }

    songListFile.close();

    return 0;
}

int loadPlaylist(PlayListMap_t &playlistMap,
                 SongMap_t &songMap,
                 const string filename) {
    string line, numberString;
    int number, popularity;

    ifstream playListFile(filename);

    if (!playListFile.is_open())
        return -1;

    while (getline(playListFile, line)) {
        istringstream iss(line);

        getline(iss, numberString, '\t');
        iss >> popularity;

        PlayListMap_t::iterator it =
                playlistMap.insert(make_pair(popularity, vector<SongMap_t::value_type*>()));
        istringstream jss(numberString);
        while (jss >> number) {
            for (auto &x: songMap) {
                if (x.second.number == number){
                    x.second.popularity += popularity;
                    x.second.playlistVector.push_back(&(*it));
                    it->second.push_back(&x);
                    break;
                }
            }
        }
    }

    playListFile.close();

    return 0;
}


int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    SongMap_t songMap;
    PlayListMap_t playListMap;

    const string songlistFileName = "../PlaylistApp-Datasets/song_list.txt";
    const string playlistFileName = "../PlaylistApp-Datasets/day00.txt";

    if (loadSongs(songMap, songlistFileName)){
        cout << "ERROR: could not open file: " << songlistFileName << endl;
        return -1;
    }

    if (loadPlaylist(playListMap, songMap, playlistFileName)){
        cout << "ERROR: could not open file: " << playlistFileName << endl;
        return -1;
    }

    printSongMap(songMap);
    printPlayListMap(playListMap);
    cout << "size of playlist is " << playListMap.size() << endl;

    return 0;
}
