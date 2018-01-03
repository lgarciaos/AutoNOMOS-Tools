/*
  Copyright 2016 Lucas Walter
*/
#ifndef MAIN_GUI_PLUGIN_H
#define MAIN_GUI_PLUGIN_H

#include <rqt_gui_cpp/plugin.h>
// #include <rqt_example_cpp/ui_my_plugin.h>
#include <ui_plugin.h>

#include <image_transport/image_transport.h>
#include <ros/package.h>
#include <ros/macros.h>
#include <sensor_msgs/Image.h>
#include <geometry_msgs/Point.h>

#include <opencv2/core/core.hpp>

#include <QAction>
#include <QImage>
#include <QList>
#include <QString>
#include <QSize>
#include <QWidget>

#include <vector>

namespace main_gui
{

class MyPlugin
  : public rqt_gui_cpp::Plugin
{
  Q_OBJECT
public:
  MyPlugin();

  virtual void initPlugin(qt_gui_cpp::PluginContext& context);

  virtual void shutdownPlugin();

  virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings, qt_gui_cpp::Settings& instance_settings) const;

  virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings, const qt_gui_cpp::Settings& instance_settings);
  
  protected slots:

  virtual void updateTopicList();



protected:

  // deprecated function for backward compatibility only, use getTopics() instead
  ROS_DEPRECATED virtual QList<QString> getTopicList(const QSet<QString>& message_types, const QList<QString>& transports);

  virtual QSet<QString> getTopics(const QSet<QString>& message_types, const QSet<QString>& message_sub_types, const QList<QString>& transports);

  virtual void selectTopic(const QString& topic);

protected slots:

  virtual void onTopicChanged(int index);

  virtual void onZoom1(bool checked);

  virtual void onDynamicRange(bool checked);

  virtual void saveImage();

  virtual void updateNumGridlines();

  virtual void onMousePublish(bool checked);

  virtual void onMouseLeft(int x, int y);

  virtual void onPubTopicChanged();

  virtual void onHideToolbarChanged(bool hide);

  void right_scroll_changed();

  void center_scroll_changed();

  void left_scroll_changed();

protected:

  virtual void callbackImage(const sensor_msgs::Image::ConstPtr& msg);

  virtual void invertPixels(int x, int y);

  QList<int> getGridIndices(int size) const;

  virtual void overlayGrid();

  Ui::MyPluginWidget ui_;

  QWidget* widget_;

  image_transport::Subscriber subscriber_;

  cv::Mat conversion_mat_;

private:

  QString arg_topic_name;
  ros::Publisher pub_mouse_left_;

  bool pub_topic_custom_;

  QAction* hide_toolbar_action_;

  int num_gridlines_;

  void set_sliders_min_val(int min_val);
  void set_sliders_max_val(int min_val);



  // virtual void initPlugin(qt_gui_cpp::PluginContext& context);
  // virtual void shutdownPlugin();
  // virtual void saveSettings(qt_gui_cpp::Settings& plugin_settings,
  //     qt_gui_cpp::Settings& instance_settings) const;
  // virtual void restoreSettings(const qt_gui_cpp::Settings& plugin_settings,
  //     const qt_gui_cpp::Settings& instance_settings);

  // Comment in to signal that the plugin has a way to configure it
  // bool hasConfiguration() const;
  // void triggerConfiguration();
// private:
//   Ui::MyPluginWidget ui_;
//   QWidget* widget_;
};
}  // namespace rqt_example_cpp
#endif  // RQT_EXAMPLE_CPP_MY_PLUGIN_H