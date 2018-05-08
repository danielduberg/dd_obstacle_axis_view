#ifndef DD_OBSTACLE_AXIS_VIEW_WIDGET_H
#define DD_OBSTACLE_AXIS_VIEW_WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QEvent>
#include <QWheelEvent>

#include <pcl_ros/point_cloud.h>

namespace dd_obstacle_axis_view
{
class ViewWidget : public QWidget
{
  Q_OBJECT
private:
  pcl::PointCloud<pcl::PointXYZ>::Ptr cloud_;

  double center_x_;
  double center_y_;

  double min_x_;
  double max_x_;
  double min_y_;
  double max_y_;

  double scale_;

public:
  ViewWidget(QWidget* parent = 0);

  virtual void mouseMoveEvent(QMouseEvent* event);

  virtual void mousePressEvent(QMouseEvent* event);

  virtual void mouseReleaseEvent(QMouseEvent* event);

  virtual void leaveEvent(QEvent* event);

  virtual void wheelEvent(QWheelEvent* event);

  virtual void paintEvent(QPaintEvent* event);

  void updateCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr& new_cloud);

  void setScale(const double scale);

Q_SIGNALS:

protected:
};
}

#endif // DD_OBSTACLE_AXIS_VIEW_WIDGET_H
