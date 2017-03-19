#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionUsing_Itunes_Link_triggered();

    void on_actionUsing_RSS_Link_triggered();

    void on_actionRefresh_Feed_triggered();

    void on_actionRemove_Podcast_triggered();

    QString addPodcast_dlg(QString Label, QString Title, bool &ok);

    bool getRSSurl(QString itunesLink, QString &rssLink);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
