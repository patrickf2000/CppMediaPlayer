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
