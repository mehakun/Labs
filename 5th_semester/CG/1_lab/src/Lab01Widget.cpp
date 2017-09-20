#include <Lab01Widget.hpp>
#include <QWidget>
#include <QtCharts>
#include <QGroupBox>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScatterSeries>
#include <QDebug>

Lab01Widget::Lab01Widget(QWidget *parent) :
  QWidget(parent),
  a(2.0), B(420.0),
  chartView(new QChartView{}),
  boxesGroup(new QGroupBox{this})
{ 
  createAxes();
  qDebug() << "created axes";
  createBoxes();
  qDebug() << "created boxes";
  auto layout = new QVBoxLayout{};
  auto valuesLabel = new QLabel{tr("Only positive values are allowed")};

  layout->addWidget(chartView);
  qDebug() << "added chartView";
  layout->addWidget(valuesLabel);
  qDebug() << "added valuesLabel";
  layout->addWidget(boxesGroup);
  qDebug() << "added boxesGroup";

  setLayout(layout);
  qDebug() << "set layout";
}

void
Lab01Widget::createBoxes()
{
  auto valuesLayout = new QHBoxLayout{};
  auto aLabel = new QLabel(tr("value for a:"));
  auto BLabel = new QLabel(tr("maximum value for φ:"));

  auto spinBoxA = new QDoubleSpinBox{};
  spinBoxA->setButtonSymbols(QAbstractSpinBox::NoButtons);
  spinBoxA->setRange(0.0000001, std::numeric_limits<double>::max());
  spinBoxA->setValue(a);
  connect(spinBoxA, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          [this](double new_a){ this->a = new_a; this->changeChart(); });

  auto spinBoxB = new QDoubleSpinBox{};
  spinBoxB->setButtonSymbols(QAbstractSpinBox::NoButtons);
  spinBoxB->setRange(0.0, std::numeric_limits<double>::max());
  spinBoxB->setValue(B);
  connect(spinBoxB, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          [this](double new_B){ this->B = new_B; this->changeChart(); });

  valuesLayout->addWidget(aLabel);
  valuesLayout->addWidget(spinBoxA);
  valuesLayout->addWidget(BLabel);
  valuesLayout->addWidget(spinBoxB);
  boxesGroup->setLayout(valuesLayout);
}

void
Lab01Widget::changeChart()
{
  chartView->chart()->removeAllSeries();
  qDebug() << "removed series from chart";

  auto series = new QtCharts::QSplineSeries{};
  series->setName(tr("ρ = aφ"));

  for (int i = 0; i <= B; ++i) {
    series->append(i, i * a);
  }
  qDebug() << "made series";

  chartView->chart()->addSeries(series);
  qDebug() << "added series to chart";

  series->attachAxis(*(chartView->chart()->axes(Qt::Vertical).begin())); // radialAxis
  series->attachAxis(*(chartView->chart()->axes(Qt::Horizontal).begin())); // angularAxis
  qDebug() << "attached axes";
}

void
Lab01Widget::createAxes()
{
  auto angularAxis = new QtCharts::QValueAxis{};
  angularAxis->setTickCount(9);
  angularAxis->setLabelFormat("%.1f");
  angularAxis->setShadesVisible(true);
  angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
  angularAxis->setRange(0, 360);
  qDebug() << "set angularAxis";

  auto radialAxis = new QtCharts::QValueAxis{};
  radialAxis->setTickCount(9);
  radialAxis->setLabelFormat("%d");
  radialAxis->setRange(0, 720);
  qDebug() << "set radialAxis";

  auto chart = new QPolarChart{};
  chart->addAxis(angularAxis, QtCharts::QPolarChart::PolarOrientationAngular);
  chart->addAxis(radialAxis, QtCharts::QPolarChart::PolarOrientationRadial);
  qDebug() << "added axes to chart";
  chart->setTitle(tr("Use wasd to scroll and +/- to zoom."));

  auto series = new QtCharts::QSplineSeries{};
  series->setName(tr("ρ = aφ"));
  for (int i = 0; i <= B; ++i) {
    series->append(i, i * a);
  }

  chart->addSeries(series);
  qDebug() << "added series to chart";

  series->attachAxis(radialAxis);
  series->attachAxis(angularAxis);

  chartView->setChart(chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  qDebug() << "set chartView";
}

void
Lab01Widget::keyPressEvent(QKeyEvent *event)
{
  switch (event->key()) {
  case Qt::Key_Plus:
    chartView->chart()->zoomIn();
    break;
  case Qt::Key_Minus:
    chartView->chart()->zoomOut();
    break;
  case Qt::Key_A:
    chartView->chart()->scroll(-1.0, 0);
    break;
  case Qt::Key_D:
    chartView->chart()->scroll(1.0, 0);
    break;
  case Qt::Key_W:
    chartView->chart()->scroll(0, 1.0);
    break;
  case Qt::Key_S:
    chartView->chart()->scroll(0, -1.0);
    break;
  default:
    QWidget::keyPressEvent(event);
    break;
  }
}
