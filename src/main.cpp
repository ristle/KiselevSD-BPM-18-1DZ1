#include <bits/stdc++.h>
#include <opencv2/opencv.hpp>

#define powSt 2.2
#define length 768
#define height 60

namespace dz1 {
    /**
     * @brief Попиксельное гамма-преобразование
     * @param source Source image
     * @return Output corrected image
     */
    inline cv::Mat firstMethod(const cv::Mat& source);

    /**
     * @brief Матричная гамма-преобразование
     * @param source Source image
     * @return Output corrected image
     */
    inline cv::Mat secondMethod(const cv::Mat& source);
}

int main() {
    /// init all needed variables
    int count = 10;
    int grayScale = -1;
    double matrixTime = 0;
    cv::Mat firstMethodImage;
    double eachPixelTime = 0;
    cv::Mat secondMethodImage;
    /// init source image with one input channel
    cv::Mat sourceImage(cv::Mat::zeros(height, length, CV_8UC1));

    for (int i = 0; i < length; i++) {
        grayScale = i % 3 == 0 ? grayScale + 1 : grayScale;

        cv::Point start(i, 0);
        cv::Point finish(i, height - 1);

        cv::line(sourceImage, start, finish, cv::Scalar(grayScale), 1, 8);
    }

    for (int i = 0; i < count; i++) {
        long long timeStartFirstMethod = cv::getTickCount();

        firstMethodImage = dz1::firstMethod(sourceImage);

        long long timeEndFirstMethod = cv::getTickCount() - timeStartFirstMethod;
        secondMethodImage = dz1::secondMethod(sourceImage);

        long long timeEndSecondMethod = cv::getTickCount() - timeStartFirstMethod - timeEndFirstMethod;

        matrixTime += double(timeEndFirstMethod) / (cv::getTickFrequency() * 1000);
        eachPixelTime += double(timeEndSecondMethod) / (cv::getTickFrequency() * 1000);
    }

    std::cout << "Matrix pow: " << matrixTime / count << std::endl;
    std::cout << "Each pixel pow: " << eachPixelTime / count << std::endl;

    cv::Mat finalImage(cv::Mat::zeros(height * 3, length, CV_8UC1));

    sourceImage.copyTo(finalImage(cv::Rect(0, height * 0, length, height)));
    firstMethodImage.copyTo(finalImage(cv::Rect(0, height * 1, length, height)));
    secondMethodImage.copyTo(finalImage(cv::Rect(0, height * 2, length, height)));

    cv::imshow("final", finalImage);
    cv::imwrite("lab01.png", finalImage);
    cv::waitKey(0);

    return 0;
}


//попиксельное гамма-преобразование
inline cv::Mat dz1::firstMethod(const cv::Mat& source) {
    cv::Mat image;
    source.convertTo(image, CV_32F);
    image /= 255.0;

    for (int i = 0; i < image.rows; i++) {
        for (int j = 0; j < image.cols; j++) {
            image.at<float>(i, j) = powf(image.at<float>(i, j), powSt);
        }
    }

    cv::Mat output;

    image *= 255.0;
    image.convertTo(output, CV_8UC1);

    return output;
}

//матричное гамма-преобразование
inline cv::Mat dz1::secondMethod(const cv::Mat& source) {
    cv::Mat image;
    cv::Mat edSource;

    source.convertTo(edSource, CV_32F);
    edSource /= 255.0;

    pow(edSource, powSt, image);

    cv::Mat output;

    image *= 255.0;
    image.convertTo(output, CV_8UC1);

    return output;
}