#include "qlockbutton/qlockbutton.h"

#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QRectF>
#include <QSvgRenderer>
#include <QtMath>

QLockButton::QLockButton(QWidget *parent)
    : QWidget(parent), mLockTimeout(DEF_TIMEOUT), mUnlockTimeout(DEF_TIMEOUT),
      mPressed(false), mTriggered(false), mBorderWidth(1),
      mStatus(Status::Unlocked), mMode(Mode::MultiShot),
      mBackgroundColor(Qt::white), mInnerColor(Qt::blue),
      mBorderColor(Qt::black), mFillStartColor(Qt::white),
      mFillEndColor(Qt::red) {
  setMouseTracking(true);
  setAutoFillBackground(true);

  mTimer.setInterval(DEF_TIMEOUT);
  mFillTimer.setInterval(DEF_UPDATE_TIMEOUT);

  connect(&mTimer, &QTimer::timeout, this, &QLockButton::onTimerTimeout);
  connect(&mFillTimer, &QTimer::timeout, this,
          &QLockButton::onFillTimerTimeout);

  mLockRenderer = new QSvgRenderer(QString(":/images/lock.svg"));
  mUnlockRenderer = new QSvgRenderer(QString(":/images/unlock.svg"));

  setFillGradient();
}

QLockButton::~QLockButton() {
  delete mLockRenderer;
  delete mUnlockRenderer;
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

  QPen _pen(Qt::black);
  _pen.setWidth(mBorderWidth);
  _pen.setColor(mBorderColor);

  painter.setPen(_pen);

  painter.setRenderHint(QPainter::Antialiasing, true);
  painter.setRenderHint(QPainter::SmoothPixmapTransform, true);

  drawBackground(painter);

  if (mPressed)
    drawFill(painter);

  if (mStatus == Status::Locked)
    drawLockGlyph(painter);
  else
    drawUnlockGlyph(painter);
}

void QLockButton::mousePressEvent(QMouseEvent *event) {
  Q_UNUSED(event)

  float _distance = qSqrt(qPow(event->pos().x() - mFrame.center().x(), 2) +
                          qPow(event->pos().y() - mFrame.center().y(), 2));

  if (_distance > mFrame.width() / 2)
    return;

  mPressed = true;

  if (mTriggered == true && mMode == Mode::SingleShot)
    return;

  mFillTimer.start();

  if (mStatus == Status::Locked)
    mTimer.start(mUnlockTimeout);
  else
    mTimer.start(mLockTimeout);
}

void QLockButton::mouseReleaseEvent(QMouseEvent *event) {
  Q_UNUSED(event)

  mPressed = false;

  if (mFillTimer.isActive()) {
    mFillTimer.stop();
    repaint();
  }

  if (mTimer.isActive()) {
    int _time = mTimer.remainingTime();

    mTimer.stop();

    emit fail(_time);
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
    changeStatus();
  }
}

void QLockButton::onFillTimerTimeout() { repaint(); }

QColor QLockButton::fillEndColor() const { return mFillEndColor; }

void QLockButton::setFillEndColor(const QColor &fillEndColor) {
  if (mFillEndColor == fillEndColor)
    return;
  mFillEndColor = fillEndColor;
  emit fillEndColorChanged();
  repaint();
  resize();
}

QColor QLockButton::fillStartColor() const { return mFillStartColor; }

void QLockButton::setFillStartColor(const QColor &fillStartColor) {
  if (mFillStartColor == fillStartColor)
    return;
  mFillStartColor = fillStartColor;
  emit fillStartColorChanged();
  repaint();
  resize();
}

QColor QLockButton::borderColor() const { return mBorderColor; }

void QLockButton::setBorderColor(const QColor &borderColor) {
  if (mBorderColor == borderColor)
    return;
  mBorderColor = borderColor;
  emit borderColorChanged();
  repaint();
}

QColor QLockButton::backgroundColor() const { return mBackgroundColor; }

void QLockButton::setBackgroundColor(const QColor &backgroundColor) {
  if (mBackgroundColor == backgroundColor)
    return;

  mBackgroundColor = backgroundColor;
  mFillGradient.setColorAt(1, mBackgroundColor);

  emit backgroundColorChanged();
  repaint();
}

QColor QLockButton::innerColor() const { return mInnerColor; }

void QLockButton::setInnerColor(const QColor &innerColor) {
  if (mInnerColor == innerColor)
    return;

  mInnerColor = innerColor;
  mFillGradient.setColorAt(0, mInnerColor);

  emit innerColorChanged();
  repaint();
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

QRectF QLockButton::getInnerFrame() {
  QRectF _frame = QRectF();

  _frame.setWidth(mFrame.width() * DEF_INNER_RATIO);
  _frame.setHeight(mFrame.height() * DEF_INNER_RATIO);
  _frame.moveCenter(mFrame.center());

  return _frame;
}

void QLockButton::resize() {
  mFrame = getFrame();
  mInnerFrame = getInnerFrame();
  mGlyphFrame = getGlyphFrame();
  mFillFrame = getFillFrame();

  setFillGradient();
}

int QLockButton::fillAngle() {
  float _ratio = 0;

  _ratio = 1 - ((float)mTimer.remainingTime() / (float)mTimer.interval());

  if (_ratio < 0)
    _ratio = 0;
  else if (_ratio > 1)
    _ratio = 1;

  float _angle = 0;

  _angle = _ratio * 360;
  _angle *= 16;

  return (int)_angle;
}

void QLockButton::setFillGradient() {
  mFillGradient.setCenter(mFrame.center());

  mFillGradient.setAngle(90);
  mFillGradient.setColorAt(1, mFillEndColor);
  mFillGradient.setColorAt(0, mFillStartColor);
}

void QLockButton::changeStatus() {
  mTriggered = true;

  if (mStatus == Status::Locked)
    mStatus = Status::Unlocked;
  else
    mStatus = Status::Locked;

  repaint();

  emit success(mStatus);
}

void QLockButton::drawBackground(QPainter &painter) {
  QBrush _brush(mBackgroundColor);

  painter.setBrush(_brush);

  painter.drawEllipse(mFrame);

  QBrush _inner_brush(mInnerColor);

  painter.setBrush(_inner_brush);

  painter.drawEllipse(mInnerFrame);
}

QRectF QLockButton::getGlyphFrame() {
  QRectF _frame = QRectF();

  _frame.setWidth(mFrame.width() * DEF_INNER_RATIO * DEF_GLYPH_RATIO);
  _frame.setHeight(mFrame.height() * DEF_INNER_RATIO * DEF_GLYPH_RATIO);
  _frame.moveCenter(mFrame.center());

  return _frame;
}

QRectF QLockButton::getFillFrame() {
  float _width = (mFrame.width() + mInnerFrame.width()) / 2;
  float _height = (mFrame.height() + mInnerFrame.height()) / 2;

  float _gap = (mFrame.width() - mInnerFrame.width()) / 2 - mBorderWidth / 2;

  mFillWidth = _gap - 1;

  QRectF _frame;

  _frame.setWidth(_width);
  _frame.setHeight(_height);

  _frame.moveCenter(mFrame.center());

  return _frame;
}

void QLockButton::drawLockGlyph(QPainter &painter) {
  mLockRenderer->render(&painter, mGlyphFrame);
}

void QLockButton::drawUnlockGlyph(QPainter &painter) {
  mUnlockRenderer->render(&painter, mGlyphFrame);
}

void QLockButton::drawFill(QPainter &painter) {
  QPen _pen(QBrush(mFillGradient), mFillWidth);
  _pen.setCapStyle(Qt::FlatCap);
  painter.setPen(_pen);

  painter.drawArc(mFillFrame, (90 + FIX_GRADIENT_START) * 16, fillAngle());
}
