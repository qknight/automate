/********************************************************************************
** Form generated from reading ui file 'controllerWidget.ui'
**
** Created: Fri Dec 25 06:30:05 2009
**      by: Qt User Interface Compiler version 4.5.3
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
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTreeWidget>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

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
        const QIcon icon = QIcon(QString::fromUtf8(":/icons/home_blue.png"));
        controllerWidget->setWindowIcon(icon);
        gridLayout = new QGridLayout(controllerWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        treeWidget = new QTreeWidget(controllerWidget);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem(treeWidget);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
        new QTreeWidgetItem(__qtreewidgetitem);
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
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(4, QApplication::translate("controllerWidget", "nodemanager", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(3, QApplication::translate("controllerWidget", "symbols", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(2, QApplication::translate("controllerWidget", "connections", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(1, QApplication::translate("controllerWidget", "nodes", 0, QApplication::UnicodeUTF8));
        ___qtreewidgetitem->setText(0, QApplication::translate("controllerWidget", "automate", 0, QApplication::UnicodeUTF8));

        const bool __sortingEnabled = treeWidget->isSortingEnabled();
        treeWidget->setSortingEnabled(false);
        QTreeWidgetItem *___qtreewidgetitem1 = treeWidget->topLevelItem(0);
        ___qtreewidgetitem1->setText(0, QApplication::translate("controllerWidget", "automate", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem2 = ___qtreewidgetitem1->child(0);
        ___qtreewidgetitem2->setText(0, QApplication::translate("controllerWidget", "nodes", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem3 = ___qtreewidgetitem1->child(1);
        ___qtreewidgetitem3->setText(0, QApplication::translate("controllerWidget", "connections", 0, QApplication::UnicodeUTF8));
        QTreeWidgetItem *___qtreewidgetitem4 = ___qtreewidgetitem1->child(2);
        ___qtreewidgetitem4->setText(0, QApplication::translate("controllerWidget", "nodemanager", 0, QApplication::UnicodeUTF8));
        treeWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QApplication::translate("controllerWidget", "This view needs to be updated manually", 0, QApplication::UnicodeUTF8));
        updateBtn->setText(QApplication::translate("controllerWidget", "&update view", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(controllerWidget);
    } // retranslateUi

};

namespace Ui {
    class controllerWidget: public Ui_controllerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONTROLLERWIDGET_H
