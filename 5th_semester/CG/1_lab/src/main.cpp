#include <Lab01Widget.hpp>
#include <QApplication>
#include <QMainWindow>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QCoreApplication::setOrganizationName("Simon The Rat King");
  QCoreApplication::setApplicationName("Computer Graphics Lab01");

  auto widget = new Lab01Widget{};

  QMainWindow window{};
  window.setCentralWidget(widget);
  window.resize(800, 600);
  window.show();
  
  return app.exec();
}
