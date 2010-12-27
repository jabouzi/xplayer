#include "player.h"
//
Player::Player( QWidget * parent, Qt::WFlags f) 
    : QMainWindow(parent, f)
{
    setupUi(this);
    path = QCoreApplication::applicationDirPath ();
    if (path.data()[path.size() - 1] != '/') path += "/";
    videoPlayer->mediaObject()->setTickInterval(1000);
    setUI();
    setActions();
    init();
    adjustWindow();
    videoPlayer->installEventFilter(this);
    videoPlayer->videoWidget()->installEventFilter(this);
    isFullScreen = false;
    //addButton->hide();
}

void Player::loadFiles(QStringList list)
{
    sources.clear();
    if (list.size() > 0)
    {
        init();    
        for (int i = 0; i < list.size(); i++)
        {            
            Phonon::MediaSource source(list.at(i));
            sources.insert(i,source);            
        }    
        playButton->setEnabled(true);    
        //addButton->setEnabled(true);
        videoPlayer->mediaObject()->setCurrentSource(getAudio());
        play();
    }
}

void Player::setTitle(QString title)
{
    this->setWindowTitle(title);    
}

void Player::init()
{
    index = 0;
    playing = 0;
    playButton->setEnabled(false);    
    nextButton->setEnabled(false);
    prevButton->setEnabled(false);
    newLoad = true;
}

void Player::init2()
{
    index = 0;
    playing = 0;
    playButton->setEnabled(true);   
    if ( sources.size() > 1)
    {
        if (index == 0)
        {
            prevButton->setEnabled(false);
            nextButton->setEnabled(true);            
        } 
    }
    videoPlayer->mediaObject()->setCurrentSource(sources.at(0)); 
    play();
}

// adjust window position to right down corner
void Player::adjustWindow()
{    
    desktop = QApplication::desktop();
    QRect rec = frameGeometry();
    width = 250;
    height = rec.height();
    QRect rec1 = desktop->screenGeometry (0);    
    QRect rec2 = desktop->availableGeometry (0);    
    x = rec2.width() - width, y = rec2.height() - height  + getTopPanel();    
    setGeometry(x,y,250,height);
}

void Player::closeEvent(QCloseEvent *event)
{
    //qDebug() << event;
    close();
}

// set player label text
void Player::setLabel()
{
    QString filename = videoPlayer->mediaObject()->currentSource().fileName();
    filename = filename.right(filename.length() - filename.lastIndexOf('/') - 1);
    //this->setWindowTitle(filename);    
    lengthLabel->setText(calculateTime(videoPlayer->mediaObject()->totalTime()));
    timeSlider->setRange(0,videoPlayer->mediaObject()->totalTime());
    volumeSlider->setRange(0,100);
    volumeSlider->setValue(videoPlayer->volume()*100);    
}

// simulate the play button clicked
void Player::autoPlay()
{
    playButton->animateClick(10);    
}

// get the audio source file
Phonon::MediaSource Player::getAudio()
{
    if (playing == 1)
        index++;            
    if (playing == 2)
        index--;
    if ( sources.size() > 1){
        if (index == 0){
            prevButton->setEnabled(false);
            nextButton->setEnabled(true);            
        } 
        else if (index > 0 && index < sources.size() - 1){
            prevButton->setEnabled(true);
            nextButton->setEnabled(true);
        }
        else if (index == sources.size() - 1){
            prevButton->setEnabled(true);
            nextButton->setEnabled(false);
        }
    }
    return sources.at(index);    
}

// actions
void Player::setActions(){
    connect(playButton, SIGNAL(clicked()), this, SLOT(play()));
    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(prevButton, SIGNAL(clicked()), this, SLOT(prev()));
    //connect(addButton, SIGNAL(clicked()), this, SLOT(load()));
    connect(videoPlayer->mediaObject(), SIGNAL(finished()), this, SLOT(finished()));
    connect(videoPlayer->mediaObject(), SIGNAL(totalTimeChanged(qint64)), this, SLOT(updateTime()));
    connect(videoPlayer->mediaObject(), SIGNAL(tick(qint64)), this, SLOT(updateTime()));    
    connect(videoPlayer->mediaObject(), SIGNAL(stateChanged(Phonon::State, Phonon::State)), this, SLOT(stateChanged(Phonon::State, Phonon::State)));
    connect(videoPlayer->mediaObject(), SIGNAL(metaDataChanged()), this, SLOT(updateInfo()));
    connect(timeSlider, SIGNAL(sliderReleased()),this, SLOT(seekFile()));
    connect(volumeSlider, SIGNAL(valueChanged(int)),this, SLOT(changeVolume()));
    connect(this, SIGNAL(enterfullScreen()), this, SLOT(setFullScreen()));
    connect(this, SIGNAL(exitfullScreen()), this, SLOT(unsetFullScreen()));
}

// set the player UI : buttons icons and sliders
void Player::setUI(){
    QColor *c = new QColor ( 238, 238, 157, 255 );    
    QPalette * p = new QPalette();
    p->setColor(QPalette::ToolTipBase,*c);
    QFont *f = new QFont ( "sans", 10, -1, false );    
    QToolTip::setFont ( *f );
    QToolTip::setPalette(*p);    
    setWindowIcon(QIcon(path+"images/mecque.png"));
    prevButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipBackward));
    nextButton->setIcon(style()->standardIcon(QStyle::SP_MediaSkipForward));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    //addButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
}

// play audio file
void Player::play()
{ 
    if (videoPlayer->mediaObject()->state() == Phonon::PlayingState)
        videoPlayer->pause();
    else if (videoPlayer->mediaObject()->state() == Phonon::PausedState || videoPlayer->mediaObject()->state() == Phonon::LoadingState || videoPlayer->mediaObject()->state() == Phonon::StoppedState)
        videoPlayer->play();
}

// show playing time (left or elapsed just click on the label to switch)
void Player::updateTime()
{
    long len = videoPlayer->mediaObject()->totalTime();
    long pos = videoPlayer->mediaObject()->currentTime();
    timeSlider->setValue(pos);
    QString timeString;    
    if (pos || len)
    {
        int sec = pos/1000;
        int min = sec/60;
        int hour = min/60;
        int msec = pos;

        QTime playTime(hour%60, min%60, sec%60, msec%1000);
        sec = len / 1000;
        min = sec / 60;
        hour = min / 60;
        msec = len;

        QTime stopTime(hour%60, min%60, sec%60, msec%1000);
        QString timeFormat = "hh:mm:ss";
        
        timeString = playTime.toString(timeFormat);
    }
    timeLabel->setText(timeString);
}

// stop playing
void Player::stop()
{
    videoPlayer->mediaObject()->stop();    
    updateTime();
}

// when the audio source is finished
void Player::finished(){
    stop();
    if (index < sources.size() - 1)
    {
        next();
    }
    else
    {
        close();
    }
}

// forward
void Player::next()
{
    playing = 1;
    videoPlayer->mediaObject()->setCurrentSource(getAudio());
    play();
    
}

// backward
void Player::prev()
{
    playing = 2;
    videoPlayer->mediaObject()->setCurrentSource(getAudio());
    play();
}

// load media files
void Player::load()
{    
    sources.clear();
    QStringList list = QFileDialog::getOpenFileNames(this,tr("Open one or more files"),".",tr("audios (*.mp3 *.wma *.ogg *.wave *.midi *.avi *.mpeg *.mpg *.wmv *.divx *.xvid *.mp4 *.flv *.ogv)"));
    if (list.size() > 0)
    {
        init();    
        for (int i = 0; i < list.size(); i++)
        {            
            Phonon::MediaSource source(list.at(i));
            sources.insert(i,source);            
        }    
        playButton->setEnabled(true);    
        //addButton->setEnabled(true);
        videoPlayer->mediaObject()->setCurrentSource(getAudio());
        play();
    }
}

// add media files
void Player::add()
{
    QStringList list = QFileDialog::getOpenFileNames(this,tr("Open one or more files"),".",tr("audios (*.mp3 *.wma *.ogg *.wave *.midi *.avi *.mpeg *.mpg *.wmv *.divx *.xvid *.mp4 *.flv *.ogv)"));
    if (list.size() > 0)
    {        
        for (int i = 0; i < list.size(); i++)
        {            
            Phonon::MediaSource source(list.at(i));
            sources.append(source);            
        }    
        nextButton->setEnabled(true);
    }
}

void Player::seekFile()
{
    videoPlayer->seek(timeSlider->value());
}

void Player::changeVolume()
{
    float volume = float(volumeSlider->value())/100.0;
    videoPlayer->setVolume(volume);
}

// detect the phonon status
void Player::stateChanged(Phonon::State newstate, Phonon::State oldstate)
{
    if (oldstate == Phonon::LoadingState)
    {    
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
        playButton->setToolTip("Pause");
    }
    if( newstate == Phonon::StoppedState || newstate == Phonon::PausedState)
    {        
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
        playButton->setToolTip("Play");
    }
    else if (newstate == Phonon::PlayingState)
    {
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause)); 
        playButton->setToolTip("Pause"); 
    }    
    else if (newstate == Phonon::ErrorState)
    {            
        if (videoPlayer->mediaObject()->errorType() == Phonon::FatalError)
        {
            init2();
        } 
        else 
        {
            videoPlayer->mediaObject()->pause();
        }
     }
}

// update file infos
void Player::updateInfo()
{    
    QMap <QString, QString> metaData = videoPlayer->mediaObject()->metaData();
    QString trackArtist = metaData.value("ARTIST");
    QString trackTitle = metaData.value("TITLE");
    setLabel();
}

QString Player::calculateTime(int time_)
{
    time_ = time_ /1000;
    int hours = time_ / 3600;
    int minutes = (time_ - (hours*3600)) / 60;
    int seconds = (time_ - (hours*3600) - (minutes*60)) % 60;
    QString hzero = "";
    QString mzero = "";
    QString szero = "";
    if (hours < 10) hzero = "0";
    if (minutes < 10) mzero = "0";
    if (seconds < 10) szero = "0";
    QString times = hzero+QString::number(hours)+":"+ mzero+QString::number(minutes)+":"+szero+QString::number(seconds);
    return times;
}

void Player::keyPressEvent(QKeyEvent *event)
{
    //qDebug() << event->key();
    QMainWindow::keyPressEvent(event);        
    switch (event->key()) 
    {
        case Qt::Key_F:    // F button pressed
            emit(enterfullScreen());            
            break;
        case Qt::Key_F11:    // F11 button pressed
            emit(enterfullScreen());            
            break;
        case Qt::Key_E:    // E button pressed  
            emit(exitfullScreen());
            break;
        case Qt::Key_Escape:    // Escape button pressed   
            emit(exitfullScreen());
            break;
    }
}

void Player::moveEvent(QMoveEvent *event)
{
    QMainWindow::moveEvent(event);   
    //qDebug() << "x1" << event->pos().x();
    //qDebug() << "y1" << event->pos().y();
    
}

void Player::mouseMoveEvent(QMouseEvent *event)
{
    QMainWindow::mouseMoveEvent(event);   
    //qDebug() << "x2" << event->pos().x();
    //qDebug() << "y2" << event->pos().y();
}

// detect click on the time label
bool Player::eventFilter(QObject *o, QEvent *e)
{
    //qDebug() << QString::number(e->type());
    if (e->type() == QEvent::MouseButtonDblClick)
    {
        
        if (o == videoPlayer)
        {
            if (!isFullScreen)
            {
                setFullScreen();
                isFullScreen = true;
            }
            else
            {
                unsetFullScreen();
                isFullScreen = false;
            }
            return TRUE;
        }             
    }

    return QWidget::eventFilter(o, e);
}

void Player::setFullScreen()
{

    //~ hide();
    //~ videoPlayer->videoWidget()->setFullScreen(true);
    
    prevButton->hide();
    nextButton->hide();    
    //addButton->hide();
    playButton->hide();
    volumeSlider->hide();
    timeLabel->hide();
    lengthLabel->hide();
    timeSlider->hide();
    menubar->hide();    
    
    desktop = QApplication::desktop();
    QRect rect = desktop->screenGeometry (desktop->screenNumber(this));   
    setGeometry(0,0,rect.width(),rect.height()); 
    videoPlayer->setGeometry(0,0,rect.width(),rect.height());
    //this->showFullScreen();
}


void Player::unsetFullScreen()
{
    prevButton->show();
    nextButton->show(); 
    //addButton->show();
    playButton->show();
    volumeSlider->show();
    timeLabel->show();
    lengthLabel->show();
    timeSlider->show();
    menubar->show();
    
    this->showNormal();
    
    //~ videoPlayer->videoWidget()->setFullScreen(false);
    //~ show();
}

int Player::getTopPanel()
{
    int topPanel = 0;
    #ifdef Q_WS_X11
    char * pPath = getenv ("KDE_FULL_SESSION"); // KDE or Gnome
    if (QString(pPath) == NULL) // Gnome
    {
        QProcess gconf;
        gconf.start("gconftool", QStringList() << "--get" <<  "/schemas/apps/panel/toplevels/size");   
        
        gconf.waitForStarted();         
        gconf.closeWriteChannel();
        gconf.waitForFinished();

        QByteArray result = gconf.readAll();
        
        QString str = QString(result);
        int j = 0;
        j = str.indexOf("Default Value:", j);
        
        int k = 0;
        k = str.indexOf("Owner:", k);         
        
        topPanel = str.section("", j, k).trimmed().section("",-3,-1).toInt();
    }
    #endif
    return topPanel;
}
//
