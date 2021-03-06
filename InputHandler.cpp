//
// Created by uros on 20/04/22.
//

#include "InputHandler.h"

void InputHandler::parse_input(std::string s) {
    /**
*Parse parameters of linear function from file
*/
    std::ifstream infile;
    infile.open(INPUT_FILE + s);

    if (!infile.is_open()) {
        std::cout << "Couldn't open file " << INPUT_FILE << std::endl;
        std::exit(-2);
    }

    std::string line;
    std::string delimiter = "|";
    getline(infile, line);
    this->a = std::stod(line);
    getline(infile, line);
    this->b = std::stod(line);
    getline(infile, line);
    this->point_num = std::stod(line);
    getline(infile, line);
    this->x_err = std::stod(line);
    getline(infile, line);
    this->y_err = std::stod(line);
    getline(infile, line);
    this->min_x = std::stod(line);
    getline(infile, line);
    this->max_x = std::stod(line);

    for (int i = 0; i < 4; ++i) {
        getline(infile, line);
        this->cutoff.push_back(std::stod(line));
    }

    for (int i = 0; i < point_num; ++i) {
        getline(infile, line);
        double x = std::stod(line);
        getline(infile, line);
        double y = std::stod(line);
        stl_points.push_back(Point(x, y));
        concurrent_points.push_back(Point(x, y));
        stl_x.push_back(x);
        concurrent_x.push_back(x);
    }

    infile.close();
}

tbb::concurrent_vector<Point> points;

struct Shaker {
    double increment;
    double x_error;
    double y_error;
    double a;
    double b;

    void operator()(const tbb::blocked_range<int> &range) const {
        for (int i = range.begin(); i != range.end(); ++i) {
            srand(time(NULL));
            double x_rand = (rand() % 101 - 50) / 100.0;
            double y_rand = (rand() % 101 - 50) / 100.0;
            double new_x = increment * (i + 1);
            double calculated_x_err = x_error * x_rand / 100 * new_x;
            new_x += calculated_x_err;
            double new_y = (a * increment * (i + 1) + b);
            double calculated_y_err = y_error * y_rand / 100 * new_y;
            new_y += calculated_y_err;


            points.push_back(Point(new_x, new_y));
        }
    }

    Shaker(double a, double b, double increment, double x_error, double y_error) : a(a), b(b), increment(increment),
                                                                                   x_error(x_error),
                                                                                   y_error(y_error) {};
};


tbb::concurrent_vector<Point>
InputHandler::generate_dots(double x_min, double x_max, double x_error, double y_error, int point_count) {
    /**
*Generate points with error
* @param values  x_min minimum value of x, x_max maximum value of x,
 * x_error percent of error on x axis, y_error percent of error on y axis, point_count count of points to be generated
* @return generated points stored in concurrent vector
*/
    Shaker shaker(a, b, (x_max - x_min) / point_count, x_error, y_error);

    tbb::parallel_for(tbb::blocked_range<int>(0, point_count), shaker);
    return points;

}

double InputHandler::calculate_original(double x) const {
    return this->a * x + this->b;
}
