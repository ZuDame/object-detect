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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QFrame *frame;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QCheckBox *checkBoxDrawMatches;
    QCheckBox *checkBoxDrawKeyPoints;
    QCheckBox *checkBoxLocaliseObject;
    QSpacerItem *verticalSpacer;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_11;
    QPushButton *pushButtonSourceImage;
    QPushButton *pushButtonSceneImage;
    QGroupBox *groupBox_5;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButtonCpu;
    QPushButton *pushButtonGpu;
    QGroupBox *groupBox_11;
    QGridLayout *gridLayout_9;
    QLabel *label_7;
    QGridLayout *gridLayout_7;
    QLineEdit *lineEditExecutionTimeCpu;
    QLineEdit *lineEditExecutionTimeGpu;
    QSpacerItem *horizontalSpacer;
    QLabel *label_8;
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
    QLabel *label_3;
    QLabel *label_4;
    QSpinBox *spinBoxGoodMatchesThreshold;
    QSpinBox *spinBoxMinHessian;
    QLabel *labelOutputImage;
    QProgressBar *progressBar;

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
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        checkBoxDrawMatches = new QCheckBox(groupBox_3);
        checkBoxDrawMatches->setObjectName(QStringLiteral("checkBoxDrawMatches"));

        gridLayout_3->addWidget(checkBoxDrawMatches, 1, 0, 1, 1);

        checkBoxDrawKeyPoints = new QCheckBox(groupBox_3);
        checkBoxDrawKeyPoints->setObjectName(QStringLiteral("checkBoxDrawKeyPoints"));

        gridLayout_3->addWidget(checkBoxDrawKeyPoints, 0, 0, 1, 1);

        checkBoxLocaliseObject = new QCheckBox(groupBox_3);
        checkBoxLocaliseObject->setObjectName(QStringLiteral("checkBoxLocaliseObject"));

        gridLayout_3->addWidget(checkBoxLocaliseObject, 2, 0, 1, 1);


        gridLayout->addWidget(groupBox_3, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 6, 0, 1, 1);

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

        groupBox_5 = new QGroupBox(frame);
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


        gridLayout->addWidget(groupBox_5, 7, 0, 1, 1);

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
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEditExecutionTimeCpu->sizePolicy().hasHeightForWidth());
        lineEditExecutionTimeCpu->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(lineEditExecutionTimeCpu, 0, 1, 1, 1);

        lineEditExecutionTimeGpu = new QLineEdit(groupBox_11);
        lineEditExecutionTimeGpu->setObjectName(QStringLiteral("lineEditExecutionTimeGpu"));
        sizePolicy1.setHeightForWidth(lineEditExecutionTimeGpu->sizePolicy().hasHeightForWidth());
        lineEditExecutionTimeGpu->setSizePolicy(sizePolicy1);

        gridLayout_7->addWidget(lineEditExecutionTimeGpu, 1, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 58, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer, 0, 0, 2, 1);


        gridLayout_9->addLayout(gridLayout_7, 0, 1, 2, 1);

        label_8 = new QLabel(groupBox_11);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_9->addWidget(label_8, 1, 0, 1, 1);


        gridLayout->addWidget(groupBox_11, 5, 0, 1, 1);

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


        gridLayout->addWidget(groupBox, 4, 0, 1, 1);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout_2->addWidget(label_4, 1, 0, 1, 2);

        spinBoxGoodMatchesThreshold = new QSpinBox(groupBox_2);
        spinBoxGoodMatchesThreshold->setObjectName(QStringLiteral("spinBoxGoodMatchesThreshold"));
        spinBoxGoodMatchesThreshold->setMinimum(1);
        spinBoxGoodMatchesThreshold->setMaximum(100);
        spinBoxGoodMatchesThreshold->setValue(20);

        gridLayout_2->addWidget(spinBoxGoodMatchesThreshold, 1, 2, 1, 1);

        spinBoxMinHessian = new QSpinBox(groupBox_2);
        spinBoxMinHessian->setObjectName(QStringLiteral("spinBoxMinHessian"));
        spinBoxMinHessian->setMinimum(10);
        spinBoxMinHessian->setMaximum(800);
        spinBoxMinHessian->setValue(100);

        gridLayout_2->addWidget(spinBoxMinHessian, 0, 2, 1, 1);


        gridLayout->addWidget(groupBox_2, 2, 0, 1, 1);

        groupBox_5->raise();
        groupBox_2->raise();
        groupBox->raise();
        groupBox_4->raise();
        groupBox_3->raise();
        groupBox_11->raise();

        gridLayout_4->addWidget(frame, 0, 0, 2, 1);

        labelOutputImage = new QLabel(centralWidget);
        labelOutputImage->setObjectName(QStringLiteral("labelOutputImage"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(labelOutputImage->sizePolicy().hasHeightForWidth());
        labelOutputImage->setSizePolicy(sizePolicy3);
        labelOutputImage->setMinimumSize(QSize(1, 1));
        labelOutputImage->setFrameShape(QFrame::StyledPanel);
        labelOutputImage->setScaledContents(true);
        labelOutputImage->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(labelOutputImage, 0, 1, 1, 1);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(0);

        gridLayout_4->addWidget(progressBar, 1, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        QWidget::setTabOrder(pushButtonSourceImage, pushButtonSceneImage);
        QWidget::setTabOrder(pushButtonSceneImage, checkBoxDrawMatches);
        QWidget::setTabOrder(checkBoxDrawMatches, spinBoxMinHessian);
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
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Display options", 0));
        checkBoxDrawMatches->setText(QApplication::translate("MainWindow", "Draw Matches", 0));
        checkBoxDrawKeyPoints->setText(QApplication::translate("MainWindow", "Draw Keypoints", 0));
        checkBoxLocaliseObject->setText(QApplication::translate("MainWindow", "Localise Object", 0));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Input", 0));
        pushButtonSourceImage->setText(QApplication::translate("MainWindow", "Object", 0));
        pushButtonSceneImage->setText(QApplication::translate("MainWindow", "Scene", 0));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Execute", 0));
        pushButtonCpu->setText(QApplication::translate("MainWindow", "CPU", 0));
        pushButtonGpu->setText(QApplication::translate("MainWindow", "GPU", 0));
        groupBox_11->setTitle(QApplication::translate("MainWindow", "Execution time in ms", 0));
        label_7->setText(QApplication::translate("MainWindow", "CPU", 0));
        label_8->setText(QApplication::translate("MainWindow", "GPU", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Information about last kernel", 0));
        labelGoodMatches->setText(QApplication::translate("MainWindow", "Good Matches", 0));
        label->setText(QApplication::translate("MainWindow", "Object / Scene", 0));
        labelMatches->setText(QApplication::translate("MainWindow", "Matches", 0));
        labelKeyPoints->setText(QApplication::translate("MainWindow", "KeyPoints", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "SURF Parameters", 0));
        label_3->setText(QApplication::translate("MainWindow", "SURF Threshold", 0));
        label_4->setText(QApplication::translate("MainWindow", "Filter Matches", 0));
        labelOutputImage->setText(QApplication::translate("MainWindow", "Processed Image", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
