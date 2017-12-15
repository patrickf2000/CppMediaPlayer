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
#include <QPushButton>
#include <QRadioButton>

#include "settingswidget.hh"
#include "settings.hh"

PlaylistSettings playlistSettings;

PlaylistSettingsWidget::PlaylistSettingsWidget() {
	initStructDefaults();

	layout = new QVBoxLayout;
	this->setLayout(layout);
	
	QVBoxLayout *topLayout = new QVBoxLayout;
	QWidget *topWidget = new QWidget;
	topWidget->setLayout(topLayout);
	layout->addWidget(topWidget,0,Qt::AlignTop);
	
	QVBoxLayout *buttonLayout = new QVBoxLayout;
	QWidget *buttonWidget = new QWidget;
	buttonWidget->setLayout(buttonLayout);
	topLayout->addWidget(buttonWidget);
	
	QPushButton *saveButton = new QPushButton(QIcon::fromTheme("document-save"),"Save Playlist");
	QPushButton *openButton = new QPushButton(QIcon::fromTheme("document-open"),"Open Playlist");
	
	//TODO: Implement these buttons and their actions
	/*buttonLayout->addWidget(saveButton);
	buttonLayout->addWidget(openButton);*/
	
	QWidget *orderWidget = new QWidget;
	QVBoxLayout *orderLayout = new QVBoxLayout;
	orderWidget->setLayout(orderLayout);
	topLayout->addWidget(orderWidget);
	
	QRadioButton *inOrder = new QRadioButton("Play in order",orderWidget);
	QRadioButton *randomly = new QRadioButton("Play randomly",orderWidget);
	
	orderLayout->addWidget(inOrder);
	orderLayout->addWidget(randomly);
	
	inOrder->setChecked(true);
	
	connect(saveButton,&QPushButton::clicked,this,&PlaylistSettingsWidget::onSaveButtonClicked);
	connect(openButton,&QPushButton::clicked,this,&PlaylistSettingsWidget::onOpenButtonClicked);
	connect(inOrder,&QRadioButton::toggled,this,&PlaylistSettingsWidget::onInOrderToggled);
	connect(randomly,&QRadioButton::toggled,this,&PlaylistSettingsWidget::onRandomlyToggled);
}

PlaylistSettingsWidget::~PlaylistSettingsWidget() {
}

void PlaylistSettingsWidget::initStructDefaults() {
	playlistSettings.startIndex = 1;
	playlistSettings.random = false;
}

void PlaylistSettingsWidget::onSaveButtonClicked() {

}

void PlaylistSettingsWidget::onOpenButtonClicked() {

}

void PlaylistSettingsWidget::onInOrderToggled() {
	playlistSettings.random = false;
}

void PlaylistSettingsWidget::onRandomlyToggled() {
	playlistSettings.random = true;
}
