#include "qlockbutton/qlockbutton.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QRectF>
#include <QtMath>

QLockButton::QLockButton(QWidget *parent) : QWidget(parent) {
  setMouseTracking(true);
  setAutoFillBackground(true);

  mStatus = Status::Unlocked;
  mMode = Mode::MultiShot;

  mLockTimeout = DEF_TIMEOUT;
  mUnlockTimeout = DEF_TIMEOUT;
  mPressed = false;
  mTriggered = false;
  mBorderWidth = 1;

  mTimer.setInterval(DEF_TIMEOUT);
  connect(&mTimer, &QTimer::timeout, this, &QLockButton::onTimerTimeout);
}

QString QLockButton::ModeToString(Mode mode) {
  switch (mode) {
  case Mode::SingleShot:
    return "SingleShot";
  default:
  case Mode::MultiShot:
    return "MultiShot";
    break;
  }
}

QLockButton::Mode QLockButton::StringToMode(QString mode) {
  if (mode.toLower() == "singleshot")
    return Mode::SingleShot;
  else // if(mode.toLower()=="multishot")
    return Mode::MultiShot;
}

QString QLockButton::StatusToString(Status status) {
  switch (status) {
  case Status::Unlocked:
    return "Unlocked";
  default:
  case Status::Locked:
    return "Locked";
    break;
  }
}

QLockButton::Status QLockButton::StringToStatus(QString status) {
  if (status.toLower() == "unlocked")
    return Status::Unlocked;
  else // if(status.toLower()=="locked")
    return Status::Locked;
}

void QLockButton::resizeEvent(QResizeEvent *event) {
  Q_UNUSED(event)
  resize();
}

void QLockButton::paintEvent(QPaintEvent *event) {
  Q_UNUSED(event)

  QPainter painter(this);

  painter.setRenderHint(QPainter::Antialiasing, true);

  drawBackground(painter);

  if (mStatus == Status::Locked)
    drawLockGlyph(painter);
  else
    drawUnlockGlyph(painter);
}

void QLockButton::mousePressEvent(QMouseEvent *event) {
  Q_UNUSED(event)

  float _distance = qSqrt(qPow(event->pos().x() - mFrame.center().x(), 2) +
                          qPow(event->pos().y() - mFrame.center().y(), 2));

  if(_distance > mFrame.width()/2)
      return;

  mPressed = true;

  if (mTriggered == true && mMode == Mode::SingleShot)
    return;

  if (mStatus == Status::Locked)
    mTimer.start(mUnlockTimeout);
  else
    mTimer.start(mLockTimeout);
}

void QLockButton::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event)

  mPressed = false;

  if (mTimer.isActive()) {
    int _time = mTimer.remainingTime();

    mTimer.stop();

    emit failed(_time);
  }
}

void QLockButton::mouseMoveEvent(QMouseEvent *event) { Q_UNUSED(event) }

int QLockButton::lockTimeout() const { return mLockTimeout; }

void QLockButton::setLockTimeout(int lockTimeout) {
  if (mLockTimeout == lockTimeout)
    return;

  if (lockTimeout > MAX_TIMEOUT || lockTimeout < MIN_TIMEOUT)
    return;

  mLockTimeout = lockTimeout;
  emit lockTimeoutChanged();
  repaint();
}

void QLockButton::onTimerTimeout() {
  if (mPressed) {
    mTimer.stop();
    commute();
  }
}

int QLockButton::unlockTimeout() const { return mUnlockTimeout; }

void QLockButton::setUnlockTimeout(int unlockTimeout) {
  if (mUnlockTimeout == unlockTimeout)
    return;

  if (unlockTimeout > MAX_TIMEOUT || unlockTimeout < MIN_TIMEOUT)
    return;

  mUnlockTimeout = unlockTimeout;
  emit unlockTimeoutChanged();
  repaint();
}

QLockButton::Mode QLockButton::mode() const { return mMode; }

void QLockButton::setMode(Mode mode) {
  if (mMode == mode)
    return;
  mMode = mode;
  emit modeChanged();
  repaint();
}

void QLockButton::reset() { mTriggered = false; }

QLockButton::Status QLockButton::status() const { return mStatus; }

void QLockButton::setStatus(Status status) {
  if (mStatus == status)
    return;
  mStatus = status;
  emit statusChanged();
  repaint();
}

int QLockButton::borderWidth() const { return mBorderWidth; }

void QLockButton::setBorderWidth(int borderWidth) {
  if (mBorderWidth == borderWidth)
    return;

  if (borderWidth > mFrame.width() / 8 || borderWidth < 1)
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

void QLockButton::commute() {
  mTriggered = true;

  if (mStatus == Status::Locked)
    mStatus = Status::Unlocked;
  else
    mStatus = Status::Locked;

  emit commuted(mStatus);
}

void QLockButton::drawBackground(QPainter &painter) {
  QPen _pen(Qt::black);
  _pen.setWidth(mBorderWidth);

  painter.setPen(_pen);

  painter.drawEllipse(mFrame);
}

void QLockButton::drawLockGlyph(QPainter &painter) { Q_UNUSED(painter) }

void QLockButton::drawUnlockGlyph(QPainter &painter) { Q_UNUSED(painter) }
