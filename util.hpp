#ifndef __UTIL_SUGAR__
#define __UTIL_SUGAR__

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

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

    static std::vector<std::string> ReadAllLinesFromFile(const std::string &fn) {
        std::vector<std::string> result;
        std::ifstream ifs(fn);
        if (!ifs) {
            throw std::runtime_error("Cannot open file!");
        }
        std::string tmp;
        while (ifs) {
            std::getline(ifs, tmp);
            result.push_back(tmp);
        }
        result.erase(result.end() - 1);    // a weird behavior of c++
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

    // Replace the `from` within `str` to `to`. 
    // Return true if found, otherwise false.
	static bool Replace(std::string& str, const std::string& from, const std::string& to) 
	{
		size_t start_pos = str.find(from);
		if(start_pos == std::string::npos)
			return false;
		str.replace(start_pos, from.length(), to);
		return true;
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
