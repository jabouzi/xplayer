#ifndef PLAYER_H
#define PLAYER_H
//
#include <QMainWindow>
#include <QtGui>
#include <QDialog>
#include <QString>
#include <phonon>
#include "database.h"
#include "ui_player.h"
//
class Player : public QMainWindow, public Ui::Player
{
Q_OBJECT
public:
    Player( QWidget * parent = 0, Qt::WFlags f = 0 );
    
public:
    void loadFiles(QStringList);
    void setTitle(QString);
    
private:
    bool eventFilter(QObject *, QEvent *);
    QList<Phonon::MediaSource> sources;
    void setActions();
    void setUI();
    bool isplay;
    QStringList audioSource;
    QString audioLabel;
    void adjustWindow();
    int screenx;
    int screeny;
    bool timeLeft;
    QString path;
    int index;
    bool stopped;
    int playing;
    bool newLoad;
    void init();
    void init2();
    int getTopPanel();
    void closeEvent(QCloseEvent *);
    void keyPressEvent(QKeyEvent *event);
    void moveEvent(QMoveEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void setLabel();
    void setAudio(QStringList);
    void initVolume();
    Phonon::MediaSource getAudio();    
    QString calculateTime(int);
    QDesktopWidget *desktop;
    int screenWidth, width; 
    int screenHeight, height;
    int x, y;
    bool isFullScreen;
    Database *db;
    float volume;

private slots:
    void finished();
    void next();
    void prev();
    void load();
    void play();
    void stop();
    void autoPlay();
    void updateTime();
    void seekFile();
    void stateChanged ( Phonon::State, Phonon::State );
    void updateInfo();
    void add();
    void changeVolume();
    void setFullScreen();
    void unsetFullScreen();
    void saveVolume();

signals:
    void enterfullScreen();
    void exitfullScreen();
};
#endif




