#ifndef DECODEFILEDLG_H
#define DECODEFILEDLG_H

#include <QMainWindow>
#include "dec3glassesfile.h"

namespace Ui {
class DecodeFileDlg;
}

class DecodeFileDlg : public QMainWindow
{
    Q_OBJECT

public:
    explicit DecodeFileDlg(QWidget *parent = 0);
    ~DecodeFileDlg();

public slots:
    void selectFile(bool b);
    void DecodeFile(bool b);

private:
    Ui::DecodeFileDlg *ui;
    QString SrcFileName_;
    QString DstFileName_;
    Dec3GlassesFile decodfile_;
};

#endif // DECODEFILEDLG_H
