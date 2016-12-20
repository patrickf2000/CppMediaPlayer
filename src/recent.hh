//recent.hh
//Contains the controls to read and write the recent file.
#pragma once

#include <QString>
#include <QVector>

class Recent {
public:
	Recent();
	~Recent();
	void addRecent(QString name);
	QVector<QString> *getRecentItems();
	void write();
private:
	QVector<QString> *recentItems;
};
