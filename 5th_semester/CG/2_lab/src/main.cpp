#include <QApplication>
#include <QMainWindow>
#include <MyWidget.hpp>
#include <QSurfaceFormat>

//Лабораторная работа №2.
//Тема: Каркасная визуализация выпуклого многогранника. Удаление невидимых линий.
//Задание: Разработать формат представления многогранника и процедуру его каркасной отрисовки в ортографической и
//изометрической проекциях. Обеспечить удаление невидимых линий и возможность пространственных поворотов и
//масштабирования многогранника. Обеспечить автоматическое центрирование и изменение размеров изображения при
//изменении размеров окна.
//Вариант 12 - 5–гранная прямая правильная пирамида

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
