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
  a(2.0), B(120.0), chartView(new QChartView{}),
  angularAxis(new QtCharts::QValueAxis{}),
  radialAxis(new QtCharts::QValueAxis{}),
  boxesGroup(new QGroupBox{this}),
  spinBoxA(new QDoubleSpinBox{}), spinBoxB(new QDoubleSpinBox{})
{
  createAxes();
  qDebug() << "created axises\n";
  createBoxes();
  qDebug() << "created boxes\n";
  auto layout = new QVBoxLayout{};
  auto valuesLabel = new QLabel{tr("Enter positive values")};

  layout->addWidget(chartView);
  qDebug() << "added this";
  layout->addWidget(valuesLabel);
  qDebug() << "added valLabel";
  layout->addWidget(boxesGroup);
  qDebug() << "added boxesGroup";

  setLayout(layout);
  qDebug() << "finished";
}

void
Lab01Widget::createBoxes()
{
  auto valuesLayout = new QHBoxLayout{};

  auto aLabel = new QLabel(tr("\ta:"));
  auto BLabel = new QLabel(tr("\tB:"));

  spinBoxA->setButtonSymbols(QAbstractSpinBox::NoButtons);
  spinBoxA->setRange(0.0000001, std::numeric_limits<double>::max());
  spinBoxA->setValue(a);
  connect(spinBoxA, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          [this](double new_a){ this->a = new_a; this->changeChart(); });

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
  qDebug() << "setRange\n";
  chartView->chart()->removeAllSeries();
  auto radialAxis = *(chartView->chart()->axes(Qt::Vertical).begin());
  radialAxis->setRange(0, a * B);
  auto angularAxis = *(chartView->chart()->axes(Qt::Horizontal).begin());
  angularAxis->setRange(0, B);
  
  auto series = new QtCharts::QSplineSeries{};
  series->setName(tr("ρ = aφ"));

  for (int i = 0; i <= B; ++i) {
    series->append(i * a, i);
  }

  chartView->chart()->addSeries(series);

  series->attachAxis(radialAxis);
  series->attachAxis(angularAxis);
}

void
Lab01Widget::createAxes()
{

  angularAxis->setTickCount(9); // First and last ticks are co-located on 0/360 angle.
  angularAxis->setLabelFormat("%.1f");
  angularAxis->setShadesVisible(true);
  angularAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
  qDebug() << "made angularAxis\n";
  auto chart = new QPolarChart{};
  chart->addAxis(angularAxis, QtCharts::QPolarChart::PolarOrientationAngular);

  radialAxis->setTickCount(9);
  radialAxis->setLabelFormat("%d");
  qDebug() << "made radialAxis\n";
  chart->addAxis(radialAxis, QtCharts::QPolarChart::PolarOrientationRadial);
  qDebug() << "added axis\n";
  chart->setTitle(tr("Use arrow keys to scroll and +/- to zoom."));

  auto series = new QtCharts::QSplineSeries{};
  series->setName(tr("ρ = aφ"));
  qDebug() << "setName\n";

  radialAxis->setRange(0, a * B + 1);
  angularAxis->setRange(0, B + 1);

  for (int i = 0; i <= B; ++i) {
    series->append(i * a, i);
  }

  chart->addSeries(series);

  series->attachAxis(radialAxis);
  series->attachAxis(angularAxis);

  chartView->setChart(chart);
  qDebug() << "set chart\n";
  chartView->setRenderHint(QPainter::Antialiasing);
}

void Lab01Widget::keyPressEvent(QKeyEvent *event)
{
  switch (event->key()) {
  case Qt::Key_Plus:
    chartView->chart()->zoomIn();
    break;
  case Qt::Key_Minus:
    chartView->chart()->zoomOut();
    break;
  case Qt::Key_Left:
    chartView->chart()->scroll(-1.0, 0);
    break;
  case Qt::Key_Right:
    chartView->chart()->scroll(1.0, 0);
    break;
  case Qt::Key_Up:
    chartView->chart()->scroll(0, 1.0);
    break;
  case Qt::Key_Down:
    chartView->chart()->scroll(0, -1.0);
    break;
  default:
    QWidget::keyPressEvent(event);
    break;
  }
}
