//control.cxx
//The source file for the media control bar.
#include <QToolBar>
#include <QToolButton>
#include <QLabel>
#include <QSlider>
#include <QPixmap>

#include "control.hh"
#include "actions.hh"
#include "videopane.hh"
#include "settings/get_settings.hh"

ControlBar::ControlBar() {
    Open = new QToolButton;
    Play = new QToolButton;
    Pause = new QToolButton;
    Stop = new QToolButton;
    volumeLabel = new QLabel("Volume:");
    volume = new QSlider(Qt::Horizontal);

    volume->setMinimum(0);
    volume->setMaximum(100);
    volume->setValue(Settings::getVolume());

    QPixmap documentOpenIcon(":/icons/document-open.png");
    QPixmap playIcon(":/icons/media-playback-start.png");
    QPixmap pauseIcon(":/icons/media-playback-pause.png");
    QPixmap stopIcon(":/icons/media-playback-stop.png");
#ifdef NO_THEME_ICONS
    Open->setIcon(documentOpenIcon);
    Play->setIcon(playIcon);
    Pause->setIcon(pauseIcon);
    Stop->setIcon(stopIcon);
#else
    Open->setIcon(QIcon::fromTheme("document-open",documentOpenIcon));
    Play->setIcon(QIcon::fromTheme("media-playback-start",playIcon));
    Pause->setIcon(QIcon::fromTheme("media-playback-pause",pauseIcon));
    Stop->setIcon(QIcon::fromTheme("media-playback-stop",stopIcon));
#endif

    connect(Open,SIGNAL(clicked(bool)),this,SLOT(onOpenClicked()));
    connect(Play,SIGNAL(clicked(bool)),this,SLOT(onPlayClicked()));
    connect(Pause,SIGNAL(clicked(bool)),this,SLOT(onPauseClicked()));
    connect(Stop,SIGNAL(clicked(bool)),this,SLOT(onStopClicked()));
    connect(volume,SIGNAL(valueChanged(int)),this,SLOT(onVolumeChanged()));

    this->addWidget(Open);
    this->addWidget(Play);
    this->addWidget(Pause);
    this->addWidget(Stop);
    this->addWidget(volumeLabel);
    this->addWidget(volume);
}

ControlBar::~ControlBar() {
    delete Open;
    delete Play;
    delete Pause;
    delete Stop;
    delete volumeLabel;
    delete volume;
}

void ControlBar::onOpenClicked() {
    Actions::open();
}

void ControlBar::onPlayClicked() {
    VideoPane::player->play();
}

void ControlBar::onPauseClicked() {
    VideoPane::player->pause();
}

void ControlBar::onStopClicked() {
    VideoPane::player->stop();
}

void ControlBar::onVolumeChanged() {
    VideoPane::player->setVolume(volume->value());
}
