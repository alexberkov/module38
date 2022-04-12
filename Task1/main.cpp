#include <QApplication>
#include <QPushButton>
#include <QPixmap>
#include <QPaintEvent>
#include <QPainter>
#include <QTimer>
#include <QMediaPlayer>

using namespace std;

class ImageButton: public QPushButton {
    Q_OBJECT
public:
    ImageButton() = default;
    explicit ImageButton(QWidget *parent);
    void paintEvent(QPaintEvent *e) override;
    [[nodiscard]] QSize sizeHint() const override;
    [[nodiscard]] QSize minimumSizeHint() const override;
    void keyPressEvent(QKeyEvent *e) override;
public slots:
    void setUp();
    void setDown();
private:
    QPixmap mCurrentButtonPixmap;
    QPixmap mButtonDownPixmap;
    QPixmap mButtonUpPixmap;
};

ImageButton::ImageButton(QWidget *parent) {
  setParent(parent);
  setToolTip("Press me!");
  setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mButtonDownPixmap = QPixmap("../red_button_down.png");
  mButtonUpPixmap = QPixmap("../red_button_up.png");
  mCurrentButtonPixmap = mButtonUpPixmap;
  setGeometry(mCurrentButtonPixmap.rect());
  connect(this, &QPushButton::clicked, this, &ImageButton::setDown);
}

void ImageButton::paintEvent(QPaintEvent *e) {
  QPainter p(this);
  p.drawPixmap(e->rect(), mCurrentButtonPixmap);
}

QSize ImageButton::sizeHint() const {
  return {200, 200};
}

QSize ImageButton::minimumSizeHint() const {
  return sizeHint();
}

void ImageButton::keyPressEvent(QKeyEvent *e) {
  setDown();
}

void ImageButton::setDown() {
  mCurrentButtonPixmap = mButtonDownPixmap;
  update();
  QTimer::singleShot(100, this, &ImageButton::setUp);
}

void ImageButton::setUp() {
  mCurrentButtonPixmap = mButtonUpPixmap;
  update();
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  ImageButton redButton(nullptr);
  redButton.setFixedSize(200, 200);
  redButton.move(1000,400);

  auto *player = new QMediaPlayer(&redButton);
  player->setMedia(QUrl::fromLocalFile("/Users/alexberkov/CLionProjects/Task38-1/click.wav"));
  player->setVolume(75);
  QObject::connect(&redButton, &QPushButton::clicked, [player]() {
    player->play();
  });

  redButton.show();
  return QApplication::exec();
}

#include <main.moc>
