#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QRegularExpressionValidator *keyValidator = new QRegularExpressionValidator(QRegularExpression("[0-9A-F]{0,32}"));

    QStringList *operationsLst = new QStringList({"XOR", "OR", "AND", "NOT"});
    QStringList *masksList = nullptr;

    QLabel *inputLbl = new QLabel("Исходная папка: ");
    QLabel *outputLbl = new QLabel("Выходная папка: ");
    QLabel *maskLbl = new QLabel("Маска: ");
    QLabel *searchInAttachedLbl = new QLabel("Искать в подпапках: ");
    QLabel *deleteBaseLbl = new QLabel("Удалить исходный файл: ");
    QLabel *rewriteLbl = new QLabel("Перезаписывать при совпадении имён: ");
    QLabel *keyLbl = new QLabel("Ключ шифрования: ");
    QLabel *useTimerLbl = new QLabel("Использовать таймер: ");
    QLabel *timerLbl = new QLabel("Установите интервал: ");
    QLabel *operationLbl = new QLabel("Операция: ");
    QLabel *statusLbl = new QLabel("Готово к работе");

    QWidget *centralWgt = new QWidget();
    QWidget *inputFileWgt = new QWidget();
    QWidget *outputFileWgt = new QWidget();
    QWidget *maskWgt = new QWidget();
    QWidget *searchInAttachedWgt = new QWidget();
    QWidget *deleteBaseWgt= new QWidget();
    QWidget *rewriteWgt = new QWidget();
    QWidget *keyWgt = new QWidget();
    QWidget *operationWgt = new QWidget();
    QWidget *useTimerWgt = new QWidget();
    QWidget *timerWgt = new QWidget();
    QWidget *btnWgt = new QWidget();

    QPushButton *selectInputFolderBtn = new QPushButton("...");
    QPushButton *selectOutputFolderBtn = new QPushButton("...");
    QPushButton *startBtn = new QPushButton("Начать");
    QPushButton *stopBtn = new QPushButton("Остановить");

    QVBoxLayout *layout = new QVBoxLayout();

    QHBoxLayout *checkBoxLayout = new QHBoxLayout();
    QHBoxLayout *inputFileLayout = new QHBoxLayout();
    QHBoxLayout *maskLayout = new QHBoxLayout();
    QHBoxLayout *outputFileLayout = new QHBoxLayout();
    QHBoxLayout *useTimerLayout = new QHBoxLayout();
    QHBoxLayout *timerLayout = new QHBoxLayout();
    QHBoxLayout *searchInAttachedLayout = new QHBoxLayout();
    QHBoxLayout *deleteBaseLayout = new QHBoxLayout();
    QHBoxLayout *rewriteLayout = new QHBoxLayout();
    QHBoxLayout *keyLayout = new QHBoxLayout();
    QHBoxLayout *operationLayout = new QHBoxLayout();
    QHBoxLayout *btnLayout = new QHBoxLayout();

    QStatusBar *statusBar = new QStatusBar();

    QFileDialog *inputFolderDlg = new QFileDialog();
    QFileDialog *outputFolderDlg = new QFileDialog();

    QLineEdit *maskEdt = new QLineEdit();
    QLineEdit *keyEdt = new QLineEdit();
    QLineEdit *inputFileEdt = new QLineEdit();
    QLineEdit *outputFileEdt = new QLineEdit();

    QCheckBox *searchInAttachedCB = new QCheckBox();
    QCheckBox *deleteBaseCB = new QCheckBox();
    QCheckBox *rewriteCB = new QCheckBox();
    QCheckBox *timerCB = new QCheckBox();
    QComboBox *operationCB = new QComboBox();

    QTimer *timerTmr = new QTimer();
    QTime *timeOnTimeEdt = new QTime();
    QTimeEdit *timerEdt = new QTimeEdit(*timeOnTimeEdt);

    void searchFiles(QStringList*, QString);
    void setInterfaceEnabled(bool);
    void encoding();

private slots:
    void slotTimeAlarm();
    void setInputPath();
    void setOutputPath();
    void startWorking();
    void stopTimer();

};
#endif // MAINWINDOW_H
