// Copyright 2017 Patrick Flynn
//
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice,
//	this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice, this
//	list of conditions and the following disclaimer in the documentation and/or
//	other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its contributors may
//	be used to endorse or promote products derived from this software
//	without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
// IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
// INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
// NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
// PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include <QString>
#include <QVector>
#include <QDir>
#include <QFile>
#include <string>
#include <fstream>
#include <iostream>

#include "recent.hh"

using std::string;
using std::ifstream;
using std::getline;
using std::ofstream;
using std::endl;

Recent::Recent() {
	recentItems = new QVector<QString>();
	QString path = QDir::homePath();
    path+="/.cpp-media-player";
    if (!QDir(path).exists()) {
        QDir().mkpath(path);
	}
    path+="/recent";
    ifstream reader(path.toStdString().c_str());
    if (reader.is_open()) {
        string line = "";
        while (getline(reader,line)) {
            recentItems->push_back(QString::fromStdString(line));
        }
        reader.close();
    }
}

Recent::~Recent() {
	delete recentItems;
}

void Recent::addRecent(QString name) {
	if (recentItems->size()==5) {
		recentItems->remove(4);
	}
	recentItems->push_front(name);
}

QVector<QString> *Recent::getRecentItems() {
	return recentItems;
}

void Recent::write() {
	QString path1 = QDir::homePath();
    path1+="/.cpp-media-player";
	if (not QDir(path1).exists()) {
		QDir(path1).mkdir(path1);
	}
	path1+="/recent";
	string path = path1.toStdString();
	ofstream writer;
	writer.open(path.c_str());
	writer << "";
	for (int i = 0; i<recentItems->size(); i++) {
		writer << recentItems->at(i).toStdString() << endl;
	}
	writer.close();
}
