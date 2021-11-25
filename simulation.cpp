#include <iostream>
#include <random>
#include <cmath>
#include <ctime>
#include <fstream>

// g++ simulation.cpp -o simulation -std=c++11

// quand la bactérie avance et reçoit plus de "nourriture", il retarde le tumble

class Environment {
public:
    int _fps;

    Environment() {
        _fps = 1;
    }

    Environment(int fps) : _fps(fps) {}
};

class Bacteria {
private:
    const unsigned int seed = std::time(0);
    std::mt19937 rng; // Standard mersenne_twister_engine
    std::uniform_real_distribution<> random_0_1;

protected:
    int _id;

    Environment* _env;

    double _x; // µm
    double _y; // µm

    double _current_speed; // µm/s

    double _current_theta; // rad

    int _run_count = 0;
    int _tumble_count = 0;

    void move_one_step() {
        this->_x += this->_current_speed * std::cos(this->_current_theta) / this->_env->_fps;
        this->_y += this->_current_speed * std::sin(this->_current_theta) / this->_env->_fps;
    }

public:
    Bacteria(Environment& env) : _x(0), _y(0), _current_speed(10), _current_theta(0) {
        this->_env = &env;

        this->rng.seed(this->seed);
        this->random_0_1 = std::uniform_real_distribution<>(0., 1.0);
    }

    void tumble() {
        // random speed
        this->_current_speed *= 1.05 - this->random_0_1(rng) * 0.1; // [0.95, 1.05)

        // randomize theta
        this->_current_theta += this->random_0_1(rng) * 2 - 1; // [-1, 1) rad
        // move
        move_one_step();

        this->_tumble_count++;
    }

    void run() {
        // random speed
        this->_current_speed *= 1.05 - this->random_0_1(rng) * 0.1; // [0.95, 1.05)

        // just move
        move_one_step();

        this->_run_count++;
    }

    void run_or_tumble() {
        double proba = random_0_1(rng);

        if (proba < 0.8) {
            run();
            // std::cout << "x " << this->_x << "  y " << this->_y << " v " << _current_speed << " t " << _current_theta << " run" << std::endl;
        } else {
            tumble();
            // std::cout << "x " << this->_x << "  y " << this->_y << " v " << _current_speed << " t " << _current_theta << " tumble" << std::endl;
        }
    }

    void print_stats() {
        std::cout << this->_run_count << " runs | " << this->_tumble_count << " tumbles" << std::endl;
    }

    void simulate(int nb_steps, bool print_stats = false, bool print_to_file = false) {
        std::ofstream file;

        if (print_to_file) {
            file.open("res.csv");
            file << "x" << ";" << "y" << ";" << "v" << ";" << "theta" << ";" << "t" << "\n";
        }

        for (int i = 0; i < nb_steps; i++) {
            this->run_or_tumble();
            file << this->_x << ";" << this->_y << ";" << this->_current_speed << ";" << this->_current_theta << ";" << i << "\n";
        }

        if (print_stats) {
            this->print_stats();
        }

        if (print_to_file) {
            file.close();
        }
    }
};

int main() {
    Environment* env = new Environment(1);

    Bacteria* e_coli = new Bacteria(*env);

    e_coli->simulate(1000, false, true);

    delete e_coli;
    delete env;

    return 0;
}
