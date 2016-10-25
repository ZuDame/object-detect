/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QProgressBar *progressBar;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_5;
    QFrame *frame;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_10;
    QLabel *labelGoodMatches;
    QGridLayout *gridLayout1;
    QLabel *label;
    QLineEdit *lineEditMatches;
    QLineEdit *lineEditGoodMatches;
    QLineEdit *lineEditKeyPoints;
    QSpacerItem *horizontalSpacer_2;
    QLabel *labelMatches;
    QLabel *labelKeyPoints;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    QLabel *lbl_oc;
    QLabel *label_4;
    QSpinBox *spinBoxGoodMatchesThreshold;
    QSpinBox *spinBoxMinHessian;
    QLabel *label_3;
    QLabel *label_2;
    QCheckBox *checkBoxExtended;
    QSpinBox *spinBoxOctaveLayers;
    QSpinBox *spinBoxOctaves;
    QLabel *label_6;
    QCheckBox *checkBoxUpright;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_11;
    QPushButton *pushButtonSourceImage;
    QPushButton *pushButtonSceneImage;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_9;
    QLabel *label_7;
    QGridLayout *gridLayout_7;
    QLineEdit *lineEditExecutionTimeCpu;
    QLineEdit *lineEditExecutionTimeGpu;
    QSpacerItem *horizontalSpacer;
    QLabel *label_8;
    QSpacerItem *verticalSpacer;
    QLabel *labelOutputImage;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonCpu;
    QPushButton *pushButtonGpu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1280, 598);
        QSizePolicy sizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout_4->addWidget(progressBar, 1, 1, 1, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(350, 0));
        scrollArea->setFrameShape(QFrame::StyledPanel);
        scrollArea->setFrameShadow(QFrame::Sunken);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 332, 581));
        gridLayout_5 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        frame = new QFrame(scrollAreaWidgetContents);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::NoFrame);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(0);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout_10 = new QGridLayout(groupBox);
        gridLayout_10->setSpacing(6);
        gridLayout_10->setContentsMargins(11, 11, 11, 11);
        gridLayout_10->setObjectName(QStringLiteral("gridLayout_10"));
        labelGoodMatches = new QLabel(groupBox);
        labelGoodMatches->setObjectName(QStringLiteral("labelGoodMatches"));

        gridLayout_10->addWidget(labelGoodMatches, 3, 0, 1, 1);

        gridLayout1 = new QGridLayout();
        gridLayout1->setSpacing(6);
        gridLayout1->setObjectName(QStringLiteral("gridLayout1"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout1->addWidget(label, 0, 1, 1, 1);

        lineEditMatches = new QLineEdit(groupBox);
        lineEditMatches->setObjectName(QStringLiteral("lineEditMatches"));

        gridLayout1->addWidget(lineEditMatches, 2, 1, 1, 1);

        lineEditGoodMatches = new QLineEdit(groupBox);
        lineEditGoodMatches->setObjectName(QStringLiteral("lineEditGoodMatches"));

        gridLayout1->addWidget(lineEditGoodMatches, 3, 1, 1, 1);

        lineEditKeyPoints = new QLineEdit(groupBox);
        lineEditKeyPoints->setObjectName(QStringLiteral("lineEditKeyPoints"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEditKeyPoints->sizePolicy().hasHeightForWidth());
        lineEditKeyPoints->setSizePolicy(sizePolicy2);

        gridLayout1->addWidget(lineEditKeyPoints, 1, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(18, 98, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout1->addItem(horizontalSpacer_2, 0, 0, 4, 1);


        gridLayout_10->addLayout(gridLayout1, 0, 1, 4, 1);

        labelMatches = new QLabel(groupBox);
        labelMatches->setObjectName(QStringLiteral("labelMatches"));

        gridLayout_10->addWidget(labelMatches, 2, 0, 1, 1);

        labelKeyPoints = new QLabel(groupBox);
        labelKeyPoints->setObjectName(QStringLiteral("labelKeyPoints"));

        gridLayout_10->addWidget(labelKeyPoints, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox, 3, 0, 1, 1);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 3, 0, 1, 1);

        lbl_oc = new QLabel(groupBox_2);
        lbl_oc->setObjectName(QStringLiteral("lbl_oc"));

        gridLayout_2->addWidget(lbl_oc, 1, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 5, 0, 1, 2);

        spinBoxGoodMatchesThreshold = new QSpinBox(groupBox_2);
        spinBoxGoodMatchesThreshold->setObjectName(QStringLiteral("spinBoxGoodMatchesThreshold"));
        spinBoxGoodMatchesThreshold->setMinimum(1);
        spinBoxGoodMatchesThreshold->setMaximum(100);
        spinBoxGoodMatchesThreshold->setValue(20);

        gridLayout_2->addWidget(spinBoxGoodMatchesThreshold, 5, 2, 1, 1);

        spinBoxMinHessian = new QSpinBox(groupBox_2);
        spinBoxMinHessian->setObjectName(QStringLiteral("spinBoxMinHessian"));
        spinBoxMinHessian->setMinimum(10);
        spinBoxMinHessian->setMaximum(800);
        spinBoxMinHessian->setValue(100);

        gridLayout_2->addWidget(spinBoxMinHessian, 0, 2, 1, 1);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_2->addWidget(label_2, 2, 0, 1, 1);

        checkBoxExtended = new QCheckBox(groupBox_2);
        checkBoxExtended->setObjectName(QStringLiteral("checkBoxExtended"));
        checkBoxExtended->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(checkBoxExtended, 3, 2, 1, 1);

        spinBoxOctaveLayers = new QSpinBox(groupBox_2);
        spinBoxOctaveLayers->setObjectName(QStringLiteral("spinBoxOctaveLayers"));
        spinBoxOctaveLayers->setMinimum(1);
        spinBoxOctaveLayers->setValue(2);

        gridLayout_2->addWidget(spinBoxOctaveLayers, 2, 2, 1, 1);

        spinBoxOctaves = new QSpinBox(groupBox_2);
        spinBoxOctaves->setObjectName(QStringLiteral("spinBoxOctaves"));
        spinBoxOctaves->setValue(4);

        gridLayout_2->addWidget(spinBoxOctaves, 1, 2, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 4, 0, 1, 1);

        checkBoxUpright = new QCheckBox(groupBox_2);
        checkBoxUpright->setObjectName(QStringLiteral("checkBoxUpright"));
        checkBoxUpright->setLayoutDirection(Qt::RightToLeft);

        gridLayout_2->addWidget(checkBoxUpright, 4, 2, 1, 1);


        gridLayout->addWidget(groupBox_2, 1, 0, 1, 1);

        groupBox_4 = new QGroupBox(frame);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        gridLayout_11 = new QGridLayout(groupBox_4);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        pushButtonSourceImage = new QPushButton(groupBox_4);
        pushButtonSourceImage->setObjectName(QStringLiteral("pushButtonSourceImage"));

        gridLayout_11->addWidget(pushButtonSourceImage, 0, 0, 1, 1);

        pushButtonSceneImage = new QPushButton(groupBox_4);
        pushButtonSceneImage->setObjectName(QStringLiteral("pushButtonSceneImage"));

        gridLayout_11->addWidget(pushButtonSceneImage, 0, 1, 1, 1);


        gridLayout->addWidget(groupBox_4, 0, 0, 1, 1);

        groupBox_11 = new QGroupBox(frame);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        gridLayout_9 = new QGridLayout(groupBox_11);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        label_7 = new QLabel(groupBox_11);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_9->addWidget(label_7, 0, 0, 1, 1);

        gridLayout_7 = new QGridLayout();
        gridLayout_7->setSpacing(6);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        lineEditExecutionTimeCpu = new QLineEdit(groupBox_11);
        lineEditExecutionTimeCpu->setObjectName(QStringLiteral("lineEditExecutionTimeCpu"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEditExecutionTimeCpu->sizePolicy().hasHeightForWidth());
        lineEditExecutionTimeCpu->setSizePolicy(sizePolicy3);

        gridLayout_7->addWidget(lineEditExecutionTimeCpu, 0, 1, 1, 1);

        lineEditExecutionTimeGpu = new QLineEdit(groupBox_11);
        lineEditExecutionTimeGpu->setObjectName(QStringLiteral("lineEditExecutionTimeGpu"));
        sizePolicy3.setHeightForWidth(lineEditExecutionTimeGpu->sizePolicy().hasHeightForWidth());
        lineEditExecutionTimeGpu->setSizePolicy(sizePolicy3);

        gridLayout_7->addWidget(lineEditExecutionTimeGpu, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 58, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer, 0, 0, 2, 1);


        gridLayout_9->addLayout(gridLayout_7, 0, 1, 2, 1);

        label_8 = new QLabel(groupBox_11);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_9->addWidget(label_8, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_11, 4, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        groupBox_2->raise();
        groupBox->raise();
        groupBox_4->raise();
        groupBox_11->raise();

        gridLayout_5->addWidget(frame, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_4->addWidget(scrollArea, 0, 0, 1, 1);

        labelOutputImage = new QLabel(centralWidget);
        labelOutputImage->setObjectName(QStringLiteral("labelOutputImage"));
        QSizePolicy sizePolicy4(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy4.setHorizontalStretch(1);
        sizePolicy4.setVerticalStretch(1);
        sizePolicy4.setHeightForWidth(labelOutputImage->sizePolicy().hasHeightForWidth());
        labelOutputImage->setSizePolicy(sizePolicy4);
        labelOutputImage->setMinimumSize(QSize(1, 1));
        labelOutputImage->setFrameShape(QFrame::StyledPanel);
        labelOutputImage->setScaledContents(true);
        labelOutputImage->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(labelOutputImage, 0, 1, 1, 1);

        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        horizontalLayout_2 = new QHBoxLayout(groupBox_5);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButtonCpu = new QPushButton(groupBox_5);
        pushButtonCpu->setObjectName(QStringLiteral("pushButtonCpu"));

        horizontalLayout_2->addWidget(pushButtonCpu);

        pushButtonGpu = new QPushButton(groupBox_5);
        pushButtonGpu->setObjectName(QStringLiteral("pushButtonGpu"));

        horizontalLayout_2->addWidget(pushButtonGpu);


        gridLayout_4->addWidget(groupBox_5, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(pushButtonSourceImage, pushButtonSceneImage);
        QWidget::setTabOrder(pushButtonSceneImage, spinBoxMinHessian);
        QWidget::setTabOrder(spinBoxMinHessian, spinBoxGoodMatchesThreshold);
        QWidget::setTabOrder(spinBoxGoodMatchesThreshold, pushButtonCpu);
        QWidget::setTabOrder(pushButtonCpu, pushButtonGpu);
        QWidget::setTabOrder(pushButtonGpu, lineEditKeyPoints);
        QWidget::setTabOrder(lineEditKeyPoints, lineEditMatches);
        QWidget::setTabOrder(lineEditMatches, lineEditGoodMatches);
        QWidget::setTabOrder(lineEditGoodMatches, lineEditExecutionTimeCpu);
        QWidget::setTabOrder(lineEditExecutionTimeCpu, lineEditExecutionTimeGpu);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Object Detect", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Information about last kernel", 0));
        labelGoodMatches->setText(QApplication::translate("MainWindow", "Good Matches", 0));
        label->setText(QApplication::translate("MainWindow", "Object / Scene", 0));
        labelMatches->setText(QApplication::translate("MainWindow", "Matches", 0));
        labelKeyPoints->setText(QApplication::translate("MainWindow", "KeyPoints", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "SURF Parameters", 0));
        label_5->setText(QApplication::translate("MainWindow", "Extended", 0));
        lbl_oc->setText(QApplication::translate("MainWindow", "Number of octaves", 0));
        label_4->setText(QApplication::translate("MainWindow", "Filter Matches", 0));
        label_3->setText(QApplication::translate("MainWindow", "SURF Threshold", 0));
        label_2->setText(QApplication::translate("MainWindow", "Octave layers", 0));
        checkBoxExtended->setText(QString());
        label_6->setText(QApplication::translate("MainWindow", "Upright only", 0));
        checkBoxUpright->setText(QString());
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Input", 0));
        pushButtonSourceImage->setText(QApplication::translate("MainWindow", "Object", 0));
        pushButtonSceneImage->setText(QApplication::translate("MainWindow", "Scene", 0));
        groupBox_11->setTitle(QApplication::translate("MainWindow", "Execution time in ms", 0));
        label_7->setText(QApplication::translate("MainWindow", "CPU", 0));
        label_8->setText(QApplication::translate("MainWindow", "GPU", 0));
        labelOutputImage->setText(QApplication::translate("MainWindow", "Processed Image", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Execute", 0));
        pushButtonCpu->setText(QApplication::translate("MainWindow", "CPU", 0));
        pushButtonGpu->setText(QApplication::translate("MainWindow", "GPU", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
