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
        -0.000557246, -1.91871e-05, 3.64865e-05, -0.000174678, -4.16519e-05,
        2.09643e-06, 3.49307e-06, -1.05011e-05, -0.000472014, -3.93203e-06,
        0.000152117, 0.00016113, -2.02534e-05, -0.000228394, 0.000168178,
        -1.04183e-05, 9.51545e-05, 0.000136021, 6.12364e-05, 0.00123887,
        -1.95963e-05, -1.86062e-05, -2.23122e-05, -0.00133366, -2.67941e-05,
        -6.13811e-05, 0.0020968, -0.00257579, 0.000133028, 0.000125964,
        7.11653e-05, 3.86562e-05, 0.00271601, -2.6028e-05, 0.000115805,
        -3.44433e-05, -6.6229e-05, -3.97414e-05, -6.85452e-05, -5.14098e-05,
        // -3.44433e-05, -6.6229e-05, -3.97414e-05, -6.85452e-05, -5.14098e-05,
        // -3.44433e-05, -6.6229e-05, -3.97414e-05, -6.85452e-05, -5.14098e-05,
        0.00628354
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
    ////////////////
        auto zstd = Lossless_zstd();
    ///////////////
    delete[] cmpData;
    return 0;
}


