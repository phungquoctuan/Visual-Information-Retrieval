#include <opencv2/opencv.hpp>

using namespace cv;

int main() {
    // Mở tệp video hoặc camera
    VideoCapture cap("2024-05-28 18-47-25.mp4"); // Thay đổi thành 0 nếu muốn sử dụng camera

    // Kiểm tra nếu video được mở thành công
    if (!cap.isOpened()) {
        std::cerr << "Không thể mở tệp video hoặc kết nối với camera!" << std::endl;
        return -1;
    }

    Mat frame;

    // Vòng lặp để đọc từng khung hình
    while (true) {
        // Đọc một khung hình từ video
        cap >> frame;

        // Kiểm tra xem có còn khung hình nào không
        if (frame.empty()) {
            std::cerr << "Không thể đọc khung hình từ video!" << std::endl;
            break;
        }

        // Tính toán histogram của khung hình
        Mat hist;
        int channels[] = {0, 1, 2}; // Tính histogram cho tất cả các kênh màu
        int histSize[] = {256, 256, 256}; // Kích thước của histogram
        float range[] = {0, 256}; // Phạm vi của giá trị pixel
        const float* ranges[] = {range, range, range};
        calcHist(&frame, 1, channels, Mat(), hist, 3, histSize, ranges, true, false);

        // Vẽ histogram
        int hist_w = 512, hist_h = 400;
        int bin_w = cvRound((double) hist_w / 256);
        Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

        // Chuẩn hóa histogram để nó vẽ trong phạm vi của hình
        normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

        // Vẽ histogram cho mỗi kênh màu
        for (int i = 1; i < 256; i++) {
            line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
                 Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
                 Scalar(255, 255, 255), 2, 8, 0);
        }

        // Hiển thị khung hình và histogram
        imshow("Khung hình", frame);
        imshow("Histogram", histImage);

        // Thoát nếu nhấn phím 'q'
        if (waitKey(30) == 'q') {
            break;
        }
    }

    // Giải phóng bộ nhớ và đóng video
    cap.release();
    destroyAllWindows();

    return 0;
}
