#include "widget.h"
#include "splashscreen.h"
#include <QApplication>
#include <QDebug>
#include <QTimer>
#include <QFile>
#include <QVBoxLayout>
#include <QSoundEffect>
#include <QAudioDevice>
#include <QAudioOutput>
#include <QMediaPlayer>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 关键设置：告诉Qt即使所有窗口都关闭也不要退出应用
    QApplication::setQuitOnLastWindowClosed(false);

    qDebug() << "应用程序启动";

    QString gifPath;
    QString mp3Path;
#ifdef Q_OS_ANDROID
    gifPath = "assets:/splash.gif";
    mp3Path = "qrc:/audio/HAVK.mp3";
#else
    gifPath = "splash.gif";
    mp3Path = "天空属于哈夫克.mp3";
#endif

    // 创建主窗口
    Widget *mainWindow = new Widget();
    mainWindow->hide();

    // 创建启动画面
    SplashScreen *splash = new SplashScreen();

    if(QFile::exists(gifPath) || gifPath.startsWith("assets:")) {
        splash->showGifSplash(gifPath, 5000);
    } else {
        splash->showFor(5000);
    }
    qDebug()<<"开始播放音频|Path:"<<mp3Path;
    QMediaPlayer *player = new QMediaPlayer;
    QAudioOutput *audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    audioOutput->setVolume(5.0);
#ifdef Q_OS_ANDROID
    player->setSource(QUrl(mp3Path));
#else
    player->setSource(QUrl::fromLocalFile(mp3Path));  // 本地文件路径
#endif
    player->play();
    qDebug()<<"play完成";
    // 连接信号
    QObject::connect(splash, &SplashScreen::finished, [mainWindow, splash, &app]() {
        qDebug() << "启动画面完成";

        // 关闭启动画面
        splash->close();
        splash->deleteLater();

        // 显示主窗口
        mainWindow->show();

        // 恢复正常的退出行为
        QTimer::singleShot(1000, [&app]() {
            QApplication::setQuitOnLastWindowClosed(true);
        });
    });

    qDebug() << "进入事件循环";
    QWidget window;

    return app.exec();
}
