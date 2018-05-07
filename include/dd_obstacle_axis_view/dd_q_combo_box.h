#ifndef DD_OBSTACLE_AXIS_VIEW_Q_COMBO_BOX_H
#define DD_OBSTACLE_AXIS_VIEW_Q_COMBO_BOX_H

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif

#include <QComboBox>

namespace dd_obstacle_axis_view
{
class DDQComboBox : public QComboBox
{
  Q_OBJECT
public:
  explicit DDQComboBox(QWidget* parent = 0);
  virtual ~DDQComboBox();

public:
  virtual void showPopup();
};
}

#endif // DD_OBSTACLE_AXIS_VIEW_Q_COMBO_BOX_H
