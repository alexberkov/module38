#include <QApplication>
#include <QHBoxLayout>
#include <QWebEngineView>
#include <QPlainTextEdit>

using namespace std;

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  QSizePolicy p(QSizePolicy::Preferred, QSizePolicy::Preferred);
  p.setHorizontalStretch(1);
  auto *mainWindow = new QWidget;
  auto *window = new QHBoxLayout(mainWindow);
  auto *editor = new QPlainTextEdit;
  editor->setSizePolicy(p);
  auto *preview = new QWebEngineView;
  preview->setSizePolicy(p);
  window->addWidget(editor);
  window->addWidget(preview);
  preview->setHtml(editor->toPlainText());
  QObject::connect(editor, &QPlainTextEdit::textChanged, [editor, preview]() {
    preview->setHtml(editor->toPlainText());
    editor->setFocus();
  });
  mainWindow->show();
  return QApplication::exec();
}
