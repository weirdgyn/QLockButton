#include "qlockbutton/qlockbutton.h"

#include <QPainter>
#include <QRectF>

QLockButton::QLockButton(QWidget *parent) : QWidget(parent) {
  setMouseTracking(true);
  setAutoFillBackground(true);
  mTimer.setInterval(DEF_TIMEOUT);
  connect(&mTimer, &QTimer::timeout, this, &QLockButton::onTimerTimeout);
  mPressed = false;
  mRetriggerable = false;
  mBorderWidth = 1;
}

void QLockButton::resizeEvent(QResizeEvent *event) { resize(); }

void QLockButton::paintEvent(QPaintEvent *event) {
  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing, true);

  QPen _pen(Qt::black);
  _pen.setWidth(mBorderWidth);

  painter.drawEllipse(mFrame);
}

void QLockButton::mousePressEvent(QMouseEvent *event) {
  mPressed = true;

  mTimer.start();
}

void QLockButton::mouseReleaseEvent(QMouseEvent *event) {
  if (mTimer.isActive()) {
    mTimer.stop();

    emit premature(mTimer.remainingTime());
  }

  mPressed = false;
}

void QLockButton::mouseMoveEvent(QMouseEvent *event) {}

int QLockButton::timeout() const { return mTimeout; }

void QLockButton::setTimeout(int timeout) {
  if (mTimeout == timeout)
    return;

  mTimeout = timeout;
  mTimer.setInterval(timeout);

  emit timeoutChanged();
}

void QLockButton::resetTimeout() { setTimeout(DEF_TIMEOUT); }

void QLockButton::onTimerTimeout() {
  if (mPressed) {
    mTimer.stop();
    emit release();
  }
}

bool QLockButton::retriggerable() const { return mRetriggerable; }

void QLockButton::setRetriggerable(bool retriggerable) {
  if (mRetriggerable == retriggerable)
    return;
  mRetriggerable = retriggerable;
  emit retriggerableChanged();
}

int QLockButton::borderWidth() const { return mBorderWidth; }

void QLockButton::setBorderWidth(int borderWidth) {
  if (mBorderWidth == borderWidth)
    return;

  if (borderWidth < 1)
    return;

  mBorderWidth = borderWidth;
  emit borderWidthChanged();
  resize();
  repaint();
}

QRectF QLockButton::getFrame() {
  int _size = qMin(this->width(), this->height()) - mBorderWidth;

  QSizeF _widgetSize = QSizeF(_size, _size);

  QRectF _frame = QRectF();
  _frame.setSize(_widgetSize);

  float _xOffset = (this->width() - _widgetSize.width()) / 2;
  float _yOffset = (this->height() - _widgetSize.height()) / 2;

  QPointF _offsetPoint(_xOffset, _yOffset);
  _frame.moveTopLeft(_offsetPoint);

  return _frame;
}

void QLockButton::resize() { mFrame = getFrame(); }
