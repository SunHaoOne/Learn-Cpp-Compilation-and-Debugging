#include <iostream>
#include <cmath>
#include <vector>

class Velocity
{
public:
    static Velocity *create(double vx, double vy, double lane_heading)
    {
        if (lane_heading == -999)
            return nullptr;
        else
            return new Velocity(vx, vy, lane_heading);
    }

    std::pair<double, double> decompose_velocity()
    {
        // 计算道路方向向量和垂直方向向量
        double lx = cos(this->lane_heading);
        double ly = sin(this->lane_heading);

        // 计算沿着道路方向的速度
        double speed_along_lane = this->vx * lx + this->vy * ly;

        // 计算垂直道路方向的速度
        double speed_perpendicular_to_lane = this->vx * (-ly) + this->vy * lx;

        return std::make_pair(speed_along_lane, speed_perpendicular_to_lane);
    }

    void print_decomposed_velocity()
    {
        auto speeds = decompose_velocity();
        std::cout << "vl = " << speeds.first << ", vs = " << speeds.second << std::endl;
    }

private:
    Velocity(double vx, double vy, double lane_heading)
    {
        this->vx = vx;
        this->vy = vy;
        this->lane_heading = lane_heading;
    }
    double vx;
    double vy;
    double lane_heading;
};

int main()
{

    auto *ptr1 = Velocity::create(10, 10, M_PI / 4.0);
    auto *ptr2 = Velocity::create(10, 10, -999); // 可能由于没有获取到lane_id信息,lane_heading=-999

    ptr1->print_decomposed_velocity();
    ptr2->print_decomposed_velocity(); // ptr2指针为空，报错

    delete ptr1;
    delete ptr2;
    return 0;
}