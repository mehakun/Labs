#ifndef SETTINGS_ATTR
#define SETTINGS_ATTR

#include <QGroupBox>
#include <QString>
#include <QDoubleSpinBox>
#include <QLabel>

class SettingsAttr : public QGroupBox {
  Q_OBJECT
  
public:
  SettingsAttr(QWidget *parent = nullptr,
               const QString &tittle = tr("test"), double min_val = 0,
               double max_val = std::numeric_limits<double>::max());
  virtual ~SettingsAttr() {};
  double getValue() const;
  void setRange(double min, double max);
  void setName(const QString &new_name);
  void setValue(double val);

private:
  QDoubleSpinBox *spinBox;
  QString name;
  QLabel *label;
  double min;
  double max;
  double spinbox_value;
};

#endif // SETTINGS_ATTR
