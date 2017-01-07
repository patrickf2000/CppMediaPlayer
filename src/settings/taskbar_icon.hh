//taskbar_icon.hh
#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QCheckBox>

class TaskbarIcon : public QWidget {
    Q_OBJECT
public:
    TaskbarIcon();
    ~TaskbarIcon();
private:
    QHBoxLayout *layout;
    QCheckBox *showIcon;
private slots:
    void onShowIconToggled();
};
