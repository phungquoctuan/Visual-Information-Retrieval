#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>

using namespace cv;
using namespace std;

void calcAndDisplayHistogram(Mat& frame) {
	// Chuyển đổi khung hình sang ảnh xám
	Mat gray;
	cvtColor(frame, gray, COLOR_BGR2GRAY);

	// Thiết lập các tham số cho histogram
	int histSize = 256;
	float range[] = { 0, 256 };
	const float* histRange = { range };
	bool uniform = true, accumulate = false;

	// Tính toán histogram
	Mat hist;
	calcHist(&gray, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

	// Vẽ histogram
	int hist_w = 512; int hist_h = 400;
	int bin_w = cvRound((double)hist_w / histSize);
	Mat histImage(hist_h, hist_w, CV_8UC1, Scalar(0, 0, 0));

	// Chuẩn hóa histogram để khớp với chiều cao của ảnh histogram
	normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	for (int i = 1; i < histSize; i++) {
		line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
			Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
			Scalar(255, 255, 255), 2, 8, 0);
	}

	// Hiển thị histogram
	imshow("Histogram", histImage);
}

int main(int argc, char** argv) {
	// Kiểm tra đối số đầu vào
	if (argc < 3) {
		cerr << "Usage: " << argv[0] << " <video_path> <speed_factor>" << endl;
		return -1;
	}

	// Mở video từ file
	VideoCapture cap(argv[1]);
	if (!cap.isOpened()) {
		cerr << "Error opening video stream or file" << endl;
		return -1;
	}

	// Lấy tốc độ phát từ tham số đầu vào, min = 0.1, max = infinity
	double speedFactor = atof(argv[2]);

	while (true) {
		Mat frame;
		cap >> frame; // Đọc từng khung hình

		if (frame.empty()) {
			break; // Dừng khi không còn khung hình nào
		}

		// Hiển thị khung hình
		imshow("Frame", frame);

		// Tính toán và hiển thị histogram
		calcAndDisplayHistogram(frame);

		// Thoát khi nhấn phím 'q'
		if (waitKey(30 / speedFactor) >= 0 && (char)waitKey(30 / speedFactor) == 'q') {
			break;
		}
	}

	// Giải phóng video capture
	cap.release();
	destroyAllWindows();

	return 0;
}
