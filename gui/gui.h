#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMainWindow>
#include <QDebug>
#include <QColorDialog>

#include <filesystem>
#include <memory>
#include <iostream>

#include "inc/fractal_generator.h"


const std::filesystem::path kDataDirPath{DATA_DIR_PATH};
const auto kTestFilePath{ kDataDirPath / "test.bmp" };



class Gui : public QMainWindow {
    Q_OBJECT
  
  public:
    using GuiPtr = std::unique_ptr<Gui, std::default_delete<Gui>>;

    static GuiPtr CreateGui(QWidget* parent = nullptr);

    explicit Gui(QWidget* parent = nullptr);
    Gui(const Gui& other) = delete;
    Gui& operator=(const Gui& other) = delete;
    Gui(Gui&& other) noexcept;
    Gui& operator=(Gui&& other) noexcept;
    virtual ~Gui();

    void swap(Gui& other) noexcept;
    friend void swap(Gui& lhs, Gui& rhs) noexcept;

  private slots:
    void BrowseFile();
    void ShowColorDialog();
    void ChangeColorButton();

  private:
    void SetupCentralWidget();
    void SetupSignals();
    void LoadImage(const QString& file_path);

    QGridLayout *grid_{new QGridLayout()};
    QWidget *central_{new QWidget()};
    QLabel *image_{new QLabel()};
    QPushButton *browse_button_{new QPushButton("Browse", this)};
    QPushButton *color_button_{new QPushButton("Color", this)};
    QColorDialog *color_dialog_{new QColorDialog(this)};
};
