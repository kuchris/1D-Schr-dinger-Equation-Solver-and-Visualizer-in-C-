/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "CustomChartView.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    CustomChartView *chartView;
    QVBoxLayout *verticalLayout;
    QLabel *label_5;
    QComboBox *initialWavePacketComboBox;
    QLabel *sigmaLabel;
    QDoubleSpinBox *sigmaSpinBox;
    QLabel *x0Label;
    QDoubleSpinBox *x0SpinBox;
    QLabel *k0Label;
    QDoubleSpinBox *k0SpinBox;
    QLabel *label_4;
    QComboBox *methodComboBox;
    QLabel *label_3;
    QComboBox *potentialComboBox;
    QLabel *sizeLabel;
    QSpinBox *sizeSpinBox;
    QLabel *dtLabel;
    QDoubleSpinBox *dtSpinBox;
    QLabel *label_2;
    QDoubleSpinBox *dxSpinBox;
    QPushButton *startButton;
    QPushButton *resetButton;
    QPushButton *pauseResumeButton;
    QPushButton *saveDataButton;
    QCheckBox *probDensityCheckBox;
    QCheckBox *realPartCheckBox;
    QCheckBox *imagPartCheckBox;
    QCheckBox *potentialCheckBox;
    QCheckBox *autoZoomCheckBox;
    QLabel *expectationPositionLabel;
    QLabel *expectationMomentumLabel;
    QLabel *expectationEnergyLabel;
    QLabel *timeLabel;
    QSpacerItem *verticalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 756);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chartView = new CustomChartView(centralwidget);
        chartView->setObjectName(QString::fromUtf8("chartView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(3);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chartView->sizePolicy().hasHeightForWidth());
        chartView->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(chartView);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout->addWidget(label_5);

        initialWavePacketComboBox = new QComboBox(centralwidget);
        initialWavePacketComboBox->setObjectName(QString::fromUtf8("initialWavePacketComboBox"));

        verticalLayout->addWidget(initialWavePacketComboBox);

        sigmaLabel = new QLabel(centralwidget);
        sigmaLabel->setObjectName(QString::fromUtf8("sigmaLabel"));

        verticalLayout->addWidget(sigmaLabel);

        sigmaSpinBox = new QDoubleSpinBox(centralwidget);
        sigmaSpinBox->setObjectName(QString::fromUtf8("sigmaSpinBox"));
        sigmaSpinBox->setDecimals(7);
        sigmaSpinBox->setValue(0.050000000000000);

        verticalLayout->addWidget(sigmaSpinBox);

        x0Label = new QLabel(centralwidget);
        x0Label->setObjectName(QString::fromUtf8("x0Label"));

        verticalLayout->addWidget(x0Label);

        x0SpinBox = new QDoubleSpinBox(centralwidget);
        x0SpinBox->setObjectName(QString::fromUtf8("x0SpinBox"));
        x0SpinBox->setDecimals(7);
        x0SpinBox->setValue(0.500000000000000);

        verticalLayout->addWidget(x0SpinBox);

        k0Label = new QLabel(centralwidget);
        k0Label->setObjectName(QString::fromUtf8("k0Label"));

        verticalLayout->addWidget(k0Label);

        k0SpinBox = new QDoubleSpinBox(centralwidget);
        k0SpinBox->setObjectName(QString::fromUtf8("k0SpinBox"));
        k0SpinBox->setDecimals(7);
        k0SpinBox->setValue(50.000000000000000);

        verticalLayout->addWidget(k0SpinBox);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout->addWidget(label_4);

        methodComboBox = new QComboBox(centralwidget);
        methodComboBox->setObjectName(QString::fromUtf8("methodComboBox"));

        verticalLayout->addWidget(methodComboBox);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        potentialComboBox = new QComboBox(centralwidget);
        potentialComboBox->setObjectName(QString::fromUtf8("potentialComboBox"));

        verticalLayout->addWidget(potentialComboBox);

        sizeLabel = new QLabel(centralwidget);
        sizeLabel->setObjectName(QString::fromUtf8("sizeLabel"));

        verticalLayout->addWidget(sizeLabel);

        sizeSpinBox = new QSpinBox(centralwidget);
        sizeSpinBox->setObjectName(QString::fromUtf8("sizeSpinBox"));
        sizeSpinBox->setMinimum(100);
        sizeSpinBox->setMaximum(10000);
        sizeSpinBox->setSingleStep(100);
        sizeSpinBox->setValue(100);

        verticalLayout->addWidget(sizeSpinBox);

        dtLabel = new QLabel(centralwidget);
        dtLabel->setObjectName(QString::fromUtf8("dtLabel"));

        verticalLayout->addWidget(dtLabel);

        dtSpinBox = new QDoubleSpinBox(centralwidget);
        dtSpinBox->setObjectName(QString::fromUtf8("dtSpinBox"));
        dtSpinBox->setDecimals(7);
        dtSpinBox->setMinimum(0.000000100000000);
        dtSpinBox->setMaximum(0.100000000000000);
        dtSpinBox->setSingleStep(0.000001000000000);
        dtSpinBox->setValue(0.000010000000000);

        verticalLayout->addWidget(dtSpinBox);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        dxSpinBox = new QDoubleSpinBox(centralwidget);
        dxSpinBox->setObjectName(QString::fromUtf8("dxSpinBox"));
        dxSpinBox->setDecimals(5);
        dxSpinBox->setMinimum(0.000010000000000);
        dxSpinBox->setMaximum(1.000000000000000);
        dxSpinBox->setSingleStep(0.001000000000000);
        dxSpinBox->setValue(0.010000000000000);

        verticalLayout->addWidget(dxSpinBox);

        startButton = new QPushButton(centralwidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout->addWidget(startButton);

        resetButton = new QPushButton(centralwidget);
        resetButton->setObjectName(QString::fromUtf8("resetButton"));

        verticalLayout->addWidget(resetButton);

        pauseResumeButton = new QPushButton(centralwidget);
        pauseResumeButton->setObjectName(QString::fromUtf8("pauseResumeButton"));

        verticalLayout->addWidget(pauseResumeButton);

        saveDataButton = new QPushButton(centralwidget);
        saveDataButton->setObjectName(QString::fromUtf8("saveDataButton"));

        verticalLayout->addWidget(saveDataButton);

        probDensityCheckBox = new QCheckBox(centralwidget);
        probDensityCheckBox->setObjectName(QString::fromUtf8("probDensityCheckBox"));
        probDensityCheckBox->setChecked(true);

        verticalLayout->addWidget(probDensityCheckBox);

        realPartCheckBox = new QCheckBox(centralwidget);
        realPartCheckBox->setObjectName(QString::fromUtf8("realPartCheckBox"));
        realPartCheckBox->setChecked(true);

        verticalLayout->addWidget(realPartCheckBox);

        imagPartCheckBox = new QCheckBox(centralwidget);
        imagPartCheckBox->setObjectName(QString::fromUtf8("imagPartCheckBox"));
        imagPartCheckBox->setChecked(true);

        verticalLayout->addWidget(imagPartCheckBox);

        potentialCheckBox = new QCheckBox(centralwidget);
        potentialCheckBox->setObjectName(QString::fromUtf8("potentialCheckBox"));
        potentialCheckBox->setChecked(true);

        verticalLayout->addWidget(potentialCheckBox);

        autoZoomCheckBox = new QCheckBox(centralwidget);
        autoZoomCheckBox->setObjectName(QString::fromUtf8("autoZoomCheckBox"));
        autoZoomCheckBox->setChecked(true);

        verticalLayout->addWidget(autoZoomCheckBox);

        expectationPositionLabel = new QLabel(centralwidget);
        expectationPositionLabel->setObjectName(QString::fromUtf8("expectationPositionLabel"));
        expectationPositionLabel->setMinimumSize(QSize(300, 0));

        verticalLayout->addWidget(expectationPositionLabel);

        expectationMomentumLabel = new QLabel(centralwidget);
        expectationMomentumLabel->setObjectName(QString::fromUtf8("expectationMomentumLabel"));
        expectationMomentumLabel->setMinimumSize(QSize(300, 0));

        verticalLayout->addWidget(expectationMomentumLabel);

        expectationEnergyLabel = new QLabel(centralwidget);
        expectationEnergyLabel->setObjectName(QString::fromUtf8("expectationEnergyLabel"));
        expectationEnergyLabel->setMinimumSize(QSize(300, 0));

        verticalLayout->addWidget(expectationEnergyLabel);

        timeLabel = new QLabel(centralwidget);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));
        timeLabel->setMinimumSize(QSize(300, 0));

        verticalLayout->addWidget(timeLabel);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1200, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "1D Schr\303\266dinger Equation Solver", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Initial Wave Packet", nullptr));
        sigmaLabel->setText(QCoreApplication::translate("MainWindow", "Sigma:", nullptr));
        x0Label->setText(QCoreApplication::translate("MainWindow", "x0:", nullptr));
        k0Label->setText(QCoreApplication::translate("MainWindow", "k0:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Method", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Potential", nullptr));
        sizeLabel->setText(QCoreApplication::translate("MainWindow", "Simulation Size:", nullptr));
        dtLabel->setText(QCoreApplication::translate("MainWindow", "dt", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "dx", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "Start", nullptr));
        resetButton->setText(QCoreApplication::translate("MainWindow", "Reset", nullptr));
        pauseResumeButton->setText(QCoreApplication::translate("MainWindow", "Pause", nullptr));
        saveDataButton->setText(QCoreApplication::translate("MainWindow", "Save Data", nullptr));
        probDensityCheckBox->setText(QCoreApplication::translate("MainWindow", "Show Probability Density", nullptr));
        realPartCheckBox->setText(QCoreApplication::translate("MainWindow", "Show Real Part", nullptr));
        imagPartCheckBox->setText(QCoreApplication::translate("MainWindow", "Show Imaginary Part", nullptr));
        potentialCheckBox->setText(QCoreApplication::translate("MainWindow", "Show Potential", nullptr));
        autoZoomCheckBox->setText(QCoreApplication::translate("MainWindow", "Auto Zoom Y-Axis", nullptr));
        expectationPositionLabel->setText(QCoreApplication::translate("MainWindow", "Expectation Position <x>:", nullptr));
        expectationMomentumLabel->setText(QCoreApplication::translate("MainWindow", "Expectation Momentum <p>:", nullptr));
        expectationEnergyLabel->setText(QCoreApplication::translate("MainWindow", "Expectation Energy <H>:", nullptr));
        timeLabel->setText(QCoreApplication::translate("MainWindow", "Time: 0.0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
