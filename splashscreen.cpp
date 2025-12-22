#include "splashscreen.h"
#include <QApplication>
#include <QScreen>
#include <QDebug>
#include <QVBoxLayout>
#include <QFile>
#include<QDir>
SplashScreen::SplashScreen(QWidget *parent)
    : QWidget(parent)
    , m_timer(new QTimer(this))
    , m_splashLabel(new QLabel(this))
    , m_gifMovie(nullptr)
    , m_gifSizeAdjusted(false)
{
    setupUI();
    connect(m_timer, &QTimer::timeout, this, &SplashScreen::closeSplash);
}

SplashScreen::~SplashScreen()
{
    qDebug() << "启动窗口销毁";
    if(m_timer->isActive()) {
        m_timer->stop();
    }
    if(m_gifMovie) {
        m_gifMovie->stop();
        delete m_gifMovie;
    }
}

void SplashScreen::setupUI()
{
    // 设置窗口属性
    setWindowFlags(Qt::SplashScreen | Qt::FramelessWindowHint);

    // 设置小尺寸
    int width = 265;   // 小宽度
    int height = 250;  // 小高度

    setFixedSize(width, height);

    // 居中显示
    QScreen *screen = QApplication::primaryScreen();
    QRect screenGeometry = screen->availableGeometry();
    int x = (screenGeometry.width() - width) / 2;
    int y = (screenGeometry.height() - height) / 2;
    move(x, y);

    // 设置标签
    m_splashLabel->setFixedSize(width, height);
    m_splashLabel->setAlignment(Qt::AlignCenter);
    m_splashLabel->setStyleSheet("background-color: #2c3e50;");

    // 设置布局
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(m_splashLabel);
    setLayout(layout);

    qDebug() << "启动画面初始尺寸:" << width << "x" << height;
}

void SplashScreen::showGifSplash(const QString &gifPath, int maxDuration)
{
    /*qDebug() << "尝试加载GIF文件:" << gifPath;

    m_gifMovie = new QMovie(gifPath);

    if(m_gifMovie->isValid()) {
        qDebug() << "GIF文件有效，开始播放";

        // 设置最大尺寸限制
        int maxWidth = 450;   // 最大宽度
        int maxHeight = 280;  // 最大高度

        // 尝试获取GIF尺寸
        QSize gifSize = m_gifMovie->frameRect().size();
        if(gifSize.isValid() && !gifSize.isEmpty()) {
            // 按比例缩放
            QSize scaledSize = gifSize.scaled(maxWidth, maxHeight, Qt::KeepAspectRatio);
            setFixedSize(scaledSize);
            m_splashLabel->setFixedSize(scaledSize);
            qDebug() << "按比例缩放尺寸:" << scaledSize;
        } else {
            // 如果获取不到GIF尺寸，使用固定小尺寸
            setFixedSize(maxWidth, maxHeight);
            m_splashLabel->setFixedSize(maxWidth, maxHeight);
            qDebug() << "使用固定小尺寸:" << maxWidth << "x" << maxHeight;
        }

        m_splashLabel->setScaledContents(true);

        // 重新居中
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width()) / 2;
        int y = (screenGeometry.height() - height()) / 2;
        move(x, y);

        m_splashLabel->setMovie(m_gifMovie);
        m_gifMovie->start();
    } else {
        qDebug() << "GIF文件无效，使用备用界面";
        setupFallbackUI();
        delete m_gifMovie;
        m_gifMovie = nullptr;
    }

    show();
    m_timer->start(maxDuration);
    */
    qDebug() << "尝试加载GIF文件:" << gifPath;

    m_gifMovie = new QMovie(gifPath);

    if(m_gifMovie->isValid()) {
        qDebug() << "GIF文件有效，开始播放";

        // 设置固定的高质量尺寸
        int width = 500;   // 宽
        int height = 300;  // 长

        setFixedSize(width, height);
        m_splashLabel->setFixedSize(width, height);

        // 关键：设置高质量渲染提示
        setAttribute(Qt::WA_TranslucentBackground);
        setAttribute(Qt::WA_NoSystemBackground);

        // 高质量缩放设置
        m_splashLabel->setScaledContents(true);
        m_splashLabel->setAlignment(Qt::AlignCenter);

        // 设置渲染质量
        m_splashLabel->setStyleSheet(
            "QLabel {"
            "    background-color: transparent;"
            "    border: none;"
            "}"
            );

        // 重新居中
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - width) / 2;
        int y = (screenGeometry.height() - height) / 2;
        move(x, y);

        m_splashLabel->setMovie(m_gifMovie);
        m_gifMovie->setScaledSize(QSize(width, height));  // 设置GIF缩放尺寸
        m_gifMovie->start();

    } else {
        qDebug() << "GIF文件无效，使用备用界面";
        setupFallbackUI();
        delete m_gifMovie;
        m_gifMovie = nullptr;
    }

    show();
    m_timer->start(maxDuration);
}

void SplashScreen::onFrameChanged(int frameNumber)
{
    Q_UNUSED(frameNumber)

    // 在第一帧时调整窗口尺寸
    if(!m_gifSizeAdjusted && m_gifMovie && m_gifMovie->currentImage().isNull() == false) {
        QSize gifSize = m_gifMovie->currentImage().size();
        if(gifSize.isValid() && !gifSize.isEmpty()) {
            qDebug() << "检测到GIF尺寸:" << gifSize << "，调整窗口大小";
            resizeToGif();
            m_gifSizeAdjusted = true;
        }
    }
}

void SplashScreen::resizeToGif()
{
    if(m_gifMovie && m_gifMovie->currentImage().isNull() == false) {
        QSize gifSize = m_gifMovie->currentImage().size();

        // 设置窗口大小为GIF尺寸
        setFixedSize(gifSize);
        m_splashLabel->setFixedSize(gifSize);

        // 重新居中窗口
        QScreen *screen = QApplication::primaryScreen();
        QRect screenGeometry = screen->availableGeometry();
        int x = (screenGeometry.width() - gifSize.width()) / 2;
        int y = (screenGeometry.height() - gifSize.height()) / 2;
        move(x, y);

        qDebug() << "窗口已调整到GIF尺寸:" << gifSize;
    }
}

void SplashScreen::setupFallbackUI()
{
    m_splashLabel->setText("Hello World\n加载中...");
    m_splashLabel->setStyleSheet(
        "background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #667eea, stop:1 #764ba2);"
        "color: white;"
        "font-size: 18px;"
        "font-weight: bold;"
        );
}

void SplashScreen::showFor(int milliseconds)
{
    setupFallbackUI();
    show();
    m_timer->start(milliseconds);
}

void SplashScreen::hide()
{
    closeSplash();
}

void SplashScreen::closeSplash()
{
    qDebug() << "开始关闭启动画面";

    // 停止所有活动
    if(m_timer && m_timer->isActive()) {
        m_timer->stop();
        qDebug() << "定时器已停止";
    }

    if(m_gifMovie && m_gifMovie->state() == QMovie::Running) {
        m_gifMovie->stop();
        qDebug() << "GIF动画已停止";
    }

    // 先发射信号
    qDebug() << "发射finished信号";
    emit finished();

    // 然后关闭窗口
    qDebug() << "关闭窗口";
    close();

    // 最后删除自己
    qDebug() << "准备删除自己";
    QTimer::singleShot(100, this, &SplashScreen::deleteLater);
}
