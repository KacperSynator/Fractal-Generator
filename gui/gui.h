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
#include <QComboBox>
#include <QSlider>
#include <QMessageBox>

#include <filesystem>
#include <memory>
#include <iostream>

#include "inc/fractal_generator.h"


const std::filesystem::path kDataDirPath{DATA_DIR_PATH};
const auto kTestFilePath{ kDataDirPath / "test.bmp" };
const std::string kOutputFileName{ "out" };
const auto kOutputFilePath{ kDataDirPath / (kOutputFileName + ".bmp") };

const auto kMaxIterations{1000};
const auto kImgWidth{800};
const auto kImgHeight{600};

constexpr auto kZoomStartX = kImgWidth / 2;
constexpr auto kZoomStartY = kImgHeight / 2;
constexpr auto kZoomStartSCale = 4.0 / kImgWidth;

const auto kColorRangeSliderWidth{200};
const auto kColorRangeSliderMaxVal{100};
const auto kZoomScaleSliderWidth{200};
const auto kZoomScaleSliderMaxVal{100};

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
    void SaveAs();
    void ShowColorDialog();
    void ChangeColorButton();
    void GenerateFractal();
    void UpdateColorRangeValue();
    void UpdateZoomScaleValue();
    void ValidateColorRangeSlider();
    void AddColorRange();
    void PopColorRange();
    void AddZoom();
    void PopZoom();
  
  protected:
    void mouseReleaseEvent(QMouseEvent *event) override;

  private:
    void SetupCentralWidget();
    void FillComboBoxes();
    void SetupSignals();
    void CreateFractalGenerator();
    void LoadImage(const QString& file_path);
    void SetupColorRangeSlider();
    void SetupZoomScaleSlider();
    

    std::unique_ptr< FractalGenerator > fg_{nullptr};
    FractalGeneratorBuilder fgb_{kImgWidth, kImgHeight, kMaxIterations};
    std::vector<float> color_ranges_;
    ZoomList zooms_{kImgWidth, kImgHeight};
    Zoom current_zoom_;

    QGridLayout *grid_{new QGridLayout()};
    QWidget *central_{new QWidget()};
    QLabel *image_{new QLabel(this)};
    QPushButton *browse_button_{new QPushButton("Browse", this)};
    QPushButton *save_as_button_{new QPushButton("Save As", this)};
    QPushButton *color_button_{new QPushButton("Color", this)};
    QPushButton *generate_button_{new QPushButton("Generate", this)};
    QColorDialog *color_dialog_{new QColorDialog(this)};
    QSlider *color_range_slider_{new QSlider{Qt::Orientation::Horizontal, this}};
    QLabel *color_slider_value_{new QLabel("0.00", this)};
    QPushButton * add_color_range_button_ {new QPushButton("Add color range", this)};
    QPushButton * pop_color_range_button_ {new QPushButton("Pop color range", this)};
    QLabel *fractal_text_{new QLabel("Fractal: ", this)};
    QComboBox *fractal_box_{new QComboBox(this)};
    QLabel *coloring_text_{new QLabel("Coloring: ", this)};
    QComboBox *coloring_box_{new QComboBox(this)};
    QLabel *image_text_{new QLabel("Image: ", this)};
    QComboBox *image_box_{new QComboBox(this)};
    QLabel *zoom_offset_{new QLabel{"Zoom: x:  y:  scale: ", this}};
    QSlider *zoom_scale_slider_{new QSlider{Qt::Orientation::Horizontal, this}};
    QPushButton * add_zoom_button_ {new QPushButton("Add zoom", this)};
    QPushButton * pop_zoom_button_ {new QPushButton("Pop zoom", this)};

    QMessageBox *error_box_{new QMessageBox(this)};
};
