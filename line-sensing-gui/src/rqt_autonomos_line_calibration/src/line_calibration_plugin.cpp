/*
  Copyright 2016 Lucas Walter
*/

#include "line_calibration_plugin.h"

#include <pluginlib/class_list_macros.h>
#include <QStringList>

#include <ui_line_calibration_plugin.h>
#include <pluginlib/class_list_macros.h>
#include <ros/master.h>
#include <sensor_msgs/image_encodings.h>

#include <cv_bridge/cv_bridge.h>
#include <opencv2/imgproc/imgproc.hpp>

#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>

#include <stdio.h>

#define MIN_VAL 0
#define MAX_VAL 160


namespace rqt_autonomos_line_calibration
{

line_calibration_plugin::line_calibration_plugin()
  : rqt_gui_cpp::Plugin()
  , widget_(0)
  , num_gridlines_(0)
{
  // Constructor is called first before initPlugin function, needless to say.

  // give QObjects reasonable names
  setObjectName("line_calibration_plugin");
}

void line_calibration_plugin::initPlugin(qt_gui_cpp::PluginContext& context)
{
  // access standalone command line arguments
  // QStringList argv = context.argv();
  // // create QWidget
  // widget_ = new QWidget();
  // // extend the widget with all attributes and children from UI file
  // ui_.setupUi(widget_);
  // // add widget to the user interface
  // context.addWidget(widget_);
  
  widget_ = new QWidget();
  ui_.setupUi(widget_);

  if (context.serialNumber() > 1)
  {
    widget_->setWindowTitle(widget_->windowTitle() + " (" + QString::number(context.serialNumber()) + ")");
  }
  context.addWidget(widget_);

  updateTopicList();
  ui_.topics_combo_box->setCurrentIndex(ui_.topics_combo_box->findText(""));
  connect(ui_.topics_combo_box, SIGNAL(currentIndexChanged(int)), this, SLOT(onTopicChanged(int)));

  ui_.refresh_topics_push_button->setIcon(QIcon::fromTheme("view-refresh"));
  connect(ui_.refresh_topics_push_button, SIGNAL(pressed()), this, SLOT(updateTopicList()));

  ui_.zoom_1_push_button->setIcon(QIcon::fromTheme("zoom-original"));
  connect(ui_.zoom_1_push_button, SIGNAL(toggled(bool)), this, SLOT(onZoom1(bool)));

  connect(ui_.dynamic_range_check_box, SIGNAL(toggled(bool)), this, SLOT(onDynamicRange(bool)));

  ui_.save_as_image_push_button->setIcon(QIcon::fromTheme("document-save-as"));
  connect(ui_.save_as_image_push_button, SIGNAL(pressed()), this, SLOT(saveImage()));

  connect(ui_.num_gridlines_spin_box, SIGNAL(valueChanged(int)), this, SLOT(updateNumGridlines()));

  // set topic name if passed in as argument
  const QStringList& argv = context.argv();
  if (!argv.empty()) {
    arg_topic_name = argv[0];
    selectTopic(arg_topic_name);
  }
  pub_topic_custom_ = false;

  ui_.image_frame->setOuterLayout(ui_.image_layout);

  QRegExp rx("([a-zA-Z/][a-zA-Z0-9_/]*)?"); //see http://www.ros.org/wiki/ROS/Concepts#Names.Valid_Names (but also accept an empty field)
  ui_.publish_click_location_topic_line_edit->setValidator(new QRegExpValidator(rx, this));
  connect(ui_.publish_click_location_check_box, SIGNAL(toggled(bool)), this, SLOT(onMousePublish(bool)));
  connect(ui_.image_frame, SIGNAL(mouseLeft(int, int)), this, SLOT(onMouseLeft(int, int)));
  connect(ui_.publish_click_location_topic_line_edit, SIGNAL(editingFinished()), this, SLOT(onPubTopicChanged()));

  connect(ui_.smooth_image_check_box, SIGNAL(toggled(bool)), ui_.image_frame, SLOT(onSmoothImageChanged(bool)));

  hide_toolbar_action_ = new QAction(tr("Hide toolbar"), this);
  hide_toolbar_action_->setCheckable(true);
  ui_.image_frame->addAction(hide_toolbar_action_);
  connect(hide_toolbar_action_, SIGNAL(toggled(bool)), this, SLOT(onHideToolbarChanged(bool)));

  set_sliders_min_val(MIN_VAL);
  set_sliders_max_val(MAX_VAL);

  connect(ui_.horizontalScrollBar_right,  SIGNAL(valueChanged(int)), this, SLOT(right_scroll_changed()));
  connect(ui_.horizontalScrollBar_center, SIGNAL(valueChanged(int)), this, SLOT(center_scroll_changed()));
  connect(ui_.horizontalScrollBar_left,   SIGNAL(valueChanged(int)), this, SLOT(left_scroll_changed()));

  int default_x_center, default_x_right, default_x_left;
  ros::param::param<int>("/line_detection_fu_node/defaultXCenter", default_x_center, -1);
  ros::param::param<int>("/line_detection_fu_node/defaultXLeft", default_x_left, -1);
  ros::param::param<int>("/line_detection_fu_node/defaultXRight", default_x_right, -1);

  ui_.horizontalScrollBar_right -> setValue(default_x_right);
  ui_.horizontalScrollBar_center -> setValue(default_x_center);
  ui_.horizontalScrollBar_left -> setValue(default_x_left);

}

void line_calibration_plugin::shutdownPlugin()
{
  // unregister all publishers here

  subscriber_.shutdown();
  pub_mouse_left_.shutdown();
}

void line_calibration_plugin::saveSettings(qt_gui_cpp::Settings& plugin_settings,
    qt_gui_cpp::Settings& instance_settings) const
{
  QString topic = ui_.topics_combo_box->currentText();
  qDebug("ImageView::saveSettings() topic '%s'", topic.toStdString().c_str());
  instance_settings.setValue("topic", topic);
  instance_settings.setValue("zoom1", ui_.zoom_1_push_button->isChecked());
  instance_settings.setValue("dynamic_range", ui_.dynamic_range_check_box->isChecked());
  instance_settings.setValue("max_range", ui_.max_range_double_spin_box->value());
  instance_settings.setValue("publish_click_location", ui_.publish_click_location_check_box->isChecked());
  instance_settings.setValue("mouse_pub_topic", ui_.publish_click_location_topic_line_edit->text());
  instance_settings.setValue("toolbar_hidden", hide_toolbar_action_->isChecked());
  instance_settings.setValue("num_gridlines", ui_.num_gridlines_spin_box->value());
}

void line_calibration_plugin::restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
    const qt_gui_cpp::Settings& instance_settings)
{
    bool zoom1_checked = instance_settings.value("zoom1", false).toBool();
  ui_.zoom_1_push_button->setChecked(zoom1_checked);

  bool dynamic_range_checked = instance_settings.value("dynamic_range", false).toBool();
  ui_.dynamic_range_check_box->setChecked(dynamic_range_checked);

  double max_range = instance_settings.value("max_range", ui_.max_range_double_spin_box->value()).toDouble();
  ui_.max_range_double_spin_box->setValue(max_range);

  num_gridlines_ = instance_settings.value("num_gridlines", ui_.num_gridlines_spin_box->value()).toInt();
  ui_.num_gridlines_spin_box->setValue(num_gridlines_);

  QString topic = instance_settings.value("topic", "").toString();
  // don't overwrite topic name passed as command line argument
  if (!arg_topic_name.isEmpty())
  {
    arg_topic_name = "";
  }
  else
  {
    //qDebug("ImageView::restoreSettings() topic '%s'", topic.toStdString().c_str());
    selectTopic(topic);
  }

  bool publish_click_location = instance_settings.value("publish_click_location", false).toBool();
  ui_.publish_click_location_check_box->setChecked(publish_click_location);

  QString pub_topic = instance_settings.value("mouse_pub_topic", "").toString();
  ui_.publish_click_location_topic_line_edit->setText(pub_topic);

  bool toolbar_hidden = instance_settings.value("toolbar_hidden", false).toBool();
  hide_toolbar_action_->setChecked(toolbar_hidden);
}

void line_calibration_plugin::updateTopicList()
{
  QSet<QString> message_types;
  message_types.insert("sensor_msgs/Image");
  QSet<QString> message_sub_types;
  message_sub_types.insert("sensor_msgs/CompressedImage");

  // get declared transports
  QList<QString> transports;
  image_transport::ImageTransport it(getNodeHandle());
  std::vector<std::string> declared = it.getDeclaredTransports();
  for (std::vector<std::string>::const_iterator it = declared.begin(); it != declared.end(); it++)
  {
    //qDebug("ImageView::updateTopicList() declared transport '%s'", it->c_str());
    QString transport = it->c_str();

    // strip prefix from transport name
    QString prefix = "image_transport/";
    if (transport.startsWith(prefix))
    {
      transport = transport.mid(prefix.length());
    }
    transports.append(transport);
  }

  QString selected = ui_.topics_combo_box->currentText();

  // fill combo box
  QList<QString> topics = getTopics(message_types, message_sub_types, transports).values();
  topics.append("");
  qSort(topics);
  ui_.topics_combo_box->clear();
  for (QList<QString>::const_iterator it = topics.begin(); it != topics.end(); it++)
  {
    QString label(*it);
    label.replace(" ", "/");
    ui_.topics_combo_box->addItem(label, QVariant(*it));
  }

  // restore previous selection
  selectTopic(selected);
}

QList<QString> line_calibration_plugin::getTopicList(const QSet<QString>& message_types, const QList<QString>& transports)
{
  QSet<QString> message_sub_types;
  return getTopics(message_types, message_sub_types, transports).values();
}

QSet<QString> line_calibration_plugin::getTopics(const QSet<QString>& message_types, const QSet<QString>& message_sub_types, const QList<QString>& transports)
{
  ros::master::V_TopicInfo topic_info;
  ros::master::getTopics(topic_info);

  QSet<QString> all_topics;
  for (ros::master::V_TopicInfo::const_iterator it = topic_info.begin(); it != topic_info.end(); it++)
  {
    all_topics.insert(it->name.c_str());
  }

  QSet<QString> topics;
  for (ros::master::V_TopicInfo::const_iterator it = topic_info.begin(); it != topic_info.end(); it++)
  {
    if (message_types.contains(it->datatype.c_str()))
    {
      QString topic = it->name.c_str();

      // add raw topic
      topics.insert(topic);
      //qDebug("ImageView::getTopics() raw topic '%s'", topic.toStdString().c_str());

      // add transport specific sub-topics
      for (QList<QString>::const_iterator jt = transports.begin(); jt != transports.end(); jt++)
      {
        if (all_topics.contains(topic + "/" + *jt))
        {
          QString sub = topic + " " + *jt;
          topics.insert(sub);
          //qDebug("ImageView::getTopics() transport specific sub-topic '%s'", sub.toStdString().c_str());
        }
      }
    }
    if (message_sub_types.contains(it->datatype.c_str()))
    {
      QString topic = it->name.c_str();
      int index = topic.lastIndexOf("/");
      if (index != -1)
      {
        topic.replace(index, 1, " ");
        topics.insert(topic);
        //qDebug("ImageView::getTopics() transport specific sub-topic '%s'", topic.toStdString().c_str());
      }
    }
  }
  return topics;
}

void line_calibration_plugin::selectTopic(const QString& topic)
{
  int index = ui_.topics_combo_box->findText(topic);
  if (index == -1)
  {
    // add topic name to list if not yet in
    QString label(topic);
    label.replace(" ", "/");
    ui_.topics_combo_box->addItem(label, QVariant(topic));
    index = ui_.topics_combo_box->findText(topic);
  }
  ui_.topics_combo_box->setCurrentIndex(index);
}

void line_calibration_plugin::onTopicChanged(int index)
{
  subscriber_.shutdown();

  // reset image on topic change
  ui_.image_frame->setImage(QImage());

  QStringList parts = ui_.topics_combo_box->itemData(index).toString().split(" ");
  QString topic = parts.first();
  QString transport = parts.length() == 2 ? parts.last() : "raw";

  if (!topic.isEmpty())
  {
    image_transport::ImageTransport it(getNodeHandle());
    image_transport::TransportHints hints(transport.toStdString());
    try {
      subscriber_ = it.subscribe(topic.toStdString(), 1, &line_calibration_plugin::callbackImage, this, hints);
      //qDebug("ImageView::onTopicChanged() to topic '%s' with transport '%s'", topic.toStdString().c_str(), subscriber_.getTransport().c_str());
    } catch (image_transport::TransportLoadException& e) {
      QMessageBox::warning(widget_, tr("Loading image transport plugin failed"), e.what());
    }
  }

  onMousePublish(ui_.publish_click_location_check_box->isChecked());
}

void line_calibration_plugin::onZoom1(bool checked)
{
  if (checked)
  {
    if (ui_.image_frame->getImage().isNull())
    {
      return;
    }
    ui_.image_frame->setInnerFrameFixedSize(ui_.image_frame->getImage().size());
  } else {
    ui_.image_frame->setInnerFrameMinimumSize(QSize(80, 60));
    ui_.image_frame->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
    widget_->setMinimumSize(QSize(80, 60));
    widget_->setMaximumSize(QSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX));
  }
}

void line_calibration_plugin::onDynamicRange(bool checked)
{
  ui_.max_range_double_spin_box->setEnabled(!checked);
}

void line_calibration_plugin::updateNumGridlines()
{
  num_gridlines_ = ui_.num_gridlines_spin_box->value();
}

void line_calibration_plugin::saveImage()
{
  // take a snapshot before asking for the filename
  QImage img = ui_.image_frame->getImageCopy();

  QString file_name = QFileDialog::getSaveFileName(widget_, tr("Save as image"), "image.png", tr("Image (*.bmp *.jpg *.png *.tiff)"));
  if (file_name.isEmpty())
  {
    return;
  }

  img.save(file_name);
}

void line_calibration_plugin::onMousePublish(bool checked)
{
  std::string topicName;
  if(pub_topic_custom_)
  {
    topicName = ui_.publish_click_location_topic_line_edit->text().toStdString();
  } else {
    if(!subscriber_.getTopic().empty())
    {
      topicName = subscriber_.getTopic()+"_mouse_left";
    } else {
      topicName = "mouse_left";
    }
    ui_.publish_click_location_topic_line_edit->setText(QString::fromStdString(topicName));
  }

  if(checked)
  {
    pub_mouse_left_ = getNodeHandle().advertise<geometry_msgs::Point>(topicName, 1000);
  } else {
    pub_mouse_left_.shutdown();
  }
}

void line_calibration_plugin::onMouseLeft(int x, int y)
{
  if(ui_.publish_click_location_check_box->isChecked() && !ui_.image_frame->getImage().isNull())
  {
    geometry_msgs::Point clickLocation;
    // Publish click location in pixel coordinates
    clickLocation.x = round((double)x/(double)ui_.image_frame->width()*(double)ui_.image_frame->getImage().width());
    clickLocation.y = round((double)y/(double)ui_.image_frame->height()*(double)ui_.image_frame->getImage().height());
    clickLocation.z = 0;
    pub_mouse_left_.publish(clickLocation);
  }
}

void line_calibration_plugin::onPubTopicChanged()
{
  pub_topic_custom_ = !(ui_.publish_click_location_topic_line_edit->text().isEmpty());
  onMousePublish(ui_.publish_click_location_check_box->isChecked());
}

void line_calibration_plugin::onHideToolbarChanged(bool hide)
{
  ui_.toolbar_widget->setVisible(!hide);
}

void line_calibration_plugin::invertPixels(int x, int y)
{
  // Could do 255-conversion_mat_.at<cv::Vec3b>(cv::Point(x,y))[i], but that doesn't work well on gray
  cv::Vec3b & pixel = conversion_mat_.at<cv::Vec3b>(cv::Point(x, y));
  if (pixel[0] + pixel[1] + pixel[2] > 3 * 127)
    pixel = cv::Vec3b(0,0,0);
  else
    pixel = cv::Vec3b(255,255,255);
}

QList<int> line_calibration_plugin::getGridIndices(int size) const
{
  QList<int> indices;

  // the spacing between adjacent grid lines
  float grid_width = 1.0f * size / (num_gridlines_ + 1);

  // select grid line(s) closest to the center
  float index;
  if (num_gridlines_ % 2)  // odd
  {
    indices.append(size / 2);
    // make the center line 2px wide in case of an even resolution
    if (size % 2 == 0)  // even
      indices.append(size / 2 - 1);
    index = 1.0f * (size - 1) / 2;
  }
  else  // even
  {
    index = grid_width * (num_gridlines_ / 2);
    // one grid line before the center
    indices.append(round(index));
    // one grid line after the center
    indices.append(size - 1 - round(index));
  }

  // add additional grid lines from the center to the border of the image
  int lines = (num_gridlines_ - 1) / 2;
  while (lines > 0)
  {
    index -= grid_width;
    indices.append(round(index));
    indices.append(size - 1 - round(index));
    lines--;
  }

  return indices;
}

void line_calibration_plugin::overlayGrid()
{
  // vertical gridlines
  QList<int> columns = getGridIndices(conversion_mat_.cols);
  for (QList<int>::const_iterator x = columns.begin(); x != columns.end(); ++x)
  {
    for (int y = 0; y < conversion_mat_.rows; ++y)
    {
      invertPixels(*x, y);
    }
  }

  // horizontal gridlines
  QList<int> rows = getGridIndices(conversion_mat_.rows);
  for (QList<int>::const_iterator y = rows.begin(); y != rows.end(); ++y)
  {
    for (int x = 0; x < conversion_mat_.cols; ++x)
    {
      invertPixels(x, *y);
    }
  }
}

void line_calibration_plugin::callbackImage(const sensor_msgs::Image::ConstPtr& msg)
{
  try
  {
    // First let cv_bridge do its magic
    cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg, sensor_msgs::image_encodings::RGB8);
    conversion_mat_ = cv_ptr->image;

    if (num_gridlines_ > 0)
      overlayGrid();
  }
  catch (cv_bridge::Exception& e)
  {
    try
    {
      // If we're here, there is no conversion that makes sense, but let's try to imagine a few first
      cv_bridge::CvImageConstPtr cv_ptr = cv_bridge::toCvShare(msg);
      if (msg->encoding == "CV_8UC3")
      {
        // assuming it is rgb
        conversion_mat_ = cv_ptr->image;
      } else if (msg->encoding == "8UC1") {
        // convert gray to rgb
        cv::cvtColor(cv_ptr->image, conversion_mat_, CV_GRAY2RGB);
      } else if (msg->encoding == "16UC1" || msg->encoding == "32FC1") {
        // scale / quantify
        double min = 0;
        double max = ui_.max_range_double_spin_box->value();
        if (msg->encoding == "16UC1") max *= 1000;
        if (ui_.dynamic_range_check_box->isChecked())
        {
          // dynamically adjust range based on min/max in image
          cv::minMaxLoc(cv_ptr->image, &min, &max);
          if (min == max) {
            // completely homogeneous images are displayed in gray
            min = 0;
            max = 2;
          }
        }
        cv::Mat img_scaled_8u;
        cv::Mat(cv_ptr->image-min).convertTo(img_scaled_8u, CV_8UC1, 255. / (max - min));
        cv::cvtColor(img_scaled_8u, conversion_mat_, CV_GRAY2RGB);
      } else {
        qWarning("line_calibration_plugin.callback_image() could not convert image from '%s' to 'rgb8' (%s)", msg->encoding.c_str(), e.what());
        ui_.image_frame->setImage(QImage());
        return;
      }
    }
    catch (cv_bridge::Exception& e)
    {
      qWarning("line_calibration_plugin.callback_image() while trying to convert image from '%s' to 'rgb8' an exception was thrown (%s)", msg->encoding.c_str(), e.what());
      ui_.image_frame->setImage(QImage());
      return;
    }
  }

  // image must be copied since it uses the conversion_mat_ for storage which is asynchronously overwritten in the next callback invocation
  QImage image(conversion_mat_.data, conversion_mat_.cols, conversion_mat_.rows, conversion_mat_.step[0], QImage::Format_RGB888);
  ui_.image_frame->setImage(image);

  if (!ui_.zoom_1_push_button->isEnabled())
  {
    ui_.zoom_1_push_button->setEnabled(true);
  }
  // Need to update the zoom 1 every new image in case the image aspect ratio changed,
  // though could check and see if the aspect ratio changed or not.
  onZoom1(ui_.zoom_1_push_button->isChecked());
}

void line_calibration_plugin::set_sliders_min_val(int min_val)
{
  ui_.horizontalScrollBar_right->setMinimum(min_val);
  ui_.horizontalScrollBar_center->setMinimum(min_val);
  ui_.horizontalScrollBar_left->setMinimum(min_val);
}

void line_calibration_plugin::set_sliders_max_val(int max_val)
{
  ui_.horizontalScrollBar_right  -> setMaximum(max_val);
  ui_.horizontalScrollBar_center -> setMaximum(max_val);
  ui_.horizontalScrollBar_left   -> setMaximum(max_val);
}


void line_calibration_plugin::right_scroll_changed()
{
  int right_val = ui_.horizontalScrollBar_right->value();
  ui_.label_right->setText(QString("<html><head/><body><p align=\"center\">Right = %1</p></body></html>").arg(right_val));

  dynamic_reconfigure::ReconfigureRequest srv_req;
  dynamic_reconfigure::ReconfigureResponse srv_resp;
  dynamic_reconfigure::IntParameter right_param;
  dynamic_reconfigure::Config conf;
  
  right_param.name = "defaultXRight";
  right_param.value = right_val;
  conf.ints.push_back(right_param);
  
  srv_req.config = conf;
  
  ros::service::call("/line_detection_fu_node/set_parameters", srv_req, srv_resp);
}

void line_calibration_plugin::center_scroll_changed()
{
  // ui_.label_center->setText(QString("<html><head/><body><p align=\"center\">Center - %1</p></body></html>").arg(ui_.horizontalScrollBar_center->value()));
  int center_val = ui_.horizontalScrollBar_center->value();
  ui_.label_center->setText(QString("<html><head/><body><p align=\"center\">Center = %1</p></body></html>").arg(center_val));

  dynamic_reconfigure::ReconfigureRequest srv_req;
  dynamic_reconfigure::ReconfigureResponse srv_resp;
  dynamic_reconfigure::IntParameter center_param;
  dynamic_reconfigure::Config conf;
  
  center_param.name = "defaultXCenter";
  center_param.value = center_val;
  conf.ints.push_back(center_param);
  
  srv_req.config = conf;
  
  ros::service::call("/line_detection_fu_node/set_parameters", srv_req, srv_resp);  
}

void line_calibration_plugin::left_scroll_changed()
{
  // ui_.label_left->setText(QString("<html><head/><body><p align=\"center\">Left - %1</p></body></html>").arg(ui_.horizontalScrollBar_left->value()));
  int left_val = ui_.horizontalScrollBar_left->value();
  ui_.label_left->setText(QString("<html><head/><body><p align=\"center\">Left = %1</p></body></html>").arg(left_val));

  dynamic_reconfigure::ReconfigureRequest srv_req;
  dynamic_reconfigure::ReconfigureResponse srv_resp;
  dynamic_reconfigure::IntParameter left_param;
  dynamic_reconfigure::Config conf;
  
  left_param.name = "defaultXLeft";
  left_param.value = left_val;
  conf.ints.push_back(left_param);
  
  srv_req.config = conf;
  
  ros::service::call("/line_detection_fu_node/set_parameters", srv_req, srv_resp);
}
/*bool hasConfiguration() const
{
  return true;
}

void triggerConfiguration()
{
  // Usually used to open a dialog to offer the user a set of configuration
}*/

}  // namespace rqt_example_cpp
PLUGINLIB_EXPORT_CLASS(rqt_autonomos_line_calibration::line_calibration_plugin, rqt_autonomos_line_calibration::line_calibration_plugin)
PLUGINLIB_DECLARE_CLASS(rqt_autonomos_line_calibration, line_calibration_plugin, rqt_autonomos_line_calibration::line_calibration_plugin, rqt_gui_cpp::Plugin)