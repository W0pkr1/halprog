#include <iostream>
#include"poli.hh"

int main() {
    std::vector<double> init = {1.,2.};
    std::vector<double> init_2 = {1.,2.,3.};

    polinom<double> my_poli(init_2);
    polinom<double> kettes(init);

    auto addition_result = my_poli + kettes;
    auto subtraction_esult = my_poli - kettes;

    auto multiplication_result = my_poli * kettes;

    auto derivate_result = derrivate_more(my_poli,2);


    integrate(my_poli,2.,5.);


}
