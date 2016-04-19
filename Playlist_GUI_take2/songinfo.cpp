#include "songinfo.h"

#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <map>

using namespace std;
SongInfo::SongInfo() {
    const QString songlistFileName = "/Users/codiesmith/Downloads/song_list.txt";
    const QString playlistFileName = "/Users/codiesmith/Downloads/day00.txt";

    if (loadSongFile(songlistFileName)) {
        qDebug() << "ERROR: could not open file:" << songlistFileName;
    }

    if (loadPlaylistFile(playlistFileName)) {
        qDebug() << "ERROR: could not open file:" << playlistFileName;
    }
}

void SongInfo::printPlaylist(const PlayListMap_t::value_type playList) {
    qDebug() << "Playlist popularity:" << playList.first;
    for (auto &x: playList.second)
        qDebug() << "\t" << x->first;
    qDebug() << endl;
}

void SongInfo::printAllPlayLists() {
    for (auto &x: playListMap)
        printPlaylist(x);
}

void SongInfo::printSong(const SongMap_t::value_type song) {
    qDebug() << "song name:" << song.first;
    if (!(song.second.artist.isEmpty())) {
        qDebug() << "song artist:" << song.second.artist;
        qDebug() << "song popularity:" << song.second.popularity;
        qDebug() << "song number:" << song.second.number;
    }
    qDebug() << endl;
}

void SongInfo::printAllSongs() {
    for (auto &x: songMap)
        printSong(x);
}

int SongInfo::loadSongFile(const QString filename) {
    QString line, songName;
    QStringList tokens;
    QFile songListFile(filename);

    if (!songListFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;
    QTextStream songStream(&songListFile);

    while (!songStream.atEnd()) {
        line = songStream.readLine();
        SongData data;
        tokens = line.split('\t');
        data.number = tokens[0].toInt();
        songName = tokens[1];
        data.artist = tokens[2];
        songMap[songName] = data;
    }

    songListFile.close();

    return 0;
}

int SongInfo::addPlaylist(QStringList numberList, int popularity) {
    if (playListMap.size() > 1023) {
        PlayListMap_t::iterator lowestPlaylist = --playListMap.end();
        if (popularity < (*lowestPlaylist).first)
            return 0;
        else
            removePlaylist(lowestPlaylist);
    }

    PlayListMap_t::iterator it =
            playListMap.insert(make_pair(popularity, QVector<SongMap_t::iterator>()));

    for (auto &number : numberList) {
        for (SongMap_t::iterator x = songMap.begin(); x != songMap.end(); ++x) {
            if (x->second.number == number.toInt()){
                x->second.popularity += popularity;
                x->second.playlistVector.push_back(it);
                it->second.push_back(x);
                break;
            }
        }
    }
    return 1;
}

void SongInfo::removePlaylist(PlayListMap_t::iterator playlist) {
    for (auto &song : (*playlist).second){
        song->second.popularity -= (*playlist).first;
        for (PlaylistVector_t::iterator it = song->second.playlistVector.begin();
             it != song->second.playlistVector.end();
             it ++)
            if (*it == playlist) {
                song->second.playlistVector.erase(it);
                break;
            }
    }
    playListMap.erase(playlist);
}

int SongInfo::loadPlaylistFile(const QString filename) {
    QString line;
    QStringList tokens, numberList;
    int popularity;

    QFile playListFile(filename);

    if (!playListFile.open(QIODevice::ReadOnly | QIODevice::Text))
        return -1;

    while (!playListFile.atEnd()) {
        line = playListFile.readLine();
        tokens = line.split('\t');
        popularity = tokens[1].toInt();
        numberList = tokens[0].split(' ');
        addPlaylist(numberList, popularity);
    }

    playListFile.close();

    return 0;
}

/*This function finds the four most popular songs
that contain the entered text*/
QStringList SongInfo::findFourSongs(QString text){

    multimap<QString,int> newMulti;

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
            newMulti.insert(pair<QString,int>(songnombre,newInt));
        }
    }

    QString *songArray = new QString[4];
    songArray[0] = "a";
    songArray[1] = "b";
    songArray[2] = "c";
    songArray[3] = "d";

    for(int i=0; i<4; i++){
        int temp = 0;
        QString tempStr = "b";

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
    qDebug() << fourSongs;
    return fourSongs;
}

int SongInfo::getNumPlaylists() {
    return playListMap.size();
}

