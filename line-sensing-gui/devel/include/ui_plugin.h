/********************************************************************************
** Form generated from reading UI file 'plugin.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGIN_H
#define UI_PLUGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "ratio_layouted_frame.h"

QT_BEGIN_NAMESPACE

class Ui_MyPluginWidget
{
public:
    QGridLayout *gridLayout;
    QWidget *toolbar_widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QComboBox *topics_combo_box;
    QPushButton *refresh_topics_push_button;
    QPushButton *zoom_1_push_button;
    QSpinBox *num_gridlines_spin_box;
    QCheckBox *dynamic_range_check_box;
    QDoubleSpinBox *max_range_double_spin_box;
    QPushButton *save_as_image_push_button;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *publish_click_location_check_box;
    QLineEdit *publish_click_location_topic_line_edit;
    QCheckBox *smooth_image_check_box;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *image_layout;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout_4;
    main_gui::RatioLayoutedFrame *image_frame;
    QVBoxLayout *verticalLayout_sliders;
    QLabel *label_right;
    QScrollBar *horizontalScrollBar_right;
    QLabel *label_center;
    QScrollBar *horizontalScrollBar_center;
    QLabel *label_left;
    QScrollBar *horizontalScrollBar_left;

    void setupUi(QWidget *MyPluginWidget)
    {
        if (MyPluginWidget->objectName().isEmpty())
            MyPluginWidget->setObjectName(QStringLiteral("MyPluginWidget"));
        MyPluginWidget->setEnabled(true);
        MyPluginWidget->resize(453, 410);
        gridLayout = new QGridLayout(MyPluginWidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        toolbar_widget = new QWidget(MyPluginWidget);
        toolbar_widget->setObjectName(QStringLiteral("toolbar_widget"));
        verticalLayout_2 = new QVBoxLayout(toolbar_widget);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        topics_combo_box = new QComboBox(toolbar_widget);
        topics_combo_box->setObjectName(QStringLiteral("topics_combo_box"));
        topics_combo_box->setSizeAdjustPolicy(QComboBox::AdjustToContents);

        horizontalLayout_3->addWidget(topics_combo_box);

        refresh_topics_push_button = new QPushButton(toolbar_widget);
        refresh_topics_push_button->setObjectName(QStringLiteral("refresh_topics_push_button"));
        QIcon icon;
        QString iconThemeName = QStringLiteral("view-refresh");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon = QIcon::fromTheme(iconThemeName);
        } else {
            icon.addFile(QStringLiteral("../../../../../.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        }
        refresh_topics_push_button->setIcon(icon);

        horizontalLayout_3->addWidget(refresh_topics_push_button);

        zoom_1_push_button = new QPushButton(toolbar_widget);
        zoom_1_push_button->setObjectName(QStringLiteral("zoom_1_push_button"));
        zoom_1_push_button->setEnabled(false);
        QIcon icon1;
        iconThemeName = QStringLiteral("zoom-original");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon1 = QIcon::fromTheme(iconThemeName);
        } else {
            icon1.addFile(QStringLiteral("../../../../../.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        }
        zoom_1_push_button->setIcon(icon1);
        zoom_1_push_button->setCheckable(true);

        horizontalLayout_3->addWidget(zoom_1_push_button);

        num_gridlines_spin_box = new QSpinBox(toolbar_widget);
        num_gridlines_spin_box->setObjectName(QStringLiteral("num_gridlines_spin_box"));
        num_gridlines_spin_box->setMinimum(0);
        num_gridlines_spin_box->setMaximum(20);
        num_gridlines_spin_box->setValue(0);

        horizontalLayout_3->addWidget(num_gridlines_spin_box);

        dynamic_range_check_box = new QCheckBox(toolbar_widget);
        dynamic_range_check_box->setObjectName(QStringLiteral("dynamic_range_check_box"));

        horizontalLayout_3->addWidget(dynamic_range_check_box);

        max_range_double_spin_box = new QDoubleSpinBox(toolbar_widget);
        max_range_double_spin_box->setObjectName(QStringLiteral("max_range_double_spin_box"));
        max_range_double_spin_box->setMinimum(0.01);
        max_range_double_spin_box->setMaximum(100);
        max_range_double_spin_box->setValue(10);

        horizontalLayout_3->addWidget(max_range_double_spin_box);

        save_as_image_push_button = new QPushButton(toolbar_widget);
        save_as_image_push_button->setObjectName(QStringLiteral("save_as_image_push_button"));
        QIcon icon2;
        iconThemeName = QStringLiteral("image-x-generic");
        if (QIcon::hasThemeIcon(iconThemeName)) {
            icon2 = QIcon::fromTheme(iconThemeName);
        } else {
            icon2.addFile(QStringLiteral("../../../../../.designer/backup"), QSize(), QIcon::Normal, QIcon::Off);
        }
        save_as_image_push_button->setIcon(icon2);
        save_as_image_push_button->setIconSize(QSize(16, 16));

        horizontalLayout_3->addWidget(save_as_image_push_button);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        publish_click_location_check_box = new QCheckBox(toolbar_widget);
        publish_click_location_check_box->setObjectName(QStringLiteral("publish_click_location_check_box"));

        horizontalLayout->addWidget(publish_click_location_check_box);

        publish_click_location_topic_line_edit = new QLineEdit(toolbar_widget);
        publish_click_location_topic_line_edit->setObjectName(QStringLiteral("publish_click_location_topic_line_edit"));

        horizontalLayout->addWidget(publish_click_location_topic_line_edit);

        smooth_image_check_box = new QCheckBox(toolbar_widget);
        smooth_image_check_box->setObjectName(QStringLiteral("smooth_image_check_box"));

        horizontalLayout->addWidget(smooth_image_check_box);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);


        gridLayout->addWidget(toolbar_widget, 0, 0, 1, 1);

        image_layout = new QHBoxLayout();
        image_layout->setSpacing(0);
        image_layout->setObjectName(QStringLiteral("image_layout"));
        image_layout->setSizeConstraint(QLayout::SetNoConstraint);
        scrollArea = new QScrollArea(MyPluginWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setFrameShape(QFrame::NoFrame);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 433, 155));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        horizontalLayout_4 = new QHBoxLayout(scrollAreaWidgetContents);
        horizontalLayout_4->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        image_frame = new main_gui::RatioLayoutedFrame(scrollAreaWidgetContents);
        image_frame->setObjectName(QStringLiteral("image_frame"));
        image_frame->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(image_frame->sizePolicy().hasHeightForWidth());
        image_frame->setSizePolicy(sizePolicy1);
        image_frame->setMinimumSize(QSize(80, 60));
        image_frame->setContextMenuPolicy(Qt::ActionsContextMenu);
        image_frame->setProperty("lineWidth", QVariant(1));

        horizontalLayout_4->addWidget(image_frame);

        scrollArea->setWidget(scrollAreaWidgetContents);

        image_layout->addWidget(scrollArea);


        gridLayout->addLayout(image_layout, 1, 0, 1, 1);

        verticalLayout_sliders = new QVBoxLayout();
        verticalLayout_sliders->setObjectName(QStringLiteral("verticalLayout_sliders"));
        label_right = new QLabel(MyPluginWidget);
        label_right->setObjectName(QStringLiteral("label_right"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_right->sizePolicy().hasHeightForWidth());
        label_right->setSizePolicy(sizePolicy2);

        verticalLayout_sliders->addWidget(label_right);

        horizontalScrollBar_right = new QScrollBar(MyPluginWidget);
        horizontalScrollBar_right->setObjectName(QStringLiteral("horizontalScrollBar_right"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(horizontalScrollBar_right->sizePolicy().hasHeightForWidth());
        horizontalScrollBar_right->setSizePolicy(sizePolicy3);
        horizontalScrollBar_right->setMinimumSize(QSize(200, 0));
        horizontalScrollBar_right->setMouseTracking(true);
        horizontalScrollBar_right->setFocusPolicy(Qt::ClickFocus);
        horizontalScrollBar_right->setOrientation(Qt::Horizontal);

        verticalLayout_sliders->addWidget(horizontalScrollBar_right);

        label_center = new QLabel(MyPluginWidget);
        label_center->setObjectName(QStringLiteral("label_center"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_center->sizePolicy().hasHeightForWidth());
        label_center->setSizePolicy(sizePolicy4);

        verticalLayout_sliders->addWidget(label_center);

        horizontalScrollBar_center = new QScrollBar(MyPluginWidget);
        horizontalScrollBar_center->setObjectName(QStringLiteral("horizontalScrollBar_center"));
        horizontalScrollBar_center->setMouseTracking(true);
        horizontalScrollBar_center->setFocusPolicy(Qt::ClickFocus);
        horizontalScrollBar_center->setOrientation(Qt::Horizontal);

        verticalLayout_sliders->addWidget(horizontalScrollBar_center);

        label_left = new QLabel(MyPluginWidget);
        label_left->setObjectName(QStringLiteral("label_left"));
        sizePolicy4.setHeightForWidth(label_left->sizePolicy().hasHeightForWidth());
        label_left->setSizePolicy(sizePolicy4);

        verticalLayout_sliders->addWidget(label_left);

        horizontalScrollBar_left = new QScrollBar(MyPluginWidget);
        horizontalScrollBar_left->setObjectName(QStringLiteral("horizontalScrollBar_left"));
        horizontalScrollBar_left->setMouseTracking(true);
        horizontalScrollBar_left->setFocusPolicy(Qt::ClickFocus);
        horizontalScrollBar_left->setOrientation(Qt::Horizontal);

        verticalLayout_sliders->addWidget(horizontalScrollBar_left);


        gridLayout->addLayout(verticalLayout_sliders, 2, 0, 1, 1);

        toolbar_widget->raise();

        retranslateUi(MyPluginWidget);

        QMetaObject::connectSlotsByName(MyPluginWidget);
    } // setupUi

    void retranslateUi(QWidget *MyPluginWidget)
    {
        MyPluginWidget->setWindowTitle(QApplication::translate("MyPluginWidget", "Line Calibration", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        refresh_topics_push_button->setToolTip(QApplication::translate("MyPluginWidget", "Refresh topics", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        zoom_1_push_button->setToolTip(QApplication::translate("MyPluginWidget", "Original zoom", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        num_gridlines_spin_box->setToolTip(QApplication::translate("MyPluginWidget", "# of gridlines to overlay", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        dynamic_range_check_box->setToolTip(QApplication::translate("MyPluginWidget", "Dynamic depth range", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        dynamic_range_check_box->setText(QString());
#ifndef QT_NO_TOOLTIP
        max_range_double_spin_box->setToolTip(QApplication::translate("MyPluginWidget", "Max depth", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        max_range_double_spin_box->setSuffix(QApplication::translate("MyPluginWidget", "m", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        save_as_image_push_button->setToolTip(QApplication::translate("MyPluginWidget", "Save as image", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        publish_click_location_check_box->setText(QString());
#ifndef QT_NO_TOOLTIP
        publish_click_location_topic_line_edit->setToolTip(QApplication::translate("MyPluginWidget", "Click location topic (leave empty for auto-naming)", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        smooth_image_check_box->setToolTip(QApplication::translate("MyPluginWidget", "Dynamic depth range", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        smooth_image_check_box->setText(QApplication::translate("MyPluginWidget", "Smooth scaling", Q_NULLPTR));
        label_right->setText(QApplication::translate("MyPluginWidget", "<html><head/><body><p align=\"center\">Right -</p></body></html>", Q_NULLPTR));
        label_center->setText(QApplication::translate("MyPluginWidget", "<html><head/><body><p align=\"center\">Center - </p></body></html>", Q_NULLPTR));
        label_left->setText(QApplication::translate("MyPluginWidget", "<html><head/><body><p align=\"center\">Left - </p></body></html>", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyPluginWidget: public Ui_MyPluginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGIN_H
