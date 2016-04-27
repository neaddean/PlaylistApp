#include "songinfo.h"

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <map>

using namespace std;
/**
 * SongInfo constructor
 * Loads the day 0 playlist file and song list
 */
SongInfo::SongInfo() {
    const QString songlistFileName = "../datasets/song_list.txt";
    const QString playlistFileName = "../datasets/day00.txt";

    if (loadSongFile(songlistFileName)) {
        qDebug() << "ERROR: could not open file:" << songlistFileName;
    }

    if (loadPlaylistFile(playlistFileName)) {
        qDebug() << "ERROR: could not open file:" << playlistFileName;
    }
}

/**
 * printPlaylist
 * Prints the contents of a playlist to the console
 */
void SongInfo::printPlaylist(const PlayListMap_t::value_type playList) {
    qDebug() << "Playlist popularity:" << playList.first;
    for (auto &x: playList.second)
        qDebug() << "\t" << x->first;
    qDebug() << endl;
}

/**
 * printAllPlayLists
 * Prints off of the playlists stored in the playlist map to the console
 */
void SongInfo::printAllPlayLists() {
    for (auto &x: playListMap)
        printPlaylist(x);
}

/**
 * printSong
 * Prints the contents of a song to the console
 */
void SongInfo::printSong(const SongMap_t::value_type song) {
    qDebug() << "song name:" << song.second.name;
    if (!(song.second.artist.isEmpty())) {
        qDebug() << "song artist:" << song.second.artist;
        qDebug() << "song popularity:" << song.second.popularity;
        qDebug() << "song number:" << song.second.number;
    }
    qDebug() << endl;
}

/**
 * printAllSongs
 * Prints all of the songs stored in the song map to the console
 */
void SongInfo::printAllSongs() {
    for (auto &x: songMap)
        printSong(x);
}

/**
 * loadSongFile
 * Loads the songs from a file into the song map
 */
int SongInfo::loadSongFile(const QString filename) {
    QString line, songName;
    QStringList tokens;
    QFile songListFile(filename);

    if (!songListFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    // create stream to read from file
    QTextStream songStream(&songListFile);

    while (!songStream.atEnd()) {
        line = songStream.readLine();
        SongData data;
        tokens = line.split('\t'); // split line by tabs
        data.number = tokens[0].toInt(); // extract song number
        songName = tokens[1]; // extract song name
        data.name = songName;
        data.artist = tokens[2]; // extract song artist
        songMap[songName.toLower()] = data; // add song to song map
    }

    songListFile.close();

    return 0;
}

/**
 * addPlaylist
 * Adds a playlist to the map. If there are more than 1024, then it removes
 * the least popular one.
 */
int SongInfo::addPlaylist(QStringList numberList, int popularity) {
    if (playListMap.size() > 1023) {
        // Get iterator to least popular playlist
        PlayListMap_t::iterator lowestPlaylist = --playListMap.end();
        if (popularity < lowestPlaylist->first)
            return 0;
        else
            removePlaylist(lowestPlaylist);
    }

    // Add an empty playlist. Must create an empty vector to put into map.
    // QVector<SongMap_t::iterator>() creates the empty vector
    PlayListMap_t::iterator it =
            playListMap.insert(make_pair(popularity, QVector<SongMap_t::iterator>()));

    // iterate though the songs that are being added
    for (auto &number : numberList) {
        // iterate though every song in the map
        for (SongMap_t::iterator x = songMap.begin(); x != songMap.end(); ++x) {
            // if the song in the map matches the song we are seeking
            if (x->second.number == number.toInt()){
                x->second.popularity += popularity; // update song popularity
                x->second.playlistVector.push_back(it); // add playlist to song
                it->second.push_back(x); // add song to playlist
                break; // go to the next song that is to be added
            }
        }
    }
    return 1;
}

/**
 * removePlaylist
 * Removes a playlist from the playlist map. First, it removes
 * the playlist from all song it is contained on, then removes
 * the playlist from the map.
 */
void SongInfo::removePlaylist(PlayListMap_t::iterator playlist) {
    // iterate through the songs on the playlist
    for (auto &song : playlist->second){
        // update song popularity
        song->second.popularity -= playlist->first;
        // then, iterate through the playlists of the given song
        for (PlaylistVector_t::iterator it = song->second.playlistVector.begin();
             it != song->second.playlistVector.end();
             it ++)
            // then remove the playlist from the list of playlists in the given song
            if (*it == playlist) {
                song->second.playlistVector.erase(it);
                break;
            }
    }
    playListMap.erase(playlist);
}

/**
 * loadPlaylistFile
 * Loads all the playlists in a given file
 */

int SongInfo::loadPlaylistFile(const QString filename) {
    QString line;
    QStringList tokens, numberList;
    int popularity;

    QFile playListFile(filename);

    if (!playListFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    while (!playListFile.atEnd()) {
        line = playListFile.readLine();
        tokens = line.split('\t'); // First, split the popularity from the songs
        popularity = tokens[1].toInt(); // Extract popularity
        numberList = tokens[0].split(' '); // Split remaining song numbers into a list
        addPlaylist(numberList, popularity); // add playlist to mapp
    }

    playListFile.close();

    return 0;
}

/*This function finds the four most popular songs
that contain the entered text*/
QStringList SongInfo::findFourSongs(QString text){

    multimap<QString,int> newMulti;

    // make text lowercase for better matching
    text = text.toLower();

    for(SongMap_t::iterator iter = songMap.begin(); iter != songMap.end(); ++iter){
        QString songnombre = iter->first;
        SongData info = iter->second;

        /*iterates through the length of the entered text and if
         the current iterator does not match the song name, it is not entered
         into the temporary map*/
        bool songIn = true;
        for(int i=0; i < text.length(); i++){
            if(text[i] != songnombre[i]){
                songIn = false;
                break;
            }
        }
        if(songIn){
            int newInt = info.popularity;
            newMulti.insert(pair<QString,int>(info.name,newInt));
        }
    }

    QString *songArray = new QString[4];
    songArray[0] = "";
    songArray[1] = "";
    songArray[2] = "";
    songArray[3] = "";

    for(int i=0; i<4; i++){
        int temp = 0;
        QString tempStr = "";

        for(multimap<QString,int>::iterator itah = newMulti.begin(); itah != newMulti.end(); ++itah){
            if(itah->second > temp){
                temp = itah->second;
                tempStr = itah->first;
            }
        songArray[i] = tempStr;
        }
      newMulti.erase(tempStr);
    }

    QStringList fourSongs = (QStringList()<<songArray[0]<<songArray[1]<<songArray[2]<<songArray[3]);
    return fourSongs;
}

/**
 * getNumPlaylists
 * Gets the numbers of playlists in the map
 */
int SongInfo::getNumPlaylists() {
    return playListMap.size();
}

QStringList SongInfo::Top8Playlists() {

    QStringList finalList;
    PlayListMap_t::iterator TopPlaylist = playListMap.begin();

    for (int i = 0; i<8 ; i++) {

         finalList<<QString("Number %1 Playlist; Popularity = %2:").arg(QString::number(i+1),QString::number(TopPlaylist->first));

         for (auto &song: TopPlaylist -> second) {
             finalList<<QString("       %1; by: %2").arg(song->second.name,song->second.artist);
         }
         TopPlaylist++;
    }
    return finalList;
}
