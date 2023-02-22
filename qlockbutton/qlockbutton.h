#ifndef QLOCKBUTTON_H
#define QLOCKBUTTON_H

#include <QTimer>
#include <QWidget>
#include <QSvgRenderer>

#define FIX_GRADIENT_START 1
/**
 * @brief QLockButton class 
 * 
 * QLockButton implements a two state, time based lock button.
 */
class QLockButton : public QWidget {
  Q_OBJECT

public:
  /**
  * @brief Size ratio of inner area (button actuator) against the full widget frame.
  */
  constexpr static const float DEF_INNER_RATIO = 0.8f;
  /**
  * @brief Size ratio of glyph/symbol ratio relative to inner area.
  */
  constexpr static const float DEF_GLYPH_RATIO = 0.8f;
  /**
   * @brief Default timeout value for both locking and unlocking (ms).
   */
  constexpr static const int DEF_TIMEOUT = 3000;
  /**
   * @brief Maximum timeout value for locking and unlocking (ms).
   */
  constexpr static const int MAX_TIMEOUT = 3000;
  /**
   * @brief Minimum timeout value for locking and unlocking (ms).
   */
  constexpr static const int MIN_TIMEOUT = 500;
  /**
   * @brief Timeout value for paint update (only used for fill effect).
   */
  constexpr static const int DEF_UPDATE_TIMEOUT = 50;

  /**
   * @brief Construct a new QLockButton object.
   * 
   * @param parent parent object
   */
  QLockButton(QWidget *parent = 0);
  /**
   * @brief Destroy the QLockButton object.
   */
  ~QLockButton();

  /**
   * @brief LockButton function Mode.
   */
  enum class Mode { 
    SingleShot = 0, /**< Only one successful status switch allowed */ 
    MultiShot       /**< Unlimited number of status switch allowed */
  };
  Q_ENUM(Mode)

  /**
   * @brief Convert argument into a readable string.
   * 
   * @param mode 
   * @return QString 
   */
  QString static ModeToString(Mode mode);

  /**
   * @brief Convert argument string in a Mode value.
   * 
   * @param mode 
   * @return Mode 
   */
  Mode static StringToMode(QString mode);

  /**
   * @brief LockButton status.
   */
  enum class Status { 
    Unlocked = 0, /**< Unlocked */ 
    Locked        /**< Locked */
  };
  Q_ENUM(Status)

  /**
   * @brief Convert argument into a readable string.
   * 
   * @param status 
   * @return QString 
   */
  QString static StatusToString(Status status);
  /**
   * @brief Convert argument in a Status value.
   * 
   * @param status 
   * @return Status 
   */
  Status static StringToStatus(QString status);

  Q_PROPERTY(int lockTimeout READ lockTimeout WRITE setLockTimeout NOTIFY
                 lockTimeoutChanged)
  /**
  * @brief lockTimeout property getter.
  * 
  * @return int lockTimeout value.
  * @see mLockTimeout
  */
  int lockTimeout() const;
  /**
   * @brief lockTimeout property setter.
   * 
   * @param lockTimeout new value 
  * @see mLockTimeout
   */
  void setLockTimeout(int lockTimeout);

  Q_PROPERTY(int unlockTimeout READ unlockTimeout WRITE setUnlockTimeout NOTIFY
                 unlockTimeoutChanged)
  /**
   * @brief unlockTimeout property getter.
   * 
   * @return int unlockTimeout value
   * @see mUnlockTimeout
   */
  int unlockTimeout() const;
  /**
   * @brief unlockTimeout property setter.
   * 
   * @param unlockTimeout new value
   * @see mUnlockTimeout
   */
  void setUnlockTimeout(int unlockTimeout);

  Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderWidth NOTIFY
                 borderWidthChanged)
  /**
   * @brief borderWidth property getter.
   * 
   * @return int borderWidth value
   * @see mBorderWidth
   */
  int borderWidth() const;
  /**
   * @brief borderWidth property setter.
   * 
   * @param borderWidth new value
   * @see mBorderWidth
   */
  void setBorderWidth(int borderWidth);

  Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)
  /**
   * @brief status property getter.
   * 
   * @return Status status value
   * @see mStatus
   */
  Status status() const;
  /**
   * @brief status property setter.
   * 
   * @param status new value
   * @see mStatus
   */
  void setStatus(Status status);

  Q_PROPERTY(Mode mode READ mode WRITE setMode NOTIFY modeChanged)
  /**
   * @brief mode property getter.
   * 
   * @return Mode mode value
   * @see Mode, mMode
   */
  Mode mode() const;
  /**
   * @brief mode property setter.
   * 
   * @param mode new value
   * @see Mode, mMode
   */
  void setMode(Mode mode);

  /**
   * @brief reset internal status.
   * 
   * Reset interal object status to allow further re-triggers (only when used in SingleShot mode)
   * @see mTriggered
   */
  void reset();

  Q_PROPERTY(QColor innerColor READ innerColor WRITE setInnerColor NOTIFY
                 innerColorChanged)
  /**
   * @brief innerColor property getter.
   * 
   * @return QColor innerColor value.
   * @see mInnerColor
   */
  QColor innerColor() const;
  /**
   * @brief innerColor propery setter.
   * 
   * @param innerColor new value
   * @see mInnerColor
   */
  void setInnerColor(const QColor &innerColor);

  Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE
                 setBackgroundColor NOTIFY backgroundColorChanged)
  /**
   * @brief backgroundColor property getter.
   * 
   * @return QColor backgroundColor value
   * @see mBackgroundColor
   */
  QColor backgroundColor() const;
  /**
   * @brief backgroundColor property setter.
   * 
   * @param backgroundColor new value
   * @see mBackgroundColor
   */
  void setBackgroundColor(const QColor &backgroundColor);

  Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY
                 borderColorChanged)
  /**
   * @brief borderColor property getter.
   * 
   * @return QColor borderColor value
   * @see mBorderColor
   */
  QColor borderColor() const;
  /**
   * @brief borderColor property setter.
   * 
   * @param borderColor new value
   * @see mBorderColor
   */
  void setBorderColor(const QColor &borderColor);

  Q_PROPERTY(QColor fillStartColor READ fillStartColor WRITE setFillStartColor NOTIFY fillStartColorChanged)
  /**
   * @brief fillStartColor property getter.
   * 
   * @return QColor 
   * @see mFillStartColor
   */
  QColor fillStartColor() const;
  /**
   * @brief fillStartColor property setter.
   * 
   * @param fillStartColor new value
   * @see mFillStartColor
   */
  void setFillStartColor(const QColor &fillStartColor);

  Q_PROPERTY(QColor fillEndColor READ fillEndColor WRITE setFillEndColor NOTIFY fillEndColorChanged)
  /**
   * @brief fillEndColor property getter.
   * 
   * @return QColor fillEndColor value
   * @see mFillEndColor
   */
  QColor fillEndColor() const;
  /**
   * @brief fillEndColor property setter.
   * 
   * @param fillEndColor new value
   * @see mFillEndColor
   */
  void setFillEndColor(const QColor &fillEndColor);

signals:
  /**
   * @brief signal successful change in status.
   * 
   * @param status reached status
   * @see Status, mStatus
   */
  void success(QLockButton::Status status);
  /**
   * @brief signal unsuccessful attempt.
   * 
   * @param remainingTime time missing to a successfull status change (ms)
   */
  void fail(int remainingTime);
  /**
   * @brief signal change in lockTimeout property value.
   * @see mLockTimeout
   */
  void lockTimeoutChanged();
  /**
   * @brief signal change in unlockTimeout property value.
   * @see mUnlockTimeout
   */
  void unlockTimeoutChanged();
  /**
   * @brief signal change in borderWidth property value.
   * @see mBorderWidth
   */
  void borderWidthChanged();
  /**
   * @brief signal change in status property value.
   * @see mStatus, Status
   */
  void statusChanged();
  /**
   * @brief signal change in mode property value.
   * @see mMode
   */  
  void modeChanged();
  /**
   * @brief signal innerColor in mode property value.
   * @see mInnerColor
   */  
  void innerColorChanged();
  /**
   * @brief signal backgroundColor in mode property value.
   * @see mBackgroundColor
   */    
  void backgroundColorChanged();
  /**
   * @brief signal borderColor in mode property value.
   * @see mBorderColor
   */      
  void borderColorChanged();
  /**
   * @brief signal fillStartColor in mode property value.
   * @see mFillStartColor
   */    
  void fillStartColorChanged();
  /**
   * @brief signal fillEndColor in mode property value.
   * @see mFillEndColor
   */   
  void fillEndColorChanged();

protected:
  /**
   * @brief override of base class resizeEvent. 
   * 
   * Invoked when widget area is resized.
   * Will update internal sub-areas size accordingly with defined ratios.
   * 
   * @param event Event descriptor
   * @see resize()
   */
  void resizeEvent(QResizeEvent *event);
  /**
   * @brief override of base class paintEvent.
   * 
   * Invoked when widget area need to be repainted.
   * Forced by repaint() method calls.
   * Will depict widget current status.
   * 
   * @param event Event descriptor
   */
  void paintEvent(QPaintEvent *event);
  /**
   * @brief override of base class mousePressEvent
   * 
   * Invoked when user press mouse button/touch inside widget area.
   * This action start the status change evaluation process/timeout.
   * 
   * @param event Event descriptor
   */
  void mousePressEvent(QMouseEvent *event);
  /**
   * @brief override of base class mouseReleaseEvent
   * 
   * Invoked when the user release mouse button/touch inside widget area.
   * This action usually reports an unsuccessfull status change.
   * 
   * @param event event descriptor
   */
  void mouseReleaseEvent(QMouseEvent *event);
  /**
   * @brief override of base class mouseMoveEvent
   * 
   * N/A
   * 
   * @param event event descriptor
   */
  void mouseMoveEvent(QMouseEvent *event);

private slots:
  /**
   * @brief handle main timer timeout.
   * 
   * This timeout evaluate a successfull status change.
   * 
   */
  void onTimerTimeout();
  /**
   * @brief handle fill timer timeout.
   * 
   * This timeout triggers painting of fill effect.
   * 
   */
  void onFillTimerTimeout();

private:
  /**
   * @brief Main timer.
   * 
   */
  QTimer mTimer;
  /**
   * @brief Fill timer.
   * 
   */
  QTimer mFillTimer;
  /**
   * @brief Widget frame.
   * 
   * The widget frame is evaluated as the largest square area inside designed widget area.
   * The frame is centered in widget area.
   * 
   */
  QRectF mFrame;
  /**
   * @brief Inner frame.
   * 
   * The inner frame house the button actuator area, the size is defined as DEF_INNER_RATIO against mFrame size, centered on the widget frame.
   * The inner frame size is defined as DEF_INNER_RATIO against mFrame size,
   * 
   */
  QRectF mInnerFrame;
  /**
   * @brief Glyph frame.
   * 
   * The glyph frame house the button lock/unlock status symbol, centered on inner frame.
   * The glyph frame size is defined as DEF_GLYPH_RATIO against mInnerFrame size,
   * 
   */
  QRectF mGlyphFrame;
  /**
   * @brief Fill effect/gradient frame.
   * 
   * The fill frame defines the frame where the fill gradient is painted.
   * The fill frame is centered on mFrame/mInnerFrame.
   * The fill frame is comprised between mFrame and mInnerFrame.
   * 
   */
  QRectF mFillFrame;
  /**
   * @brief Locking timeout (ms) [property]
   * 
   * Time needed to switch from Unlocked to Locked status.
   * 
   */
  int mLockTimeout;
  /**
   * @brief Unlocking timeout (ms) [property]
   * 
   * Time needed to switch from Locked to Unlocked status.
   * 
   */
  int mUnlockTimeout;
  /**
   * @brief Current status of button.
   * 
   */
  bool mPressed;
  /**
   * @brief Record triggering of button (SingleShot mode)
   * 
   */
  bool mTriggered;
  /**
   * @brief Width of widget borders (px) [property]
   * 
   */
  int mBorderWidth;
  /**
   * @brief Status of widget (Locked, Unlocked) [property]
   * 
   */
  Status mStatus;
  /**
   * @brief Working mode of the widget (SingleShot, MultiShot) [property]
   * 
   */
  Mode mMode;
  /**
   * @brief Lock symbol renderer.
   * 
   */
  QSvgRenderer *mLockRenderer;
  /**
   * @brief Unlock symbol renderer.
   * 
   */
  QSvgRenderer *mUnlockRenderer;
  /**
   * @brief Color of button background (external rim) [property]
   * 
   */
  QColor mBackgroundColor;
  /**
   * @brief Color of inner area (button actuator) [property]
   * 
   */
  QColor mInnerColor;
  /**
   * @brief Color of border [property]
   * 
   */
  QColor mBorderColor;
  /**
   * @brief Fill effect gradient
   * 
   */
  QConicalGradient mFillGradient;
  /**
   * @brief Fill effect rim depth.
   * 
   */
  float mFillWidth;
  /**
   * @brief Start color of fill effect/gradient.
   * 
   */
  QColor mFillStartColor;
  /**
   * @brief End color of fill effect/gradient.
   * 
   */
  QColor mFillEndColor;

  /**
   * @brief Evaluate internal widget frame.
   * 
   * @return QRectF
   * @see mFrame 
   */
  QRectF getFrame();
  /**
   * @brief Evaluate inner frame.
   * 
   * @return QRectF
   * @see mInnerFrame 
   */
  QRectF getInnerFrame();
  /**
   * @brief Evaluate glyph frame.
   * 
   * @return QRectF 
   * @see mGlyphFrame 
   */
  QRectF getGlyphFrame();
  /**
   * @brief Evaluate fill frame.
   * 
   * @return QRectF 
   * @see mFillFrame 
   */
  QRectF getFillFrame();

  /**
   * @brief Resize handler.
   * 
   * Handles resize related actions.
   * 
   */
  void resize();
  /**
   * @brief Change status value.
   * 
   * Switch the value of the status (based on the current status).
   * The funciton is called from internal methods on successfull state changes.
   * @see resizeEvent
   */
  void changeStatus();
  /**
   * @brief Draw widget background and inner frame. 
   * 
   * @param painter 
   */
  void drawBackground(QPainter &painter);
  /**
   * @brief Draw locked glyph.
   * 
   * @param painter 
   */
  void drawLockGlyph(QPainter &painter);
  /**
   * @brief Draw unlocked glyph.
   * 
   * @param painter 
   */
  void drawUnlockGlyph(QPainter &painter);
  /**
   * @brief Draw fill effect/gradient glyph.
   * 
   * @param painter 
   */
  void drawFill(QPainter &painter);
  /**
   * @brief Evaluate fill angle.
   * 
   * Evaluate value of fill angle from the remaining time of mTimer.
   * 
   * @return int Fill angle in degrees*16
   */
  int fillAngle();
  /**
   * @brief Sets fill effect gradient.
   * 
   */
  void setFillGradient();
};

#endif // QLOCKBUTTON_H
