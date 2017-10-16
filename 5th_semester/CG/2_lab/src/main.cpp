#include <QApplication>
#include <QMainWindow>
#include <MyWidget.hpp>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QSurfaceFormat format;
    format.setDepthBufferSize(24);
    QSurfaceFormat::setDefaultFormat(format);

    app.setApplicationName("Pyramid by Simon");
    app.setApplicationVersion("0.666");

    auto widget = new MyWidget{};

    QMainWindow window{};
    window.setCentralWidget(widget);
    window.resize(QSize(800, 600));
    window.show();

    return app.exec();
}
