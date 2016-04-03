#include "songinfo.h"

#include <QDebug>

int main(int argc, char const *argv[])
{
    (void) argc;
    (void) argv;

    SongInfo songInfo;

    songInfo.loadPlaylistFile("../datasets/day01.txt");
    songInfo.loadPlaylistFile("../datasets/day02.txt");

    songInfo.printSongMap();
    songInfo.printPlayListMap();

    qDebug() << "Number of playlists:" << songInfo.getNumPlaylists();
    return 0;
}
