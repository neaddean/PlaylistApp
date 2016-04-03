#include "songinfo.h"

#include <iostream>
#include <vector>
#include <map>
#include <QString>
#include <QStringList>
#include <QTextStream>
#include <QDebug>
#include <QFile>

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

void SongInfo::printPlaylist(const PlayListMap_t::value_type playList) {
    qDebug() << "Playlist popularity:" << playList.first;
    for (auto &x: playList.second)
        qDebug() << "\t" << x->first;
    qDebug() << endl;
}

void SongInfo::printPlayListMap() {
    for (auto &x: playListMap)
        printPlaylist(x);
}

void SongInfo::printSong(const SongMap_t::value_type song) {
    qDebug() << "song name:" << song.first;
    if (!(song.second.artist.isEmpty())){
        qDebug() << "song artist:" << song.second.artist;
        qDebug() << "song popularity:" << song.second.popularity;
        qDebug() << "song number:" << song.second.number;
    }
    qDebug() << endl;
}

void SongInfo::printSongMap() {
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
        PlayListMap_t::iterator lowestPlaylist = (--playListMap.end());
        if (popularity < (*lowestPlaylist).first)
            return 0;
        else
            removePlaylist(lowestPlaylist);
    }

    PlayListMap_t::iterator it =
            playListMap.insert(make_pair(popularity, std::vector<SongMap_t::value_type*>()));

    for (auto &number : numberList) {
        for (auto &x: songMap) {
            if (x.second.number == number.toInt()){
                x.second.popularity += popularity;
                x.second.playlistVector.push_back(&(*it));
                it->second.push_back(&x);
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
            if (*it == &(*playlist)) {
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

int SongInfo::getNumPlaylists() {
    return playListMap.size();
}
