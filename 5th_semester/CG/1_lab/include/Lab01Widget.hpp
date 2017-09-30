#ifndef CG_LAB01_WIDGET
#define CG_LAB01_WIDGET

#include <QWidget>
#include <QtCharts>
#include <SettingsWidget.hpp>

class Lab01Widget : public QWidget {
  Q_OBJECT
  
public:
  Lab01Widget(QWidget *parent = nullptr);
  virtual ~Lab01Widget() = default;

protected:
  void keyPressEvent(QKeyEvent *event) override;

private:
  void createBoxes();
  void changeChart();
  void createAxes();

  double a;
  double B;
  QChartView *chartView;
  SettingsWidget *settings;
};

#endif // CG_LAB01_WIDGET
