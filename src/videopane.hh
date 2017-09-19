#pragma once

#include <QVideoWidget>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QMediaPlaylist>

class VideoPane : public QVideoWidget {
    Q_OBJECT
public:
    VideoPane();
    static QMediaPlayer *player;
    static QMediaPlaylist *playlist;
    static void addMedia(QString path);
    static void setAndRunPlaylist(QMediaPlaylist *playlist);
    static void startPlaying();
protected:
	void mousePressEvent(QMouseEvent *event);
private slots:
    void onPlayerChanged(qint64 pos);
    void onDurationChanged(qint64 pos);
};
