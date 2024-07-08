#include "ResizableWindow.h"
#include "ui_ResizableWindow.h"

#include <QDebug>

ResizableWindow::ResizableWindow()
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Window);
    setMinimumSize(200, 200);
    setMouseTracking(true);

    // 布局
    QVBoxLayout *layout = new QVBoxLayout(this);
//    layout->setMargin(10);
    QWidget *wgt = new QWidget;
    wgt->setStyleSheet("background-color: green;");
    layout->addWidget(wgt); // 可以添加其他组件
    layout->setMargin(6);

    // 定义边框宽度
    borderWidth = this->layout()->margin(); // 可调整边框宽度
}

void ResizableWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dragStartPos = event->globalPos();
        originalGeometry = geometry();
    }
}

void ResizableWindow::mouseMoveEvent(QMouseEvent *event)
{
    QPoint pos = event->pos(); // 获取相对窗口的鼠标位置
    if (event->buttons() & Qt::LeftButton) {
        QPoint delta = event->globalPos() - dragStartPos;
        QRect newGeometry = originalGeometry;

        // 检查鼠标是否在调整大小的区域
        if (resizeDirection & Left) {
            newGeometry.setLeft(originalGeometry.left() + delta.x());
        }
        if (resizeDirection & Right) {
            newGeometry.setRight(originalGeometry.right() + delta.x());
        }
        if (resizeDirection & Top) {
            newGeometry.setTop(originalGeometry.top() + delta.y());
        }
        if (resizeDirection & Bottom) {
            newGeometry.setBottom(originalGeometry.bottom() + delta.y());
        }

        setGeometry(newGeometry);
    } else {
        setResizeCursor(pos); // 更新光标形状
    }
}

void ResizableWindow::setResizeCursor(QPoint pos)
{
    // 检查鼠标在边框的哪个部分
    bool atLeft = pos.x() < borderWidth;
    bool atRight = pos.x() > width() - borderWidth;
    bool atTop = pos.y() < borderWidth;
    bool atBottom = pos.y() > height() - borderWidth;

    resizeDirection = NoResize;

    if (atLeft) {
        resizeDirection |= Left;
        setCursor(Qt::SizeHorCursor);
    }
    if (atRight) {
        resizeDirection |= Right;
        setCursor(Qt::SizeHorCursor);
    }
    if (atTop) {
        resizeDirection |= Top;
        setCursor(Qt::SizeVerCursor);
    }
    if (atBottom) {
        resizeDirection |= Bottom;
        setCursor(Qt::SizeVerCursor);
    }
    if (atLeft && atTop) {
        resizeDirection |= TopLeft;
        setCursor(Qt::SizeFDiagCursor);
    }
    if (atRight && atTop) {
        resizeDirection |= TopRight;
        setCursor(Qt::SizeBDiagCursor);
    }
    if (atLeft && atBottom) {
        resizeDirection |= BottomLeft;
        setCursor(Qt::SizeBDiagCursor);
    }
    if (atRight && atBottom) {
        resizeDirection |= BottomRight;
        setCursor(Qt::SizeFDiagCursor);
    }

    if (!(resizeDirection & (Left | Right | Top | Bottom))) {
        setCursor(Qt::ArrowCursor);
    }
}
