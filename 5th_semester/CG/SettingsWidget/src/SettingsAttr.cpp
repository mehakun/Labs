#include <QDoubleSpinBox>
#include <QString>
#include <QVBoxLayout>
#include <QLabel>
#include <SettingsAttr.hpp>

SettingsAttr::SettingsAttr(QWidget *parent, const QString &tittle,
                           double min_val, double max_val) :
  QGroupBox(parent), spinBox(new QDoubleSpinBox{}), name(tittle), label(new QLabel{name}), min(min_val), max(max_val), spinbox_value(0)
{
  spinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
  spinBox->setRange(min, max);
  spinBox->setValue(spinbox_value);
  connect(spinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
          [this](double new_value){ this->spinbox_value = new_value; });

  auto layout = new QVBoxLayout{};
  layout->addWidget(label);
  layout->addWidget(spinBox);

  setLayout(layout);
}

void
SettingsAttr::setName(const QString &new_name)
{
  label->setText(new_name);
}

void
SettingsAttr::setRange(double min, double max)
{
  spinBox->setRange(min, max);
}

void
SettingsAttr::setValue(double val)
{
  spinBox->setValue(val);
}

double
SettingsAttr::getValue() const
{
  return spinbox_value;
}
