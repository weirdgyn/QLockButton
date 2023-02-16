#ifndef QLOCKBUTTON_H
#define QLOCKBUTTON_H

#include <QTimer>
#include <QWidget>

#define DEF_TIMEOUT 3000

class QLockButton : public QWidget {
  Q_OBJECT

public:
  QLockButton(QWidget *parent = 0);

  Q_PROPERTY(int timeout READ timeout WRITE setTimeout RESET resetTimeout NOTIFY
                 timeoutChanged)
  int timeout() const;
  void setTimeout(int timeout);
  void resetTimeout();

  Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY
                 borderWidthChanged)
  int borderWidth() const;
  void setBorderWidth(int borderWidth);

  Q_PROPERTY(bool retriggerable READ retriggerable WRITE setRetriggerable NOTIFY
                 retriggerableChanged)
  bool retriggerable() const;
  void setRetriggerable(bool retriggerable);

protected:
  void resizeEvent(QResizeEvent *event);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);

signals:
  void release();
  void premature(int remainingTime);
  void timeoutChanged();
  void borderWidthChanged();

  void retriggerableChanged();

private slots:
  void onTimerTimeout();

private:
  QTimer mTimer;
  QRectF mFrame;
  int mTimeout;
  bool mPressed;
  int mBorderWidth;
  bool mRetriggerable;

  QRectF getFrame();
  void resize();
};

#endif // QLOCKBUTTON_H
