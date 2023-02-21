#ifndef QLOCKBUTTON_H
#define QLOCKBUTTON_H

#include <QTimer>
#include <QWidget>
#include <QSvgRenderer>

#define FIX_GRADIENT_START 1

class QLockButton : public QWidget {
  Q_OBJECT

public:
  constexpr static const float DEF_INNER_RATIO = 0.8f;
  constexpr static const float DEF_GLYPH_RATIO = 0.8f;
  constexpr static const int DEF_TIMEOUT = 3000;
  constexpr static const int MAX_TIMEOUT = 3000;
  constexpr static const int MIN_TIMEOUT = 500;
  constexpr static const int DEF_UPDATE_TIMEOUT = 50;

  QLockButton(QWidget *parent = 0);
  ~QLockButton();

  enum class Mode { SingleShot = 0, MultiShot };
  Q_ENUM(Mode)

  QString static ModeToString(Mode mode);

  Mode static StringToMode(QString mode);

  enum class Status { Unlocked = 0, Locked };
  Q_ENUM(Status)

  QString static StatusToString(Status status);

  Status static StringToStatus(QString status);

  Q_PROPERTY(int lockTimeout READ lockTimeout WRITE setLockTimeout NOTIFY
                 lockTimeoutChanged)
  int lockTimeout() const;
  void setLockTimeout(int lockTimeout);

  Q_PROPERTY(int unlockTimeout READ unlockTimeout WRITE setUnlockTimeout NOTIFY
                 unlockTimeoutChanged)
  int unlockTimeout() const;
  void setUnlockTimeout(int unlockTimeout);

  Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY
                 borderWidthChanged)
  int borderWidth() const;
  void setBorderWidth(int borderWidth);

  Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
  Status status() const;
  void setStatus(Status status);

  Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY modeChanged)
  Mode mode() const;
  void setMode(Mode mode);

  void reset();

  Q_PROPERTY(QColor innerColor READ innerColor WRITE setInnerColor NOTIFY
                 innerColorChanged)
  QColor innerColor() const;
  void setInnerColor(const QColor &innerColor);

  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE
                 setBackgroundColor NOTIFY backgroundColorChanged)
  QColor backgroundColor() const;
  void setBackgroundColor(const QColor &backgroundColor);

  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY
                 borderColorChanged)
  QColor borderColor() const;
  void setBorderColor(const QColor &borderColor);

  Q_PROPERTY(QColor fillStartColor READ fillStartColor WRITE setFillStartColor NOTIFY fillStartColorChanged)
  QColor fillStartColor() const;
  void setFillStartColor(const QColor &fillStartColor);

  Q_PROPERTY(QColor fillEndColor READ fillEndColor WRITE setFillEndColor NOTIFY fillEndColorChanged)
  QColor fillEndColor() const;
  void setFillEndColor(const QColor &fillEndColor);

protected:
  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

signals:
  void success(QLockButton::Status status);
  void fail(int remainingTime);
  void lockTimeoutChanged();
  void unlockTimeoutChanged();
  void borderWidthChanged();
  void retriggerableChanged();
  void statusChanged();
  void modeChanged();
  void innerColorChanged();
  void backgroundColorChanged();
  void borderColorChanged();
  void fillStartColorChanged();
  void fillEndColorChanged();

private slots:
  void onTimerTimeout();
  void onFillTimerTimeout();

private:
  QTimer mTimer;
  QTimer mFillTimer;
  QRectF mFrame;
  QRectF mInnerFrame;
  QRectF mGlyphFrame;
  QRectF mFillFrame;
  int mLockTimeout;
  int mUnlockTimeout;
  bool mPressed;
  bool mTriggered;
  int mBorderWidth;
  Status mStatus;
  Mode mMode;
  QSvgRenderer *mLockRenderer;
  QSvgRenderer *mUnlockRenderer;
  QColor mBackgroundColor;
  QColor mInnerColor;
  QColor mBorderColor;
  QConicalGradient mFillGradient;
  float mFillWidth;
  QColor mFillStartColor;
  QColor mFillEndColor;

  QRectF getFrame();
  QRectF getInnerFrame();
  QRectF getGlyphFrame();
  QRectF getFillFrame();

  void resize();
  void changeStatus();
  void drawBackground(QPainter &painter);
  void drawLockGlyph(QPainter &painter);
  void drawUnlockGlyph(QPainter &painter);
  void drawFill(QPainter &painter);
  int fillAngle();
  void setFillGradient();
};

#endif // QLOCKBUTTON_H
