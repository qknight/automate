/********************************************************************************
** Form generated from reading ui file 'controllerWidget.ui'
**
** Created: Sun May 25 00:16:59 2008
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_CONTROLLERWIDGET_H
#define UI_CONTROLLERWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGridLayout>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

class Ui_controllerWidget
{
public:
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QLabel *label;
    QSpacerItem *spacerItem;
    QPushButton *updateBtn;

    void setupUi(QWidget *controllerWidget)
    {
    if (controllerWidget->objectName().isEmpty())
        controllerWidget->setObjectName(QString::fromUtf8("controllerWidget"));
    controllerWidget->resize(745, 511);
    gridLayout = new QGridLayout(controllerWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    treeWidget = new QTreeWidget(controllerWidget);
    treeWidget->setObjectName(QString::fromUtf8("treeWidget"));
    treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    gridLayout->addWidget(treeWidget, 0, 0, 1, 3);

    label = new QLabel(controllerWidget);
    label->setObjectName(QString::fromUtf8("label"));

    gridLayout->addWidget(label, 1, 0, 1, 1);

    spacerItem = new QSpacerItem(371, 30, QSizePolicy::Expanding, QSizePolicy::Minimum);

    gridLayout->addItem(spacerItem, 1, 1, 1, 1);

    updateBtn = new QPushButton(controllerWidget);
    updateBtn->setObjectName(QString::fromUtf8("updateBtn"));

    gridLayout->addWidget(updateBtn, 1, 2, 1, 1);


    retranslateUi(controllerWidget);

    QMetaObject::connectSlotsByName(controllerWidget);
    } // setupUi

    void retranslateUi(QWidget *controllerWidget)
    {
    controllerWidget->setWindowTitle(QApplication::translate("controllerWidget", "automate controller widget", 0, QApplication::UnicodeUTF8));
    treeWidget->headerItem()->setText(0, QApplication::translate("controllerWidget", "automate", 0, QApplication::UnicodeUTF8));
    treeWidget->headerItem()->setText(1, QApplication::translate("controllerWidget", "nodes", 0, QApplication::UnicodeUTF8));
    treeWidget->headerItem()->setText(2, QApplication::translate("controllerWidget", "connections", 0, QApplication::UnicodeUTF8));
    treeWidget->headerItem()->setText(3, QApplication::translate("controllerWidget", "symbols", 0, QApplication::UnicodeUTF8));
    treeWidget->headerItem()->setText(4, QApplication::translate("controllerWidget", "nodemanager", 0, QApplication::UnicodeUTF8));
    treeWidget->clear();

    QTreeWidgetItem *__item = new QTreeWidgetItem(treeWidget);
    __item->setText(0, QApplication::translate("controllerWidget", "automate", 0, QApplication::UnicodeUTF8));
    __item->setText(1, QString());
    __item->setText(2, QString());
    __item->setText(3, QString());
    __item->setText(4, QString());

    QTreeWidgetItem *__item1 = new QTreeWidgetItem(__item);
    __item1->setText(0, QApplication::translate("controllerWidget", "nodes", 0, QApplication::UnicodeUTF8));
    __item1->setText(1, QString());
    __item1->setText(2, QString());
    __item1->setText(3, QString());
    __item1->setText(4, QString());

    QTreeWidgetItem *__item2 = new QTreeWidgetItem(__item);
    __item2->setText(0, QApplication::translate("controllerWidget", "connections", 0, QApplication::UnicodeUTF8));
    __item2->setText(1, QString());
    __item2->setText(2, QString());
    __item2->setText(3, QString());
    __item2->setText(4, QString());

    QTreeWidgetItem *__item3 = new QTreeWidgetItem(__item);
    __item3->setText(0, QApplication::translate("controllerWidget", "nodemanager", 0, QApplication::UnicodeUTF8));
    __item3->setText(1, QString());
    __item3->setText(2, QString());
    __item3->setText(3, QString());
    __item3->setText(4, QString());
    label->setText(QApplication::translate("controllerWidget", "This view needs to be updated manually", 0, QApplication::UnicodeUTF8));
    updateBtn->setText(QApplication::translate("controllerWidget", "&update view", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(controllerWidget);
    } // retranslateUi

};

namespace Ui {
    class controllerWidget: public Ui_controllerWidget {};
} // namespace Ui

#endif // UI_CONTROLLERWIDGET_H
