//
// Created by Kai Zhao on 11/10/22.
//

#include <SZ3/api/sz.hpp>

#include "SZ3/compressor/specialized/SZTruncateCompressor.hpp"
#include "SZ3/encoder/ArithmeticEncoder.hpp"
#include "SZ3/encoder/BypassEncoder.hpp"
#include "SZ3/encoder/RunlengthEncoder.hpp"
#include "SZ3/lossless/Lossless_bypass.hpp"

// int main(int argc, char **argv) {
//     std::vector<size_t> dims({100, 200, 300});
//     SZ3::Config conf({dims[0], dims[1], dims[2]});
//     conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
//     conf.errorBoundMode = SZ3::EB_ABS;  // refer to def.hpp for all supported error bound mode
//     conf.absErrorBound = 1E-3;          // absolute error bound 1e-3

//     std::vector<float> input_data(conf.num);
//     std::vector<float> dec_data(conf.num);
//     std::vector<size_t> stride({dims[1] * dims[2], dims[2], 1});

//     for (size_t i = 0; i < dims[0]; ++i) {
//         for (size_t j = 0; j < dims[1]; ++j) {
//             for (size_t k = 0; k < dims[2]; ++k) {
//                 double x = static_cast<double>(i) - static_cast<double>(dims[0]) / 2.0;
//                 double y = static_cast<double>(j) - static_cast<double>(dims[1]) / 2.0;
//                 double z = static_cast<double>(k) - static_cast<double>(dims[2]) / 2.0;
//                 input_data[i * stride[0] + j * stride[1] + k] =
//                     static_cast<float>(.0001 * y * sin(y) + .0005 * cos(pow(x, 2) + x) + z);
//             }
//         }
//     }

//     std::vector<float> input_data_copy(input_data);
//     conf.openmp = true;
//     size_t cmpSize;
//     char *cmpData = SZ_compress(conf, input_data.data(), cmpSize);
//     auto dec_data_p = dec_data.data();
//     SZ_decompress(conf, cmpData, cmpSize, dec_data_p);

//     double max_err = 0.0;
//     for (size_t i = 0; i < conf.num; i++) {
//         if (fabs(dec_data[i] - input_data_copy[i]) > max_err) {
//             max_err = fabs(dec_data[i] - input_data_copy[i]);
//         }
//     }
//     printf("Smoke test %s", max_err <= conf.absErrorBound ? "passed" : "failed");
//     //    printf("%lu ", conf.num);
//     delete[] cmpData;
//     return 0;
// }
    template <typename T>
    char *compress_data(T *uncompressedData, size_t size, size_t &cmpSize)
    {
        SZ3::Config conf({size});
        conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
        conf.errorBoundMode = SZ3::EB_ABS;
        conf.absErrorBound = 1e-3;
        char *cmpData = SZ_compress(conf, uncompressedData, cmpSize);
        return cmpData;
    }
int main(int argc, char **argv) {
    size_t size=41;
    SZ3::Config conf({size});
    conf.cmprAlgo = SZ3::ALGO_INTERP_LORENZO;
    conf.errorBoundMode = SZ3::EB_ABS;  // refer to def.hpp for all supported error bound mode
    conf.absErrorBound = 1E-3;          // absolute error bound 1e-3

       std::vector<double> input_data = {
        0.322303, 0.118728, 0.172796, 0.124927, 0.16159, 0.135291, 0.0325391,
        0.15763, 0.0817775, 0.0693074, 0.0442343, 0.0211984, 0.0298839,
        0.047828, 0.0554918, 0.105536, 0.0632089, 0.0358594, 0.0338688,
        0.0443082, 0.227095, 0.146193, 0.136544, 0.0837664, 0.0358977,
        0.0829236, -0.0136721, 0.0146789, 0.0471617, 0.0634289, 0.0464465,
        0.0406016, 0.0616216, 0.117805, 0.0631437, 0.15275, 0.0628439,
        0.160152, 0.135846, 0.0539329, 0.0701087
    };
    //   for (size_t i = 0; i < conf.num; i++) {
    //     input_data[i] = static_cast<double>(i * 1000UL);
    // }
      std::cout << "Vector size: " << input_data.size() << std::endl;
    size_t cmpSize;
    // char *cmpData = SZ_compress(conf, input_data.data(), cmpSize);

    char *cmpData = compress_data<double>(input_data.data(), size, cmpSize);

    // auto dec_data_p = dec_data.data();
    // SZ_decompress(conf, cmpData, cmpSize, dec_data_p);
    std::cout << "Compressed" <<cmpSize<< std::endl;
    //    printf("%lu ", conf.num);
    delete[] cmpData;
    return 0;
}


