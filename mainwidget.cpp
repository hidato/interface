#include "mainwidget.h"
#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    setupEvent();
}

MainWidget::~MainWidget()
{
    if (gMap){
        delete gMap;
    }
}

void MainWidget::setupUi(QWidget *Form)
{
    if (Form->objectName().isEmpty())
        Form->setObjectName(QStringLiteral("Form"));
    Form->resize(400, 300);
    pushButton_generate = new QPushButton(Form);
    pushButton_generate->setObjectName(QStringLiteral("pushButton_generate"));
    pushButton_generate->setGeometry(QRect(150, 30, 75, 23));
    horizontalLayoutWidget = new QWidget(Form);
    horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
    horizontalLayoutWidget->setGeometry(QRect(20, 20, 111, 41));
    horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);
    lineEdit_width = new QLineEdit(horizontalLayoutWidget);
    lineEdit_width->setObjectName(QStringLiteral("lineEdit_width"));

    horizontalLayout->addWidget(lineEdit_width);

    label_x = new QLabel(horizontalLayoutWidget);
    label_x->setObjectName(QStringLiteral("label_x"));

    horizontalLayout->addWidget(label_x);

    lineEdit_height = new QLineEdit(horizontalLayoutWidget);
    lineEdit_height->setObjectName(QStringLiteral("lineEdit_height"));

    horizontalLayout->addWidget(lineEdit_height);

    gridLayoutWidget = new QWidget(Form);
    gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(20, 80, 360, 200));
    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    retranslateUi(Form);

    QMetaObject::connectSlotsByName(Form);
} // setupUi

void MainWidget::setupEvent()
{
    connect(pushButton_generate,SIGNAL(released()),this,SLOT(drawGrid()));
}

void MainWidget::retranslateUi(QWidget *Form)
{
    Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
    pushButton_generate->setText(QApplication::translate("Form", "generate", nullptr));
    lineEdit_width->setText(QApplication::translate("Form", "6", nullptr));
    label_x->setText(QApplication::translate("Form", "X", nullptr));
    lineEdit_height->setText(QApplication::translate("Form", "4", nullptr));
} // retranslateUi

void MainWidget::drawGrid()
{
    if (gMap){
        delete gMap;
        gMap = nullptr;
    }

    for (auto &e:labelVector){
        delete e;
    }
    labelVector.clear();

    int width = lineEdit_width->text().toInt();
    int height = lineEdit_height->text().toInt();

    if (0<width && 0<height){
        gMap = new GridMap(width,height);

        for (auto column=0; column<gMap->width; ++column){
            for (auto row=0; row<gMap->height; ++row){
                auto e = new QLabel(gridLayoutWidget);
                //    e->setObjectName(QStringLiteral("label_1"));
                e->setAlignment(Qt::AlignCenter);
                auto str = QString::number(gMap->at(row,column));
                e->setText(str);
//                e->setText(QApplication::translate("Form", str, nullptr));
                gridLayout->addWidget(e,row,column);
                labelVector.push_back(e);
            }
        }

    }

}
