#ifndef WIDGET_H
#define WIDGET_H

#include <vector>

#include "types.h"
#include "gridbox.h"

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtDebug>


class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget();
    QPushButton *pushButton_generate;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_width;
    QLabel *label_x;
    QLineEdit *lineEdit_height;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;

    GridMap *gMap = nullptr;
    std::vector<GridBox*> labelVector;

    void setupUi(QWidget *Form);
    void retranslateUi(QWidget *Form);
    void setupEvent();

public slots:
    void drawGrid();
    void gridClick(GridBox* self);

};

#endif // WIDGET_H
