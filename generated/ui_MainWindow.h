/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QOpenGLWidget>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionClose;
    QWidget *centralwidget;
    QLabel *labelTop;
    QProgressBar *progressBar;
    QCheckBox *cb_MIP;
    QCheckBox *cb_AlphaCompositing;
    QSlider *sl_AlphaCompositing;
    QLabel *label_2;
    QGroupBox *groupBox;
    QGroupBox *gb_transform;
    QSlider *sl_xTranslate;
    QLabel *label;
    QLabel *label_3;
    QSlider *sl_yTranslate;
    QOpenGLWidget *openGLWidget;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;
    QMenu *menuFile;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1192, 700);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionClose = new QAction(MainWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        labelTop = new QLabel(centralwidget);
        labelTop->setObjectName(QStringLiteral("labelTop"));
        labelTop->setGeometry(QRect(20, 20, 1001, 16));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(false);
        progressBar->setGeometry(QRect(657, 20, 521, 23));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        cb_MIP = new QCheckBox(centralwidget);
        cb_MIP->setObjectName(QStringLiteral("cb_MIP"));
        cb_MIP->setGeometry(QRect(1020, 90, 70, 17));
        cb_MIP->setChecked(true);
        cb_AlphaCompositing = new QCheckBox(centralwidget);
        cb_AlphaCompositing->setObjectName(QStringLiteral("cb_AlphaCompositing"));
        cb_AlphaCompositing->setGeometry(QRect(1020, 110, 111, 17));
        sl_AlphaCompositing = new QSlider(centralwidget);
        sl_AlphaCompositing->setObjectName(QStringLiteral("sl_AlphaCompositing"));
        sl_AlphaCompositing->setGeometry(QRect(1020, 160, 151, 22));
        sl_AlphaCompositing->setOrientation(Qt::Horizontal);
        sl_AlphaCompositing->setTickPosition(QSlider::TicksBelow);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(1020, 140, 131, 16));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(1010, 60, 171, 141));
        gb_transform = new QGroupBox(centralwidget);
        gb_transform->setObjectName(QStringLiteral("gb_transform"));
        gb_transform->setGeometry(QRect(1010, 220, 171, 231));
        sl_xTranslate = new QSlider(gb_transform);
        sl_xTranslate->setObjectName(QStringLiteral("sl_xTranslate"));
        sl_xTranslate->setGeometry(QRect(10, 50, 151, 22));
        sl_xTranslate->setValue(50);
        sl_xTranslate->setOrientation(Qt::Horizontal);
        sl_xTranslate->setTickPosition(QSlider::TicksBelow);
        label = new QLabel(gb_transform);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 81, 16));
        label_3 = new QLabel(gb_transform);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 80, 81, 16));
        sl_yTranslate = new QSlider(gb_transform);
        sl_yTranslate->setObjectName(QStringLiteral("sl_yTranslate"));
        sl_yTranslate->setGeometry(QRect(10, 100, 151, 22));
        sl_yTranslate->setValue(50);
        sl_yTranslate->setOrientation(Qt::Horizontal);
        sl_yTranslate->setTickPosition(QSlider::TicksBelow);
        openGLWidget = new QOpenGLWidget(centralwidget);
        openGLWidget->setObjectName(QStringLiteral("openGLWidget"));
        openGLWidget->setGeometry(QRect(9, 59, 991, 611));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setGeometry(QRect(10, 60, 991, 611));
        MainWindow->setCentralWidget(centralwidget);
        openGLWidget->raise();
        graphicsView->raise();
        groupBox->raise();
        labelTop->raise();
        progressBar->raise();
        cb_MIP->raise();
        cb_AlphaCompositing->raise();
        sl_AlphaCompositing->raise();
        label_2->raise();
        gb_transform->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1192, 21));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuFile->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionClose);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Visualisierung 1", 0));
        actionOpen->setText(QApplication::translate("MainWindow", "Open ...", 0));
        actionClose->setText(QApplication::translate("MainWindow", "Close", 0));
        labelTop->setText(QApplication::translate("MainWindow", "No data loaded", 0));
        cb_MIP->setText(QApplication::translate("MainWindow", "MIP", 0));
        cb_AlphaCompositing->setText(QApplication::translate("MainWindow", "Alpha Compositing", 0));
        label_2->setText(QApplication::translate("MainWindow", "Alpha Comp Treshold", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Settings", 0));
        gb_transform->setTitle(QApplication::translate("MainWindow", "Transformations", 0));
        label->setText(QApplication::translate("MainWindow", "X-Translate", 0));
        label_3->setText(QApplication::translate("MainWindow", "Y-Translate", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
