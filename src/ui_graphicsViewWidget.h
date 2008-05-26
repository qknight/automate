/********************************************************************************
** Form generated from reading ui file 'graphicsViewWidget.ui'
**
** Created: Sun May 25 00:16:59 2008
**      by: Qt User Interface Compiler version 4.3.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_GRAPHICSVIEWWIDGET_H
#define UI_GRAPHICSVIEWWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QTextBrowser>
#include <QtGui/QWidget>

class Ui_graphicsViewWidget
{
public:
    QGridLayout *gridLayout;
    QGraphicsView *view;
    QWidget *spacerWidget;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *graphicsViewWidget)
    {
    if (graphicsViewWidget->objectName().isEmpty())
        graphicsViewWidget->setObjectName(QString::fromUtf8("graphicsViewWidget"));
    graphicsViewWidget->resize(944, 556);
    gridLayout = new QGridLayout(graphicsViewWidget);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    view = new QGraphicsView(graphicsViewWidget);
    view->setObjectName(QString::fromUtf8("view"));
    QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(20);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(view->sizePolicy().hasHeightForWidth());
    view->setSizePolicy(sizePolicy);

    gridLayout->addWidget(view, 0, 0, 1, 1);

    spacerWidget = new QWidget(graphicsViewWidget);
    spacerWidget->setObjectName(QString::fromUtf8("spacerWidget"));

    gridLayout->addWidget(spacerWidget, 0, 1, 1, 1);

    textBrowser = new QTextBrowser(graphicsViewWidget);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setMaximumSize(QSize(16777215, 140));

    gridLayout->addWidget(textBrowser, 1, 0, 1, 1);


    retranslateUi(graphicsViewWidget);

    QMetaObject::connectSlotsByName(graphicsViewWidget);
    } // setupUi

    void retranslateUi(QWidget *graphicsViewWidget)
    {
    graphicsViewWidget->setWindowTitle(QApplication::translate("graphicsViewWidget", "GraphicsView", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(graphicsViewWidget);
    } // retranslateUi

};

namespace Ui {
    class graphicsViewWidget: public Ui_graphicsViewWidget {};
} // namespace Ui

#endif // UI_GRAPHICSVIEWWIDGET_H
