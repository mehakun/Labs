#ifndef MYWIDGET_HPP
#define MYWIDGET_HPP
#include <QVector2D>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <utility>
#include <vector>
#include <QWidget>
#include <SettingsWidget.hpp>

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);

    virtual ~MyWidget() = default;

protected:
  void keyPressEvent(QKeyEvent *event) override;

private:
    double begin = 0;
    double end = 2;
    std::vector<QVector2D> splinePoints;
    std::vector<QVector2D> splineTangents;
    QtCharts::QChartView *chartView;

    void draw();
    std::pair<SettingsWidget *, SettingsWidget *> makeLines();
};

#endif // MYWIDGET_HPP
