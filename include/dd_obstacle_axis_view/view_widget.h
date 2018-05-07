#ifndef DD_OBSTACLE_AXIS_VIEW_WIDGET_H
#define DD_OBSTACLE_AXIS_VIEW_WIDGET_H

#include <QWidget>

namespace dd_obstacle_axis_view
{
class ViewWidget : public QWidget
{
  Q_OBJECT
public:
  ViewWidget(QWidget* parent = 0);

  virtual void mouseMoveEvent(QMouseEvent* event);

  virtual void mousePressEvent(QMouseEvent* event);

  virtual void mouseReleaseEvent(QMouseEvent* event);

  virtual void leaveEvent(QEvent* event);

  virtual void wheelEvent(QWheelEvent* event);

Q_SIGNALS:

protected:
};
}

#endif // DD_OBSTACLE_AXIS_VIEW_WIDGET_H
