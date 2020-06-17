#ifndef ENCODEFILEDLG_H
#define ENCODEFILEDLG_H

#include <QMainWindow>
#include "en3glassesfile.h"
namespace Ui {
class EncodeFileDlg;
}

class EncodeFileDlg : public QMainWindow
{
    Q_OBJECT

public:
    explicit EncodeFileDlg(QWidget *parent = 0);
    ~EncodeFileDlg();

public slots:
    void selectFile(bool b);
    void EncodeFile(bool b);

private:
    Ui::EncodeFileDlg *ui;
};

#endif // ENCODEFILEDLG_H
