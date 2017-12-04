#include <QApplication>
#include <QMainWindow>
#include <MyWidget.hpp>
#include <QSurfaceFormat>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QTimer>
#include <QLabel>

template <typename Str, typename Parent>
auto
make_label(const Str &s, Parent p)
{
    auto label = new QLabel{s, p};
    auto vbox = new QHBoxLayout{};
    vbox->addWidget(label);
    vbox->addWidget(p);

    auto gbox = new QGroupBox{};
    gbox->setLayout(vbox);

    return gbox;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Cylinder by Simon");
    app.setApplicationVersion("0.666");

    auto widget = new MyWidget{};

    // slider for setting aprroximation
    auto approxSlider = new QSlider{Qt::Horizontal};
    approxSlider->setTickPosition(QSlider::NoTicks);
    approxSlider->setValue(4);
    approxSlider->setMinimum(4);
    approxSlider->setMaximum(256);
    approxSlider->setSingleStep(1);

    // slider for setting "brightness" of diffuse light
    auto brightSlider = new QSlider{Qt::Horizontal};
    brightSlider->setTickPosition(QSlider::NoTicks);
    brightSlider->setValue(50);
    brightSlider->setMinimum(0);
    brightSlider->setMaximum(256);
    brightSlider->setSingleStep(1);

    // slider for setting ambient part of light
//    auto ambientSlider = new QSlider{Qt::Horizontal};
//    ambientSlider->setTickPosition(QSlider::NoTicks);
//    ambientSlider->setValue(50);
//    ambientSlider->setMinimum(0);
//    ambientSlider->setMaximum(100);
//    ambientSlider->setSingleStep(1);

    // timer for changing ambient part of light
    auto ambientTimer = new QTimer{};
    QObject::connect(ambientTimer, &QTimer::timeout, widget, &MyWidget::onAmbientChange);
    ambientTimer->start(100);

    // slider for setting shiness of material
    auto shineSlider = new QSlider{Qt::Horizontal};
    shineSlider->setTickPosition(QSlider::NoTicks);
    shineSlider->setValue(50);
    shineSlider->setMinimum(0);
    shineSlider->setMaximum(100);
    shineSlider->setSingleStep(1);

    // connecting sliders to widget
    QObject::connect(approxSlider, &QSlider::valueChanged, widget, &MyWidget::onApproxChange);
    QObject::connect(brightSlider, &QSlider::valueChanged, widget, &MyWidget::onBrightChange);
    QObject::connect(shineSlider, &QSlider::valueChanged, widget, &MyWidget::onShineChange);

    auto qvbox = new QVBoxLayout{};
    qvbox->addWidget(widget, 9);

    // labels for sliders
    qvbox->addWidget(make_label(QObject::tr("Approximation slider"), approxSlider));
    qvbox->addWidget(make_label(QObject::tr("Brightness slider"), brightSlider));
    qvbox->addWidget(make_label(QObject::tr("Shineness slider"), shineSlider));

    auto groupbox = new QGroupBox{QObject::tr("Nevrev Semen")};
    groupbox->setLayout(qvbox);

    QMainWindow window{};
    window.setCentralWidget(groupbox);
    window.resize(QSize(800, 600));
    window.show();

    return app.exec();
}
