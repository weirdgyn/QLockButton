#ifndef QLOCKBUTTON_H
#define QLOCKBUTTON_H

#include <QTimer>
#include <QWidget>

class QLockButton : public QWidget {
  Q_OBJECT

public:
  constexpr static const int DEF_TIMEOUT = 3000;
  constexpr static const int MAX_TIMEOUT = 3000;
  constexpr static const int MIN_TIMEOUT = 500;

  QLockButton(QWidget *parent = 0);

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

protected:
  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

signals:
  void commuted(QLockButton::Status status);
  void failed(int remainingTime);
  void lockTimeoutChanged();
  void unlockTimeoutChanged();
  void borderWidthChanged();
  void retriggerableChanged();
  void statusChanged();
  void modeChanged();

private slots:
  void onTimerTimeout();

private:
  QTimer mTimer;
  QRectF mFrame;
  int mLockTimeout;
  int mUnlockTimeout;
  bool mPressed;
  bool mTriggered;
  int mBorderWidth;
  Status mStatus;
  Mode mMode;

  QRectF getFrame();
  void resize();
  void commute();
  void drawBackground(QPainter &painter);
  void drawLockGlyph(QPainter &painter);
  void drawUnlockGlyph(QPainter &painter);
};

#endif // QLOCKBUTTON_H
