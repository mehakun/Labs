#ifndef SETTINGS_WIDGET
#define SETTINGS_WIDGET

#include <QWidget>
#include <QGroupBox>
#include <SettingsAttr.hpp>
#include <QString>
#include <QVector>

class SettingsWidget : public QGroupBox {
  Q_OBJECT
  
public:
  SettingsWidget(QWidget *parent = nullptr,
                 size_t options_amount = 1,
                 size_t rows = 1, size_t cols = 1,
                 const QString& button_text = tr("Plot"));
  virtual ~SettingsWidget() {};
  void setRangeAt(double min, double max, size_t index);
  void setTextAt(const QString &text, size_t index);
  void setValueAt(double val, size_t index);

signals:
  void released(const QVector<SettingsAttr*> &attributes);

public slots:
  void onButtonReleased();

private:
  QVector<SettingsAttr*> attributes;
};

#endif // SETTINGS_WIDGET
