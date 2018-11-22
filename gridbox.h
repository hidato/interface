#ifndef GRIDBOX_H
#define GRIDBOX_H

#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <Qt>

class GridBox : public QLabel
{
    Q_OBJECT

public:
    explicit GridBox(QWidget* parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());
    ~GridBox();

signals:
    void clicked(GridBox* self);

protected:
    void mousePressEvent(QMouseEvent* event);

};

#endif // GRIDBOX_H
