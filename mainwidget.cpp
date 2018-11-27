#include "mainwidget.h"
#include "mainwidget.h"
#include <algorithm>

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

    pushButton_save = new QPushButton(Form);
    pushButton_save->setObjectName(QStringLiteral("pushButton_save"));

    horizontalLayoutWidget = new QWidget(Form);
    horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));

    horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
    horizontalLayout->setContentsMargins(0, 0, 0, 0);

    lineEdit_height = new QLineEdit(horizontalLayoutWidget);
    lineEdit_height->setObjectName(QStringLiteral("lineEdit_height"));
    horizontalLayout->addWidget(lineEdit_height);

    label_x = new QLabel(horizontalLayoutWidget);
    label_x->setObjectName(QStringLiteral("label_x"));
    horizontalLayout->addWidget(label_x);

    lineEdit_width = new QLineEdit(horizontalLayoutWidget);
    lineEdit_width->setObjectName(QStringLiteral("lineEdit_width"));
    horizontalLayout->addWidget(lineEdit_width);

    gridLayoutWidget = new QWidget(Form);
    gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));

    gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    gridLayout->setSpacing(1);

    // fill default text
    Form->setWindowTitle(QApplication::translate("Form", "Form", nullptr));
    pushButton_generate->setText(QApplication::translate("Form", "generate", nullptr));
    pushButton_save->setText(QApplication::translate("Form", "save", nullptr));
    pushButton_save->setToolTip(tr("Save Grid as file"));
    lineEdit_width->setText(QApplication::translate("Form", "4", nullptr));
    label_x->setText(QApplication::translate("Form", "X", nullptr));
    lineEdit_height->setText(QApplication::translate("Form", "6", nullptr));

    retranslateUi(Form);

    QMetaObject::connectSlotsByName(Form);
} // setupUi

void MainWidget::setupEvent()
{
    connect(pushButton_generate,SIGNAL(released()),this,SLOT(drawGrid()));
    connect(pushButton_save,SIGNAL(clicked()),this,SLOT(saveGridAsFile()));

}

void MainWidget::retranslateUi(QWidget *Form)
{
    pushButton_generate->setGeometry(QRect(150, 30, 75, 23));
    pushButton_save->setGeometry(QRect(310, 30, 75, 23));
    horizontalLayoutWidget->setGeometry(QRect(20, 20, 110, 40));
    gridLayoutWidget->setGeometry(QRect(20, 80, 360, 200));

} // retranslateUi

void MainWidget::gridClick(GridBox* self)
{
    if (gMap){
        auto index = self->objectName().toInt();
        if (self->text()=="1"){
            self->setText("0");
            this->gMap->at(index) = 0;
        } else{
            self->setText("1");
            this->gMap->at(index) = 1;
        }
    }
}

void MainWidget::saveGridAsFile()
{
    if (gMap){
        QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save Grid file"), "",
            tr("Hidato Grid file (*.hgrid);;All Files (*)")
        );
        if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

            // write file
            QTextStream out(&file);
            out<<gMap->height<<' '<<gMap->width<<endl;
            for (auto row=0; row<gMap->height; ++row){
                for (auto column=0; column<gMap->width; ++column){
                    out<< gMap->at(row, column) << ' ';
                }
                out<<endl;
            }
        }
    }
}

void MainWidget::drawGrid()
{
    if (gMap){
        delete gMap;
        gMap = nullptr;
    }

    // delete labelVector elements
    for (auto &e:labelVector){
        delete e;
    }
    labelVector.clear();

    // get width, height from textbox
    int width = lineEdit_width->text().toInt();
    int height = lineEdit_height->text().toInt();

    if (0<width && 0<height){
        retranslateUi(this);

        // set geometry
        auto geometry = gridLayoutWidget->geometry();
        auto grid_width = geometry.width() / width;
        auto grid_height = geometry.height() / height;
        grid_width = grid_height = std::min(grid_width, grid_height);
        geometry.setWidth(grid_width * width + (width - 1)); // space: (width - 1)
        geometry.setHeight(grid_height * height + (height -1)); // space: (height -1)
        gridLayoutWidget->setGeometry(geometry);

        // create GridMap
        gMap = new GridMap(width,height);
        auto grid_num=0;
        for (auto row=0; row<gMap->height; ++row){
            for (auto column=0; column<gMap->width; ++column){
                auto e = new GridBox(gridLayoutWidget);
                e->setObjectName(QString::number(grid_num));
                e->setFrameShape(QFrame::Panel);
                e->setAlignment(Qt::AlignCenter);
                e->setText(QString::number(gMap->at(row,column)));
                gridLayout->addWidget(e,row,column);
                connect(e,SIGNAL(clicked(GridBox*)),this,SLOT(gridClick(GridBox*)));
                labelVector.push_back(e);
                ++grid_num;
            }
        }

    }

}


