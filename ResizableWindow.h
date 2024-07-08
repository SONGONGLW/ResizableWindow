#ifndef RESIZABLEWINDOW_H
#define RESIZABLEWINDOW_H

#include <QWidget>
#include <QMouseEvent>
#include <QApplication>
#include <QVBoxLayout>
#include <QCursor>

class ResizableWindow : public QWidget {
public:
    ResizableWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void setResizeCursor(QPoint pos);

private:
    int borderWidth;
    QPoint dragStartPos; // 开始拖动的位置
    QRect originalGeometry; // 初始窗口几何形状
    int resizeDirection = NoResize; // 当前调整方向

    enum ResizeDirection {
        NoResize = 0,
        Left = 1,
        Right = 2,
        Top = 4,
        Bottom = 8,
        TopLeft = Top | Left,
        TopRight = Top | Right,
        BottomLeft = Bottom | Left,
        BottomRight = Bottom | Right,
    };
};


#endif // RESIZABLEWINDOW_H
