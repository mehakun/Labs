#ifndef CG_LAB01_WIDGET
#define CG_LAB01_WIDGET

#include <QWidget>
#include <QtCharts>
#include <QGroupBox>
#include <QDoubleSpinBox>

class Lab01Widget : public QWidget {
  Q_OBJECT
  
public:
  Lab01Widget(QWidget *parent = nullptr);

protected:
  void keyPressEvent(QKeyEvent *event) override;

private:
  void createBoxes();
  void changeChart();
  void createAxes();

  double a;
  double B;
  QChartView *chartView;
  QtCharts::QValueAxis *angularAxis;
  QtCharts::QValueAxis *radialAxis;
  QGroupBox *boxesGroup;
  QDoubleSpinBox *spinBoxA;
  QDoubleSpinBox *spinBoxB;
};

#endif // CG_LAB01_WIDGET
