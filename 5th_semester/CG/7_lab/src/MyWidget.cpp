#include <QMouseEvent>
#include <cmath>
#include <QVBoxLayout>
#include <QLabel>
#include <MyWidget.hpp>
#include <QDebug>
#include "splines/cubic_hermite_spline.h"
#include <SettingsWidget.hpp>
#include <QValueAxis>
#include <utility>

MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    splinePoints{{0.0, 0.0}, {1.0, 1.0}, {4., 4.}},
    splineTangents{{0.5, 0.2}, {std::tan(1.5), std::tan(1.6)}, {std::tan(3.0), std::tan(3.0)}}
{
    auto series = new QtCharts::QLineSeries{};

    double tmp = begin;

    CubicHermiteSpline<QVector2D> spline(splinePoints, splineTangents);

    while (end - tmp >= std::numeric_limits<double>::epsilon()) {
        qDebug() << tmp << " <====> " <<spline.getPosition(tmp).toPointF();
        series->append(spline.getPosition(tmp).toPointF());

        tmp += 0.1;
    }

    auto chart = new QtCharts::QChart{};
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple spline");

    chartView = new QtCharts::QChartView{chart};
    chartView->setRenderHint(QPainter::Antialiasing);

    auto layout = new QVBoxLayout{};

    layout->addWidget(chartView, 9);
    qDebug() << "added chartView";

    auto res = makeLines();

    layout->addWidget(res.first);
    layout->addWidget(res.second);

    setLayout(layout);
    qDebug() << "set layout";
}

void
MyWidget::draw()
{
    auto xAxis = new QtCharts::QValueAxis{};
    xAxis->setTickCount(9);
    xAxis->setLabelFormat("%.1f");
    xAxis->setShadesBrush(QBrush(QColor(249, 249, 255)));
    xAxis->setRange(begin, end);

    auto yAxis = new QtCharts::QValueAxis{};
    yAxis->setTickCount(9);
    yAxis->setLabelFormat("%.1f");
    yAxis->setRange(begin, end);

    auto series = new QtCharts::QLineSeries{};

    double tmp = begin;

    CubicHermiteSpline<QVector2D> spline(splinePoints, splineTangents);

    while (end - tmp > std::numeric_limits<double>::epsilon()) {
        qDebug() << tmp << " <====> " << spline.getPosition(tmp).toPointF();
        series->append(spline.getPosition(tmp).toPointF());

        tmp += 0.01;
    }

    auto chart = new QtCharts::QChart{};
    chart->legend()->hide();

    chart->addAxis(xAxis, Qt::AlignLeft);
    chart->addAxis(yAxis, Qt::AlignBottom);
    chart->setTitle(tr("Use wasd to scroll and +/- to zoom."));
    chart->addSeries(series);
    chart->setTitle("Simple spline");

    series->attachAxis(xAxis);
    series->attachAxis(yAxis);

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

std::pair<SettingsWidget *, SettingsWidget *>
MyWidget::makeLines()
{
    auto coords = new SettingsWidget{this, 6, 2, 3};

    for (int i = 0; i < 6; ++i) {
        coords->setRangeAt(std::numeric_limits<double>::min(),
                           std::numeric_limits<double>::max(),
                           i);
        coords->setValueAt(i, i);
        if (i < 3) {
            coords->setTextAt("X coord", i);
        } else {
            coords->setTextAt("Y coord", i);
        }

    }

    connect(coords, &SettingsWidget::released,
            [this](const auto& coord_vec)
    {
        for (int i = 0; i < 3; ++i) {
            this->splinePoints[i].setX(coord_vec[i]->getValue());
            this->splinePoints[i].setY(coord_vec[i + 3]->getValue());
        }

        this->draw();
    }
    );

    auto tangs = new SettingsWidget{this, 3, 1, 3};

    for (int i = 0; i < 3; ++i) {
        tangs->setRangeAt(std::numeric_limits<double>::min(),
                           std::numeric_limits<double>::max(),
                           i);
        tangs->setValueAt(i, i);
        tangs->setTextAt("coeff", i);
    }

    connect(tangs, &SettingsWidget::released,
            [this](const auto& tang_vec)
    {
        for (int i = 0; i < 3; ++i) {
            this->splineTangents[i].setX(std::tan(tang_vec[i]->getValue()));
            this->splineTangents[i].setY(std::tan(tang_vec[i]->getValue()) + 0.2);
        }

        this->draw();
    }
    );

    return std::make_pair(coords, tangs);
}

void
MyWidget::keyPressEvent(QKeyEvent *event)
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

