#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QLabel>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void createBubble();
    void updateScores();
    void checkGameOver();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    int score1;
    int score2;
    int playerTurn;
    QVector<QLabel*> bubbles;
    QLabel *scoreLabel1;
    QLabel *scoreLabel2;
    QLabel *turnLabel;

    void initializeGame();
    void handleBubbleClick(QLabel *bubble);
    void removeOldBubbles();
    void switchTurn();
};

#endif // MAINWINDOW_H
