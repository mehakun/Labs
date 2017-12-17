#include <SettingsWidget.hpp>
#include <QGridLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QHBoxLayout>

SettingsWidget::SettingsWidget(QWidget *parent,
                               size_t options_amount,
                               size_t rows, size_t cols,
                               const QString& button_text) :
  QGroupBox(parent)
{
  auto button = new QPushButton{button_text, this};
  connect(button, &QAbstractButton::released, this, &SettingsWidget::onButtonReleased);

  auto layout = new QGridLayout{};

  for (size_t i = 0; i < options_amount; ++i) {
    attributes.push_back(new SettingsAttr{});
  }

  size_t item = 0;
  for (size_t row = 0; row < rows; ++row) {
    for (size_t column = 0; column < cols; ++column) {
      layout->addWidget(attributes[item++], row, column);
    }
  }

  auto attrs_box = new QGroupBox{this};
  attrs_box->setLayout(layout);

  auto this_layout = new QHBoxLayout{};
  this_layout->addWidget(attrs_box);
  this_layout->addWidget(button);

  setLayout(this_layout);
}

void
SettingsWidget::setRangeAt(double min, double max, size_t index)
{
  attributes[index]->setRange(min, max);
}

void
SettingsWidget::setTextAt(const QString &text, size_t index)
{
  attributes[index]->setName(text);
}

void
SettingsWidget::setValueAt(double val, size_t index)
{
  attributes[index]->setValue(val);
}

void
SettingsWidget::onButtonReleased()
{
  emit released(attributes);
}
