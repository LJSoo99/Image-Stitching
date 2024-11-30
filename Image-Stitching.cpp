#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main() {

    Mat left = imread("C:/Users/jisuu/OneDrive/바탕 화면/left.jpg");
    Mat right = imread("C:/Users/jisuu/OneDrive/바탕 화면/right.jpg");

    Ptr<FeatureDetector> detector = FastFeatureDetector::create();
    Ptr<DescriptorExtractor> extractor = ORB::create();

    vector<KeyPoint> keypoint1, keypoint2;
    Mat descriptors1, descriptors2;

    detector->detect(left, keypoint1);
    detector->detect(right, keypoint2);

    extractor->compute(left, keypoint1, descriptors1);
    extractor->compute(right, keypoint2, descriptors2);

    BFMatcher matcher(NORM_HAMMING);
    vector<DMatch> matches;
    matcher.match(descriptors1, descriptors2, matches);

    vector<Point2f> p1, p2;
    for (size_t i = 0; i < matches.size(); i++) {
        p1.push_back(keypoint1[matches[i].queryIdx].pt);
        p2.push_back(keypoint2[matches[i].trainIdx].pt);
    }

    Mat midresult;
    drawMatches(left, keypoint1, right, keypoint2, matches, midresult);
    imshow("중간결과", midresult);
    waitKey(0);

    Mat H = findHomography(p2, p1, RANSAC);

    Mat warpresult;
    warpPerspective(right, warpresult, H, Size(left.cols * 2, left.rows));

    Mat finalresult = warpresult.clone();
    left.copyTo(finalresult(Rect(0, 0, left.cols, left.rows)));

    imshow("최종결과", finalresult);
    waitKey(0);

    return 0;
}