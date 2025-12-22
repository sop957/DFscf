#ifndef SPLASHSCREEN_H
#define SPLASHSCREEN_H

#include <QWidget>
#include <QTimer>
#include <QLabel>
#include <QMovie>

class SplashScreen : public QWidget
{
    Q_OBJECT

public:
    explicit SplashScreen(QWidget *parent = nullptr);
    ~SplashScreen();

    void showFor(int milliseconds);
    void showGifSplash(const QString &gifPath, int maxDuration = 5000);

public slots:
    void hide();

signals:
    void finished();

private slots:
    void closeSplash();
    void onFrameChanged(int frameNumber);  // 新增：帧改变信号

private:
    void setupUI();
    void setupFallbackUI();
    void resizeToGif();  // 新增：调整窗口尺寸

    QTimer *m_timer;
    QLabel *m_splashLabel;
    QMovie *m_gifMovie;
    bool m_gifSizeAdjusted;  // 新增：标记是否已调整尺寸
};

#endif // SPLASHSCREEN_H
