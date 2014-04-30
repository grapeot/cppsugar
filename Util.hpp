#ifndef __CPP_SUGAR__
#define __CPP_SUGAR__

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <functional>
#include <algorithm>
#include <numeric>
#include <set>

// some syntax sugar for easier functional programming in C++ 11
namespace func {
    // Similar to python's range
    static std::vector<int> Range(int start, int step, int end) {
        std::vector<int> result;
        result.reserve((end - start) / step + 1);
        for (int i = start; i < end; i += step) {
            result.push_back(i);
        }
        return result;
    }

    static std::vector<int> Range(int start, int end) {
        std::vector<int> result(end - start);
        std::iota(result.begin(), result.end(), start);
        return result;
    }

    static std::vector<int> Range(int end) {
        return Range(0, end);
    }

    template<typename TIn, typename TOut>
        static std::vector<TOut> Map(const std::vector<TIn> &in, std::function<TOut(TIn)> f) {
            std::vector<TOut> result(in.size());
            std::transform(in.begin(), in.end(), result.begin(), f);
            return result;
        }

    template<typename TIn, typename TOut>
        static TOut Reduce(const std::vector<TIn> &in, std::function<TOut(TIn, TIn)> f) {
            TIn init = in[0];
            for (int i = 1; i < in.size(); i++) {
                init = f(init, in[i]);
            }
            return init;
        }

    template<typename T>
        static bool Any(const std::vector<T> &in, std::function<bool(const T &)> f) {
            for (auto i : in) {
                if (f(i)) {
                    return true;
                }
            }
            return false;
        }

    template<typename TIn>
        static TIn Sum(const std::vector<TIn> &in) {
            return Reduce<TIn, TIn>(in, [](const TIn &a, const TIn &b) { return a + b; });
        }

    template<typename TIn>
        static TIn Average(const std::vector<TIn> &in) {
            return Sum(in) / in.size();
        }

    template<typename TIn>
        static TIn Min(const std::vector<TIn> &in) {
            return Reduce<TIn, TIn>(in, [](const TIn &a, const TIn &b) { return a < b ? a : b; });
        }

    template<typename TIn>
        static TIn Max(const std::vector<TIn> &in) {
            return Reduce<TIn, TIn>(in, [](const TIn &a, const TIn &b) { return a > b ? a : b; });
        }

    template<typename TIn, typename TOut>
        static TOut Min(const std::vector<TIn> &in, const std::function<TOut(TIn)> f) {
            return Min(Map(in, f));
        }

    template<typename TIn, typename TOut>
        static TOut Max(const std::vector<TIn> &in, const std::function<TOut(TIn)> f) {
            return Max(Map(in, f));
        }

    template<typename TIn, typename TOut>
        static std::vector<TOut> Zip(const std::vector<TIn> &in1, const std::vector<TIn> &in2, std::function<TOut(TIn, TIn)> f) {
            if (in1.size() != in2.size()) {
                throw std::runtime_error("Inconsistent size.");
            }
            std::vector<TOut> result(in1.size());
            for (size_t i = 0; i < in1.size(); i++) {
                result[i] = f(in1[i], in2[i]);
            }
            return result;
        }

    template<typename T>
        static std::vector<T> Unique(const std::vector<T> &in) {
            std::set<T> s(in.begin(), in.end());
            return std::vector<T>(s.begin(), s.end());
        }

    template<typename T>
        static std::vector<T> Filter(const std::vector<T> &in, const std::function<bool(T)> f) {
            std::vector<T> result;
            result.reserve(in.size());
            for (auto i : in) {
                if (f(i)) {
                    result.push_back(i);
                }
            }
            return result;
        }

    template<typename T>
        static size_t Count(const std::vector<T> &in, const std::function<bool(T)> f) {
            size_t count;
            for (auto i : in) {
                if (f(i)) {
                    count++;
                }
            }
            return count;
        }
};

// the class to provide some utility functions.
// some global configurations are also put in this file.
namespace util {
    template<typename T>
        static std::vector<T> ReadAllBytesFromFile(const std::string &fn, size_t size) {
            std::vector<T> result(size);
            std::ifstream ifs(fn, std::ios::binary);
            if (!ifs) {
                throw std::runtime_error("Cannot open file!");
            }
            ifs.read((char *)&result[0], sizeof(T)* size);
            ifs.close();
            return result;
        }

    template<typename T1>
        static std::string Print(T1 a) {
            std::stringstream ss;
            ss << a;
            return ss.str();
        }

    template<typename T1, typename T2>
        static std::string Print(T1 a, T2 b) {
            std::stringstream ss;
            ss << a << b;
            return ss.str();
        }

    template<typename T1, typename T2, typename T3>
        static std::string Print(T1 a, T2 b, T3 c) {
            std::stringstream ss;
            ss << a << b << c;
            return ss.str();
        }

    template<typename T1, typename T2, typename T3, typename T4>
        static std::string Print(T1 a, T2 b, T3 c, T4 d) {
            std::stringstream ss;
            ss << a << b << c << d;
            return ss.str();
        }

    template<typename T1, typename T2, typename T3, typename T4, typename T5>
        static std::string Print(T1 a, T2 b, T3 c, T4 d, T5 e) {
            std::stringstream ss;
            ss << a << b << c << d << e;
            return ss.str();
        }

    template<typename T>
        static void WriteAllBytesToFile(const std::string &fn, const std::vector<T> &vec) {
            std::ofstream ofs(fn, std::ios::binary);
            if (!ofs) {
                throw std::runtime_error("Cannot open file.");
            }
            ofs.write((char *)&vec[0], sizeof(T)* vec.size());
            ofs.close();
        }

    static void WriteStringToFile(const std::string &fn, const std::string &content) {
        std::ofstream ofs(fn);
        if (!ofs) {
            throw std::runtime_error("Cannot open file.");
        }
        ofs << content << std::endl;
        ofs.close();
    }

    static void WriteAllLinesToFile(const std::string &fn, const std::vector<std::string> &lines) {
        std::ofstream ofs(fn);
        if (!ofs) {
            throw std::runtime_error("Cannot open file.");
        }
        for (auto line : lines) {
            ofs << line << std::endl;
        }
        ofs.close();
    }

    template<typename T>
        static void VisualizeMatrix(const std::vector<T> &mat, int height, int width,
                const std::string &imgfn = "",
                const std::string &dtype = "float32",
                const std::string &fn = std::string("tmp.dat")) {
            if (mat.size() != height * width) {
                throw std::runtime_error("Inconsistent size.");
            }
            WriteAllBytesToFile(fn, mat);

            std::stringstream ss;
            ss << "python -c \"import numpy; import pylab; a = numpy.fromfile('"
                << fn << "', dtype='" << dtype << "');"
                << "pylab.imshow(numpy.reshape(a, ("
                << height << ", " << width << ")));"
                << "pylab.colorbar();";
            if (imgfn.empty()) {
                ss << " pylab.show(); \"";
            }
            else {
                ss << " pylab.savefig('" << imgfn << "');";
            }
            system(ss.str().c_str());
        }

    struct RGB { unsigned char r, g, b; };
    static RGB JetColor(float val, float scale) {
        if (val > scale) {
            val = scale;
        }
        int yellowCount = (int)(scale * 0.6 + 0.5);
        int yellowLength = scale - yellowCount;
        int greenCount = yellowCount / 2;
        int greenLength = yellowCount - greenCount;
        int whiteLength = greenCount;
        if (val >= yellowCount) {
            unsigned char green = (int)(0xff - (val - yellowCount) * 0xff / yellowLength);
            return RGB{ 0xff, green, 0 };
        }
        else if (val >= greenCount) {
            unsigned char red = (unsigned char)((val - greenCount) * 0xff / greenLength);
            return RGB{ red, 0xff, 0 };
        }
        else {
            unsigned char red = (unsigned char)(0xff - (val)* 0xff / whiteLength);
            return RGB{ red, 0xff, red };
        }
    }
};

#endif
