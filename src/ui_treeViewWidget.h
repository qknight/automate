/********************************************************************************
** Form generated from reading ui file 'treeViewWidget.ui'
**
** Created: Sun May 25 00:16:59 2008
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_TREEVIEWWIDGET_H
#define UI_TREEVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolButton>
#include <QtGui/QTreeView>
#include <QtGui/QWidget>

class Ui_treeViewWidget
{
public:
    QTreeView *nodeTreeView;
    QTextBrowser *textBrowser;
    QPushButton *collapseAllBtn;
    QPushButton *expandAllBtn;
    QPushButton *delNodeBtn;
    QPushButton *addNodeBtn;
    QPushButton *delConnectionBtn;
    QPushButton *addConnectionBtn;
    QLineEdit *lineEdit;
    QToolButton *toolButton;
    QTreeView *debugTreeView;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *treeViewWidget)
    {
    if (treeViewWidget->objectName().isEmpty())
        treeViewWidget->setObjectName(QString::fromUtf8("treeViewWidget"));
    treeViewWidget->resize(1260, 586);
    nodeTreeView = new QTreeView(treeViewWidget);
    nodeTreeView->setObjectName(QString::fromUtf8("nodeTreeView"));
    nodeTreeView->setGeometry(QRect(10, 50, 388, 521));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(2);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(nodeTreeView->sizePolicy().hasHeightForWidth());
    nodeTreeView->setSizePolicy(sizePolicy);
    nodeTreeView->setAlternatingRowColors(true);
    nodeTreeView->setAutoExpandDelay(2000);
    nodeTreeView->setSortingEnabled(true);
    textBrowser = new QTextBrowser(treeViewWidget);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setGeometry(QRect(400, 220, 391, 351));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(5);
    sizePolicy1.setHeightForWidth(textBrowser->sizePolicy().hasHeightForWidth());
    textBrowser->setSizePolicy(sizePolicy1);
    collapseAllBtn = new QPushButton(treeViewWidget);
    collapseAllBtn->setObjectName(QString::fromUtf8("collapseAllBtn"));
    collapseAllBtn->setGeometry(QRect(350, 10, 86, 30));
    expandAllBtn = new QPushButton(treeViewWidget);
    expandAllBtn->setObjectName(QString::fromUtf8("expandAllBtn"));
    expandAllBtn->setGeometry(QRect(230, 10, 122, 30));
    delNodeBtn = new QPushButton(treeViewWidget);
    delNodeBtn->setObjectName(QString::fromUtf8("delNodeBtn"));
    delNodeBtn->setGeometry(QRect(600, 50, 86, 30));
    addNodeBtn = new QPushButton(treeViewWidget);
    addNodeBtn->setObjectName(QString::fromUtf8("addNodeBtn"));
    addNodeBtn->setGeometry(QRect(440, 50, 81, 30));
    delConnectionBtn = new QPushButton(treeViewWidget);
    delConnectionBtn->setObjectName(QString::fromUtf8("delConnectionBtn"));
    delConnectionBtn->setGeometry(QRect(570, 90, 119, 30));
    addConnectionBtn = new QPushButton(treeViewWidget);
    addConnectionBtn->setObjectName(QString::fromUtf8("addConnectionBtn"));
    addConnectionBtn->setGeometry(QRect(440, 90, 122, 30));
    lineEdit = new QLineEdit(treeViewWidget);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
    lineEdit->setGeometry(QRect(460, 180, 331, 26));
    toolButton = new QToolButton(treeViewWidget);
    toolButton->setObjectName(QString::fromUtf8("toolButton"));
    toolButton->setGeometry(QRect(410, 180, 35, 29));
    debugTreeView = new QTreeView(treeViewWidget);
    debugTreeView->setObjectName(QString::fromUtf8("debugTreeView"));
    debugTreeView->setGeometry(QRect(830, 40, 421, 541));
    pushButton = new QPushButton(treeViewWidget);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(1040, 10, 94, 30));
    pushButton_2 = new QPushButton(treeViewWidget);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(1150, 10, 94, 30));
    label = new QLabel(treeViewWidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(10, 10, 211, 20));
    label_2 = new QLabel(treeViewWidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(830, 10, 181, 20));

    retranslateUi(treeViewWidget);
    QObject::connect(toolButton, SIGNAL(clicked()), lineEdit, SLOT(clear()));
    QObject::connect(expandAllBtn, SIGNAL(clicked()), nodeTreeView, SLOT(expandAll()));
    QObject::connect(collapseAllBtn, SIGNAL(clicked()), nodeTreeView, SLOT(collapseAll()));
    QObject::connect(pushButton, SIGNAL(clicked()), debugTreeView, SLOT(expandAll()));
    QObject::connect(pushButton_2, SIGNAL(clicked()), debugTreeView, SLOT(collapseAll()));

    QMetaObject::connectSlotsByName(treeViewWidget);
    } // setupUi

    void retranslateUi(QWidget *treeViewWidget)
    {
    treeViewWidget->setWindowTitle(QApplication::translate("treeViewWidget", "treeView", 0, QApplication::UnicodeUTF8));
    collapseAllBtn->setText(QApplication::translate("treeViewWidget", "&CollapseAll", 0, QApplication::UnicodeUTF8));
    expandAllBtn->setText(QApplication::translate("treeViewWidget", "&ExpandAll", 0, QApplication::UnicodeUTF8));
    delNodeBtn->setText(QApplication::translate("treeViewWidget", "&Del Node", 0, QApplication::UnicodeUTF8));
    addNodeBtn->setText(QApplication::translate("treeViewWidget", "&Add Node", 0, QApplication::UnicodeUTF8));
    delConnectionBtn->setText(QApplication::translate("treeViewWidget", "Del C&onnection", 0, QApplication::UnicodeUTF8));
    addConnectionBtn->setText(QApplication::translate("treeViewWidget", "Add co&nnection", 0, QApplication::UnicodeUTF8));
    toolButton->setText(QApplication::translate("treeViewWidget", "...", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("treeViewWidget", "&ExpandAll", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("treeViewWidget", "&CollapseAll", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("treeViewWidget", "This is the proxymodel view", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("treeViewWidget", "This is the model view", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(treeViewWidget);
    } // retranslateUi

};

namespace Ui {
    class treeViewWidget: public Ui_treeViewWidget {};
} // namespace Ui

#endif // UI_TREEVIEWWIDGET_H
