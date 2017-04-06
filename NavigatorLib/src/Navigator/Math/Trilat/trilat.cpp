//
// Created by  Oleksiy Grechnyev on 3/13/2017.
// Trilateration routines stolen from the old tracking_lib
//

#include <cmath>

#include "Eigen/Dense"

#include "Navigator/Math/Trilat/trilat.h"

namespace Navigator {
    namespace Math {
        namespace Trilat {

            bool trilatLocation2d(const std::vector<TrilatRecord> &records,
                                  Position3D &location) {
                // To locate position on a 2d plan, have to get at least 3 becaons,
                // otherwise return false.
                if (records.size() < 3) {
                    return false;
                }

                // Define the matrix that we are going to use
                size_t count = records.size();
                size_t rows = count * (count - 1) / 2;
                Eigen::MatrixXd m(rows, 2);
                Eigen::VectorXd b(rows);

                // Fill in matrix according to the equations
                size_t row = 0;
                double x1, x2, y1, y2, r1, r2;
                Position3D beacon1, beacon2;

                for (auto rit_i = records.begin(); rit_i != records.end(); ++rit_i) {
                    beacon1 = (*rit_i).pos;
                    for (auto rit_j = rit_i + 1; rit_j != records.end(); ++rit_j) {
                        beacon2 = (*rit_j).pos;
                        x1 = beacon1.x, y1 = beacon1.y;
                        x2 = beacon2.x, y2 = beacon2.y;
                        r1 = (*rit_i).dist;
                        r2 = (*rit_j).dist;
                        m(row, 0) = x1 - x2;
                        m(row, 1) = y1 - y2;
                        b(row) = ((std::pow(x1, 2) - std::pow(x2, 2)) +
                                  (std::pow(y1, 2) - std::pow(y2, 2)) -
                                  (std::pow(r1, 2) - std::pow(r2, 2))) / 2;
                        row++;
                    }
                }

                // Then calculate to solve the equations, using the least square solution
                Eigen::Vector2d pos = m.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);

                location.x = pos(0);
                location.y = pos(1);
                location.z = 0;

                return true;
            }

            Position3D
            trilatLocation2d(const std::vector<TrilatRecord> &records) {
                Position3D p;
                bool success = trilatLocation2d(records, p);
                if (!success)
                    throw std::runtime_error("Impossible to trilat, wrong input.");
                return p;
            }

            bool trilatLocation3d(const std::vector<TrilatRecord> &records,
                                  Position3D &location) {

                // To locate position in a 3D space, have to get at least 4 becaons,
                // otherwise return false.
                if (records.size() < 4) {
                    return false;
                }


                // Define the matrix that we are going to use
                size_t count = records.size();
                size_t rows = count * (count - 1) / 2;
                Eigen::MatrixXd m(rows, 3);
                Eigen::VectorXd b(rows);

                // Fill in matrix according to the equations
                size_t row = 0;
                double x1, x2, y1, y2, z1, z2, r1, r2;
                Position3D beacon1, beacon2;

                for (auto rit_i = records.begin(); rit_i != records.end(); ++rit_i) {

                    beacon1 = (*rit_i).pos;
                    for (auto rit_j = rit_i + 1; rit_j != records.end(); ++rit_j) {
                        beacon2 = (*rit_j).pos;
                        x1 = beacon1.x, y1 = beacon1.y;
                        z1 = beacon1.z;
                        x2 = beacon2.x, y2 = beacon2.y;
                        z2 = beacon2.z;
                        r1 = (*rit_i).dist;
                        r2 = (*rit_j).dist;
                        m(row, 0) = x1 - x2;
                        m(row, 1) = y1 - y2;
                        m(row, 2) = z1 - z2;
                        b(row) = ((std::pow(x1, 2) - std::pow(x2, 2)) +
                                  (std::pow(y1, 2) - std::pow(y2, 2)) +
                                  (std::pow(z1, 2) - std::pow(z2, 2)) -
                                  (std::pow(r1, 2) - std::pow(r2, 2))) / 2;
                        row++;
                    }
                }


                // Then calculate to solve the equations, using the least square solution
                Eigen::Vector3d pos = m.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);

                location.x = pos(0);
                location.y = pos(1);
                location.z = pos(2);

                return true;
            }


            Position3D
            trilatLocation3d(const std::vector<TrilatRecord> &records) {
                Position3D p;
                bool success = trilatLocation3d(records, p);
                if (!success)
                    throw std::runtime_error("Impossible to trilat, wrong input.");
                return p;
            }

        }
    }
}