#include <SFML/Graphics/Image.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>


int getGrayScale(const sf::Color& pixel) {
    return (pixel.r + pixel.g + pixel.b) / 3;
}

std::string toASCII(sf::Image& image, const std::string& symbols) {
    std::string ascii = "";
    int size = symbols.size() - 1;

    for (auto y = 0u; y < image.getSize().y; ++y) {
        for (auto x = 0u; x < image.getSize().x; ++x) {
            ascii.append(1, symbols[std::floor(((float)getGrayScale(image.getPixel(x, y)))/255*size)]);
        }
        ascii.append("\n ");
    }

    return ascii;
}

int main(int argc, char* argv[])
{
    if(argc != 2 && argc != 3) {
        std::cout << "ERROR: wrong count of arguments (Correct program call: './program file.jpeg')" << std::endl;
        return 0;
    }
    if(argc == 3 && std::string(argv[2]) != "-simple") {
        std::cout << "ERROR: wrong arguments (Correct program call: './program file.jpeg -simple')" << std::endl;
        return 0;
    }

    std::string fileName = argv[1];
    std::string version = argc == 3 ? "@%#*+=-:. " : "$@B8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/|()1{}[]?-_+~<>i!lI;:,^`'. ";

    std::string output;
    sf::Image inputImage;

    if (!inputImage.loadFromFile(fileName)) {
        return 0;
    }
    
    output = toASCII(inputImage, version);
    std::ofstream file(fileName.substr(0, fileName.find('.')) + ".txt");
    file << output;
    file.close();

    std::cout << output;
}