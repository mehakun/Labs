#include <Lab01Widget.hpp>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QMainWindow window{};
  auto widget = new Lab01Widget{};

  window.setCentralWidget(widget);
  window.resize(800, 600);
  window.show();
  
  return app.exec();
}
