#include <QApplication>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QLabel>
#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>

using namespace std;

QImage blurImage(const QImage& source, int blurRadius) {
  if (source.isNull()) return {};
  else {
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(source));
    auto *blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(blurRadius);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result(source.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(),
                 QRectF(0, 0, source.width(), source.height()));
    return result;
  }
}

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QWidget mainWindow;
  mainWindow.setMinimumSize(800, 600);
  QVBoxLayout vbox(&mainWindow);

  auto *imageLabel = new QLabel(&mainWindow);
  vbox.addWidget(imageLabel);

  auto *blurSlider = new QSlider(&mainWindow);
  blurSlider->setOrientation(Qt::Horizontal);
  blurSlider->setMinimum(0);
  blurSlider->setMaximum(10);
  vbox.addWidget(blurSlider);

  auto *openButton = new QPushButton("Open", &mainWindow);
  vbox.addWidget(openButton);

  QString filePath;
  QImage currImage;
  QObject::connect(openButton, &QPushButton::clicked,
                   [imageLabel, &filePath, &currImage, blurSlider]() {
    filePath = QFileDialog::getOpenFileName(nullptr, "Open image",
                                            "/Users/alexberkov/", "Images (*.jpg)");
    currImage = QImage(filePath);
    imageLabel->setPixmap(QPixmap::fromImage(blurImage(currImage, 0).scaled(
      imageLabel->width(),
      imageLabel->height(), Qt::KeepAspectRatio)));
    blurSlider->setValue(0);
  });

  QObject::connect(blurSlider, &QSlider::valueChanged,
                   [&blurSlider, imageLabel, &currImage](int value) {
    value = blurSlider->value();
    imageLabel->setPixmap(QPixmap::fromImage(blurImage(currImage, value).scaled(
      imageLabel->width(),
      imageLabel->height(), Qt::KeepAspectRatio)));
  });
  mainWindow.show();
  return QApplication::exec();
}
