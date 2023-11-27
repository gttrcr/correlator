// #pragma once

// #include "../function.h"
// #include "../arguments.h"

// #include <vector>
// #include <iostream>
// #include <algorithm>
// #include <execution>
// #include <algorithm>
// #ifdef THREAD_SUPPORT
// #include <mutex>
// #endif

// namespace analysis
// {
//     class pattern_matching
//     {
//     private:
//         struct data
//         {
//         public:
//             unsigned int degree;
//             FDST r2;
//             SOURCE source1;
//             codomain coeff;
//         };

//         arguments _args;
//         unsigned int _perc;
//         std::vector<data> _data;
// #ifdef THREAD_SUPPORT
//         std::mutex _mtx;
// #endif

//         static void _polyfit(const domain &x, const codomain &y, codomain &coeff, const unsigned int &degree)
//         {
//             Eigen::MatrixXd T(x.size(), degree + 1);
//             Eigen::VectorXd V = Eigen::VectorXd::Map(&y.front(), y.size());
//             Eigen::VectorXd result;

//             assert(x.size() == y.size());
//             assert(x.size() >= degree + 1);

//             for (size_t i = 0; i < x.size(); ++i)
//                 for (size_t j = 0; j < degree + 1; ++j)
//                     T(i, j) = pow(x[i], j);

//             result = T.householderQr().solve(V);
//             coeff.resize(degree + 1);
//             for (unsigned int k = 0; k < degree + 1; k++)
//                 coeff[k] = result[k];
//         }

//         void _execution(const unsigned int &w, const unsigned int &max_window, const unsigned int &min_window, const unsigned int &big_size, const corr_function &small, const corr_function &big, const unsigned int &parallelizzable_tasks, const SOURCE &source1)
//         {
//             std::vector<data> tmp_data;
//             const unsigned int big_step = 38;
//             for (unsigned int ws = w; ws < max_window; ws += big_step)
//                 for (int i = max_window - 1; i >= (int)(ws + min_window - 1); i -= big_step)
//                 {
//                     const unsigned int width = i - ws + 1;
//                     for (unsigned int j = 0; j <= big_size - width; j++)
//                         tmp_data.push_back(_ranges(small, big, ws, i, j, j + width - 1, source1));
//                 }

// #ifdef THREAD_SUPPORT
//             _mtx.lock();
// #endif
//             _data.insert(_data.end(), tmp_data.begin(), tmp_data.end());
//             std::cout << "\t\t" << 100.0 * (double)(_perc++) / (double)parallelizzable_tasks << std::endl;
// #ifdef THREAD_SUPPORT
//             _mtx.unlock();
// #endif
//         }

//         data _ranges(const corr_function &small, const corr_function &big, const unsigned int &small_from, const unsigned int &small_to, const unsigned int &big_from, const unsigned int &big_to, const SOURCE &source1)
//         {
//             corr_function s = small.range(small_from, small_to);
//             corr_function b = big.range(big_from, big_to);
//             corr_function f = s - b;
//             domain x = f.get_domain();
//             codomain y = f.get_codomain();
//             codomain c;
//             _polyfit(x, y, c, 2);
//             FDST r2 = statistics::get_r2(x, y, c);
//             return {2, r2, source1, c};

//             //  std::cout << "small [" << small_from << "," << small_to << "] big [" << big_from << "," << big_to << "]" << std::endl;
//         }

//         void _pattern_matching(const corr_function &f1, const corr_function &f2, const SOURCE &source1)
//         {
//             const unsigned int max_window = std::min(f1.size(), f2.size());
//             const corr_function small(f1.size() == max_window ? f1 : f2);
//             const corr_function big(f1.size() == max_window ? f2 : f1);
//             const unsigned int big_size = big.size();
//             const unsigned int min_window = 5;
//             const unsigned int window_step = 100;

//             std::vector<unsigned int> parallelizable_w;
//             for (unsigned int i = 0; i < max_window; i += window_step)
//                 parallelizable_w.push_back(i);

//             _perc = 0;
// #ifdef THREAD_SUPPORT
//             std::for_each(std::execution::par_unseq, parallelizable_w.begin(), parallelizable_w.end(), [&](unsigned int w)
//                           {
// #else
//             for (unsigned int w : parallelizable_w)
// #endif
//                               _execution(w, max_window, min_window, big_size, small, big, parallelizable_w.size(), source1);
// #ifdef THREAD_SUPPORT
//                           });
// #endif
//         }

//     public:
//         pattern_matching(const arguments &args)
//         {
//             _args = args;
//         }

//         void compute(const corr_function &f, const SOURCE &source1)
//         {
//             _pattern_matching(f, f, source1);
//         }

//         void save()
//         {
//         }
//     };
// }