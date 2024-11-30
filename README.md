# OpenCV를 활용한 파노라마 이미지 스티칭

이 프로젝트는 OpenCV를 사용하여 두 이미지를 정렬하고 합쳐서 파노라마 이미지를 생성하는 예제를 제공합니다. 특징점 검출, 매칭, 호모그래피 변환을 활용하여 이미지를 정렬하고 병합합니다.

## 주요 기능

- **특징점 검출**: `FAST` 검출기를 사용하여 이미지에서 특징점을 검출합니다.
- **기술자 추출**: `ORB`를 사용하여 기술자를 생성합니다.
- **특징점 매칭**: Brute Force (BF) 매칭 알고리즘으로 두 이미지 간의 특징점을 매칭합니다.
- **호모그래피 변환**: RANSAC을 이용해 계산한 호모그래피 행렬을 기반으로 이미지를 정렬합니다.
- **이미지 병합**: 정렬된 이미지를 하나의 파노라마 이미지로 합칩니다.

## 프로젝트 구조

- **`ConsoleApplication1.cpp`**: 파노라마 스티칭을 구현한 메인 소스 코드.
- **입력 이미지**:
  - `left.jpg`: 왼쪽 이미지.
  - `right.jpg`: 오른쪽 이미지.
- **출력 결과**:
  - OpenCV의 `imshow()`로 중간 결과와 최종 결과를 확인할 수 있습니다.

## 시작하기

### 필수 조건
1. OpenCV 라이브러리를 설치합니다. 예를 들어:
   ```bash
   sudo apt-get install libopencv-dev
   ```
2. OpenCV를 지원하는 C++ 컴파일러 또는 Visual Studio와 같은 IDE가 필요합니다.

### 설치
1. 이 저장소를 클론합니다:
   ```bash
   git clone https://github.com/your-username/panorama-stitching.git
   ```
2. 프로젝트 디렉토리로 이동합니다:
   ```bash
   cd panorama-stitching
   ```
3. 입력 이미지(`left.jpg`와 `right.jpg`)를 코드에서 지정된 경로에 배치합니다.

## 실행 방법

1. 코드를 컴파일합니다:
   ```bash
   g++ ConsoleApplication1.cpp -o panorama -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_features2d -lopencv_calib3d
   ```
2. 실행 파일을 실행합니다:
   ```bash
   ./panorama
   ```

## 결과

### 중간 결과: 특징점 매칭
두 이미지 간의 매칭된 특징점을 보여줍니다.

### 최종 결과: 파노라마
병합된 파노라마 이미지를 보여줍니다.
![output](https://github.com/user-attachments/assets/817e9a2b-a700-4050-b51d-089f0b8302df)

## 코드 개요

### 주요 단계
1. **특징점 검출**:
   ```cpp
   Ptr<FeatureDetector> detector = FastFeatureDetector::create();
   detector->detect(left, keypoint1);
   ```
2. **기술자 추출**:
   ```cpp
   Ptr<DescriptorExtractor> extractor = ORB::create();
   extractor->compute(left, keypoint1, descriptors1);
   ```
3. **특징점 매칭**:
   ```cpp
   BFMatcher matcher(NORM_HAMMING);
   matcher.match(descriptors1, descriptors2, matches);
   ```
4. **호모그래피 계산**:
   ```cpp
   Mat H = findHomography(p2, p1, RANSAC);
   ```
5. **이미지 병합**:
   ```cpp
   warpPerspective(right, warpresult, H, Size(left.cols * 2, left.rows));
   ```

## 개선 방향

- **좋은 매칭 필터링**: Lowe’s ratio test를 추가하여 잘못된 매칭을 줄입니다.
- **부드러운 이미지 합성**: Seamless Cloning을 활용하여 더 자연스러운 결과를 얻습니다.
- **확장성**: 여러 이미지를 처리할 수 있도록 코드를 확장합니다.

## 의존성

- OpenCV 4.x 이상
- C++ 컴파일러 (예: g++, MSVC)

## 기여 방법

기여, 이슈 제기, 기능 요청은 언제든 환영합니다!


## 라이선스

이 프로젝트는 MIT 라이선스 하에 제공됩니다.

## 참고 자료

- [OpenCV 공식 문서](https://docs.opencv.org/)
- [ORB를 활용한 특징점 매칭](https://docs.opencv.org/master/dc/dc3/tutorial_py_matcher.html)
