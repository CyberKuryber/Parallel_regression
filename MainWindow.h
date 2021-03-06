//
// Created by uros on 20/04/22.
//

#ifndef PARALLEL_REGRESSION_MAINWINDOW_H
#define PARALLEL_REGRESSION_MAINWINDOW_H

#include "QMainWindow"
#include "QPushButton"
#include "QString"
#include "QGridLayout"
#include "QSpinBox"
#include "QLabel"
#include "qcustomplot.h"
#include "SerialLinearRegression.h"
#include "ForParallelRegression.h"
#include "InputHandler.h"
#include "tbb/tick_count.h"
#include "iostream"
#include "TaskParallelRegression.h"
#include <string.h>
#include "ForParallelRegressionSTL.h"
#include "SerialLinearRegressionSTL.h"
#include "TaskParallelRegressionSTL.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(const QString &title);

    void handle_concurrent_serial();

    void handle_concurrent_for();

    void handle_concurrent_task();

    void handle_stl_serial();

    void handle_stl_for();

    void handle_stl_task();

    void generate_points();

    void file_test();

//     ~MainWindow();


private:
    QLabel *label_x_min;
    QLabel *label_x_max;
    QLabel *label_points;
    QLabel *label_x_err;
    QLabel *label_y_err;

    QSpinBox *input_x_min;
    QSpinBox *input_x_max;
    QSpinBox *input_points;
    QSpinBox *input_x_err;
    QSpinBox *input_y_err;
    QPushButton *button_serial;
    QPushButton *button_for;
    QPushButton *button_task;
    InputHandler input_handler;
    SerialLinearRegression serial_linear_regression;
    ForParallelRegression for_parallel_regression;
    TaskParallelRegression task_parallel_regression;
    tbb::concurrent_vector<Point> generated_points;
    SerialLinearRegressionSTL serial_linear_regression_stl;
    ForParallelRegressionSTL for_parallel_regression_stl;
    TaskParallelRegressionSTL task_parallel_regression_stl;

};


#endif //PARALLEL_REGRESSION_MAINWINDOW_H
