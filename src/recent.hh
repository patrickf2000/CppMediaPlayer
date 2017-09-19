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
