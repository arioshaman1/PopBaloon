#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRandomGenerator>
#include <QLabel>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , score1(0)
    , score2(0)
    , playerTurn(1)
{
    ui->setupUi(this);

    // Настройка таймера для создания шариков
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::createBubble);
    timer->start(1000); // Создание шариков каждые 1000 мс

    // Настройка начальных очков
    QVBoxLayout *layout = new QVBoxLayout();
    scoreLabel1 = new QLabel("Игрок 1: 0", this);
    scoreLabel2 = new QLabel("Игрок 2: 0", this);
    turnLabel = new QLabel("Ходит игрок 1", this);
    layout->addWidget(scoreLabel1);
    layout->addWidget(scoreLabel2);
    layout->addWidget(turnLabel);
    ui->centralwidget->setLayout(layout);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    bool hit = false;
    for (QLabel *bubble : bubbles) {
        if (bubble->geometry().contains(event->pos())) {
            handleBubbleClick(bubble);
            hit = true;
            break;
        }
    }
    if (!hit) {
        switchTurn();
    }
}

void MainWindow::createBubble() {
    removeOldBubbles(); // Удаляем старые шарики перед созданием нового

    QLabel *bubble = new QLabel(this);
    if (playerTurn == 1) {
        bubble->setStyleSheet("background-color: red; border-radius: 25px;");
    } else {
        bubble->setStyleSheet("background-color: blue; border-radius: 25px;");
    }

    bubble->setGeometry(QRandomGenerator::global()->bounded(ui->centralwidget->width() - 50),
                        QRandomGenerator::global()->bounded(ui->centralwidget->height() - 50),
                        50, 50);
    bubble->show();
    bubbles.append(bubble);
}

void MainWindow::handleBubbleClick(QLabel *bubble) {
    bubbles.removeOne(bubble);
    bubble->deleteLater();

    if (playerTurn == 1) {
        score1++;
    } else {
        score2++;
    }

    updateScores();
    checkGameOver();
    switchTurn();
}

void MainWindow::removeOldBubbles() {
    for (QLabel *bubble : qAsConst(bubbles)) {
        bubble->deleteLater();
    }
    bubbles.clear();
}

void MainWindow::updateScores() {
    scoreLabel1->setText(QString("Игрок 1: %1").arg(score1));
    scoreLabel2->setText(QString("Игрок 2: %1").arg(score2));
}

void MainWindow::checkGameOver() {
    if (score1 >= 10) {
        timer->stop();
        QMessageBox::information(this, "Игра окончена", "Игрок 1 выиграл!");
    } else if (score2 >= 10) {
        timer->stop();
        QMessageBox::information(this, "Игра окончена", "Игрок 2 выиграл!");
    }
}

void MainWindow::switchTurn() {
    if (playerTurn == 1) {
        playerTurn = 2;
        turnLabel->setText("Ходит игрок 2");
    } else {
        playerTurn = 1;
        turnLabel->setText("Ходит игрок 1");
    }
}
