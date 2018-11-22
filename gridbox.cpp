#include "gridbox.h"



GridBox::GridBox(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {
}

GridBox::~GridBox() {}

void GridBox::mousePressEvent(QMouseEvent* event) {
    emit clicked(this);
}
