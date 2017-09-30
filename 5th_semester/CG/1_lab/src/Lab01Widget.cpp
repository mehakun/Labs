#include <Lab01Widget.hpp>
#include <SettingsWidget.hpp>
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
  settings(new SettingsWidget{this, 2, 1, 2})
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
  layout->addWidget(settings);
  qDebug() << "added settings";

  setLayout(layout);
  qDebug() << "set layout";
}

void
Lab01Widget::createBoxes()
{
  settings->setRangeAt(0.0000001, std::numeric_limits<double>::max(), 0);
  settings->setTextAt(tr("value for a:"), 0);
  settings->setValueAt(a, 0);
  settings->setRangeAt(0.0, std::numeric_limits<double>::max(), 1);
  settings->setTextAt(tr("maximum value for φ:"), 1);
  settings->setValueAt(B, 1);

  connect(settings, &SettingsWidget::released, [this](const auto &boxes_vec){
      if (boxes_vec[0]->getValue() != this->a || boxes_vec[1]->getValue() != this->B) {
        this->a = boxes_vec[0]->getValue();
        this->B = boxes_vec[1]->getValue();

        this->changeChart();
      }
    });
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
