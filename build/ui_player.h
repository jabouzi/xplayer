/********************************************************************************
** Form generated from reading UI file 'player.ui'
**
** Created: Thu Apr 22 19:11:26 2010
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER_H
#define UI_PLAYER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>
#include <phonon/videoplayer.h>

QT_BEGIN_NAMESPACE

class Ui_Player
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    Phonon::VideoPlayer *videoPlayer;
    QLabel *timeLabel;
    QSlider *timeSlider;
    QLabel *lengthLabel;
    QPushButton *prevButton;
    QPushButton *playButton;
    QPushButton *nextButton;
    QPushButton *addButton;
    QSpacerItem *horizontalSpacer;
    QSlider *volumeSlider;
    QMenuBar *menubar;

    void setupUi(QMainWindow *Player)
    {
        if (Player->objectName().isEmpty())
            Player->setObjectName(QString::fromUtf8("Player"));
        Player->resize(282, 246);
        centralwidget = new QWidget(Player);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        videoPlayer = new Phonon::VideoPlayer(centralwidget);
        videoPlayer->setObjectName(QString::fromUtf8("videoPlayer"));

        gridLayout->addWidget(videoPlayer, 0, 0, 1, 8);

        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));

        gridLayout->addWidget(timeLabel, 1, 0, 1, 2);

        timeSlider = new QSlider(centralwidget);
        timeSlider->setObjectName(QString::fromUtf8("timeSlider"));
        timeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(timeSlider, 1, 2, 1, 5);

        lengthLabel = new QLabel(centralwidget);
        lengthLabel->setObjectName(QString::fromUtf8("lengthLabel"));

        gridLayout->addWidget(lengthLabel, 1, 7, 1, 1);

        prevButton = new QPushButton(centralwidget);
        prevButton->setObjectName(QString::fromUtf8("prevButton"));

        gridLayout->addWidget(prevButton, 2, 0, 1, 1);

        playButton = new QPushButton(centralwidget);
        playButton->setObjectName(QString::fromUtf8("playButton"));

        gridLayout->addWidget(playButton, 2, 1, 1, 2);

        nextButton = new QPushButton(centralwidget);
        nextButton->setObjectName(QString::fromUtf8("nextButton"));

        gridLayout->addWidget(nextButton, 2, 3, 1, 1);

        addButton = new QPushButton(centralwidget);
        addButton->setObjectName(QString::fromUtf8("addButton"));

        gridLayout->addWidget(addButton, 2, 4, 1, 1);

        horizontalSpacer = new QSpacerItem(93, 28, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 5, 1, 1);

        volumeSlider = new QSlider(centralwidget);
        volumeSlider->setObjectName(QString::fromUtf8("volumeSlider"));
        volumeSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(volumeSlider, 2, 6, 1, 2);

        Player->setCentralWidget(centralwidget);
        menubar = new QMenuBar(Player);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 282, 23));
        Player->setMenuBar(menubar);

        retranslateUi(Player);

        QMetaObject::connectSlotsByName(Player);
    } // setupUi

    void retranslateUi(QMainWindow *Player)
    {
        Player->setWindowTitle(QApplication::translate("Player", "MainWindow", 0, QApplication::UnicodeUTF8));
        timeLabel->setText(QApplication::translate("Player", "00:00:00", 0, QApplication::UnicodeUTF8));
        lengthLabel->setText(QApplication::translate("Player", "00:00:00", 0, QApplication::UnicodeUTF8));
        prevButton->setText(QString());
        playButton->setText(QString());
        nextButton->setText(QString());
        addButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Player: public Ui_Player {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_H
