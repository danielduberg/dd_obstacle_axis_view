#include <dd_obstacle_axis_view/view_widget.h>

#include <QPainter>
#include <QPoint>

namespace dd_obstacle_axis_view
{
ViewWidget::ViewWidget(QWidget* parent)
    : cloud_(new pcl::PointCloud<pcl::PointXYZ>), center_x_(0), center_y_(0),
      min_x_(-1), max_x_(1), min_y_(-1), max_y_(1), scale_(40.0),
      left_button_pressed_(false), right_button_pressed_(false)
{
}

void ViewWidget::mouseMoveEvent(QMouseEvent* event)
{
  // TODO: Implement
  std::cout << "Mouse move event" << std::endl;

  if (event->buttons() == Qt::RightButton)
  {
    // event->
  }

  std::cout << "[" << event->localPos().x() << ", " << event->localPos().y()
            << "], [" << event->pos().rx() << ", " << event->pos().ry()
            << "], [" << event->globalPos().rx() << ", "
            << event->globalPos().ry() << "]" << std::endl;

  event->accept();
  // update();
}

void ViewWidget::mousePressEvent(QMouseEvent* event)
{
  // TODO: Implement
  std::cout << "Mouse press event" << std::endl;

  if (event->buttons() == Qt::LeftButton)
  {
    left_button_pressed_ = true;
    left_button_pos_ = event->globalPos();
  }

  if (event->buttons() == Qt::RightButton)
  {
    right_button_pressed_ = true;
    right_button_pos_ = event->globalPos();
  }

  event->accept();
  update();
}

void ViewWidget::mouseReleaseEvent(QMouseEvent* event)
{
  // TODO: Implement
  std::cout << "Mouse release event" << std::endl;

  event->accept();
  update();
}

void ViewWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
  // TODO: Implement
  if (event->buttons() == Qt::LeftButton)
  {
    double span_x = max_x_ - min_x_;
    double span_y = max_y_ - min_y_;

    max_x_ = span_x / 2.0;
    min_x_ = -max_x_;

    max_y_ = span_y / 2.0;
    min_y_ = -max_y_;

    event->accept();
    update();
  }
}

void ViewWidget::leaveEvent(QEvent* event)
{
  // TODO: Implement
  std::cout << "Leave event" << std::endl;

  event->accept();
  update();
}

void ViewWidget::wheelEvent(QWheelEvent* event)
{
  std::cout << "Wheel event" << std::endl;
  // http://doc.qt.io/qt-5/qwheelevent.html#details
  QPoint num_pixels = event->pixelDelta();
  QPoint num_degrees = event->angleDelta() / 8;

  if (!num_pixels.isNull())
  {
    // TODO: Implement
    // num_pixels
  }
  else if (!num_degrees.isNull())
  {
    QPoint num_steps = num_degrees / 15;
    double current_x_span = max_x_ - min_x_;
    double current_y_span = max_y_ - min_y_;

    const int& y_steps = num_steps.ry();

    if (y_steps > 0)
    {
      // Zoom in
      for (int i = 0; i < y_steps; ++i)
      {
        // TODO: Check so that max >= min?

        if (current_x_span <= 0)
        {
          break;
        }
        else
        {
          min_x_ += (current_x_span / 20);
          max_x_ -= (current_x_span / 20);
        }

        if (current_y_span <= 0)
        {
          break;
        }
        else
        {
          min_y_ += (current_y_span / 20);
          max_y_ -= (current_y_span / 20);
        }

        current_x_span = max_x_ - min_x_;
        current_y_span = max_y_ - min_y_;
      }
    }
    else if (y_steps < 0)
    {
      // Zoom out
      for (int i = 0; i > y_steps; --i)
      {
        // TODO: Check so that max >= min?

        min_x_ -= (current_x_span / 20);
        max_x_ += (current_x_span / 20);

        min_y_ -= (current_y_span / 20);
        max_y_ += (current_y_span / 20);

        current_x_span = max_x_ - min_x_;
        current_y_span = max_y_ - min_y_;
      }
    }
  }

  event->accept();

  update();
}

void ViewWidget::paintEvent(QPaintEvent* event)
{
  std::cout << "Paint event" << std::endl;
  QColor background;
  QColor lines;
  if (isEnabled())
  {
    background = Qt::white;
    lines = Qt::black;
  }
  else
  {
    background = Qt::lightGray;
    lines = Qt::darkGray;
  }

  int w = width();
  int h = height();
  std::cout << "Width: " << w << ", height: " << h << std::endl;
  int size = ((w > h) ? h : w) - 1;
  int horizontal_padding = (w - size) / 2;
  int vertical_padding = (h - size) / 2;

  QPainter painter(this);
  painter.setBrush(background);
  painter.setPen(lines);

  painter.drawRect(QRect(0, 0, w, h));

  background = Qt::black;
  painter.setBrush(background);

  // Fill in the CloudIn data
  cloud_->width = 1;
  cloud_->height = 1;
  cloud_->is_dense = false;
  cloud_->points.resize(cloud_->width * cloud_->height);
  //  for (size_t i = 0; i < cloud_->points.size(); ++i)
  //  {
  //    cloud_->points[i].x = 1024 * rand() / (RAND_MAX + 1.0f);
  //    cloud_->points[i].y = 1024 * rand() / (RAND_MAX + 1.0f);
  //    cloud_->points[i].z = 1024 * rand() / (RAND_MAX + 1.0f);
  //    std::cout << "    " << cloud_->points[i].x << " " << cloud_->points[i].y
  //              << " " << cloud_->points[i].z << std::endl;
  //  }
  cloud_->points[0].x = 0.9;
  cloud_->points[0].y = 0;
  cloud_->points[0].z = 0;

  if (isEnabled() && cloud_->size() > 0)
  {
    double x_total = max_x_ - min_x_;
    double y_total = max_y_ - min_y_;

    for (pcl::PointCloud<pcl::PointXYZ>::iterator it = cloud_->begin();
         it != cloud_->end(); ++it)
    {
      if (it->x >= min_x_ && it->x <= max_x_ && it->y >= min_y_ &&
          it->y <= max_y_)
      {
        double x_coord = it->x - min_x_;
        x_coord = w * (x_coord / x_total);
        double y_coord = it->y - min_y_;
        y_coord = h * (y_coord / y_total);

        painter.drawEllipse((int)x_coord, (int)y_coord, size / scale_,
                            size / scale_);
        // painter.draw
      }
    }
  }

  // TODO: Draw robot
}

void ViewWidget::updateCloud(pcl::PointCloud<pcl::PointXYZ>::Ptr& new_cloud)
{
  cloud_ = new_cloud;
  update();
}

void ViewWidget::setScale(const double scale)
{
  scale_ = scale;
  update();
}
}
