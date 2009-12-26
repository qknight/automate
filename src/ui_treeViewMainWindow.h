/********************************************************************************
** Form generated from reading ui file 'treeViewMainWindow.ui'
**
** Created: Fri Dec 25 16:17:08 2009
**      by: Qt User Interface Compiler version 4.5.3
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TREEVIEWMAINWINDOW_H
#define UI_TREEVIEWMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_treeViewMainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTreeView *nodeTreeView;
    QGridLayout *gridLayout1;
    QPushButton *collapseAllBtn;
    QPushButton *expandAllBtn;
    QPushButton *addConnectionBtn;
    QPushButton *delConnectionBtn;
    QPushButton *addNodeBtn;
    QPushButton *delNodeBtn;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *treeViewMainWindow)
    {
        if (treeViewMainWindow->objectName().isEmpty())
            treeViewMainWindow->setObjectName(QString::fromUtf8("treeViewMainWindow"));
        treeViewMainWindow->resize(900, 633);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        treeViewMainWindow->setWindowIcon(icon);
        treeViewMainWindow->setDockNestingEnabled(true);
        centralwidget = new QWidget(treeViewMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        nodeTreeView = new QTreeView(centralwidget);
        nodeTreeView->setObjectName(QString::fromUtf8("nodeTreeView"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(nodeTreeView->sizePolicy().hasHeightForWidth());
        nodeTreeView->setSizePolicy(sizePolicy);
        nodeTreeView->setAlternatingRowColors(true);
        nodeTreeView->setSelectionMode(QAbstractItemView::ExtendedSelection);
        nodeTreeView->setAutoExpandDelay(20);
        nodeTreeView->setUniformRowHeights(false);
        nodeTreeView->setSortingEnabled(true);
        nodeTreeView->setAnimated(false);

        gridLayout->addWidget(nodeTreeView, 0, 0, 1, 1);

        gridLayout1 = new QGridLayout();
        gridLayout1->setObjectName(QString::fromUtf8("gridLayout1"));
        collapseAllBtn = new QPushButton(centralwidget);
        collapseAllBtn->setObjectName(QString::fromUtf8("collapseAllBtn"));

        gridLayout1->addWidget(collapseAllBtn, 0, 0, 1, 1);

        expandAllBtn = new QPushButton(centralwidget);
        expandAllBtn->setObjectName(QString::fromUtf8("expandAllBtn"));

        gridLayout1->addWidget(expandAllBtn, 0, 1, 1, 2);

        addConnectionBtn = new QPushButton(centralwidget);
        addConnectionBtn->setObjectName(QString::fromUtf8("addConnectionBtn"));

        gridLayout1->addWidget(addConnectionBtn, 1, 0, 1, 3);

        delConnectionBtn = new QPushButton(centralwidget);
        delConnectionBtn->setObjectName(QString::fromUtf8("delConnectionBtn"));

        gridLayout1->addWidget(delConnectionBtn, 2, 0, 1, 3);

        addNodeBtn = new QPushButton(centralwidget);
        addNodeBtn->setObjectName(QString::fromUtf8("addNodeBtn"));

        gridLayout1->addWidget(addNodeBtn, 3, 0, 1, 2);

        delNodeBtn = new QPushButton(centralwidget);
        delNodeBtn->setObjectName(QString::fromUtf8("delNodeBtn"));

        gridLayout1->addWidget(delNodeBtn, 3, 2, 1, 1);

        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(5);
        sizePolicy1.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
        textBrowser->setSizePolicy(sizePolicy1);

        gridLayout1->addWidget(textBrowser, 4, 0, 1, 3);


        gridLayout->addLayout(gridLayout1, 0, 1, 1, 1);

        treeViewMainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(treeViewMainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 31));
        treeViewMainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(treeViewMainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        treeViewMainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(treeViewMainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        treeViewMainWindow->addToolBar(Qt::TopToolBarArea, toolBar);

        retranslateUi(treeViewMainWindow);
        QObject::connect(expandAllBtn, SIGNAL(clicked()), nodeTreeView, SLOT(expandAll()));
        QObject::connect(collapseAllBtn, SIGNAL(clicked()), nodeTreeView, SLOT(collapseAll()));

        QMetaObject::connectSlotsByName(treeViewMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *treeViewMainWindow)
    {
        treeViewMainWindow->setWindowTitle(QApplication::translate("treeViewMainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        collapseAllBtn->setText(QApplication::translate("treeViewMainWindow", "&CollapseAll", 0, QApplication::UnicodeUTF8));
        expandAllBtn->setText(QApplication::translate("treeViewMainWindow", "&ExpandAll", 0, QApplication::UnicodeUTF8));
        addConnectionBtn->setText(QApplication::translate("treeViewMainWindow", "Add co&nnection", 0, QApplication::UnicodeUTF8));
        delConnectionBtn->setText(QApplication::translate("treeViewMainWindow", "Del C&onnection", 0, QApplication::UnicodeUTF8));
        addNodeBtn->setText(QApplication::translate("treeViewMainWindow", "&Add Node", 0, QApplication::UnicodeUTF8));
        delNodeBtn->setText(QApplication::translate("treeViewMainWindow", "&Del Node", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("treeViewMainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(treeViewMainWindow);
    } // retranslateUi

};

namespace Ui {
    class treeViewMainWindow: public Ui_treeViewMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TREEVIEWMAINWINDOW_H
