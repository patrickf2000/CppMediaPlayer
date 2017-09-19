#pragma once

#include <QMenu>
#include <QAction>

class ViewMenu : public QMenu {
    Q_OBJECT
public:
    ViewMenu();
    ~ViewMenu();
private:
    QAction *fullScreen;
private slots:
    void onFullScreenClicked();
};
